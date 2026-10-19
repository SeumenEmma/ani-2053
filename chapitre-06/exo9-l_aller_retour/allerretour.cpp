#include <NKNetwork/Protocol/NkConnection.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

using namespace nkentseu;
using namespace nkentseu::net;

namespace
{
    constexpr uint16 PORT = 5000;
    constexpr int NOMBRE_MESURES = 100;
    constexpr double ALPHA = 0.125;
    constexpr double RTT_INITIAL = 100.0;

    using Horloge = std::chrono::steady_clock;

    void attendre(int millisecondes = 2)
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(millisecondes)
        );
    }

    int lancerServeur()
    {
        NkConnectionManager manager;

        if (manager.StartServer(PORT) != NkNetResult::NK_NET_OK)
        {
            std::cerr << "Impossible de demarrer le serveur.\n";
            return 1;
        }

        std::cout << "Serveur demarre sur le port "
                  << PORT << ".\n";
        std::cout << "En attente des messages du client...\n";

        while (true)
        {
            NkVector<NkReceiveMsg> messages;
            manager.DrainAll(messages);

            for (const auto& msg : messages)
            {
                // Le serveur renvoie exactement le message reçu.
                const auto resultat = manager.SendTo(
                    msg.from,
                    msg.data,
                    msg.size,
                    msg.channel
                );

                if (resultat != NkNetResult::NK_NET_OK)
                {
                    std::cerr
                        << "Erreur lors du renvoi du message.\n";
                }
            }

            attendre();
        }

        return 0;
    }

    int lancerClient()
    {
        NkConnectionManager manager;

        const NkAddress adresse = NkAddress::Loopback(PORT);

        if (!adresse.IsValid())
        {
            std::cerr << "Adresse du serveur invalide.\n";
            return 1;
        }

        std::cout << "Adresse valide : "
                  << adresse.IsValid() << '\n';
        std::cout << "Adresse loopback : "
                  << adresse.IsLoopback() << '\n';
        std::cout << "Port : " << adresse.Port() << '\n';

        if (manager.Connect(adresse) != NkNetResult::NK_NET_OK)
        {
            std::cerr << "Impossible de se connecter au serveur.\n";
            return 1;
        }

        std::cout << "Connexion initiee. Preparation des mesures...\n";

        // Laisser le temps à la connexion de s'établir.
        attendre(1000);

        std::vector<double> mesures;
        mesures.reserve(NOMBRE_MESURES);

        double rttLisse = RTT_INITIAL;
        double rttMoteur = 0.0;

        for (int i = 1; i <= NOMBRE_MESURES; ++i)
        {
            const std::string message =
                "RTT_" + std::to_string(i);

            const auto debut = Horloge::now();

            const auto resultatEnvoi = manager.SendTo(
                NkPeerId::Server(),
                reinterpret_cast<const uint8*>(message.data()),
                static_cast<uint32>(message.size())
            );

            if (resultatEnvoi != NkNetResult::NK_NET_OK)
            {
                std::cerr << "Echec de l'envoi numero "
                          << i << ".\n";
                return 1;
            }

            bool echoRecu = false;

            // Attendre la réponse correspondante avant la mesure suivante.
            const auto limite = Horloge::now()
                              + std::chrono::seconds(5);

            while (Horloge::now() < limite && !echoRecu)
            {
                NkVector<NkReceiveMsg> messages;
                manager.DrainAll(messages);

                for (const auto& msg : messages)
                {
                    const std::string reponse(
                        reinterpret_cast<const char*>(msg.data),
                        msg.size
                    );

                    if (reponse == message)
                    {
                        const auto fin = Horloge::now();

                        const double rtt =
                            std::chrono::duration<double,
                                std::milli>(fin - debut).count();

                        mesures.push_back(rtt);

                        // Formule de lissage exponentiel (SRTT).
                        rttLisse =
                            ALPHA * rtt
                            + (1.0 - ALPHA) * rttLisse;

                        echoRecu = true;

                        std::cout << "Mesure "
                                  << i << "/"
                                  << NOMBRE_MESURES
                                  << " : "
                                  << std::fixed
                                  << std::setprecision(3)
                                  << rtt << " ms\n";

                        break;
                    }
                }

                if (!echoRecu)
                {
                    attendre();
                }
            }

            if (!echoRecu)
            {
                std::cerr
                    << "Delai depasse pour la mesure "
                    << i << ". Verifie que le serveur fonctionne.\n";
                return 1;
            }
        }

        // Enregistrer les 100 mesures brutes.
        std::ofstream fichierMesures("mesures-rtt.txt");

        if (!fichierMesures)
        {
            std::cerr
                << "Impossible de creer mesures-rtt.txt.\n";
            return 1;
        }

        fichierMesures << std::fixed << std::setprecision(3);

        for (double valeur : mesures)
        {
            fichierMesures << valeur << '\n';
        }

        fichierMesures.close();

        // Calcul des statistiques.
        const double moyenne =
            std::accumulate(mesures.begin(), mesures.end(), 0.0)
            / mesures.size();

        const auto bornes =
            std::minmax_element(mesures.begin(), mesures.end());

        const double minimum = *bornes.first;
        const double maximum = *bornes.second;

        // RTT obtenu auprès du moteur NKNetwork.
        NkConnectionStats stats{};

        if (manager.GetConnectionStats(NkPeerId::Server(), stats))
        {
            rttMoteur = stats.rttMs;
        }

        // Écart-type de la série de mesures.
        double sommeCarres = 0.0;

        for (double valeur : mesures)
        {
            const double difference = valeur - moyenne;
            sommeCarres += difference * difference;
        }

        const double ecart =
            std::sqrt(sommeCarres / mesures.size());

        // Écrire le rapport final.
        std::ofstream fichierRapport("rtt.txt");

        if (!fichierRapport)
        {
            std::cerr << "Impossible de creer rtt.txt.\n";
            return 1;
        }

        fichierRapport << std::fixed << std::setprecision(3);
        fichierRapport << "Moyenne : " << moyenne << " ms\n";
        fichierRapport << "Minimum : " << minimum << " ms\n";
        fichierRapport << "Maximum : " << maximum << " ms\n";
        fichierRapport << "Lissée : " << rttLisse << " ms\n";
        fichierRapport << "Moteur : " << rttMoteur << " ms\n";
        fichierRapport << "Écart : " << ecart << " ms\n";

        fichierRapport.close();

        std::cout << "\nLes 100 mesures sont terminees.\n";
        std::cout << "Fichier cree : mesures-rtt.txt\n";
        std::cout << "Rapport cree : rtt.txt\n";

        return 0;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Utilisation :\n"
                  << "  jenga run --args serveur\n"
                  << "  jenga run --args client\n";
        return 1;
    }

    const std::string mode = argv[1];

    if (mode == "serveur")
    {
        return lancerServeur();
    }

    if (mode == "client")
    {
        return lancerClient();
    }

    std::cerr << "Argument inconnu : " << mode << '\n';
    return 1;
}