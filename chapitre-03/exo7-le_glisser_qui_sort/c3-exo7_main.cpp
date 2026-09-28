#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"


using namespace nkentseu;
math::NkVec2u positionZone = {300, 250};
math::NkVec2u tailleZone = {200, 100};
bool zoneEnDeplacement = false; //variable pour gerer le deplacement
math::NkVec2i decalageSouris = {0, 0};

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
    window.SetCursor(NkWindow::NkCursorType::Hand);
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
    math::NkVec2u previousSize = window.GetSize();//permet de conserver une ancienne taille et ne traite le redimensionnement que lorsque la taille change.
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
            if (e->Is<NkMouseButtonReleaseEvent>()) {
                auto* mouse = e->As<NkMouseButtonReleaseEvent>();

                if (mouse->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    zoneEnDeplacement = false;
                    logger.Info("FIN DU GLISSER");
                    window.CaptureMouse(false);
                }
            }
            if (e->Is<NkMouseButtonPressEvent>()) {
                auto* mouse = e->As<NkMouseButtonPressEvent>();

                if (mouse->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    int x = mouse->GetX();
                    int y = mouse->GetY();
                    logger.Info("CLIC GAUCHE DETECTE");

                    bool sourisDansZone =
                        x >= static_cast<int>(positionZone.x) &&
                        x <= static_cast<int>(positionZone.x + tailleZone.x) &&
                        y >= static_cast<int>(positionZone.y) &&
                        y <= static_cast<int>(positionZone.y + tailleZone.y);

                    if (sourisDansZone) {
                        zoneEnDeplacement = true;
                        logger.Info("DEBUT DU GLISSER");
                        decalageSouris.x = x - static_cast<int>(positionZone.x);
                        decalageSouris.y = y - static_cast<int>(positionZone.y);
                        //window.CaptureMouse(true);
                    }
                }
            }
            if (e->Is<NkMouseMoveEvent>()) {
                auto* mouse = e->As<NkMouseMoveEvent>();

                int x = mouse->GetX();
                int y = mouse->GetY();
                logger.Info("Souris : {} x {}", x, y);

                if (zoneEnDeplacement) {
                    positionZone.x = x - decalageSouris.x;
                    positionZone.y = y - decalageSouris.y;
                }
            }
        }
    }
    return 0;
}