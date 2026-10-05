#include <iostream>
#include <cmath>

int main()
{
    const double pi = 3.141592653589793;

    int N;
    std::cin >> N;

    int visibles = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        int r;
        int n;
        std::cin >> r >> n;

        if (n < 3)
        {
            std::cout << r << " " << n << " REFUSE\n";
            ++refuses;
            continue;
        }

        double gap = static_cast<double>(r) *
                     (1.0 - std::cos(pi / static_cast<double>(n)));

        if (gap == 0.0)
        {
            std::cout << r << " " << n << " 0 JAMAIS\n";
            continue;
        }

        long long ecart =
            static_cast<long long>(std::floor(gap * 1000.0));

        long long zoom =
            static_cast<long long>(std::ceil(100.0 / gap));

        if (zoom <= 100)
        {
            std::cout << r << " " << n << " "
                      << ecart << " "
                      << zoom << " VISIBLE\n";

            ++visibles;
        }
        else
        {
            std::cout << r << " " << n << " "
                      << ecart << " "
                      << zoom << " INVISIBLE\n";
        }
    }

    std::cout << "VISIBLES " << visibles << "\n";
    std::cout << "REFUSES " << refuses << "\n";

    return 0;
}