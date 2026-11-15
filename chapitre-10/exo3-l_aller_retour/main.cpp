#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

void afficher2(double valeur)
{
    if (round(valeur * 100.0) == 0.0)
        valeur = 0.0;

    cout << fixed << setprecision(2) << valeur;
}

int main()
{
    double W, H;

    if (!(cin >> W >> H))
        return 0;

    double cx = 0.0;
    double cy = 0.0;
    double zoom = 1.0;

    string commande;

    while (cin >> commande)
    {
        if (commande == "VERS_MONDE")
        {
            double px, py;
            cin >> px >> py;

            double x = cx + (px - W / 2.0) / zoom;
            double y = cy + (py - H / 2.0) / zoom;

            cout << "MONDE ";
            afficher2(x);
            cout << " ";
            afficher2(y);
            cout << "\n";
        }
        else if (commande == "VERS_PIXEL")
        {
            double mx, my;
            cin >> mx >> my;

            double x = (mx - cx) * zoom + W / 2.0;
            double y = (my - cy) * zoom + H / 2.0;

            cout << "PIXEL ";
            afficher2(x);
            cout << " ";
            afficher2(y);
            cout << "\n";
        }
        else if (commande == "DEPLACE")
        {
            double dx, dy;
            cin >> dx >> dy;

            cx -= dx / zoom;
            cy -= dy / zoom;
        }
        else if (commande == "ZOOM")
        {
            double f, px, py;
            cin >> f >> px >> py;

            double ax = cx + (px - W / 2.0) / zoom;
            double ay = cy + (py - H / 2.0) / zoom;

            zoom = clamp(zoom * f, 0.02, 64.0);

            cx = ax - (px - W / 2.0) / zoom;
            cy = ay - (py - H / 2.0) / zoom;
        }
        else if (commande == "GRILLE")
        {
            double m;
            cin >> m;

            double s = 1.0;

            while (s * zoom < m)
                s *= 2.0;

            while (s * 0.5 * zoom >= m)
                s *= 0.5;

            cout << "GRILLE " << fixed << setprecision(6) << s << "\n";
        }
        else if (commande == "ORIGINE")
        {
            cx = 0.0;
            cy = 0.0;
            zoom = 1.0;
        }
    }

    cout << "CENTRE ";
    afficher2(cx);
    cout << " ";
    afficher2(cy);
    cout << "\n";

    cout << "ZOOM ";
    afficher2(zoom);
    cout << "\n";

    return 0;
}