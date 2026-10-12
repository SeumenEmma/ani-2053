#include <iostream>
#include <string>
using namespace std;

int main() {
    long long S;
    int N;
    cin >> S;
    cin >> N;

    long long totalMemoire = 0;
    int nombreFlux = 0;
    int nombreRefuses = 0;

    for (int i = 0; i < N; i++) {
        string nom;
        long long frequence, canaux, bits, duree, fichier;

        cin >> nom >> frequence >> canaux
            >> bits >> duree >> fichier;

        if (bits != 8 && bits != 16 &&
            bits != 24 && bits != 32) {

            cout << nom << " REFUSE" << endl;
            nombreRefuses++;
        } else {
            long long brut = frequence * canaux
                           * (bits / 8) * duree / 1000;

            long long pourcent = fichier * 100 / brut;

            if (brut > S) {
                cout << nom << " "
                     << brut << " "
                     << pourcent << " FLUX" << endl;

                nombreFlux++;
            } else {
                cout << nom << " "
                     << brut << " "
                     << pourcent << " MEMOIRE" << endl;

                totalMemoire = totalMemoire + brut;
            }
        }
    }

    cout << "MEMOIRE " << totalMemoire << endl;
    cout << "FLUX " << nombreFlux << endl;
    cout << "REFUSES " << nombreRefuses << endl;

    return 0;
}
