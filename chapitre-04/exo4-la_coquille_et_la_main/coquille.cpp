#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

class fenetre : public nkentseu::renderer::NkCanvasApp
{
public:
    fenetre()
    {
        Config().title = "La coquille";
        Config().width = 1280;
        Config().height = 720;
        Config().clearColor = NkColor2D(18, 18, 24, 255);
    }

    void OnUpdate(float dt) override
    {
        x += 100 * dt;

        if (x > Config().width)
        {
            x = 0;
        }
    }

    void OnRender(nkentseu::renderer::NkRenderWindow &) override { 
        Target().GetRenderer2D().DrawFilledRect(
            nkentseu::renderer::NkRect2f{x, 250.0f, 50.0f, 50.0f},
             nkentseu::renderer::NkColor2D::Red);
    }

private:
    float x = 0.0f;
};

int nkmain(const nkentseu::NkEntryState &state)
{
    return NkCanvasApp::Run<fenetre>(state);
}