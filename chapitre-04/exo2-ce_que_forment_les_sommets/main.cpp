#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;
    int totalPoints = 0;
    int totalSegments = 0;
    int totalTriangles = 0;
    int totalRefuses = 0;

    for (int i = 0; i < n; i++)
    {
        std::string type;
        int sommets;

        std::cin >> type >> sommets;
        if (type == "POINTS")
        {
            std::cout << type << " " << sommets << " "
                    << sommets << " POINTS 0\n";

            totalPoints += sommets;
        }
        else if (type == "LINES")
        {
            int segments = sommets / 2;
            int restants = sommets % 2;

            std::cout << type << " " << sommets << " "
                    << segments << " SEGMENTS " << restants << "\n";

            totalSegments += segments;
        }
        else if (type == "LINE_STRIP")
        {
            int segments;
            int restants;

            if (sommets >= 2)
            {
                segments = sommets - 1;
                restants = 0;
            }
            else
            {
                segments = 0;
                restants = sommets;
            }

            std::cout << type << " " << sommets << " "
                    << segments << " SEGMENTS " << restants << "\n";

            totalSegments += segments;
        }
        else if (type == "TRIANGLES")
        {
            int triangles = sommets / 3;
            int restants = sommets % 3;

            std::cout << type << " " << sommets << " "
                    << triangles << " TRIANGLES " << restants << "\n";

            totalTriangles += triangles;
        }
        else if (type == "TRIANGLE_STRIP")
        {
            int triangles;
            int restants;

            if (sommets >= 3)
            {
                triangles = sommets - 2;
                restants = 0;
            }
            else
            {
                triangles = 0;
                restants = sommets;
            }

            std::cout << type << " " << sommets << " "
                    << triangles << " TRIANGLES " << restants << "\n";

            totalTriangles += triangles;
        }
        else if (type == "TRIANGLE_FAN")
        {
            int triangles;
            int restants;

            if (sommets >= 3)
            {
                triangles = sommets - 2;
                restants = 0;
            }
            else
            {
                triangles = 0;
                restants = sommets;
            }

            std::cout << type << " " << sommets << " "
                    << triangles << " TRIANGLES " << restants << "\n";

            totalTriangles += triangles;
        }
        else
        {
            std::cout << type << " " << sommets << " REFUSE\n";

            totalRefuses++;
        }
        std::cout << "POINTS " << totalPoints << "\n";
        std::cout << "SEGMENTS " << totalSegments << "\n";
        std::cout << "TRIANGLES " << totalTriangles << "\n";
        std::cout << "REFUSES " << totalRefuses << "\n";
    }
    return 0;
}