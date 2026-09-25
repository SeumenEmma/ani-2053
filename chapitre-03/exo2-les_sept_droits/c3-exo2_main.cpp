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
        }
    }
    return 0;
}