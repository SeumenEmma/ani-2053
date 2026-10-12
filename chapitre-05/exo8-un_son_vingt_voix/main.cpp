#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long D, C;
    int N;
    cin >> D >> C;
    cin >> N;

    vector<long long> temps(N);

    for (int i = 0; i < N; i++) {
        cin >> temps[i];
    }

    long long voixMax = 0;
    long long retardMax = 0;
    int coupes = 0;

    long long finChargement = 0;

    for (int i = 0; i < N; i++) {
        long long t = temps[i];

        long long voix = 0;

        for (int j = 0; j <= i; j++) {
            if (temps[j] + D > t) {
                voix++;
            }
        }

        long long debutChargement = t;

        if (finChargement > debutChargement) {
            debutChargement = finChargement;
        }

        finChargement = debutChargement + C;

        long long retard = finChargement - t;

        if (voix > voixMax) {
            voixMax = voix;
        }

        if (retard > retardMax) {
            retardMax = retard;
        }

        string etat = "ENTIER";

        if (i + 1 < N) {
            if (temps[i + 1] < t + D) {
                etat = "COUPE";
                coupes++;
            }
        }

        cout << t << " "
             << voix << " "
             << retard << " "
             << etat << endl;
    }

    cout << "VOIX_MAX " << voixMax << endl;
    cout << "RETARD_MAX " << retardMax << endl;
    cout << "COUPES " << coupes << endl;

    return 0;
}
