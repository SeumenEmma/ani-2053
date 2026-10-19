#include <NKThreading/NkThread.h>

#include <iostream>
#include <vector>

using nkentseu::threading::NkThread;

int compteur = 0;

int main()
{
    constexpr int NB_FILS = 8;
    constexpr int INCREMENTS = 1'000'000;

    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    for (int i = 0; i < NB_FILS; ++i)
    {
        fils.emplace_back();
        fils.back().Start([](void*)
        {
            for (int j = 0; j < INCREMENTS; ++j)
                compteur += 1;
        });
    }

    for (auto& fil : fils)
        fil.Join();

    std::cout << "Total obtenu : " << compteur << '\n';
    std::cout << "Total attendu : "
              << NB_FILS * INCREMENTS << '\n';

    return 0;
}