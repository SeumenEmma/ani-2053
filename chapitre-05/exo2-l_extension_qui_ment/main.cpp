#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

int hexValeur(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

vector<int> decoderHex(const string& hex)
{
    vector<int> octets;

    if (hex == "-") return octets;

    for (size_t i = 0; i + 1 < hex.size(); i += 2)
    {
        int haut = hexValeur(hex[i]);
        int bas = hexValeur(hex[i + 1]);

        if (haut == -1 || bas == -1) return {};

        octets.push_back(haut * 16 + bas);
    }

    return octets;
}

bool signature(const vector<int>& b, const vector<int>& sig)
{
    if (b.size() < sig.size()) return false;

    for (size_t i = 0; i < sig.size(); ++i)
    {
        if (b[i] != sig[i]) return false;
    }

    return true;
}

string reconnaitre(int taille, const vector<int>& b)
{
    if (taille < 4) return "";

    if (taille >= 8 && signature(b, {0x89, 0x50, 0x4E, 0x47}))
        return "PNG";

    if (signature(b, {0xFF, 0xD8, 0xFF}))
        return "JPEG";

    if (signature(b, {0x42, 0x4D}))
        return "BMP";

    if (signature(b, {0x71, 0x6F, 0x69, 0x66}))
        return "QOI";

    if (signature(b, {0x47, 0x49, 0x46, 0x38}))
        return "GIF";

    if (b.size() >= 4 && b[0] == 0x00 && b[1] == 0x00 &&
        (b[2] == 0x01 || b[2] == 0x02) && b[3] == 0x00)
        return "ICO";

    if (taille >= 10 && signature(b, {0x23, 0x3F}))
        return "HDR";

    if (signature(b, {0x76, 0x2F, 0x31, 0x01}))
        return "EXR";

    if (b.size() >= 2 && b[0] == 0x50 &&
        b[1] >= 0x31 && b[1] <= 0x36)
    {
        if (b[1] == 0x31 || b[1] == 0x34) return "PBM";
        if (b[1] == 0x32 || b[1] == 0x35) return "PGM";
        return "PPM";
    }

    if (taille >= 18 && b.size() >= 3 && b[2] <= 0x03)
        return "TGA";

    if (taille >= 18 && b.size() >= 3 &&
        (b[2] == 0x09 || b[2] == 0x0A || b[2] == 0x0B))
        return "TGA";

    size_t i = 0;

    if (b.size() >= 3 && b[0] == 0xEF &&
        b[1] == 0xBB && b[2] == 0xBF)
        i = 3;

    while (i < b.size() &&
           (b[i] == 0x20 || b[i] == 0x09 ||
            b[i] == 0x0A || b[i] == 0x0D))
    {
        ++i;
    }

    vector<int> reste;
    for (size_t j = i; j < b.size(); ++j)
        reste.push_back(b[j]);

    if (signature(reste, {0x3C, 0x3F, 0x78, 0x6D, 0x6C}) ||
        signature(reste, {0x3C, 0x73, 0x76, 0x67}))
        return "SVG";

    return "";
}

string extension(const string& nom)
{
    size_t point = nom.find_last_of('.');
    if (point == string::npos) return "";

    string ext = nom.substr(point + 1);

    transform(ext.begin(), ext.end(), ext.begin(),
        [](unsigned char c) { return static_cast<char>(tolower(c)); });

    return ext;
}

bool extensionCorrecte(const string& format, const string& ext)
{
    if (format == "PNG") return ext == "png";
    if (format == "JPEG") return ext == "jpg" || ext == "jpeg";
    if (format == "BMP") return ext == "bmp";
    if (format == "QOI") return ext == "qoi";
    if (format == "GIF") return ext == "gif";
    if (format == "ICO") return ext == "ico" || ext == "cur";
    if (format == "HDR") return ext == "hdr";
    if (format == "EXR") return ext == "exr";
    if (format == "PBM") return ext == "pbm";
    if (format == "PGM") return ext == "pgm";
    if (format == "PPM") return ext == "ppm";
    if (format == "TGA") return ext == "tga";
    if (format == "SVG") return ext == "svg";
    return false;
}

int main()
{
    int N;
    cin >> N;

    int lus = 0;
    int mensonges = 0;
    int refuses = 0;

    for (int i = 0; i < N; ++i)
    {
        string nom, hex;
        int taille;
        cin >> nom >> taille >> hex;

        vector<int> octets = decoderHex(hex);
        string format = reconnaitre(taille, octets);

        if (format.empty())
        {
            cout << nom << " REFUSE\n";
            ++refuses;
        }
        else
        {
            ++lus;

            if (extensionCorrecte(format, extension(nom)))
                cout << nom << " " << format << " OK\n";
            else
            {
                cout << nom << " " << format << " MENT\n";
                ++mensonges;
            }
        }
    }

    cout << "LUS " << lus << '\n';
    cout << "MENSONGES " << mensonges << '\n';
    cout << "REFUSES " << refuses << '\n';

    return 0;
}