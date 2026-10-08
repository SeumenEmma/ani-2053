#include <iostream>
#include "NKImage/NKImage.h"
#include "NKLogger/NkLog.h"

void mesurerImage(const char* nom, const char* chemin)
{
    nkentseu::NkImage img;

    if (!img.Load(chemin)) {
        logger.Error("Chargement echoue : {}", nom);
        return;
    }

    int largeur = img.Width();
    int hauteur = img.Height();
    int bytesPP = img.BytesPP();

    long long calcul =
        static_cast<long long>(largeur) *
        static_cast<long long>(hauteur) *
        static_cast<long long>(bytesPP);

    logger.Info("Image : {}", nom);
    logger.Info("Largeur : {}", largeur);
    logger.Info("Hauteur : {}", hauteur);
    logger.Info("BytesPP : {}", bytesPP);
    logger.Info("Calcul : {} octets", calcul);
}

int main()
{
    mesurerImage(
        "icone.png",
        "C:/Users/emmas/OneDrive/Documents/Exercice3/Exercice_chap5/assets/icone.png"
    );

    mesurerImage(
        "dessin.png",
        "C:/Users/emmas/OneDrive/Documents/Exercice3/Exercice_chap5/assets/dessin.png"
    );

    mesurerImage(
        "capture.png",
        "C:/Users/emmas/OneDrive/Documents/Exercice3/Exercice_chap5/assets/capture.png"
    );

    mesurerImage(
        "photo1.jpg",
        "C:/Users/emmas/OneDrive/Documents/Exercice3/Exercice_chap5/assets/photo1.jpg"
    );

    mesurerImage(
        "photo2.jpg",
        "C:/Users/emmas/OneDrive/Documents/Exercice3/Exercice_chap5/assets/photo2.jpg"
    );

    return 0;
}