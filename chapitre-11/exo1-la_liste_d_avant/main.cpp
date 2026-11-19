#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    int n, c, a;
    string mot;

    vector<string> avant;
    unordered_set<string> corrige;
    unordered_set<string> apres;
    unordered_set<string> anciennes;

    cin >> mot >> n;
    for (int i = 0; i < n; i++) {
        string cle;
        cin >> cle;
        avant.push_back(cle);
        anciennes.insert(cle);
    }

    cin >> mot >> c;
    for (int i = 0; i < c; i++) {
        string cle;
        cin >> cle;
        corrige.insert(cle);
    }

    cin >> mot >> a;
    for (int i = 0; i < a; i++) {
        string cle;
        cin >> cle;
        apres.insert(cle);
    }

    int vraies = 0;
    int fausses = 0;
    int oubliees = 0;
    int nouvelles = 0;

    for (int i = 0; i < n; i++) {
        const string& cle = avant[i];

        if (corrige.count(cle)) {
            cout << i + 1 << " " << cle << " DEVENUE_FAUSSE\n";
            fausses++;
        }
        else if (apres.count(cle)) {
            cout << i + 1 << " " << cle << " ENCORE_VRAIE\n";
            vraies++;
        }
        else {
            cout << i + 1 << " " << cle << " OUBLIEE\n";
            oubliees++;
        }
    }

    for (const string& cle : apres) {
        if (!anciennes.count(cle)) {
            nouvelles++;
        }
    }

    int partOubliee = 0;

    if (vraies + oubliees != 0) {
        partOubliee = 100 * oubliees / (vraies + oubliees);
    }

    cout << "VRAIES " << vraies << '\n';
    cout << "FAUSSES " << fausses << '\n';
    cout << "OUBLIEES " << oubliees << '\n';
    cout << "NOUVELLES " << nouvelles << '\n';
    cout << "PART_OUBLIEE " << partOubliee << '\n';

    return 0;
}