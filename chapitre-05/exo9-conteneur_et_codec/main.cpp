#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();
    int nbMP4 = 0;
    int nbLisibles = 0;
    int nbInconnus = 0;

    for (int i = 0; i < N; i++) {
        string ligne;
        getline(cin, ligne);

        stringstream ss(ligne);

        string nom, octets;
        int P;

        ss >> nom >> octets >> P;

        vector<string> types(P);
        vector<string> codes(P);

        for (int j = 0; j < P; j++) {
            ss >> types[j] >> codes[j];
        }

        vector<int> b;

        if (octets != "-") {
            for (int j = 0; j + 1 < (int)octets.size(); j += 2) {
                string morceau = octets.substr(j, 2);
                int valeur = stoi(morceau, nullptr, 16);
                b.push_back(valeur);
            }
        }

        int n = (int)b.size();
        string conteneur = "INCONNU";

        if (n >= 12 &&
            b[4] == 0x66 && b[5] == 0x74 &&
            b[6] == 0x79 && b[7] == 0x70) {
            conteneur = "MP4";
        }
        else if (n >= 4 &&
                 b[0] == 0x1A && b[1] == 0x45 &&
                 b[2] == 0xDF && b[3] == 0xA3) {
            conteneur = "WEBM";
        }
        else if (n >= 12 &&
                 b[0] == 0x52 && b[1] == 0x49 &&
                 b[2] == 0x46 && b[3] == 0x46 &&
                 b[8] == 0x57 && b[9] == 0x41 &&
                 b[10] == 0x56 && b[11] == 0x45) {
            conteneur = "WAV";
        }
        else if (n >= 4 &&
                 b[0] == 0x4F && b[1] == 0x67 &&
                 b[2] == 0x67 && b[3] == 0x53) {
            conteneur = "OGG";
        }
        else if (n >= 4 &&
                 b[0] == 0x66 && b[1] == 0x4C &&
                 b[2] == 0x61 && b[3] == 0x43) {
            conteneur = "FLAC";
        }
        else if (n >= 3 &&
                 b[0] == 0x49 && b[1] == 0x44 &&
                 b[2] == 0x33) {
            conteneur = "MP3";
        }
        else if (n >= 2 &&
                 b[0] == 0xFF && b[1] >= 0xE0) {
            conteneur = "MP3";
        }

        cout << nom << " " << conteneur << endl;

        if (conteneur == "MP4") {
            nbMP4++;

            string premiereVideo = "";

            for (int j = 0; j < P; j++) {
                string type = types[j];
                string code = codes[j];
                string codec = code;
                string categorie;

                if (type == "vide") {
                    categorie = "VIDEO";

                    if (premiereVideo == "") {
                        premiereVideo = code;
                    }
                }
                else {
                    categorie = "AUDIO";
                }

                if (code == "mp4a") {
                    codec = "aac";
                }
                else if (code == "Opus" || code == "opus") {
                    codec = "opus";
                }
                else if (code == "avc1" || code == "avc3") {
                    codec = "h264";
                }
                else if (code == "hvc1" || code == "hev1") {
                    codec = "h265";
                }
                else if (code == "vp08") {
                    codec = "vp8";
                }
                else if (code == "vp09") {
                    codec = "vp9";
                }
                else if (code == "mp4v") {
                    codec = "mpeg4";
                }
                else if (code == ".mp3") {
                    codec = "mp3";
                }
                else if (code == "twos" ||
                         code == "sowt" ||
                         code == "lpcm") {
                    codec = "pcm";
                }

                cout << nom << " PISTE " << j + 1 << " "
                     << categorie << " " << codec << endl;
            }

            string verdict;

            if (premiereVideo == "") {
                verdict = "SANS_IMAGE";
            }
            else if (premiereVideo == "mjpa" ||
                     premiereVideo == "jpeg" ||
                     premiereVideo == "MJPG" ||
                     premiereVideo == "avc1" ||
                     premiereVideo == "avc3" ||
                     premiereVideo == "hvc1" ||
                     premiereVideo == "hev1" ||
                     premiereVideo == "av01") {
                verdict = "LISIBLE";
                nbLisibles++;
            }
            else {
                verdict = "ECHEC";
            }

            cout << nom << " LECTEUR " << verdict << endl;
        }

        if (conteneur == "INCONNU") {
            nbInconnus++;
        }
    }

    cout << "MP4 " << nbMP4 << endl;
    cout << "LISIBLES " << nbLisibles << endl;
    cout << "INCONNUS " << nbInconnus << endl;

    return 0;
}