#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Evenement {
    long long seconde;
    string action;
};

int main() {
    string mode;
    string mot;
    long long intervalle;
    string documentInitial;

    cin >> mot >> mode;
    cin >> mot >> intervalle;
    cin >> mot >> documentInitial;

    vector<Evenement> evenements;

    Evenement evenement;
    while (cin >> evenement.seconde >> evenement.action) {
        evenements.push_back(evenement);

        if (evenement.action == "FIN") {
            break;
        }
    }

    string cheminCourant = documentInitial;

    long long changements = 0;
    long long changementsDocument = 0;
    long long tempsEcoule = 0;

    bool change = false;
    bool etoile = false;

    size_t index = 0;
    long long seconde = 0;
    long long fin = 0;

    if (!evenements.empty()) {
        fin = evenements.back().seconde;
    }

    vector<string> sorties;

    while (seconde <= fin) {
        bool termine = false;

        // Traiter tous les événements de cette seconde.
        while (index < evenements.size() &&
               evenements[index].seconde == seconde) {

            const string& action = evenements[index].action;

            if (action == "FIN") {
                termine = true;
                break;
            }

            if (action == "CHANGE") {
                changements++;
                change = true;
                etoile = true;
            }
            else if (action == "CTRL_S") {
                sorties.push_back(
                    to_string(seconde) + " MANUEL " +
                    cheminCourant + " " + to_string(changements)
                );

                if (cheminCourant == documentInitial) {
                    changementsDocument = changements;
                }

                etoile = false;
                change = false;
                tempsEcoule = 0;
            }

            index++;
        }

        // FIN arrête le programme avant le Tick de cette seconde.
        if (termine) {
            break;
        }

        // Le Tick commence à la seconde 1.
        if (seconde >= 1) {
            tempsEcoule++;

            if (change && tempsEcoule >= intervalle) {
                string cheminSecours = cheminCourant + ".auto";

                sorties.push_back(
                    to_string(seconde) + " AUTO " +
                    cheminSecours + " " + to_string(changements)
                );

                if (mode == "NAIF") {
                    cheminCourant = cheminSecours;
                    etoile = false;
                }

                change = false;
                tempsEcoule = 0;
            }
        }

        seconde++;
    }

    for (const string& ligne : sorties) {
        cout << ligne << '\n';
    }

    cout << "FIN " << fin << '\n';
    cout << "CHEMIN_COURANT " << cheminCourant << '\n';
    cout << "ETOILE " << (etoile ? "OUI" : "NON") << '\n';
    cout << "DOCUMENT " << changementsDocument
         << " SUR " << changements << '\n';
    cout << "HORS_DOCUMENT "
         << changements - changementsDocument << '\n';

    return 0;
}