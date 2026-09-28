#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <iostream>
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    NkWindowConfig cfg2;
    cfg2.title = "Deuxieme fenetre";
    cfg2.width = 800;
    cfg2.height = 600;

    NkWindow window2(cfg2);
    NkWindowId id2 = window2.GetId();

    std::cout << "ID fenetre 2 : " << id2 << std::endl;
    if (!window2.IsOpen()) {
        logger.Error("[app] creation de la deuxieme fenetre echouee");
        return -1;
    }
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
    NkWindowId id1 = window.GetId();
    std::cout << "ID fenetre 1 : " << id1 << std::endl;

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
    NkEvents().AddEventCallback<NkMouseButtonPressEvent>(
        [&](NkMouseButtonPressEvent *event) {

            if (event->IsLeft()) {

                if (event->GetWindowId() == id1) {
                    std::cout << "Clic gauche reçu par la fenêtre 1" << std::endl;
                }
                else if (event->GetWindowId() == id2) {
                    std::cout << "Clic gauche reçu par la fenêtre 2" << std::endl;
                }
            }
        }
    );
    while (window.IsOpen() || window2.IsOpen()) {
        math::NkVec2u size = window.GetSize();
        
        while(NkEvent* e = NkEvents().PollEvent()) {
            if (e->Is<NkWindowCloseEvent>()) {
                auto *event = e->As<NkWindowCloseEvent>();

                if (event->GetWindowId() == id1) {
                    window.Close();
                }
                else if (event->GetWindowId() == id2) {
                    window2.Close();
                }
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