#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Format{
    long long octetsParPixel;
    bool couleur;
    bool transparence;
    bool flottants;
};

int main(){
    long long w, h;
    cin >> w >> h;
    int N;
    cin >> N;

    const unordered_map<string, Format> formats = {
        {"GRAY8",    {1,  false, false, false}},
        {"GRAY_A16", {2,  false, true,  false}},
        {"RGB24",    {3,  true,  false, false}},
        {"RGBA32",   {4,  true,  true,  false}},
        {"RGB96F",   {12, true,  false, true}},
        {"RGBA128F", {16, true,  true,  true}}
    };

    long long total = 0;
    int sansPerte = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i){
        string source, cible;
        cin >> source >> cible;

        auto src = formats.find(source);
        auto dst = formats.find(cible);

        if (src == formats.end() || dst == formats.end()){
            cout << source << " " << cible << " REFUSE\n";
            ++refuses;
            continue;
        }

        long long pixels = w * h;
        long long octetsSource =
            pixels * src->second.octetsParPixel;
        long long octetsCible =
            pixels * dst->second.octetsParPixel;

        string pertes;

        if (src->second.transparence && !dst->second.transparence){
            pertes = "TRANSPARENCE";
        }

        if (src->second.couleur && !dst->second.couleur){
            if (!pertes.empty()) pertes += "+";
            pertes += "COULEUR";
        }

        if (src->second.flottants && !dst->second.flottants){
            if (!pertes.empty()) pertes += "+";
            pertes += "ETENDUE";
        }

        if (pertes.empty()){
            pertes = "AUCUNE";
            ++sansPerte;
        }

        cout << source << " " << cible << " "
             << octetsSource << " " << octetsCible << " "
             << pertes << '\n';

        total += octetsCible;
    }

    cout << "TOTAL " << total << '\n';
    cout << "SANS_PERTE " << sansPerte << '\n';
    cout << "REFUSES " << refuses << '\n';

    return 0;
}