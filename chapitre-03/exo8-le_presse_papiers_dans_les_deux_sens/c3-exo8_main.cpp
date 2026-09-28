#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"


using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "MonDocument";
    cfg.width  = 1280;
    cfg.height = 720;

    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;
    
    NkWindow window(cfg);
    bool documentModifie = false;
    auto mettreAJourTitre = [&]() {
        auto taille = window.GetSize();

        NkString titre = cfg.title;

        if (documentModifie)
            titre += "*";

        titre += " - ";
        titre += NkString::Fmtf("%u x %u", taille.x, taille.y);

        window.SetTitle(titre);
    };
    mettreAJourTitre();
    auto size = window.GetSize();
    auto displaySize = window.GetDisplaySize();
    float32 scale = window.GetDpiScale();
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    NkString texte = window.GetClipboardText();
    logger.Info("Texte du presse-papiers avant : {}", texte);
    texte = texte.ToUpper();
    window.SetClipboardText(texte);
    logger.Info("Texte remis dans le presse-papiers : {}", texte);
    logger.Info("Image présente : {}", window.HasClipboardImage());
    NkClipboardImage imageTest;
    imageTest.width = 2;
    imageTest.height = 2;
    imageTest.pixels.Resize(16);
    imageTest.pixels[0] = 255;
    imageTest.pixels[1] = 0;
    imageTest.pixels[2] = 0;
    imageTest.pixels[3] = 255;
    bool imageEcrite = window.SetClipboardImage(imageTest);//pour demander a NKWindow de metttre notre image dans le presse papier.
    logger.Info("Image ecrite : {}", imageEcrite);
    NkClipboardImage image;
    bool imageLue = window.GetClipboardImage(image);
    logger.Info("Image lue : {}", imageLue);
    logger.Info("Image : {} x {} | 32 bits par pixel", image.width, image.height);
    for (usize i = 0; i + 3 < image.pixels.Size(); i += 4) {
        image.pixels[i]     = 255 - image.pixels[i];
        image.pixels[i + 1] = 255 - image.pixels[i + 1];
        image.pixels[i + 2] = 255 - image.pixels[i + 2];
    }
    bool imageRemise = window.SetClipboardImage(image);
    logger.Info("Image remise dans le presse-papiers : {}", imageRemise);
    NkClipboardImage imageFinale;
    bool imageFinaleLue = window.GetClipboardImage(imageFinale);
    logger.Info("Image finale relue : {}", imageFinaleLue);
    while (window.IsOpen()) {
        math::NkVec2u size = window.GetSize();
        
        while(NkEvent* e = NkEvents().PollEvent()) {
            if (e->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            if (e->Is<NkWindowResizeEvent>()) {
                mettreAJourTitre();
            }
            if (e->Is<NkKeyPressEvent>()) {
                documentModifie = true;
                mettreAJourTitre();
            }
        }
    }
    return 0;
}