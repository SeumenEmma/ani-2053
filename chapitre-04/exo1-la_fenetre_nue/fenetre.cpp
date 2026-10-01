#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/App/NkCanvasApp.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

class Fenetre_nue :public NkCanvasApp
{
public:
    Fenetre_nue()
    {
        Config().title = "Fenetre_nue";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = NkColor2D(150, 0, 200, 255);
    }
};
int nkmain(const NkEntryState& state)
{
    return NkCanvasApp::Run<Fenetre_nue>(state);
}