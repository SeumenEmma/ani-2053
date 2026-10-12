#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Caractere {
    long long avance;
    long long x0, y0, x1, y1;
};

struct Rectangle {
    long long minx, miny, maxx, maxy;
};

int main() {
    int G;
    cin >> G;

    map<char, Caractere> table;

    for (int i = 0; i < G; i++) {
        char c;
        Caractere car;

        cin >> c >> car.avance
            >> car.x0 >> car.y0
            >> car.x1 >> car.y1;

        table[c] = car;
    }

    int K;
    cin >> K;

    map<string, long long> crenage;

    for (int i = 0; i < K; i++) {
        string couple;
        long long correction;

        cin >> couple >> correction;
        crenage[couple] = correction;
    }

    string texte;
    long long ox, oy;
    cin >> texte >> ox >> oy;

    long long x = ox;
    int absents = 0;
    bool dessin = false;

    Rectangle boite;

    for (int i = 0; i < (int)texte.size(); i++) {
        char c = texte[i];

        if (table.find(c) == table.end()) {
            cout << c << " ABSENT" << endl;
            absents++;
            continue;
        }

        cout << c << " " << x << endl;

        Caractere car = table[c];

        if (car.x1 > car.x0 && car.y1 > car.y0) {
            Rectangle r;

            r.minx = x + car.x0;
            r.miny = oy + car.y0;
            r.maxx = x + car.x1;
            r.maxy = oy + car.y1;

            if (!dessin) {
                boite = r;
                dessin = true;
            } else {
                if (r.minx < boite.minx)
                    boite.minx = r.minx;

                if (r.miny < boite.miny)
                    boite.miny = r.miny;

                if (r.maxx > boite.maxx)
                    boite.maxx = r.maxx;

                if (r.maxy > boite.maxy)
                    boite.maxy = r.maxy;
            }
        }

        x = x + car.avance;

        if (i + 1 < (int)texte.size()) {
            string couple = "";
            couple += c;
            couple += texte[i + 1];

            if (crenage.find(couple) != crenage.end()) {
                x = x + crenage[couple];
            }
        }
    }

    cout << "CURSEUR " << x << endl;

    if (!dessin) {
        cout << "BOITE AUCUNE" << endl;
        cout << "MONTE 0" << endl;
        cout << "DESCEND 0" << endl;
        cout << "ECRAN RIEN" << endl;
    } else {
        cout << "BOITE "
             << boite.minx << " "
             << boite.miny << " "
             << boite.maxx << " "
             << boite.maxy << endl;

        long long monte = 0;
        long long descend = 0;

        if (boite.miny < oy)
            monte = oy - boite.miny;

        if (boite.maxy > oy)
            descend = boite.maxy - oy;

        cout << "MONTE " << monte << endl;
        cout << "DESCEND " << descend << endl;

        if (boite.maxy <= 0) {
            cout << "ECRAN HORS" << endl;
        } else if (boite.miny < 0) {
            cout << "ECRAN COUPE" << endl;
        } else {
            cout << "ECRAN VISIBLE" << endl;
        }
    }

    cout << "ABSENTS " << absents << endl;

    return 0;
}
