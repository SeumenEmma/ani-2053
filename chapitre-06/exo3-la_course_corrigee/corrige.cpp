#include <NKThreading/NkThread.h>
#include <NKThreading/NkMutex.h>
#include <NKCore/NkAtomic.h>
#include <NKTime/NkChrono.h>

#include <iostream>
#include <vector>
#include <algorithm>

using nkentseu::threading::NkThread;
using nkentseu::threading::NkMutex;
using nkentseu::threading::NkScopedLockMutex;
using nkentseu::NkAtomicInt;
using nkentseu::NkChrono;

constexpr int NB_FILS = 8;
constexpr int INCREMENTS = 1'000'000;

int compteur = 0;
NkMutex mutex;
NkAtomicInt compteurAtomique(0);

double mesurer(int version)
{
    compteur = 0;
    compteurAtomique.Store(0);
    std::vector<int> locaux(NB_FILS, 0);
    std::vector<NkThread> fils;
    fils.reserve(NB_FILS);

    NkChrono chrono;

    for (int i = 0; i < NB_FILS; ++i)
    {
        fils.emplace_back();
        fils.back().Start([i, version, &locaux](void*)
        {
            for (int j = 0; j < INCREMENTS; ++j)
            {
                if (version == 0)
                    compteur += 1;
                else if (version == 1)
                {
                    NkScopedLockMutex verrou(mutex);
                    compteur += 1;
                }
                else if (version == 2)
                    compteurAtomique.FetchAdd(1);
                else
                    locaux[i] += 1;
            }
        });
    }

    for (auto& fil : fils)
        fil.Join();

    double temps = chrono.Elapsed().ToMilliseconds();

    int total = version == 2 ? compteurAtomique.Load()
              : version == 3 ? 0 : compteur;

    if (version == 3)
        for (int valeur : locaux)
            total += valeur;

    std::cout << "Total : " << total
              << " | Temps : " << temps << " ms\n";

    return temps;
}

int main()
{
    const char* noms[] = {
        "Sans protection", "Mutex", "Atomique", "Local"
    };

    for (int version = 0; version < 4; ++version)
    {
        std::vector<double> temps;
        std::cout << "\n" << noms[version] << " :\n";

        for (int essai = 0; essai < 3; ++essai)
            temps.push_back(mesurer(version));

        std::sort(temps.begin(), temps.end());
        std::cout << "Médiane : " << temps[1] << " ms\n";
    }

    return 0;
}