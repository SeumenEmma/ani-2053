#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    vector<string> pileUtilisateur;
    vector<int> traitsOutil;

    string ligne;
    int numeroTrait = 0;
    int numeroAnnulation = 0;

    int justes = 0;
    int riens = 0;
    int trahis = 0;
    int operations = 0;
    int annulables = 0;

    while (getline(cin, ligne)) {
        if (ligne.empty()) {
            continue;
        }

        istringstream flux(ligne);
        string commande;
        string nom;

        flux >> commande;

        if (commande == "ANNULE") {
            numeroAnnulation++;

            string attendu = "AUCUNE";

            if (!pileUtilisateur.empty()) {
                attendu = pileUtilisateur.back();
                pileUtilisateur.pop_back();
            }

            string obtenu = "RIEN";

            if (!traitsOutil.empty()) {
                obtenu = "TRAIT " + to_string(traitsOutil.back());
                traitsOutil.pop_back();
            }

            string verdict;

            if (obtenu == attendu ||
                (attendu == "AUCUNE" && obtenu == "RIEN")) {
                verdict = "JUSTE";
                justes++;
            }
            else if (obtenu == "RIEN") {
                verdict = "RIEN";
                riens++;
            }
            else {
                verdict = "TRAHI";
                trahis++;
            }

            cout << "ANNULE " << numeroAnnulation
                 << " ATTENDU " << attendu
                 << " OBTENU " << obtenu
                 << " " << verdict << '\n';
        }
        else {
            operations++;

            if (commande == "DEPOSE" ||
                commande == "DEPLACE" ||
                commande == "SUPPRIME" ||
                commande == "MIROIR") {

                flux >> nom;
                pileUtilisateur.push_back(commande + " " + nom);
            }
            else if (commande == "TRAIT") {
                numeroTrait++;
                annulables++;

                pileUtilisateur.push_back(
                    "TRAIT " + to_string(numeroTrait)
                );

                traitsOutil.push_back(numeroTrait);
            }
            else if (commande == "RANGE") {
                pileUtilisateur.push_back("RANGE");
            }
            else if (commande == "EFFACE") {
                pileUtilisateur.push_back("EFFACE");
                traitsOutil.clear();
            }
        }
    }

    cout << "JUSTES " << justes << '\n';
    cout << "RIENS " << riens << '\n';
    cout << "TRAHIS " << trahis << '\n';
    cout << "ANNULABLES " << annulables
         << " SUR " << operations << '\n';

    return 0;
}