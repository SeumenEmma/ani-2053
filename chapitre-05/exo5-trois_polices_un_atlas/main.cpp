#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Police {
    string nom;
    long long n, w, h;
};

struct Position {
    long long x1, y1, x2, y2;
};

int main() {
    long long P, L;
    cin >> P >> L;
    int G;
    cin >> G;

    if (G == 0) {
        cout << "AUCUN" << endl;
        return 0;
    }

    vector<Police> polices(G);
    vector<Position> positions(G);

    for (int i = 0; i < G; i++) {
        cin >> polices[i].nom
            >> polices[i].n
            >> polices[i].w
            >> polices[i].h;
    }

    long long besoin = 0;
    long long occupe = 0;

    for (int i = 0; i < G; i++) {
        besoin = besoin + polices[i].n
                 * (polices[i].w + P)
                 * (polices[i].h + P);

        occupe = occupe + polices[i].n
                 * polices[i].w
                 * polices[i].h;
    }

    long long W = L;

    if (W == 0) {
        W = 512;

        while (W * W < 2 * besoin && W < 4096) {
            W = W * 2;
        }
    }

    long long H = W;

    for (int essai = 1; essai <= 8; essai++) {
        long long x = P;
        long long y = P;
        long long hauteur = 0;

        bool reussi = true;

        for (int i = 0; i < G; i++) {
            long long rw = polices[i].w + P;
            long long rh = polices[i].h + P;

            for (long long j = 0; j < polices[i].n; j++) {

                if (x + rw > W - P) {
                    x = P;
                    y = y + hauteur + P;
                    hauteur = 0;

                    if (x + rw > W - P) {
                        reussi = false;
                        break;
                    }
                }

                if (y + rh > H - P) {
                    reussi = false;
                    break;
                }

                if (j == 0) {
                    positions[i].x1 = x;
                    positions[i].y1 = y;
                }

                positions[i].x2 = x;
                positions[i].y2 = y;

                x = x + rw;

                if (rh > hauteur) {
                    hauteur = rh;
                }
            }

            if (!reussi) {
                break;
            }
        }

        if (reussi) {
            cout << "ESSAIS " << essai << endl;
            cout << "TEXTURE " << W << " " << H << endl;

            for (int i = 0; i < G; i++) {
                cout << polices[i].nom << " "
                     << positions[i].x1 << " "
                     << positions[i].y1 << " "
                     << positions[i].x2 << " "
                     << positions[i].y2 << endl;
            }

            long long surface = W * H;
            long long perdu = (surface - occupe) * 100 / surface;

            cout << "OCCUPE " << occupe << endl;
            cout << "PERDU " << perdu << endl;

            return 0;
        }

        if (W == H) {
            W = W * 2;
        } else {
            H = W;
        }
    }

    cout << "ESSAIS 8" << endl;
    cout << "ECHEC" << endl;

    return 0;
}