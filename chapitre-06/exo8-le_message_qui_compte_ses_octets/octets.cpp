
#include <NKNetwork/Transport/NkSocket.h>
#include <NKNetwork/Protocol/NkBitStream.h>
#include <NKNetwork/NKNetwork.h>

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace nkentseu;
using namespace nkentseu::net;

constexpr uint16 PORT = 7777;
constexpr uint32 BUFFER_SIZE = 256;

struct Player {
    bool alive = true;
    uint8 number = 42;
    float x = 123.456f;
    float y = -234.567f;
    float angle = 127.3f;
    int32 health = 83;
};

void writeComplete(Player p, NkBitWriter& writer) {
    writer.WriteU8(p.alive ? 1 : 0);
    writer.WriteU8(p.number);
    writer.WriteF32(p.x);
    writer.WriteF32(p.y);
    writer.WriteF32(p.angle);
    writer.WriteI32(p.health);
}

void writeQuantized(Player p, NkBitWriter& writer) {
    writer.WriteBool(p.alive);
    writer.WriteU8(p.number);
    writer.WriteF32Q(p.x, -500.f, 500.f, 0.01f);
    writer.WriteF32Q(p.y, -500.f, 500.f, 0.01f);
    writer.WriteF32Q(p.angle, 0.f, 360.f, 0.5f);
    writer.WriteInt(p.health, 0, 100);
}

Player readComplete(const uint8* data, uint32 size) {
    NkBitReader reader(data, size);
    Player p;

    p.alive = reader.ReadU8() != 0;
    p.number = reader.ReadU8();
    p.x = reader.ReadF32();
    p.y = reader.ReadF32();
    p.angle = reader.ReadF32();
    p.health = reader.ReadI32();

    return p;
}

Player readQuantized(const uint8* data, uint32 size) {
    NkBitReader reader(data, size);
    Player p;

    p.alive = reader.ReadBool();
    p.number = reader.ReadU8();
    p.x = reader.ReadF32Q(-500.f, 500.f, 0.01f);
    p.y = reader.ReadF32Q(-500.f, 500.f, 0.01f);
    p.angle = reader.ReadF32Q(0.f, 360.f, 0.5f);
    p.health = reader.ReadInt(0, 100);

    return p;
}

void displayPlayer(const char* title, const Player& p) {
    std::cout << "\n" << title << "\n";
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Vivant : " << (p.alive ? "oui" : "non") << "\n";
    std::cout << "Numero : " << static_cast<int>(p.number) << "\n";
    std::cout << "Position X : " << p.x << " m\n";
    std::cout << "Position Y : " << p.y << " m\n";
    std::cout << "Angle : " << p.angle << " degres\n";
    std::cout << "Sante : " << p.health << "\n";
}

