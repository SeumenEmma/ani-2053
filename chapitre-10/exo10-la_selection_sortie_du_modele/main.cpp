#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

struct Operation
{
    std::string commande;
    std::string nom;
    int i = 0;
    int j = 0;
};

struct Image
{
    std::string nom;
    bool selectionnee = false;
};

struct Planche
{
    std::vector<Image> images;
    std::set<int> indices;
    std::set<std::string> identifiants;
};

bool valide(const Planche& planche, int i)
{
    return i >= 0 && i < static_cast<int>(planche.images.size());
}

void appliquer(Planche& planche, const Operation& op, int conception)
{
    if (op.commande == "AJOUTE")
    {
        planche.images.push_back({op.nom, false});
    }
    else if (op.commande == "CLIC")
    {
        if (conception == 0)
        {
            for (auto& image : planche.images)
                image.selectionnee = false;
        }
        else if (conception == 1)
        {
            planche.indices.clear();
        }
        else
        {
            planche.identifiants.clear();
        }

        if (valide(planche, op.i))
        {
            if (conception == 0)
                planche.images[op.i].selectionnee = true;
            else if (conception == 1)
                planche.indices.insert(op.i);
            else
                planche.identifiants.insert(planche.images[op.i].nom);
        }
    }
    else if (op.commande == "AJOUTE_SEL")
    {
        if (valide(planche, op.i))
        {
            if (conception == 0)
                planche.images[op.i].selectionnee = true;
            else if (conception == 1)
                planche.indices.insert(op.i);
            else
                planche.identifiants.insert(planche.images[op.i].nom);
        }
    }
    else if (op.commande == "ECHANGE")
    {
        if (valide(planche, op.i) && valide(planche, op.j))
        {
            std::swap(planche.images[op.i], planche.images[op.j]);
        }
    }
    else if (op.commande == "RETIRE")
    {
        if (valide(planche, op.i))
        {
            planche.images.erase(planche.images.begin() + op.i);
        }
    }
    else if (op.commande == "SUPPRIME")
    {
        std::vector<Image> restantes;

        for (int i = 0; i < static_cast<int>(planche.images.size()); ++i)
        {
            bool selectionnee = false;

            if (conception == 0)
                selectionnee = planche.images[i].selectionnee;
            else if (conception == 1)
                selectionnee = planche.indices.count(i) > 0;
            else
                selectionnee = planche.identifiants.count(planche.images[i].nom) > 0;

            if (!selectionnee)
                restantes.push_back(planche.images[i]);
        }

        planche.images = restantes;
        planche.indices.clear();
        planche.identifiants.clear();
    }
}

void afficher(const Planche& planche, const std::string& nom, int conception)
{
    std::cout << nom << " PLANCHE";

    if (planche.images.empty())
    {
        std::cout << " AUCUN";
    }
    else
    {
        for (const auto& image : planche.images)
            std::cout << " " << image.nom;
    }

    std::cout << '\n';

    std::cout << nom << " SELECTION";

    bool auMoinsUne = false;

    for (int i = 0; i < static_cast<int>(planche.images.size()); ++i)
    {
        bool selectionnee = false;

        if (conception == 0)
            selectionnee = planche.images[i].selectionnee;
        else if (conception == 1)
            selectionnee = planche.indices.count(i) > 0;
        else
            selectionnee = planche.identifiants.count(planche.images[i].nom) > 0;

        if (selectionnee)
        {
            std::cout << " " << planche.images[i].nom;
            auMoinsUne = true;
        }
    }

    if (!auMoinsUne)
        std::cout << " AUCUN";

    std::cout << '\n';
}

int main()
{
    std::vector<Operation> operations;
    std::string ligne;

    while (std::getline(std::cin, ligne))
    {
        if (ligne.empty())
            continue;

        std::istringstream flux(ligne);
        Operation op;

        flux >> op.commande;

        if (op.commande == "AJOUTE")
            flux >> op.nom;
        else if (op.commande == "CLIC" || op.commande == "AJOUTE_SEL"
                 || op.commande == "RETIRE")
            flux >> op.i;
        else if (op.commande == "ECHANGE")
            flux >> op.i >> op.j;

        operations.push_back(op);
    }

    Planche planches[3];

    for (const auto& op : operations)
    {
        for (int conception = 0; conception < 3; ++conception)
            appliquer(planches[conception], op, conception);
    }

    afficher(planches[0], "DANS_ITEM", 0);
    afficher(planches[1], "PAR_INDEX", 1);
    afficher(planches[2], "PAR_ID", 2);

    bool faux = false;

    for (int i = 1; i < 3; ++i)
    {
        bool different = false;

        if (planches[i].images.size() != planches[0].images.size())
            different = true;
        else
        {
            for (int j = 0; j < static_cast<int>(planches[0].images.size()); ++j)
            {
                if (planches[i].images[j].nom != planches[0].images[j].nom)
                    different = true;
            }
        }

        std::vector<std::string> selection0;
        std::vector<std::string> selectionI;

        for (int j = 0; j < static_cast<int>(planches[0].images.size()); ++j)
        {
            if (planches[0].images[j].selectionnee)
                selection0.push_back(planches[0].images[j].nom);
        }

        for (int j = 0; j < static_cast<int>(planches[i].images.size()); ++j)
        {
            bool selectionnee = false;

            if (i == 1)
                selectionnee = planches[i].indices.count(j) > 0;
            else
                selectionnee = planches[i].identifiants.count(planches[i].images[j].nom) > 0;

            if (selectionnee)
                selectionI.push_back(planches[i].images[j].nom);
        }

        if (selection0 != selectionI)
            different = true;

        if (different)
        {
            std::cout << (faux ? " " : "FAUX ");
            std::cout << (i == 1 ? "PAR_INDEX" : "PAR_ID");
            faux = true;
        }
    }

    if (!faux)
        std::cout << "FAUX AUCUN";

    std::cout << '\n';

    return 0;
}