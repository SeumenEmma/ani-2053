#include <NKNetwork/NKNetwork.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

using namespace nkentseu;
using namespace nkentseu::net;

int main(int argc, char* argv[])
{
    NkSocket::PlatformInit();

    if (argc < 2)
    {
        std::cout << "Utilisation : programme serveur | client\n";
        return 1;
    }

    std::string role = argv[1];

    if (role == "serveur")
    {
        NkDiscovery::ServerInfo info{};
        std::strcpy(info.name, "Serveur Emma");
        info.maxPlayers = 8;
        info.addr = NkAddress("0.0.0.0", 7777);

        std::cout << "Serveur en diffusion : " << info.name << '\n';

        while (true)
        {
            auto resultat = NkDiscovery::Broadcast(info);

            if (resultat != NkNetResult::NK_NET_OK)
                std::cerr << "Erreur de diffusion.\n";

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    else if (role == "client")
    {
        NkVector<NkDiscovery::ServerInfo> serveurs;

        auto resultat = NkDiscovery::Listen(6000, serveurs);

        if (resultat != NkNetResult::NK_NET_OK)
        {
            std::cerr << "Erreur d'ecoute.\n";
            return 1;
        }

        std::cout << "Serveurs trouves : " << serveurs.size() << '\n';

        for (const auto& serveur : serveurs)
        {
            std::cout << "Adresse : " << serveur.addr.ToString().CStr()
                      << " | Valide : " << serveur.addr.IsValid()
                      << " | Port : " << serveur.addr.Port()
                      << " | Nom : " << serveur.name << '\n';
        }
    }
    else
    {
        std::cerr << "Role invalide.\n";
        return 1;
    }

    return 0;
}