#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Modification {
    string nom;
    long long lignes = 0;
    long long contacts = 0;
    long long touchees = 0;

    long long risque() const {
        return contacts + touchees;
    }

    string verdict() const {
        return touchees == 0 ? "AJOUT" : "MODIFICATION";
    }
};

int main() {
    vector<Modification> modifications;

    Modification* modificationCourante = nullptr;

    bool fichierExistant = false;
    bool dansBloc = false;

    string ligne;

    while (getline(cin, ligne)) {
        if (ligne.empty()) {
            continue;
        }

        istringstream flux(ligne);
        string premierMot;
        flux >> premierMot;

        if (premierMot == "PATCH") {
            string nom;
            flux >> nom;

            modifications.push_back(Modification{});
            modificationCourante = &modifications.back();
            modificationCourante->nom = nom;

            fichierExistant = false;
            dansBloc = false;
        }
        else if (premierMot == "FICHIER") {
            string nomFichier;
            string type;

            flux >> nomFichier >> type;

            fichierExistant = (type == "EXISTANT");
            dansBloc = false;
        }
        else if (modificationCourante != nullptr) {
            char signe = ligne[0];

            if (signe == '+') {
                modificationCourante->lignes++;

                if (fichierExistant && !dansBloc) {
                    modificationCourante->contacts++;
                    dansBloc = true;
                }
            }
            else if (signe == '-') {
                modificationCourante->lignes++;

                if (fichierExistant) {
                    modificationCourante->touchees++;

                    if (!dansBloc) {
                        modificationCourante->contacts++;
                        dansBloc = true;
                    }
                }
            }
            else if (signe == '=') {
                dansBloc = false;
            }
        }
    }

    if (modifications.empty()) {
        cout << "AUCUN\n";
        return 0;
    }

    size_t indicePlusSur = 0;
    size_t indicePlusCourt = 0;

    for (size_t i = 0; i < modifications.size(); i++) {
        const Modification& m = modifications[i];

        cout << m.nom
             << " LIGNES " << m.lignes
             << " CONTACTS " << m.contacts
             << " TOUCHEES " << m.touchees
             << " RISQUE " << m.risque()
             << " VERDICT " << m.verdict()
             << '\n';

        if (m.risque() < modifications[indicePlusSur].risque()) {
            indicePlusSur = i;
        }

        if (m.lignes < modifications[indicePlusCourt].lignes) {
            indicePlusCourt = i;
        }
    }

    cout << "LE_PLUS_SUR "
         << modifications[indicePlusSur].nom << '\n';

    cout << "LE_PLUS_COURT "
         << modifications[indicePlusCourt].nom << '\n';

    return 0;
}