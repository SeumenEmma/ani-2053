#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string nom, mot, document, secours, verrou;

    int proposes = 0;
    int effaces = 0;
    int lectureSeule = 0;

    while (cin >> nom >> mot >> document
               >> mot >> secours >> mot >> verrou) {

        if (verrou == "PRIS") {
            cout << nom << " LECTURE_SEULE\n";
            lectureSeule++;
        }
        else if (secours == "-") {
            if (document == "-") {
                cout << nom << " PLANCHE_VIDE\n";
            } else {
                cout << nom << " OUVRIR_DOCUMENT\n";
            }
        }
        else if (document == "-") {
            cout << nom << " PROPOSER SANS_NOM\n";
            proposes++;
        }
        else {
            long long dateDocument = stoll(document);
            long long dateSecours = stoll(secours);

            if (dateSecours <= dateDocument) {
                cout << nom << " EFFACER_SECOURS\n";
                effaces++;
            }
            else {
                long long avance = dateSecours - dateDocument;
                long long minutes = avance / 60;
                long long secondes = avance % 60;

                cout << nom << " PROPOSER "
                     << minutes << ":"
                     << setw(2) << setfill('0') << secondes
                     << setfill(' ') << "\n";

                proposes++;
            }
        }
    }

    cout << "PROPOSES " << proposes << "\n";
    cout << "EFFACES " << effaces << "\n";
    cout << "LECTURE_SEULE " << lectureSeule << "\n";

    return 0;
}