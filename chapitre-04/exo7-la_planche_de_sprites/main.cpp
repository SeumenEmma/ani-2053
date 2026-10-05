#include <iostream>

int main()
{
    int C, R, W, H, F, D, P;
    std::cin >> C >> R >> W >> H >> F >> D >> P;
    int N;
    std::cin >> N;
    int caseCourante = 0;
    int tempsAccumule = 0;
    int avances = 0;
    int plafonnes = 0;

    for (int i = 0; i < N; ++i)
    {
        int dt;
        std::cin >> dt;

        if (dt > P)
        {
            dt = P;
            ++plafonnes;
        }
        tempsAccumule += dt;

        while (tempsAccumule >= D)
        {
            tempsAccumule -= D;
            ++caseCourante;

            if (caseCourante >= F)
            {
                caseCourante = 0;
            }
            ++avances;
        }

        int x = (caseCourante % C) * W;
        int y = (caseCourante / C) * H;

        std::cout << caseCourante << " "
                  << x << " "
                  << y << " "
                  << W << " "
                  << H << "\n";
    }

    std::cout << "AVANCES " << avances << "\n";
    std::cout << "PLAFONNES " << plafonnes << "\n";

    return 0;
}