#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double pi = 3.141592653589793;

    int N;
    cin >> N;

    int visibles = 0;
    int refuses = 0;

    for (int i = 0; i < N; i++)
    {
        int r, n;
        cin >> r >> n;

        if (n < 3)
        {
            cout << r << " " << n << " REFUSE\n";
            refuses++;
            continue;
        }

        double g = static_cast<double>(r) * (1.0 - cos(pi / static_cast<double>(n)));

        if (g == 0.0)
        {
            cout << r << " " << n << " 0 JAMAIS\n";
            continue;
        }

        int ecart = static_cast<int>(floor(g * 1000.0));
        int zoom = static_cast<int>(ceil(100.0 / g));

        if (zoom <= 100)
        {
            cout << r << " " << n << " " << ecart << " " << zoom << " VISIBLE\n";
            visibles++;
        }
        else
        {
            cout << r << " " << n << " " << ecart << " " << zoom << " INVISIBLE\n";
        }
    }

    cout << "VISIBLES " << visibles << "\n";
    cout << "REFUSES " << refuses << "\n";

    return 0;
}