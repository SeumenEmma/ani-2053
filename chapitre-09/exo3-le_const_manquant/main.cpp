
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Methode {
    string nom;
    string declaration;
    int modifie;
    vector<string> nomsAppeles;
    vector<int> appels;
};

int main() {
    int n;
    cin >> n;

    vector<Methode> methodes(n);

    // Lire toutes les méthodes.
    for (int i = 0; i < n; i++) {
        int k;

        cin >> methodes[i].nom;
        cin >> methodes[i].declaration;
        cin >> methodes[i].modifie;
        cin >> k;

        for (int j = 0; j < k; j++) {
            string nomAppel;
            cin >> nomAppel;
            methodes[i].nomsAppeles.push_back(nomAppel);
        }
    }

    // Retrouver les indices des méthodes appelées.
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < methodes[i].nomsAppeles.size(); j++) {
            for (int x = 0; x < n; x++) {
                if (methodes[x].nom == methodes[i].nomsAppeles[j]) {
                    methodes[i].appels.push_back(x);
                }
            }
        }
    }

    vector<bool> pourrait(n, false);

    // Chercher les méthodes qui peuvent devenir const.
    for (int i = 0; i < n; i++) {
        if (methodes[i].declaration == "-" && methodes[i].modifie == 0) {
            pourrait[i] = true;
        }
    }

    bool changement = true;

    while (changement) {
        changement = false;

        for (int i = 0; i < n; i++) {
            if (pourrait[i] && methodes[i].declaration == "-") {
                bool correct = true;

                for (size_t j = 0; j < methodes[i].appels.size(); j++) {
                    int appel = methodes[i].appels[j];

                    if (methodes[appel].declaration != "const" && !pourrait[appel]) {
                        correct = false;
                    }
                }

                if (!correct) {
                    pourrait[i] = false;
                    changement = true;
                }
            }
        }
    }

    // Afficher les méthodes qui pourraient devenir const.
    cout << "POURRAIT";
    bool vide = true;

    for (int i = 0; i < n; i++) {
        if (pourrait[i] && methodes[i].declaration == "-") {
            cout << " " << methodes[i].nom;
            vide = false;
        }
    }

    if (vide) {
        cout << " AUCUN";
    }

    cout << '\n';

    // Afficher les racines.
    cout << "RACINES";
    vide = true;

    for (int i = 0; i < n; i++) {
        if (pourrait[i] && methodes[i].declaration == "-") {
            bool racine = true;

            for (size_t j = 0; j < methodes[i].appels.size(); j++) {
                int appel = methodes[i].appels[j];

                if (methodes[appel].declaration != "const") {
                    racine = false;
                }
            }

            if (racine) {
                cout << " " << methodes[i].nom;
                vide = false;
            }
        }
    }

    if (vide) {
        cout << " AUCUN";
    }

    cout << '\n';

    // Calculer le nombre de passes.
    vector<bool> dejaConst(n, false);

    for (int i = 0; i < n; i++) {
        if (methodes[i].declaration == "const") {
            dejaConst[i] = true;
        }
    }

    int passes = 0;
    int restantes = 0;

    for (int i = 0; i < n; i++) {
        if (pourrait[i] && methodes[i].declaration == "-") {
            restantes++;
        }
    }

    while (restantes > 0) {
        vector<int> pretes;

        for (int i = 0; i < n; i++) {
            if (pourrait[i] && !dejaConst[i]) {
                bool possible = true;

                for (size_t j = 0; j < methodes[i].appels.size(); j++) {
                    int appel = methodes[i].appels[j];

                    if (!dejaConst[appel]) {
                        possible = false;
                    }
                }

                if (possible) {
                    pretes.push_back(i);
                }
            }
        }

        if (pretes.empty()) {
            break;
        }

        for (size_t i = 0; i < pretes.size(); i++) {
            dejaConst[pretes[i]] = true;
            restantes--;
        }

        passes++;
    }

    cout << "PASSES " << passes << '\n';

    return 0;
}
