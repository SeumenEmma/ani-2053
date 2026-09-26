#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"


using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
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
    while (window.IsOpen()) {
        while(NkEvent* e = NkEvents().PollEvent()) {
            if (e->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            if (e->Is<NkWindowResizeEvent>()) {
                auto size = window.GetSize();
                logger.Info(
                    "Taille de la fenetre : {} x {}",
                    size.x,
                    size.y
                );
            }
        }
    }
    return 0;
}