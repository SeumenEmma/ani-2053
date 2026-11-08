#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

bool exigeDefinition(const string& emploi) {
    return emploi == "VALEUR" ||
           emploi == "BASE" ||
           emploi == "CORPS" ||
           emploi == "TAILLE";
}

int main() {
    int u;
    cin >> u;

    vector<string> types;
    map<string, bool> doitInclure;
    set<string> dejaVu;

    for (int i = 0; i < u; i++) {
        string type;
        string emploi;

        cin >> type >> emploi;

        if (dejaVu.count(type) == 0) {
            types.push_back(type);
            dejaVu.insert(type);
            doitInclure[type] = false;
        }

        if (exigeDefinition(emploi)) {
            doitInclure[type] = true;
        }
    }

    int a;
    cin >> a;

    set<string> inclusActuellement;

    for (int i = 0; i < a; i++) {
        string type;
        cin >> type;
        inclusActuellement.insert(type);
    }

    int nombreInclure = 0;
    int nombreAnticiper = 0;
    int inclusionsRetirees = 0;

    for (const string& type : types) {
        if (doitInclure[type]) {
            cout << type << " INCLURE\n";
            nombreInclure++;
        } else {
            cout << type << " ANTICIPER\n";
            nombreAnticiper++;

            if (inclusActuellement.count(type) > 0) {
                inclusionsRetirees++;
            }
        }
    }

    cout << "INCLURE " << nombreInclure << '\n';
    cout << "ANTICIPER " << nombreAnticiper << '\n';
    cout << "INCLUSIONS_RETIREES " << inclusionsRetirees << '\n';

    return 0;
}