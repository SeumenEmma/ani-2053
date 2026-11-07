#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Objet {
    vector<string> dependances;
    bool libere = false;
};

int main() {
    map<string, Objet> objets;
    vector<vector<string>> blocs(1);

    string commande;

    while (cin >> commande) {

        if (commande == "DECL") {
            string x;
            cin >> x;

            objets[x] = Objet();
            blocs.back().push_back(x);
        }

        else if (commande == "DEPEND") {
            string a, b;
            cin >> a >> b;

            objets[a].dependances.push_back(b);
        }

        else if (commande == "FERME") {
            string x;
            cin >> x;

            if (!objets[x].libere) {
                bool erreur = false;

                for (size_t i = 0; i < objets[x].dependances.size(); i++) {
                    string b = objets[x].dependances[i];

                    if (objets[b].libere) {
                        cout << "PLANTAGE " << x << " " << b << '\n';
                        return 0;
                    }
                }

                if (!erreur) {
                    objets[x].libere = true;
                    cout << "FERME " << x << '\n';
                }
            }
        }

        else if (commande == "{") {
            blocs.push_back(vector<string>());
        }

        else if (commande == "}") {
            for (int i = (int)blocs.back().size() - 1; i >= 0; i--) {
                string x = blocs.back()[i];

                if (!objets[x].libere) {
                    for (size_t j = 0; j < objets[x].dependances.size(); j++) {
                        string b = objets[x].dependances[j];

                        if (objets[b].libere) {
                            cout << "PLANTAGE " << x << " " << b << '\n';
                            return 0;
                        }
                    }

                    objets[x].libere = true;
                    cout << "DETRUIT " << x << '\n';
                }
            }

            blocs.pop_back();
        }
    }

    // Fermer le bloc principal.
    for (int i = (int)blocs[0].size() - 1; i >= 0; i--) {
        string x = blocs[0][i];

        if (!objets[x].libere) {
            for (size_t j = 0; j < objets[x].dependances.size(); j++) {
                string b = objets[x].dependances[j];

                if (objets[b].libere) {
                    cout << "PLANTAGE " << x << " " << b << '\n';
                    return 0;
                }
            }

            objets[x].libere = true;
            cout << "DETRUIT " << x << '\n';
        }
    }

    cout << "PROPRE\n";

    return 0;
}