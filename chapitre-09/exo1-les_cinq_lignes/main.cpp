#include <iostream>
#include <string>
#include <array>

using namespace std;

enum Etat {
    ABSENT,
    ECRIT,
    DEFAUT,
    SUPPRIME
};

int main() {
    string classe;
    getline(cin, classe);

    array<Etat, 5> etats = {
        ABSENT, ABSENT, ABSENT, ABSENT, ABSENT
    };

    string ligne;

    while (getline(cin, ligne)) {
        // Couper la ligne au premier commentaire
        size_t commentaire = ligne.find("//");
        if (commentaire != string::npos) {
            ligne = ligne.substr(0, commentaire);
        }

        // Retirer toutes les espaces
        string s;
        for (char c : ligne) {
            if (c != ' ') {
                s += c;
            }
        }

        if (s.empty()) {
            continue;
        }

        // Reconnaître les cinq membres spéciaux
        int membre = -1;

        if (s.find("~" + classe + "(") != string::npos) {
            membre = 0;
        }
        else if (s.rfind(classe + "&operator=(const" + classe + "&", 0) == 0
                 && s.substr((classe + "&operator=(const" + classe + "&").size(), 1) != "&") {
            membre = 2;
        }
        else if (s.rfind(classe + "(const" + classe + "&", 0) == 0
                 && s.substr((classe + "(const" + classe + "&").size(), 1) != "&") {
            membre = 1;
        }
        else if (s.rfind(classe + "&operator=(" + classe + "&&", 0) == 0) {
            membre = 4;
        }
        else if (s.rfind(classe + "(" + classe + "&&", 0) == 0) {
            membre = 3;
        }

        if (membre != -1 && etats[membre] == ABSENT) {
            if (s.size() >= 8 && s.substr(s.size() - 8) == "=delete;") {
                etats[membre] = SUPPRIME;
            }
            else if (s.size() >= 9 && s.substr(s.size() - 9) == "=default;") {
                etats[membre] = DEFAUT;
            }
            else {
                etats[membre] = ECRIT;
            }
        }
    }

    const array<string, 5> noms = {
        "DESTRUCTEUR",
        "COPIE",
        "AFFECTATION_COPIE",
        "DEPLACEMENT",
        "AFFECTATION_DEPLACEMENT"
    };

    const array<string, 4> valeurs = {
        "ABSENT", "ECRIT", "DEFAUT", "SUPPRIME"
    };

    // Afficher les cinq états
    for (int i = 0; i < 5; i++) {
        cout << noms[i] << " " << valeurs[etats[i]] << '\n';
    }

    int declares = 0;
    for (Etat e : etats) {
        if (e != ABSENT) {
            declares++;
        }
    }

    bool trois = etats[0] != ABSENT
              && etats[1] != ABSENT
              && etats[2] != ABSENT
              && etats[3] == ABSENT
              && etats[4] == ABSENT;

    bool cinq = declares == 5;
    bool zero = declares == 0;
    bool deplacement = etats[3] != ABSENT || etats[4] != ABSENT;

    string regle;

    if (zero) {
        regle = "ZERO";
    }
    else if (cinq) {
        regle = "CINQ";
    }
    else if (trois) {
        regle = "TROIS";
    }
    else {
        regle = "INCOMPLETE";
    }

    cout << "REGLE " << regle << '\n';

    // Afficher les membres manquants si la règle est incomplète
    if (regle == "INCOMPLETE") {
        int limite = deplacement ? 5 : 3;

        for (int i = 0; i < limite; i++) {
            if (etats[i] == ABSENT) {
                cout << "MANQUE " << noms[i] << '\n';
            }
        }
    }

    cout << "POSSEDE "
         << (etats[0] == ECRIT ? "OUI" : "NON") << '\n';

    bool unique = etats[1] == SUPPRIME
               && (etats[3] == ECRIT || etats[3] == DEFAUT);

    cout << "UNIQUE " << (unique ? "OUI" : "NON") << '\n';

    return 0;
}