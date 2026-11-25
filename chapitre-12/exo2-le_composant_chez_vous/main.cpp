#include <iostream>
#include <string>

using namespace std;

int main() {
    string mot;
    long long intervalle;
    string document;

    cin >> mot >> intervalle >> mot >> document;

    if (document == "-") {
        document = "planche-sans-nom.nkref";
    }

    string nomSecours = document + ".auto";

    long long tempsEcoule = 0;
    long long instant = 0;

    bool change = false;
    bool disqueOK = true;

    int sauvegardes = 0;
    int echecs = 0;

    string commande;

    while (cin >> commande) {
        if (commande == "TOUCH") {
            change = true;
        }
        else if (commande == "TICK") {
            long long d;
            cin >> d;

            if (d > 0) {
                tempsEcoule += d;
                instant += d;
            }

            if (change && tempsEcoule >= intervalle) {
                if (disqueOK) {
                    cout << instant << " SECOURS\n";
                    sauvegardes++;

                    change = false;
                    tempsEcoule = 0;
                }
                else {
                    cout << instant << " ECHEC\n";
                    echecs++;
                }
            }
        }
        else if (commande == "CTRL_S") {
            if (disqueOK) {
                cout << instant << " MANUELLE\n";

                change = false;
                tempsEcoule = 0;
            }
            else {
                cout << instant << " MANUELLE_ECHEC\n";
                echecs++;
            }
        }
        else if (commande == "DISQUE") {
            string etat;
            cin >> etat;

            disqueOK = (etat == "OK");
        }
    }

    cout << "SAUVEGARDES " << sauvegardes << "\n";
    cout << "ECHECS " << echecs << "\n";

    cout << "EN_ATTENTE " << (change ? "OUI" : "NON") << "\n";
    cout << "SECOURS_NOM " << nomSecours << "\n";

    return 0;
}