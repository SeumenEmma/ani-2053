#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Entree {
    string nom;
    int valeur;
    int cout;
    string etiquette;
    string genre;
    string cible;
    string raison;
    string categorie;
    int ordre;
    bool gardee;
};

int rangEtiquette(const string& etiquette) {
    if (etiquette == "MESUREE") {
        return 0;
    }

    if (etiquette == "OBSERVEE") {
        return 1;
    }

    return 2;
}

int rangCategorie(const string& categorie) {
    if (categorie == "MAINTENANT") {
        return 0;
    }

    if (categorie == "DECOUPER") {
        return 1;
    }

    if (categorie == "EN_PASSANT") {
        return 2;
    }

    return 3;
}

string determinerCategorie(int valeur, int cout) {
    bool valeurForte = valeur >= 3;
    bool coutEleve = cout >= 3;

    if (valeurForte && !coutEleve) {
        return "MAINTENANT";
    }

    if (valeurForte && coutEleve) {
        return "DECOUPER";
    }

    if (!valeurForte && !coutEleve) {
        return "EN_PASSANT";
    }

    return "ON_NE_LE_FAIT_PAS";
}

int main() {
    long long n;
    cin >> n;

    vector<Entree> entrees;
    unordered_map<string, size_t> indexParNom;

    for (long long i = 0; i < n; i++) {
        Entree entree;

        cin >> entree.nom
            >> entree.valeur
            >> entree.cout
            >> entree.etiquette
            >> entree.genre;

        entree.cible = "";

        if (entree.genre == "SOCLE") {
            cin >> entree.cible;
        }

        entree.ordre = static_cast<int>(i);
        entree.gardee = true;
        entree.raison = "";
        entree.categorie = "";

        if (entree.genre == "REECRITURE") {
            entree.gardee = false;
            entree.raison = "reecriture";
        }
        else if (entree.genre == "CHOIX") {
            entree.gardee = false;
            entree.raison = "choix";
        }
        else if (entree.etiquette == "-") {
            entree.gardee = false;
            entree.raison = "sans_etiquette";
        }

        indexParNom[entree.nom] = entrees.size();
        entrees.push_back(entree);
    }

    for (Entree& entree : entrees) {
        if (!entree.gardee) {
            continue;
        }

        if (entree.genre == "SOCLE") {
            auto recherche = indexParNom.find(entree.cible);

            if (recherche != indexParNom.end()) {
                const Entree& cible = entrees[recherche->second];

                if (cible.gardee && cible.genre == "MANQUE") {
                    entree.valeur = max(entree.valeur, cible.valeur);
                }
            }
        }

        entree.categorie =
            determinerCategorie(entree.valeur, entree.cout);
    }

    vector<Entree*> gardees;
    long long refus = 0;

    for (Entree& entree : entrees) {
        if (entree.gardee) {
            gardees.push_back(&entree);

            if (entree.categorie == "ON_NE_LE_FAIT_PAS") {
                refus++;
            }
        }
    }

    sort(
        gardees.begin(),
        gardees.end(),
        [](const Entree* a, const Entree* b) {
            int rangA = rangCategorie(a->categorie);
            int rangB = rangCategorie(b->categorie);

            if (rangA != rangB) {
                return rangA < rangB;
            }

            int etiquetteA = rangEtiquette(a->etiquette);
            int etiquetteB = rangEtiquette(b->etiquette);

            if (etiquetteA != etiquetteB) {
                return etiquetteA < etiquetteB;
            }

            if (a->valeur != b->valeur) {
                return a->valeur > b->valeur;
            }

            if (a->cout != b->cout) {
                return a->cout < b->cout;
            }

            return a->ordre < b->ordre;
        }
    );

    for (const Entree* entree : gardees) {
        cout << entree->categorie << " "
             << entree->nom << " "
             << entree->etiquette << '\n';
    }

    for (const Entree& entree : entrees) {
        if (!entree.gardee) {
            cout << "HORS_LISTE "
                 << entree.nom << " "
                 << entree.raison << '\n';
        }
    }

    if (refus > 0) {
        cout << "VERDICT HONNETE\n";
    }
    else {
        cout << "VERDICT COMPLAISANT\n";
    }

    return 0;
}