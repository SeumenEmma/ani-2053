#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    long long avertissementsAvant;
    long long avertissementsApres;

    long long totalTests;
    long long echecsTests;

    int hauteur;
    int largeur;

    string usage;

    string mot;

    cin >> mot >> avertissementsAvant >> avertissementsApres;
    cin >> mot >> totalTests >> echecsTests;
    cin >> mot >> hauteur >> largeur;

    vector<string> captureAvant(hauteur);
    vector<string> captureApres(hauteur);

    for (int i = 0; i < hauteur; i++) {
        cin >> captureAvant[i];
    }

    for (int i = 0; i < hauteur; i++) {
        cin >> captureApres[i];
    }

    cin >> mot >> usage;

    // Les résultats sont calculés après lecture de toute l'entrée.
    vector<string> resultats(4);

    int coutTotal = 0;
    int preuveEchouee = 0;

    // Preuve 1 : compilation (30 secondes).
    if (avertissementsApres <= avertissementsAvant) {
        resultats[0] = "1 COMPILATION OK";
    } else {
        resultats[0] = "1 COMPILATION ECHEC +" +
                       to_string(avertissementsApres - avertissementsAvant);
        preuveEchouee = 1;
    }

    coutTotal += 30;

    // Preuve 2 : tests (60 secondes).
    if (preuveEchouee == 0) {
        if (totalTests == 0) {
            resultats[1] = "2 TESTS ECHEC AUCUN_TEST";
            preuveEchouee = 2;
        } else if (echecsTests > 0) {
            resultats[1] = "2 TESTS ECHEC " +
                           to_string(echecsTests);
            preuveEchouee = 2;
        } else {
            resultats[1] = "2 TESTS OK " +
                           to_string(totalTests);
        }

        coutTotal += 60;
    } else {
        resultats[1] = "2 TESTS NON_JOUEE";
    }

    // Preuve 3 : comparaison des captures (180 secondes).
    if (preuveEchouee == 0) {
        int differences = 0;
        int premiereLigne = 0;
        int premiereColonne = 0;

        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                if (captureAvant[i][j] != captureApres[i][j]) {
                    differences++;

                    if (premiereLigne == 0) {
                        premiereLigne = i + 1;
                        premiereColonne = j + 1;
                    }
                }
            }
        }

        if (differences == 0) {
            resultats[2] = "3 CAPTURES OK";
        } else {
            resultats[2] = "3 CAPTURES ECHEC " +
                           to_string(differences) + " " +
                           to_string(premiereLigne) + " " +
                           to_string(premiereColonne);

            preuveEchouee = 3;
        }

        coutTotal += 180;
    } else {
        resultats[2] = "3 CAPTURES NON_JOUEE";
    }

    // Preuve 4 : usage (600 secondes).
    if (preuveEchouee == 0) {
        if (usage == "RAS") {
            resultats[3] = "4 USAGE OK";
        } else {
            resultats[3] = "4 USAGE ECHEC";
            preuveEchouee = 4;
        }

        coutTotal += 600;
    } else {
        resultats[3] = "4 USAGE NON_JOUEE";
    }

    for (const string& resultat : resultats) {
        cout << resultat << '\n';
    }

    cout << "COUT " << coutTotal << '\n';

    if (preuveEchouee == 0) {
        cout << "VERDICT RIEN_CASSE\n";
    } else {
        cout << "VERDICT CASSE " << preuveEchouee << '\n';
    }

    return 0;
}