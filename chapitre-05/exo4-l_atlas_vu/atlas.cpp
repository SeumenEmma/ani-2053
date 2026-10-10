#include <iostream>
#include <NkFont/NKFont.h>
#include <NKImage/Core/NkImage.h>

using namespace nkentseu;

int main(){
    NkFontAtlas atlas;

    NkFont *font = atlas.AddFontFromFile(
        "D:\\Nkentseu\\Applications\\NKCode\\data\\fonts\\NotoSans-Regular.ttf",
        18.f
    );

    if (font == nullptr){
        std::cerr << "Erreur : impossible de charger la police.\n";
        return 1;
    }

    std::cout << "Police chargee avec succes."<< std::endl;

    if (!atlas.Build()){
        std::cerr << "Erreur : impossible de construire l'atlas.\n";
        return 1;
    }

    std::cout << "Police chargee avec succes."<< std::endl;
    std::cout << "Nombre de glyphes : " << font->glyphCount << '\n';
    
    nkft_uint8 *pixels = nullptr;
    nkft_int32 largeur = 0;
    nkft_int32 hauteur = 0;

    atlas.GetTexDataAsRGBA32(&pixels, &largeur, &hauteur);
        nkft_int32 pixelsVisibles = 0;

    for (nkft_int32 i = 0; i < largeur * hauteur; ++i)
    {
        if (pixels[i * 4 + 3] != 0)
        {
            ++pixelsVisibles;
        }
    }

    std::cout << "Pixels visibles avant PNG : "
              << pixelsVisibles << '\n';
    NkImage image = NkImage::Wrap(
        pixels,
        largeur,
        hauteur,
        NkImagePixelFormat::NK_RGBA32
    );

    if (!image.SavePNG("atlas.png")){
        std::cerr << "Erreur : impossible d'enregistrer atlas.png.\n";
        return 1;
    }

    std::cout << "Texture enregistree : "
              << largeur << " x " << hauteur << '\n';
    return 0;
}