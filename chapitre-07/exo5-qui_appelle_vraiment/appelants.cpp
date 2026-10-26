#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Core/NkRenderer2DTypes.h"

using namespace nkentseu;

class AppelantsApp : public renderer::NkCanvasApp {
public:
    AppelantsApp() {
        Config().title = "Mon premier dessin";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = renderer::NkColor2D{18, 18, 24, 255};
    }

protected:
    void OnRender(renderer::NkRenderWindow& target) override {
        renderer::NkVertex sommets[5] = {
            {100.0f, 100.0f, 0.0f, 0.0f, 255, 0, 0, 255},
            {200.0f, 100.0f, 0.0f, 0.0f, 0, 255, 0, 255},
            {200.0f, 200.0f, 0.0f, 0.0f, 0, 0, 255, 255},
            {100.0f, 200.0f, 0.0f, 0.0f, 255, 255, 0, 255},
            {100.0f, 100.0f, 0.0f, 0.0f, 255, 0, 0, 255}
        };

        target.Draw(sommets, 5, renderer::NkPrimitiveType::NK_LINE_STRIP);
    }
};

int nkmain(const nkentseu::NkEntryState& state) {
    return nkentseu::renderer::NkCanvasApp::Run<AppelantsApp>(state);
}