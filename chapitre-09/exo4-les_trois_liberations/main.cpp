#include <iostream>
#include <vector>
using namespace std;

int main() {
    int S, V, F;
    cin >> S >> V >> F;

    int N;
    cin >> N;

    vector<int> tableau;
    vector<bool> liberees;

    int creees = 0;

    for (int i = 1; i <= N; i++) {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE") {
            creees++;
            tableau.push_back(creees);
            liberees.push_back(false);
        }

        else if (operation == "SUPPRIME") {
            int index;
            cin >> index;

            int texture = tableau[index];

            for (int j = 0; j < S; j++) {
                if (liberees[texture - 1]) {
                    cout << "PLANTAGE " << i << " TEXTURE " << texture << '\n';
                    return 0;
                }

                liberees[texture - 1] = true;
            }

            tableau.erase(tableau.begin() + index);
        }

        else if (operation == "VIDE") {
            for (size_t j = 0; j < tableau.size(); j++) {
                int texture = tableau[j];

                for (int k = 0; k < V; k++) {
                    if (liberees[texture - 1]) {
                        cout << "PLANTAGE " << i << " TEXTURE " << texture << '\n';
                        return 0;
                    }

                    liberees[texture - 1] = true;
                }
            }

            tableau.clear();
        }
    }

    // Libérations à la fin du programme.
    for (size_t i = 0; i < tableau.size(); i++) {
        int texture = tableau[i];

        for (int j = 0; j < F; j++) {
            if (liberees[texture - 1]) {
                cout << "PLANTAGE FIN TEXTURE " << texture << '\n';
                return 0;
            }

            liberees[texture - 1] = true;
        }
    }

    // Compter les textures perdues.
    int fuites = 0;

    for (int i = 0; i < creees; i++) {
        if (!liberees[i]) {
            fuites++;
        }
    }

    cout << "CREEES " << creees << '\n';
    cout << "FUITES " << fuites << '\n';
    cout << "PERDUES";

    if (fuites == 0) {
        cout << " AUCUN";
    }
    else {
        for (int i = 0; i < creees; i++) {
            if (!liberees[i]) {
                cout << " " << i + 1;
            }
        }
    }

    cout << '\n';

    return 0;
}