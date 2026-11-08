#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

bool estCpp(const string& nom) {
    return nom.size() >= 4 &&
           nom.substr(nom.size() - 4) == ".cpp";
}

bool estH(const string& nom) {
    return nom.size() >= 2 &&
           nom.substr(nom.size() - 2) == ".h";
}

int compterCpp(int depart,
               const vector<string>& noms,
               const vector<vector<int>>& inclusPar) {

    vector<bool> visite(noms.size(), false);
    queue<int> aVisiter;

    aVisiter.push(depart);
    visite[depart] = true;

    int total = 0;

    while (!aVisiter.empty()) {
        int courant = aVisiter.front();
        aVisiter.pop();

        if (estCpp(noms[courant])) {
            total++;
        }

        for (int suivant : inclusPar[courant]) {
            if (!visite[suivant]) {
                visite[suivant] = true;
                aVisiter.push(suivant);
            }
        }
    }

    return total;
}

int main() {
    int n;
    cin >> n;

    vector<string> noms(n);
    vector<vector<string>> inclusions(n);

    map<string, int> indices;

    for (int i = 0; i < n; i++) {
        int k;
        cin >> noms[i] >> k;

        indices[noms[i]] = i;

        for (int j = 0; j < k; j++) {
            string fichier;
            cin >> fichier;
            inclusions[i].push_back(fichier);
        }
    }

    vector<vector<int>> inclusPar(n);

    for (int i = 0; i < n; i++) {
        for (const string& fichier : inclusions[i]) {
            if (indices.count(fichier)) {
                int indice = indices[fichier];
                inclusPar[indice].push_back(i);
            }
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string fichier;
        cin >> fichier;

        int depart = indices[fichier];
        int total = compterCpp(depart, noms, inclusPar);

        cout << fichier << " " << total << '\n';
    }

    int maximum = -1;
    string plusLourd = "AUCUN";

    for (int i = 0; i < n; i++) {
        if (estH(noms[i])) {
            int total = compterCpp(i, noms, inclusPar);

            if (total > maximum) {
                maximum = total;
                plusLourd = noms[i];
            }
        }
    }

    if (maximum == -1) {
        cout << "PLUS_LOURD AUCUN\n";
    } else {
        cout << "PLUS_LOURD " << plusLourd
             << " " << maximum << '\n';
    }

    return 0;
}