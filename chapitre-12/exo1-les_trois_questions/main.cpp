#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Composant {
    string nom;
    vector<string> besoins;
    vector<string> parties;
    int tests;
};

int main() {
    unordered_set<string> intouchables;

    string mot;
    int k;

    cin >> mot >> k;

    for (int i = 0; i < k; i++) {
        string partie;
        cin >> partie;
        intouchables.insert(partie);
    }

    int n;
    cin >> n;

    vector<Composant> composants;

    for (int i = 0; i < n; i++) {
        Composant c;

        int b, t;

        cin >> c.nom >> b;

        for (int j = 0; j < b; j++) {
            string besoin;
            cin >> besoin;
            c.besoins.push_back(besoin);
        }

        cin >> t;

        for (int j = 0; j < t; j++) {
            string partie;
            cin >> partie;
            c.parties.push_back(partie);
        }

        cin >> c.tests;

        composants.push_back(c);
    }

    int purs = 0;
    int aRevoir = 0;
    int filetsAPoser = 0;

    vector<string> prets;

    for (const Composant& c : composants) {
        bool besoinGlue = false;
        bool besoinDecouper = false;

        for (const string& besoin : c.besoins) {
            if (besoin == "FENETRE" ||
                besoin == "SOURIS" ||
                besoin == "CLAVIER" ||
                besoin == "GPU") {
                besoinGlue = true;
            }

            if (besoin == "DISQUE" ||
                besoin == "HORLOGE" ||
                besoin == "RESEAU") {
                besoinDecouper = true;
            }
        }

        string lieu;

        if (besoinGlue) {
            lieu = "GLUE";
        } else if (besoinDecouper) {
            lieu = "DECOUPER";
        } else {
            lieu = "FICHIER_PUR";
            purs++;
        }

        string partieARevoir = "";

        for (const string& partie : c.parties) {
            if (intouchables.find(partie) != intouchables.end()) {
                partieARevoir = partie;
                break;
            }
        }

        string touche;

        if (partieARevoir.empty()) {
            touche = "INTACT";
        } else {
            touche = "REVOIR";
            aRevoir++;
        }

        string filet;

        if (c.tests == 0) {
            filet = "FILET_D_ABORD";
            filetsAPoser++;
        } else {
            filet = "FILET_EXISTANT";
        }

        cout << c.nom << " " << lieu << " ";

        if (touche == "REVOIR") {
            cout << touche << " " << partieARevoir;
        } else {
            cout << touche;
        }

        cout << " " << filet << "\n";

        if (touche == "INTACT" && c.tests > 0) {
            prets.push_back(c.nom);
        }
    }

    cout << "PURS " << purs << "\n";
    cout << "A_REVOIR " << aRevoir << "\n";
    cout << "FILETS_A_POSER " << filetsAPoser << "\n";

    cout << "PRETS";

    if (prets.empty()) {
        cout << " AUCUN";
    } else {
        for (const string& nom : prets) {
            cout << " " << nom;
        }
    }

    cout << "\n";

    return 0;
}