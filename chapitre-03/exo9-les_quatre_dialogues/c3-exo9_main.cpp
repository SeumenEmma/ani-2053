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
    NkDialogResult ouvrir = NkDialogs::OpenFileDialog("*.*", "Ouvrir un fichier");
    if (ouvrir.confirmed) {
        logger.Info("Fichier choisi : {}", ouvrir.path);
    } else {
        logger.Info("Ouverture du fichier annulee.");
    }
    NkDialogResult enregistrer = NkDialogs::SaveFileDialog("txt", "Enregistrer un fichier");
    if (enregistrer.confirmed) {
        logger.Info("Fichier a enregistrer : {}", enregistrer.path);
    } else {
        logger.Info("Enregistrement annule.");
    }
    NkDialogResult dossier = NkDialogs::OpenFolderDialog("Choisir un dossier");
    if (dossier.confirmed) {
        logger.Info("Dossier choisi : {}", dossier.path);
    } else {
        logger.Info("Selection du dossier annulee.");
    }
    NkDialogs::OpenMessageBox(
    "Test du dialogue de message.",
    "Message"
    );
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