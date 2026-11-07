#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Operation {
    string type;
    string a;
    string b;
};

int main() {
    int n;
    cin >> n;

    vector<Operation> operations(n);
    map<string, int> indices;
    vector<string> noms;

    // Lire les opérations et mémoriser l'ordre des variables.
    for (int i = 0; i < n; i++) {
        cin >> operations[i].type;

        if (operations[i].type == "NEW" ||
            operations[i].type == "RESET" ||
            operations[i].type == "USE") {

            cin >> operations[i].a;

            if (indices.find(operations[i].a) == indices.end()) {
                indices[operations[i].a] = (int)noms.size();
                noms.push_back(operations[i].a);
            }
        }

        else if (operations[i].type == "MOVE" ||
                 operations[i].type == "COPY") {

            cin >> operations[i].a >> operations[i].b;

            if (indices.find(operations[i].a) == indices.end()) {
                indices[operations[i].a] = (int)noms.size();
                noms.push_back(operations[i].a);
            }

            if (indices.find(operations[i].b) == indices.end()) {
                indices[operations[i].b] = (int)noms.size();
                noms.push_back(operations[i].b);
            }
        }
    }

    // Refuser toutes les copies avant de rejouer le programme.
    bool copie = false;

    for (int i = 0; i < n; i++) {
        if (operations[i].type == "COPY") {
            cout << "REFUSE " << i + 1 << '\n';
            copie = true;
        }
    }

    if (copie) {
        return 0;
    }

    vector<int> possede(noms.size(), 0);

    int crees = 0;
    int detruits = 0;
    int nuls = 0;

    // Rejouer les opérations.
    for (int i = 0; i < n; i++) {
        string type = operations[i].type;
        string a = operations[i].a;
        string b = operations[i].b;

        int ia = indices[a];

        if (type == "NEW") {
            crees++;

            if (possede[ia] != 0) {
                cout << "DETRUIT " << possede[ia] << '\n';
                detruits++;
            }

            possede[ia] = crees;
        }

        else if (type == "MOVE") {
            int ib = indices[b];

            int objet = possede[ia];
            possede[ia] = 0;

            if (possede[ib] != 0) {
                cout << "DETRUIT " << possede[ib] << '\n';
                detruits++;
            }

            possede[ib] = objet;
        }

        else if (type == "RESET") {
            if (possede[ia] != 0) {
                cout << "DETRUIT " << possede[ia] << '\n';
                detruits++;
                possede[ia] = 0;
            }
        }

        else if (type == "USE") {
            if (possede[ia] == 0) {
                cout << "NUL " << i + 1 << " " << a << '\n';
                nuls++;
            }
        }
    }

    // Détruire les variables dans l'ordre inverse d'apparition.
    for (int i = (int)noms.size() - 1; i >= 0; i--) {
        if (possede[i] != 0) {
            cout << "DETRUIT " << possede[i] << '\n';
            detruits++;
            possede[i] = 0;
        }
    }

    // Afficher le bilan final.
    cout << "CREES " << crees << '\n';
    cout << "DETRUITS " << detruits << '\n';
    cout << "NULS " << nuls << '\n';

    return 0;
}