#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <charconv>

using namespace std;

struct Action {
    long long numero;
    int ordre;
    string contenu;
    bool capture;
};

bool lireNombre(const string& texte, long long& nombre) {
    if (texte.empty()) {
        return false;
    }

    const char* debut = texte.data();
    const char* fin = debut + texte.size();

    if (*debut == '+') {
        ++debut;
        if (debut == fin) {
            return false;
        }
    }

    auto resultat = from_chars(debut, fin, nombre);

    return resultat.ec == errc() && resultat.ptr == fin;
}

vector<string> decouper(const string& texte, char separateur) {
    vector<string> champs;
    size_t debut = 0;

    while (true) {
        size_t position = texte.find(separateur, debut);

        if (position == string::npos) {
            champs.push_back(texte.substr(debut));
            break;
        }

        champs.push_back(texte.substr(debut, position - debut));
        debut = position + 1;
    }

    return champs;
}

int main() {
    vector<Action> actions;

    long long ignores = 0;
    long long jamais = 0;

    long long sortie = 0;
    bool sortieValide = false;

    int capturesGardees = 0;
    int depotsGardes = 0;
    int clicsGardes = 0;

    string ligne;

    while (getline(cin, ligne)) {
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }

        size_t egal = ligne.find('=');

        if (egal == string::npos) {
            ignores++;
            continue;
        }

        string nom = ligne.substr(0, egal);
        string valeur = ligne.substr(egal + 1);

        if (nom == "NK_AGENT_SHOT") {
            vector<string> elements = decouper(valeur, ',');

            for (const string& element : elements) {
                long long numero;

                if (!lireNombre(element, numero)) {
                    ignores++;
                    continue;
                }

                if (capturesGardees >= 8) {
                    ignores++;
                    continue;
                }

                capturesGardees++;

                actions.push_back({
                    numero,
                    7,
                    "CAPTURE",
                    true
                });
            }
        }

        else if (nom == "NK_AGENT_EXIT") {
            long long numero;

            if (!lireNombre(valeur, numero)) {
                ignores++;
                continue;
            }

            sortie = numero;
            sortieValide = true;
        }

        else if (nom == "NK_AGENT_PAN" ||
                 nom == "NK_AGENT_MOVE" ||
                 nom == "NK_AGENT_ZOOM" ||
                 nom == "NK_AGENT_GRID" ||
                 nom == "NK_AGENT_PACK") {

            vector<string> champs = decouper(valeur, ':');
            if (nom == "NK_AGENT_PACK" && champs.size() != 1) {
                ignores++;
                continue;
            }
            int minimumChamps = 1;
            int ordre = 0;
            string type;

            if (nom == "NK_AGENT_PAN") {
                minimumChamps = 3;
                ordre = 0;
                type = "PAN";
            }
            else if (nom == "NK_AGENT_ZOOM") {
                minimumChamps = 4;
                ordre = 1;
                type = "ZOOM";
            }
            else if (nom == "NK_AGENT_MOVE") {
                minimumChamps = 3;
                ordre = 4;
                type = "MOVE";
            }
            else if (nom == "NK_AGENT_PACK") {
                minimumChamps = 1;
                ordre = 5;
                type = "RANGE";
            }
            else {
                minimumChamps = 2;
                ordre = 6;
                type = "GRILLE";
            }

            if (static_cast<int>(champs.size()) < minimumChamps) {
                ignores++;
                continue;
            }

            long long numero;

            if (!lireNombre(champs[0], numero)) {
                ignores++;
                continue;
            }

            string contenu = type;

            for (int i = 1; i < minimumChamps; i++) {
                contenu += " " + champs[i];
            }

            actions.push_back({
                numero,
                ordre,
                contenu,
                false
            });
        }

        else if (nom == "NK_AGENT_DROP") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& element : elements) {
                size_t premier = element.find(':');
                size_t deuxieme = element.find(':', premier == string::npos ? 0 : premier + 1);
                size_t troisieme = element.find(':', deuxieme == string::npos ? 0 : deuxieme + 1);

                if (premier == string::npos ||
                    deuxieme == string::npos ||
                    troisieme == string::npos) {
                    ignores++;
                    continue;
                }

                string champNumero = element.substr(0, premier);
                string px = element.substr(premier + 1, deuxieme - premier - 1);
                string py = element.substr(deuxieme + 1, troisieme - deuxieme - 1);
                string chemin = element.substr(troisieme + 1);

                long long numero;

                if (!lireNombre(champNumero, numero)) {
                    ignores++;
                    continue;
                }

                if (depotsGardes >= 8) {
                    ignores++;
                    continue;
                }

                depotsGardes++;

                actions.push_back({
                    numero,
                    2,
                    "DEPOT " + chemin + " " + px + " " + py,
                    false
                });
            }
        }

        else if (nom == "NK_AGENT_CLICK") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& element : elements) {
                vector<string> champs = decouper(element, ':');

                if (champs.size() < 3) {
                    ignores++;
                    continue;
                }

                long long numero;

                if (!lireNombre(champs[0], numero)) {
                    ignores++;
                    continue;
                }

                if (clicsGardes >= 8) {
                    ignores++;
                    continue;
                }

                clicsGardes++;

                actions.push_back({
                    numero,
                    3,
                    "CLIC " + champs[1] + " " + champs[2],
                    false
                });
            }
        }

        else {
            ignores++;
        }
    }

    vector<Action> evenements;

    for (const Action& action : actions) {
        bool aLieu = false;

        if (action.capture) {
            aLieu = action.numero > 0 &&
                    (!sortieValide || sortie <= 0 ||
                     action.numero <= sortie);
        }
        else {
            aLieu = action.numero > 0 &&
                    (!sortieValide || sortie <= 0 ||
                     action.numero < sortie);
        }

        if (!aLieu) {
            jamais++;
            continue;
        }

        Action evenement = action;

        if (evenement.capture) {
            evenement.numero--;
        }

        evenements.push_back(evenement);
    }

    stable_sort(
        evenements.begin(),
        evenements.end(),
        [](const Action& a, const Action& b) {
            if (a.numero != b.numero) {
                return a.numero < b.numero;
            }

            return a.ordre < b.ordre;
        }
    );

    for (const Action& evenement : evenements) {
        cout << "TOUR "
             << evenement.numero
             << " "
             << evenement.contenu
             << '\n';
    }

    if (sortieValide && sortie > 0) {
        cout << "ARRET " << sortie - 1 << '\n';
    }
    else {
        cout << "SANS_ARRET\n";
    }

    cout << "JAMAIS " << jamais << '\n';
    cout << "IGNORES " << ignores << '\n';

    return 0;
}