#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

class Lecteur
{
private:
    vector<uint8_t> octets;
    size_t position = 0;

public:
    Lecteur(const vector<uint8_t>& donnees)
        : octets(donnees)
    {
    }

    bool lireU8(uint8_t& valeur)
    {
        if (position >= octets.size())
            return false;

        valeur = octets[position++];
        return true;
    }

    bool lireU32(uint32_t& valeur)
    {
        if (octets.size() - position < 4)
            return false;

        valeur = static_cast<uint32_t>(octets[position])
            | (static_cast<uint32_t>(octets[position + 1]) << 8)
            | (static_cast<uint32_t>(octets[position + 2]) << 16)
            | (static_cast<uint32_t>(octets[position + 3]) << 24);

        position += 4;
        return true;
    }

    bool lireF32(float& valeur)
    {
        uint32_t bits;

        if (!lireU32(bits))
            return false;

        static_assert(sizeof(float) == sizeof(uint32_t));

        memcpy(&valeur, &bits, sizeof(valeur));
        return true;
    }

    bool sauter(size_t nombre)
    {
        if (nombre > octets.size() - position)
            return false;

        position += nombre;
        return true;
    }
};

string nombre(float valeur)
{
    double arrondi = round(static_cast<double>(valeur) * 100.0) / 100.0;

    if (arrondi == 0.0)
        arrondi = 0.0;

    ostringstream sortie;
    sortie << fixed << setprecision(2) << arrondi;
    return sortie.str();
}

int main()
{
    size_t T;

    if (!(cin >> T))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    vector<uint8_t> octets;
    octets.reserve(T);

    string hex;

    for (size_t i = 0; i < T; i++)
    {
        if (!(cin >> hex) || hex.size() != 2)
        {
            cout << "TRONQUE\n";
            return 0;
        }

        try
        {
            size_t position = 0;
            unsigned long valeur = stoul(hex, &position, 16);

            if (position != 2 || valeur > 255)
            {
                cout << "TRONQUE\n";
                return 0;
            }

            octets.push_back(static_cast<uint8_t>(valeur));
        }
        catch (...)
        {
            cout << "TRONQUE\n";
            return 0;
        }
    }

    Lecteur lecteur(octets);

    uint8_t magique[4];

    for (int i = 0; i < 4; i++)
    {
        if (!lecteur.lireU8(magique[i]))
        {
            cout << "TRONQUE\n";
            return 0;
        }
    }

    if (magique[0] != 0x4E || magique[1] != 0x4B
        || magique[2] != 0x52 || magique[3] != 0x46)
    {
        cout << "PAS_UNE_PLANCHE\n";
        return 0;
    }

    uint32_t version;

    if (!lecteur.lireU32(version))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    if (version != 1)
    {
        cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    ostringstream resultat;

    float cx, cy, zoom;

    if (!lecteur.lireF32(cx)
        || !lecteur.lireF32(cy)
        || !lecteur.lireF32(zoom))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    resultat << "VUE " << nombre(cx) << " "
             << nombre(cy) << " " << nombre(zoom) << "\n";

    uint8_t theme, grille, remplissage;

    if (!lecteur.lireU8(theme)
        || !lecteur.lireU8(grille)
        || !lecteur.lireU8(remplissage)
        || !lecteur.lireU8(remplissage))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    resultat << "THEME " << (theme != 0 ? "SOMBRE" : "CLAIR") << "\n";
    resultat << "GRILLE " << (grille == 0 ? "AFFICHEE" : "CACHEE") << "\n";

    uint32_t nombreImages;

    if (!lecteur.lireU32(nombreImages))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    resultat << "IMAGES " << nombreImages << "\n";

    for (uint32_t i = 0; i < nombreImages; i++)
    {
        float x, y, echelle, rotation, opacite;
        uint8_t mx, my, remplissage1, remplissage2;
        uint32_t largeur, hauteur, taille;

        if (!lecteur.lireF32(x)
            || !lecteur.lireF32(y)
            || !lecteur.lireF32(echelle)
            || !lecteur.lireF32(rotation)
            || !lecteur.lireF32(opacite)
            || !lecteur.lireU8(mx)
            || !lecteur.lireU8(my)
            || !lecteur.lireU8(remplissage1)
            || !lecteur.lireU8(remplissage2)
            || !lecteur.lireU32(largeur)
            || !lecteur.lireU32(hauteur)
            || !lecteur.lireU32(taille)
            || !lecteur.sauter(taille))
        {
            cout << "TRONQUE\n";
            return 0;
        }

        resultat << "IMAGE " << i + 1 << " "
                 << nombre(x) << " "
                 << nombre(y) << " "
                 << nombre(echelle) << " "
                 << nombre(rotation) << " "
                 << nombre(opacite) << " "
                 << (mx != 0 ? 1 : 0) << " "
                 << (my != 0 ? 1 : 0) << " "
                 << largeur << " "
                 << hauteur << " "
                 << taille << "\n";
    }

    uint32_t nombreTraits;

    if (!lecteur.lireU32(nombreTraits))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    resultat << "TRAITS " << nombreTraits << "\n";

    for (uint32_t i = 0; i < nombreTraits; i++)
    {
        uint8_t r, g, b, a;
        float epaisseur;
        uint32_t nombrePoints;

        if (!lecteur.lireU8(r)
            || !lecteur.lireU8(g)
            || !lecteur.lireU8(b)
            || !lecteur.lireU8(a)
            || !lecteur.lireF32(epaisseur)
            || !lecteur.lireU32(nombrePoints))
        {
            cout << "TRONQUE\n";
            return 0;
        }

        resultat << "TRAIT " << i + 1 << " "
                 << static_cast<int>(r) << " "
                 << static_cast<int>(g) << " "
                 << static_cast<int>(b) << " "
                 << static_cast<int>(a) << " "
                 << nombre(epaisseur) << " "
                 << nombrePoints << "\n";

        for (uint32_t j = 0; j < nombrePoints; j++)
        {
            float x, y;

            if (!lecteur.lireF32(x) || !lecteur.lireF32(y))
            {
                cout << "TRONQUE\n";
                return 0;
            }

            resultat << "POINT " << nombre(x)
                     << " " << nombre(y) << "\n";
        }
    }

    cout << resultat.str();

    return 0;
}