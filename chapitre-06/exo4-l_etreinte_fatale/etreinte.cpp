#include <NKThreading/NkThread.h>
#include <NKThreading/NkMutex.h>
#include <NKTime/NkChrono.h>
#include <iostream>

using nkentseu::threading::NkThread;
using nkentseu::threading::NkMutex;
using nkentseu::threading::NkScopedLockMutex;
using nkentseu::NkChrono;

NkMutex m1, m2;

/* VERSION INCORRECTE : INTERBLOCAGE (DEADLOCK)

void threadA()
{
    NkScopedLockMutex lock1(m1);
    std::cout << "A : verrou m1 obtenu\n";

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);
    std::cout << "A : verrou m2 obtenu\n";
}

void threadB()
{
    NkScopedLockMutex lock1(m2);
    std::cout << "B : verrou m2 obtenu\n";

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m1);
    std::cout << "B : verrou m1 obtenu\n";
}

int main()
{
    NkThread a([](void*) { threadA(); });
    NkThread b([](void*) { threadB(); });

    a.Join();
    b.Join();

    std::cout << "Fin du programme\n";
    return 0;
}

FIN DE LA VERSION INCORRECTE */


/* VERSION CORRIGÉE */

void threadA()
{
    NkScopedLockMutex lock1(m1);
    std::cout << "A : verrou m1 obtenu\n";

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);
    std::cout << "A : verrou m2 obtenu\n";
}

void threadB()
{
    NkScopedLockMutex lock1(m1);
    std::cout << "B : verrou m1 obtenu\n";

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);
    std::cout << "B : verrou m2 obtenu\n";
}

int main()
{
    NkThread a([](void*) { threadA(); });
    NkThread b([](void*) { threadB(); });

    a.Join();
    b.Join();

    std::cout << "Fin du programme\n";
    return 0;
}