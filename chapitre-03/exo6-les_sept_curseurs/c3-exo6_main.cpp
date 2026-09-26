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
    logger.Info(
    "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
    size.x, size.y,
    displaySize.x, displaySize.y,
    scale
    );
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
            if (e->Is<NkMouseMoveEvent>()) {
                auto* mouse = e->As<NkMouseMoveEvent>();

                int x = mouse->GetX();
                int y = mouse->GetY();
                auto taille = window.GetSize();
                uint32 largeurZone = taille.x / 7;
                uint32 zone = (x * 7) / taille.x;
            }
        }
    }
    return 0;
}