int runServer() {
    if (NkSocket::PlatformInit() != NkNetResult::NK_NET_OK) {
        std::cerr << "Erreur d'initialisation reseau.\n";
        return 1;
    }

    NkSocket socket;

    if (socket.Create(NkAddress::Any(PORT),
                      NkSocket::Type::NK_UDP) != NkNetResult::NK_NET_OK) {
        std::cerr << "Impossible de creer le socket serveur.\n";
        return 1;
    }

    std::cout << "Socket serveur valide : "
              << socket.IsValid() << "\n";

    Player p;

    uint8 completeBuffer[BUFFER_SIZE]{};
    uint8 quantizedBuffer[BUFFER_SIZE]{};

    NkBitWriter completeWriter(completeBuffer, BUFFER_SIZE);
    writeComplete(p, completeWriter);

    NkBitWriter quantizedWriter(quantizedBuffer, BUFFER_SIZE);
    writeQuantized(p, quantizedWriter);

    if (completeWriter.IsOverflowed() ||
        quantizedWriter.IsOverflowed()) {
        std::cerr << "Depassement du buffer.\n";
        return 1;
    }

    std::cout << "Types complets : "
              << completeWriter.BytesWritten() << " octets, "
              << completeWriter.BitsWritten() << " bits\n";

    std::cout << "Quantifie : "
              << quantizedWriter.BytesWritten() << " octets, "
              << quantizedWriter.BitsWritten() << " bits\n";

    uint8 receiveBuffer[BUFFER_SIZE]{};
    uint32 receivedSize = 0;
    NkAddress clientAddress;

    std::cout << "Lancez le client dans un autre terminal...\n";

    while (receivedSize == 0) {
        socket.RecvFrom(receiveBuffer, BUFFER_SIZE,
                        receivedSize, clientAddress);
    }

    std::cout << "Message de demarrage recu : "
              << receivedSize << " octets\n";

    if (socket.SendTo(completeBuffer,
                      completeWriter.BytesWritten(),
                      clientAddress) != NkNetResult::NK_NET_OK) {
        std::cerr << "Erreur d'envoi du paquet complet.\n";
        return 1;
    }

    std::cout << "Paquet complet envoye.\n";

    if (socket.SendTo(quantizedBuffer,
                      quantizedWriter.BytesWritten(),
                      clientAddress) != NkNetResult::NK_NET_OK) {
        std::cerr << "Erreur d'envoi du paquet quantifie.\n";
        return 1;
    }

    std::cout << "Paquet quantifie envoye.\n";
    return 0;
}

int runClient() {
    if (NkSocket::PlatformInit() != NkNetResult::NK_NET_OK) {
        std::cerr << "Erreur d'initialisation reseau.\n";
        return 1;
    }

    NkSocket socket;

    if (socket.Create(NkAddress::Loopback(0),
                      NkSocket::Type::NK_UDP) != NkNetResult::NK_NET_OK) {
        std::cerr << "Impossible de creer le socket client.\n";
        return 1;
    }

    NkAddress serverAddress = NkAddress::Loopback(PORT);
    const char startMessage[] = "PRET";

    if (socket.SendTo(startMessage, sizeof(startMessage),
                      serverAddress) != NkNetResult::NK_NET_OK) {
        std::cerr << "Impossible de contacter le serveur.\n";
        return 1;
    }

    std::cout << "Message de demarrage envoye.\n";

    uint8 buffer[BUFFER_SIZE]{};
    uint32 receivedSize = 0;
    NkAddress from;

    while (receivedSize == 0) {
        socket.RecvFrom(buffer, BUFFER_SIZE, receivedSize, from);
    }

    Player complete = readComplete(buffer, receivedSize);
    displayPlayer("Joueur lu depuis le paquet complet", complete);

    receivedSize = 0;

    while (receivedSize == 0) {
        socket.RecvFrom(buffer, BUFFER_SIZE, receivedSize, from);
    }

    Player quantized = readQuantized(buffer, receivedSize);
    displayPlayer("Joueur lu depuis le paquet quantifie", quantized);

    Player original;

    std::cout << "\nEcarts absolus mesures :\n";
    std::cout << std::setprecision(6);
    std::cout << "Etat : "
              << (original.alive == quantized.alive ? 0 : 1) << "\n";
    std::cout << "Numero : "
              << std::abs(static_cast<int>(original.number) -
                          static_cast<int>(quantized.number)) << "\n";
    std::cout << "Position X : "
              << std::fabs(original.x - quantized.x) << " m\n";
    std::cout << "Position Y : "
              << std::fabs(original.y - quantized.y) << " m\n";
    std::cout << "Angle : "
              << std::fabs(original.angle - quantized.angle)
              << " degres\n";
    std::cout << "Sante : "
              << std::abs(original.health - quantized.health) << "\n";

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Utilisation : programme serveur | client\n";
        return 1;
    }

    if (std::strcmp(argv[1], "serveur") == 0) {
        return runServer();
    }

    if (std::strcmp(argv[1], "client") == 0) {
        return runClient();
    }

    std::cerr << "Mode inconnu. Utilisez serveur ou client.\n";
    return 1;
}