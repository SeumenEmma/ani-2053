#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int restent = 0;
    int changes = 0;

    for (int i = 1; i <= n; ++i)
    {
        int id;
        double x, y, echelle, rotation, opacite;
        int miroirX, miroirY;
        int largeur, hauteur;
        int selectionne;
        string chemin;
        long long octets;

        // Lire les treize champs de l'image.
        cin >> id
            >> x >> y
            >> echelle >> rotation >> opacite
            >> miroirX >> miroirY
            >> largeur >> hauteur
            >> selectionne
            >> chemin
            >> octets;

        // Une image sans octets ne peut pas être rouverte.
        if (octets == 0)
        {
            cout << "ITEM " << i << " SAUTE\n";
            continue;
        }

        // L'image est rouverte : sa nouvelle position est calculée.
        ++restent;

        cout << "ITEM " << i << " " << restent;

        bool change = false;

        // L'identifiant revient à 0.
        if (id != 0)
        {
            cout << " id";
            ++changes;
            change = true;
        }

        // La sélection revient à 0.
        if (selectionne != 0)
        {
            cout << " selected";
            ++changes;
            change = true;
        }

        // Le chemin revient vide.
        if (chemin != "-")
        {
            cout << " sourcePath";
            ++changes;
            change = true;
        }

        if (!change)
        {
            cout << " AUCUN";
        }

        cout << '\n';
    }

    cout << "RESTENT " << restent << '\n';
    cout << "CHANGES " << changes << '\n';

    return 0;
}