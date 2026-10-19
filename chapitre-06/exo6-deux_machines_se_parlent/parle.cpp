#include <NKNetwork/NKNetwork.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <atomic>
#include <thread>

using namespace nkentseu;
using namespace nkentseu::net;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Utilisation : programme serveur | client [adresse]\n";
        return 1;
    }

    NkSocket::PlatformInit();
    NkConnectionManager manager;

    manager.onPeerConnected = [](NkPeerId peer)
    {
        std::cout << "Pair connecte : " << peer.value << '\n';
    };

    std::string role = argv[1];

    if (role == "serveur")
    {
        auto resultat = manager.StartServer(7777, 8);
        if (resultat != NkNetResult::NK_NET_OK)
        {
            std::cerr << "Erreur de demarrage du serveur.\n";
            return 1;
        }

        std::cout << "Serveur en attente sur le port 7777...\n";

        while (true)
        {
            NkVector<NkReceiveMsg> messages;
            manager.DrainAll(messages);

            for (const auto& msg : messages)
            {
                std::cout << "Message du pair " << msg.from.value << " : "
                          << std::string(
                                 reinterpret_cast<const char*>(msg.data),
                                 msg.size)
                          << '\n';
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
   else if (role == "client")
   {
       std::string adresse = (argc >= 3) ? argv[2] : "127.0.0.1";

       std::atomic<uint32> peerDistant{0};

       manager.onPeerConnected = [&peerDistant](NkPeerId peer)
       {
           std::cout << "Pair connecte : " << peer.value << '\n';
           peerDistant.store(peer.value);
       };

       auto resultat = manager.Connect(NkAddress(adresse.c_str(), 7777));

       if (resultat != NkNetResult::NK_NET_OK)
       {
           std::cerr << "Erreur de connexion au serveur.\n";
           return 1;
       }

       std::cout << "Connexion au serveur " << adresse << ":7777\n";

       bool envoye = false;

       while (true)
       {
           uint32 id = peerDistant.load();

           if (id != 0 && !envoye)
           {
               const std::string message = "Bonjour serveur !";

               auto envoi = manager.SendTo(
                   NkPeerId{id},
                   reinterpret_cast<const uint8*>(message.data()),
                   static_cast<uint32>(message.size())
               );

               if (envoi == NkNetResult::NK_NET_OK)
               {
                   std::cout << "Message envoye : " << message << '\n';
                   envoye = true;
               }
           }

           NkVector<NkReceiveMsg> messages;
           manager.DrainAll(messages);

           for (const auto& msg : messages)
           {
               std::cout << "Message recu : "
                         << std::string(
                                reinterpret_cast<const char*>(msg.data),
                                msg.size)
                         << '\n';
           }

           std::this_thread::sleep_for(std::chrono::milliseconds(10));
       }
   }
    else
    {
        std::cerr << "Role invalide : utilisez serveur ou client.\n";
        return 1;
    }

    return 0;
}