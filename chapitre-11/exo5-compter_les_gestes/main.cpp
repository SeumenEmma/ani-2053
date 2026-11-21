#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void afficherTemps(long long secondes) {
    long long minutes = secondes / 60;
    long long reste = secondes % 60;

    cout << minutes << ":" << setw(2) << setfill('0') << reste;
}

int main() {
    long long instant;
    string commande;

    bool enCours = false;

    string nom;
    long long debut = 0;
    long long minimum = 0;
    long long parJour = 0;

    long long gestes = 0;
    long long attente = 0;
    long long totalJour = 0;

    while (cin >> instant >> commande) {

        if (commande == "DEBUT") {
            cin >> nom >> minimum >> parJour;

            enCours = true;
            debut = instant;
            gestes = 0;
            attente = 0;
        }
        else if (commande == "FIN") {
            string nomFin;
            cin >> nomFin;

            if (enCours) {
                long long enTrop = gestes > minimum
                    ? gestes - minimum
                    : 0;

                long long duree = instant - debut;
                long long jour = (attente * parJour) / 1000;

                cout << nom
                     << " GESTES " << gestes
                     << " EN_TROP " << enTrop
                     << " DUREE " << duree
                     << " ATTENTE " << attente
                     << " JOUR ";

                afficherTemps(jour);
                cout << '\n';

                totalJour += jour;
                enCours = false;
            }
        }
        else if (commande == "CLIC") {
            if (enCours) {
                gestes++;
            }
        }
        else if (commande == "TOUCHE") {
            string touche;
            cin >> touche;

            if (enCours) {
                gestes++;
            }
        }
        else if (commande == "MOLETTE" || commande == "GLISSE") {
            if (enCours) {
                gestes++;
            }
        }
        else if (commande == "ATTENTE") {
            long long dureeAttente;
            cin >> dureeAttente;

            if (enCours) {
                attente += dureeAttente;
            }
        }
    }

    if (enCours) {
        cout << nom << " INACHEVEE\n";
    }

    cout << "TOTAL_JOUR ";
    afficherTemps(totalJour);
    cout << '\n';

    return 0;
}