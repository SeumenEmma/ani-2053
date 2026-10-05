#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Core/NkRenderer2DTypes.h"
#include "NKTime/NkTime.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

class InterfaceApp : public NkCanvasApp
{
public:
    InterfaceApp()
    {
        Config().title = "Interface qui ne defile pas";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = NkColor2D{18, 18, 24, 255};
    }

    float centreX = 400.0f;
    float vitesse = 100.0f;

    void OnUpdate(float dt) override
    {
        centreX += vitesse * dt;

        if (centreX > 1200.0f)
        {
            centreX = 400.0f;
        }
    }

    void OnRender(NkRenderWindow& target) override
    {
        target.Clear(NkColor2D{18, 18, 24, 255});

        auto& renderer = target.GetRenderer2D();

        NkView2D vue;
        vue.center = {centreX, 300.0f};
        vue.size = {800.0f, 600.0f};
        vue.rotation = 0.0f;

        renderer.SetView(vue);

        for (int i = 0; i < 20; i++)
        {
            float x = 50.0f + i * 120.0f;

            renderer.DrawFilledRect(
                {x, 250.0f, 80.0f, 80.0f},
                NkColor2D{255, 0, 0, 255}
            );
        }

        //target.ResetView();

        renderer.DrawFilledRect(
            {0.0f, 0.0f, 800.0f, 80.0f},
            NkColor2D{40, 40, 40, 255}
        );

    }
};

int nkmain(const NkEntryState& state)
{
    return NkCanvasApp::Run<InterfaceApp>(state);
}