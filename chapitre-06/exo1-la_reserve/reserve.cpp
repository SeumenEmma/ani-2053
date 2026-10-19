
#include <NKThreading/NkThread.h>
#include <NKThreading/NkThreadPool.h>
#include <NKTime/NkChrono.h>

#include <array>
#include <iostream>
#include <vector>

using nkentseu::NkChrono;
using nkentseu::threading::NkThread;
using nkentseu::threading::NkThreadPool;

constexpr int NB_TACHES = 200;

long long calculer(int repetitions)
{
    long long somme = 0;

    for (int r = 0; r < repetitions; ++r)
        for (int i = 1; i <= 1000; ++i)
            somme += i;

    return somme;
}

double mesurer_reserve(int repetitions)
{
    NkThreadPool pool(4);
    std::array<long long, NB_TACHES> resultats{};
    NkChrono chrono;

    for (int i = 0; i < NB_TACHES; ++i)
    {
        pool.Enqueue([&, i]()
        {
            resultats[i] = calculer(repetitions);
        });
    }

    pool.Join();

    double temps = chrono.Elapsed().milliseconds;
    std::cout << "Reserve : " << temps
              << " ms, resultat : " << resultats[0] << '\n';

    return temps;
}

double mesurer_fils(int repetitions)
{
    std::array<long long, NB_TACHES> resultats{};
    std::vector<NkThread> fils;
    fils.reserve(NB_TACHES);

    NkChrono chrono;

    for (int i = 0; i < NB_TACHES; ++i)
    {
       fils.emplace_back();
       fils.back().Start([&, i](void*)
       {
           resultats[i] = calculer(repetitions);
       });
    }

    for (auto& fil : fils)
        fil.Join();

    double temps = chrono.Elapsed().milliseconds;
    std::cout << "Fils : " << temps
              << " ms, resultat : " << resultats[0] << '\n';

    return temps;
}

int main()
{
    std::cout << "Nombre de taches : " << NB_TACHES << '\n';

    std::cout << "\n=== TACHE COURTE ===\n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Mesure " << i + 1 << '\n';
        mesurer_reserve(1);
        mesurer_fils(1);
    }

    std::cout << "\n=== TACHE LONGUE ===\n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Mesure " << i + 1 << '\n';
        mesurer_reserve(100);
        mesurer_fils(100);
    }

    NkThreadPool pool(4);
    std::cout << "\nOuvriers de la reserve : "
              << pool.GetNumWorkers() << '\n';

    return 0;
}