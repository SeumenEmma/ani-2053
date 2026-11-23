#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Entree
{
    std::string nom;
    int valeur;
    int cout;
    std::string etiquette;
    std::string genre;
    std::string cible;
};

int valeurEffective(
    std::size_t index,
    const std::vector<Entree>& entrees,
    const std::unordered_map<std::string, std::size_t>& positions,
    std::vector<bool>& enCours)
{
    if (enCours[index])
    {
        throw std::runtime_error("Cycle detecte dans les SOCLE.");
    }

    enCours[index] = true;

    int valeur = entrees[index].valeur;

    if (entrees[index].genre == "SOCLE")
    {
        auto cible = positions.find(entrees[index].cible);

        if (cible == positions.end())
        {
            throw std::runtime_error(
                "Cible SOCLE introuvable : " + entrees[index].cible);
        }

        valeur = std::max(
            valeur,
            valeurEffective(cible->second, entrees, positions, enCours));
    }

    enCours[index] = false;
    return valeur;
}

int main(int argc, char* argv[])
{
    const std::string chemin =
        (argc > 1) ? argv[1] : "matrice.txt";

    std::ifstream fichier(chemin);

    if (!fichier)
    {
        std::cerr << "Impossible d'ouvrir " << chemin << '\n';
        return 1;
    }

    int nombre;
    if (!(fichier >> nombre) || nombre < 1)
    {
        std::cerr << "Nombre d'entrees invalide.\n";
        return 1;
    }

    std::vector<Entree> entrees;
    std::unordered_map<std::string, std::size_t> positions;

    for (int i = 0; i < nombre; ++i)
    {
        Entree entree;

        if (!(fichier >> entree.nom
                      >> entree.valeur
                      >> entree.cout
                      >> entree.etiquette
                      >> entree.genre))
        {
            std::cerr << "Entree incomplete a la ligne "
                      << i + 2 << ".\n";
            return 1;
        }

        if (entree.valeur < 1 || entree.valeur > 5 ||
            entree.cout < 1 || entree.cout > 5)
        {
            std::cerr << "Valeur ou cout invalide : "
                      << entree.nom << '\n';
            return 1;
        }

        if (entree.genre == "SOCLE")
        {
            if (!(fichier >> entree.cible))
            {
                std::cerr << "Cible SOCLE manquante : "
                          << entree.nom << '\n';
                return 1;
            }
        }

        if (entree.genre != "MANQUE" &&
            entree.genre != "REECRITURE" &&
            entree.genre != "CHOIX" &&
            entree.genre != "SOCLE")
        {
            std::cerr << "Genre invalide : "
                      << entree.genre << '\n';
            return 1;
        }

        if (!positions.emplace(entree.nom, entrees.size()).second)
        {
            std::cerr << "Nom en double : " << entree.nom << '\n';
            return 1;
        }

        entrees.push_back(entree);
    }

    bool refus = false;

    for (std::size_t i = 0; i < entrees.size(); ++i)
    {
        const Entree& entree = entrees[i];

        if (entree.genre == "REECRITURE")
        {
            std::cout << "HORS_LISTE " << entree.nom
                      << " reecriture\n";
            continue;
        }

        if (entree.genre == "CHOIX")
        {
            std::cout << "HORS_LISTE " << entree.nom
                      << " choix\n";
            continue;
        }

        if (entree.etiquette == "-")
        {
            std::cout << "HORS_LISTE " << entree.nom
                      << " sans_etiquette\n";
            continue;
        }

        if (entree.etiquette != "MESUREE" &&
            entree.etiquette != "OBSERVEE" &&
            entree.etiquette != "SUPPOSEE")
        {
            std::cerr << "Etiquette invalide : "
                      << entree.nom << '\n';
            return 1;
        }

        std::vector<bool> enCours(entrees.size(), false);
        int valeur = 0;

        try
        {
            valeur = valeurEffective(i, entrees, positions, enCours);
        }
        catch (const std::runtime_error& erreur)
        {
            std::cerr << erreur.what() << '\n';
            return 1;
        }

        const bool valeurForte = valeur >= 3;
        const bool coutEleve = entree.cout >= 3;

        std::string categorie;

        if (valeurForte && !coutEleve)
        {
            categorie = "MAINTENANT";
        }
        else if (valeurForte && coutEleve)
        {
            categorie = "DECOUPER";
        }
        else if (!valeurForte && !coutEleve)
        {
            categorie = "EN_PASSANT";
        }
        else
        {
            categorie = "ON_NE_LE_FAIT_PAS";
            refus = true;
        }

        std::cout << "CASE " << categorie << " "
                  << entree.nom << " "
                  << entree.etiquette << '\n';
    }

    if (refus)
    {
        std::cout << "VERDICT HONNETE\n";
    }

    return 0;
}