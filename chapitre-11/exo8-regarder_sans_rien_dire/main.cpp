#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Contournement {
    string nom;
    long long fois;
    long long premiereObservation;
    long long ordreEntree;
};

int convertirEnSecondes(const string& heure) {
    size_t separateur = heure.find(':');

    int minutes = stoi(heure.substr(0, separateur));
    int secondes = stoi(heure.substr(separateur + 1));

    return minutes * 60 + secondes;
}

int main() {
    string mot;
    long long n;

    cin >> mot >> n;

    vector<Contournement> contournements;
    unordered_map<string, size_t> indexParNom;

    long long horsSeance = 0;
    long long ordre = 0;

    for (long long i = 0; i < n; i++) {
        string heure;
        string nom;

        cin >> heure >> nom;

        int instant = convertirEnSecondes(heure);

        if (instant > 20 * 60) {
            horsSeance++;
            continue;
        }

        auto recherche = indexParNom.find(nom);

        if (recherche == indexParNom.end()) {
            size_t index = contournements.size();

            indexParNom[nom] = index;

            contournements.push_back({
                nom,
                1,
                instant,
                ordre
            });
        }
        else {
            Contournement& element =
                contournements[recherche->second];

            element.fois++;

            if (instant < element.premiereObservation) {
                element.premiereObservation = instant;
            }
        }

        ordre++;
    }

    long long m;
    cin >> mot >> m;

    unordered_set<string> nomsDits;
    vector<string> nomsCites;

    for (long long i = 0; i < m; i++) {
        string nom;
        cin >> nom;

        nomsDits.insert(nom);
        nomsCites.push_back(nom);
    }

    sort(
        contournements.begin(),
        contournements.end(),
        [](const Contournement& a, const Contournement& b) {
            if (a.fois != b.fois) {
                return a.fois > b.fois;
            }

            if (a.premiereObservation != b.premiereObservation) {
                return a.premiereObservation < b.premiereObservation;
            }

            return a.ordreEntree < b.ordreEntree;
        }
    );

    long long nonDits = 0;
    long long totalObservations = 0;
    long long observationsNonDites = 0;

    for (const Contournement& element : contournements) {
        totalObservations += element.fois;

        bool estDit = nomsDits.count(element.nom) > 0;

        cout << element.nom << " "
             << element.fois << " "
             << (estDit ? "DIT" : "NON_DIT")
             << '\n';

        if (!estDit) {
            nonDits++;
            observationsNonDites += element.fois;
        }
    }

    long long partNonDite = 0;

    if (totalObservations > 0) {
        partNonDite =
            (100 * observationsNonDites) / totalObservations;
    }

    vector<string> ditsSansVu;

    for (const string& nom : nomsCites) {
        if (indexParNom.find(nom) == indexParNom.end()) {
            ditsSansVu.push_back(nom);
        }
    }

    cout << "NON_DITS " << nonDits << '\n';

    cout << "PART_NON_DITE " << partNonDite << '\n';

    cout << "DIT_SANS_VU";

    if (ditsSansVu.empty()) {
        cout << " AUCUN";
    }
    else {
        for (const string& nom : ditsSansVu) {
            cout << " " << nom;
        }
    }

    cout << '\n';

    cout << "HORS_SEANCE " << horsSeance << '\n';

    return 0;
}