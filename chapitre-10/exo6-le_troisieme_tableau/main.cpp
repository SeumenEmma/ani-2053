#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool contient(const vector<string>& noms, const string& nom)
{
    return find(noms.begin(), noms.end(), nom) != noms.end();
}

void supprimer(vector<string>& tableau, const vector<int>& indices)
{
    for (int i = static_cast<int>(indices.size()) - 1; i >= 0; i--)
    {
        int index = indices[i];

        if (index >= 0 && index < static_cast<int>(tableau.size()))
        {
            tableau.erase(tableau.begin() + index);
        }
    }
}

void echanger(vector<string>& tableau, int i, int j)
{
    if (i >= 0 && j >= 0
        && i < static_cast<int>(tableau.size())
        && j < static_cast<int>(tableau.size()))
    {
        swap(tableau[i], tableau[j]);
    }
}

int main()
{
    vector<string> modele;
    vector<string> textures;
    vector<string> sources;

    bool ajouteTextures = false;
    bool ajouteSources = false;
    bool supprimeTextures = false;
    bool supprimeSources = false;
    bool echangeTextures = false;
    bool echangeSources = false;

    string ligne;

    getline(cin, ligne);
    {
        stringstream ss(ligne);
        string operation, nom;
        ss >> operation;

        while (ss >> nom)
        {
            if (nom == "textures")
                ajouteTextures = true;
            if (nom == "sources")
                ajouteSources = true;
        }
    }

    getline(cin, ligne);
    {
        stringstream ss(ligne);
        string operation, nom;
        ss >> operation;

        while (ss >> nom)
        {
            if (nom == "textures")
                supprimeTextures = true;
            if (nom == "sources")
                supprimeSources = true;
        }
    }

    getline(cin, ligne);
    {
        stringstream ss(ligne);
        string operation, nom;
        ss >> operation;

        while (ss >> nom)
        {
            if (nom == "textures")
                echangeTextures = true;
            if (nom == "sources")
                echangeSources = true;
        }
    }

    int N;
    cin >> N;

    for (int k = 0; k < N; k++)
    {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE")
        {
            string nom;
            cin >> nom;

            modele.push_back(nom);

            if (ajouteTextures)
                textures.push_back(nom);

            if (ajouteSources)
                sources.push_back(nom);
        }
        else if (operation == "SUPPRIME")
        {
            int c;
            cin >> c;

            vector<int> indices(c);

            for (int i = 0; i < c; i++)
                cin >> indices[i];

            supprimer(modele, indices);

            if (supprimeTextures)
                supprimer(textures, indices);

            if (supprimeSources)
                supprimer(sources, indices);
        }
        else if (operation == "MONTE")
        {
            int i;
            cin >> i;

            if (i + 1 < static_cast<int>(modele.size()))
            {
                echanger(modele, i, i + 1);

                if (echangeTextures)
                    echanger(textures, i, i + 1);

                if (echangeSources)
                    echanger(sources, i, i + 1);
            }
        }
        else if (operation == "DESCEND")
        {
            int i;
            cin >> i;

            if (i > 0 && i < static_cast<int>(modele.size()))
            {
                echanger(modele, i, i - 1);

                if (echangeTextures)
                    echanger(textures, i, i - 1);

                if (echangeSources)
                    echanger(sources, i, i - 1);
            }
        }
    }

    int L = max({
        modele.size(),
        textures.size(),
        sources.size()
    });

    int decales = 0;

    for (int i = 0; i < static_cast<int>(L); i++)
    {
        string m = i < static_cast<int>(modele.size())
            ? modele[i] : "-";

        string t = i < static_cast<int>(textures.size())
            ? textures[i] : "-";

        string s = i < static_cast<int>(sources.size())
            ? sources[i] : "-";

        cout << i << " " << m << " " << t << " " << s << "\n";

        if (m != t || m != s)
            decales++;
    }

    cout << "DECALES " << decales << "\n";

    return 0;
}