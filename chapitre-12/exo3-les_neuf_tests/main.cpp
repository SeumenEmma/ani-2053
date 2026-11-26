#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Composant {
    long long intervalle = 0;
    long long temps = 0;
    bool change = false;
    unordered_set<string> fautes;

    bool a(const string& faute) const {
        return fautes.find(faute) != fautes.end();
    }

    void Touch() {
        if (a("DEPUIS_MODIF")) {
            temps = 0;
        }

        change = true;
    }

    bool Tick(long long d) {
        if (a("ZERO_IGNORE") && d <= 0) {
            return false;
        }

        if (d > 0 || (a("NEGATIF_COMPTE") && d < 0)) {
            temps += d;
        }

        bool conditionChange = a("SANS_SALETE") || change;

        if (!conditionChange) {
            return false;
        }

        if (a("STRICT")) {
            return temps > intervalle;
        }

        return temps >= intervalle;
    }

    void Saved() {
        if (!a("SAVED_GARDE_SALETE")) {
            change = false;
        }

        if (!a("SAVED_GARDE_TEMPS")) {
            temps = 0;
        }
    }
};

string Secours(const string& doc,
               const unordered_set<string>& fautes) {
    if (fautes.find("SECOURS_FIXE") != fautes.end()) {
        return "secours.nkref.auto";
    }

    if (fautes.find("SECOURS_EST_DOC") != fautes.end()) {
        return doc;
    }

    if (fautes.find("SANS_NOM_VIDE") != fautes.end()
        && doc.empty()) {
        return "";
    }

    if (doc.empty()) {
        return "planche-sans-nom.nkref.auto";
    }

    return doc + ".auto";
}

vector<int> executerTests(const unordered_set<string>& fautes) {
    vector<int> echecs;

    // Test 1
    {
        Composant c;
        c.fautes = fautes;
        c.intervalle = 60;
        bool reussi = true;

        for (int i = 0; i < 3600; i++) {
            if (c.Tick(1)) {
                reussi = false;
            }
        }

        if (!reussi) {
            echecs.push_back(1);
        }
    }

    // Tests 2 et 3 : même composant
    {
        Composant c;
        c.fautes = fautes;
        c.intervalle = 60;
        c.Touch();

        bool reussi2 = true;

        for (int i = 0; i < 59; i++) {
            if (c.Tick(1)) {
                reussi2 = false;
            }
        }

        if (!reussi2) {
            echecs.push_back(2);
        }

        if (!c.Tick(1)) {
            echecs.push_back(3);
        }
    }

    // Tests 4 et 5 : même composant
    {
        Composant c;
        c.fautes = fautes;
        c.intervalle = 60;
        c.Touch();

        // Le résultat du 60e Tick doit être vrai.
        for (int i = 0; i < 60; i++) {
            c.Tick(1);
        }

        c.Saved();

        // Test 4 : aucun des 120 appels ne doit répondre vrai.
        bool reussi4 = true;

        for (int i = 0; i < 120; i++) {
            if (c.Tick(1)) {
                reussi4 = false;
            }
        }

        if (!reussi4) {
            echecs.push_back(4);
        }

        // Test 5 : après Touch, Tick(0) doit répondre vrai.
        c.Touch();

        if (!c.Tick(0)) {
            echecs.push_back(5);
        }
    }

    // Test 6
    {
        Composant c;
        c.fautes = fautes;
        c.intervalle = 10;
        c.Touch();
        c.Saved();

        bool reussi = true;

        for (int i = 0; i < 100; i++) {
            if (c.Tick(1)) {
                reussi = false;
            }
        }

        if (!reussi) {
            echecs.push_back(6);
        }
    }

    // Tests 7, 8 et 9 : nom du secours
    {
        const string doc = "D:/planches/personnages.nkref";
        const string secours = Secours(doc, fautes);

        if (secours == doc) {
            echecs.push_back(7);
        }

        if (secours.compare(0, doc.size(), doc) != 0) {
            echecs.push_back(8);
        }

        const string secoursSansNom = Secours("", fautes);

        if (secoursSansNom.empty()) {
            echecs.push_back(9);
        }
    }

    return echecs;
}

int main() {
    string ligne;

    int detectes = 0;
    int nonDetectes = 0;

    vector<string> anglesMorts;

    while (getline(cin, ligne)) {
        if (ligne.empty()) {
            continue;
        }

        istringstream flux(ligne);

        string nom;
        flux >> nom;

        unordered_set<string> fautes;

        string faute;

        while (flux >> faute) {
            if (faute != "AUCUN") {
                fautes.insert(faute);
            }
        }

        vector<int> echecs = executerTests(fautes);

        cout << nom;

        if (echecs.empty()) {
            cout << " PASSE\n";

            if (!fautes.empty()) {
                nonDetectes++;
                anglesMorts.push_back(nom);
            }
        } else {
            cout << " ECHOUE";

            for (int numero : echecs) {
                cout << " " << numero;
            }

            cout << "\n";

            if (!fautes.empty()) {
                detectes++;
            }
        }
    }

    cout << "DETECTES " << detectes << "\n";
    cout << "NON_DETECTES " << nonDetectes << "\n";

    cout << "ANGLE_MORT";

    if (anglesMorts.empty()) {
        cout << " AUCUN";
    } else {
        for (const string& nom : anglesMorts) {
            cout << " " << nom;
        }
    }

    cout << "\n";

    return 0;
}