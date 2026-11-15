#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Image
{
    string nom;
    double x, y;
    double largeur, hauteur;
    double echelle;
};

bool touche(const Image& image, double px, double py)
{
    double demiLargeur = image.largeur * image.echelle / 2.0;
    double demiHauteur = image.hauteur * image.echelle / 2.0;

    return abs(px - image.x) <= demiLargeur
        && abs(py - image.y) <= demiHauteur;
}

int main()
{
    int N;
    cin >> N;

    vector<Image> images(N);

    for (int i = 0; i < N; i++)
    {
        cin >> images[i].nom
            >> images[i].x
            >> images[i].y
            >> images[i].largeur
            >> images[i].hauteur
            >> images[i].echelle;
    }

    int Q;
    cin >> Q;

    int erreurs = 0;

    for (int k = 1; k <= Q; k++)
    {
        double px, py;
        cin >> px >> py;

        string arriere = "AUCUN";
        string endroit = "AUCUN";

        // Recherche à rebours : dernière image vers première.
        for (int i = N - 1; i >= 0; i--)
        {
            if (touche(images[i], px, py))
            {
                arriere = images[i].nom;
                break;
            }
        }

        // Recherche à l'endroit : première image vers dernière.
        for (int i = 0; i < N; i++)
        {
            if (touche(images[i], px, py))
            {
                endroit = images[i].nom;
                break;
            }
        }

        if (arriere != endroit)
            erreurs++;

        cout << "CLIC " << k << " "
             << arriere << " " << endroit << "\n";
    }

    cout << "ERREURS " << erreurs << "\n";

    return 0;
}