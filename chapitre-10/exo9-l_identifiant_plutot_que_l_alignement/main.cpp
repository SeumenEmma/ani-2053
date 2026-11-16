#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;

    std::vector<int> planche;

    int prochainIdentifiant = 1;

    long long occasions = 0;
    long long repercutes = 0;
    long long recherches = 0;

    for (int operation = 0; operation < N; ++operation)
    {
        std::string commande;
        std::cin >> commande;

        if (commande == "AJOUTE")
        {
            planche.push_back(prochainIdentifiant);
            ++prochainIdentifiant;
        }
        else if (commande == "SUPPRIME")
        {
            int c;
            std::cin >> c;

            std::vector<int> indices(c);

            for (int i = 0; i < c; ++i)
            {
                std::cin >> indices[i];
            }

            for (int i = c - 1; i >= 0; --i)
            {
                planche.erase(planche.begin() + indices[i]);
            }

            ++occasions;
            repercutes += 2LL * c;
        }
        else if (commande == "MONTE")
        {
            int i;
            std::cin >> i;

            if (i + 1 < static_cast<int>(planche.size()))
            {
                std::swap(planche[i], planche[i + 1]);

                ++occasions;
                repercutes += 2;
            }
        }
        else if (commande == "DESCEND")
        {
            int i;
            std::cin >> i;

            if (i > 0)
            {
                std::swap(planche[i], planche[i - 1]);

                ++occasions;
                repercutes += 2;
            }
        }
        else if (commande == "DESSINE")
        {
            recherches += static_cast<long long>(planche.size());
        }
    }

    std::cout << "ORDRE";

    if (planche.empty())
    {
        std::cout << " AUCUN";
    }
    else
    {
        for (int identifiant : planche)
        {
            std::cout << " " << identifiant;
        }
    }

    std::cout << '\n';
    std::cout << "OCCASIONS " << occasions << '\n';
    std::cout << "REPERCUTES " << repercutes << '\n';
    std::cout << "RECHERCHES " << recherches << '\n';

    return 0;
}