#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Annonce {
    string hash;
    string etat;
    string fonction;
};

int main() {
    int H;
    cin >> H;

    vector<string> hashes(H + 1);
    vector<unordered_set<string>> historiques(H + 1);
    unordered_map<string, int> positions;

    for (int i = 1; i <= H; i++) {
        string action;
        int k;

        cin >> hashes[i] >> action >> k;
        positions[hashes[i]] = i;

        historiques[i] = historiques[i - 1];

        for (int j = 0; j < k; j++) {
            string fonction;
            cin >> fonction;

            if (action == "AJOUTE") {
                historiques[i].insert(fonction);
            } else if (action == "RETIRE") {
                historiques[i].erase(fonction);
            }
        }
    }

    int A;
    cin >> A;

    vector<Annonce> annonces(A);

    for (int i = 0; i < A; i++) {
        cin >> annonces[i].hash
            >> annonces[i].etat
            >> annonces[i].fonction;
    }

    int mensonges = 0;

    for (int i = 0; i < A; i++) {
        const Annonce& annonce = annonces[i];

        int debut = positions[annonce.hash];

        auto estFausse = [&](int commit) {
            bool presente =
                historiques[commit].count(annonce.fonction) > 0;

            if (annonce.etat == "A_VENIR") {
                return presente;
            }

            return !presente;
        };

        if (!estFausse(H)) {
            cout << "ANNONCE " << i + 1 << " VRAI\n";
        } else {
            int h = H;

            while (h > debut && estFausse(h - 1)) {
                h--;
            }

            cout << "ANNONCE " << i + 1
                 << " MENT " << hashes[h] << '\n';

            mensonges++;
        }
    }

    cout << "MENSONGES " << mensonges << '\n';

    return 0;
}