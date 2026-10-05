#include <iostream>
#include <string>

struct Objet
{
    std::string nom;
    std::string parent;

    int tx;
    int ty;
    int angle;
    int echelle;

    int x;
    int y;
    int angleMonde;
    int echelleMonde;
    int niveau;
};

int trouverParent(Objet objets[], int nombre, const std::string &nom)
{
    for (int i = 0; i < nombre; ++i)
    {
        if (objets[i].nom == nom)
        {
            return i;
        }
    }

    return -1;
}

int normaliserAngle(int angle)
{
    angle %= 360;

    if (angle < 0)
    {
        angle += 360;
    }

    return angle;
}

int main()
{
    int N;
    std::cin >> N;

    Objet objets[100];

    for (int i = 0; i < N; ++i)
    {
        std::cin >> objets[i].nom
                 >> objets[i].parent
                 >> objets[i].tx
                 >> objets[i].ty
                 >> objets[i].angle
                 >> objets[i].echelle;

        if (objets[i].parent == "-")
        {
            objets[i].x = objets[i].tx;
            objets[i].y = objets[i].ty;
            objets[i].angleMonde = normaliserAngle(objets[i].angle);
            objets[i].echelleMonde = objets[i].echelle;
            objets[i].niveau = 1;
        }
        else
        {
            int parentIndex =
                trouverParent(objets, i, objets[i].parent);

            Objet &parent = objets[parentIndex];

            int ax = objets[i].tx * parent.echelleMonde;
            int ay = objets[i].ty * parent.echelleMonde;

            int rx;
            int ry;

            if (parent.angleMonde == 0)
            {
                rx = ax;
                ry = ay;
            }
            else if (parent.angleMonde == 90)
            {
                rx = -ay;
                ry = ax;
            }
            else if (parent.angleMonde == 180)
            {
                rx = -ax;
                ry = -ay;
            }
            else
            {
                rx = ay;
                ry = -ax;
            }

            objets[i].x = parent.x + rx;
            objets[i].y = parent.y + ry;

            objets[i].angleMonde =
                normaliserAngle(parent.angleMonde + objets[i].angle);

            objets[i].echelleMonde =
                parent.echelleMonde * objets[i].echelle;

            objets[i].niveau =
                parent.niveau + 1;
        }
    }

    int profondeur = 0;

    for (int i = 0; i < N; ++i)
    {
        std::cout << objets[i].nom << " "
                  << objets[i].x << " "
                  << objets[i].y << " "
                  << objets[i].angleMonde << " "
                  << objets[i].echelleMonde << '\n';

        if (objets[i].niveau > profondeur)
        {
            profondeur = objets[i].niveau;
        }
    }

    std::cout << "PROFONDEUR " << profondeur << '\n';

    return 0;
}