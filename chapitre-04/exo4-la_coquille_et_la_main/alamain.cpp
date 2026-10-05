#include "NKWindow/NKWindow.h" 
#include "NKWindow/NKMain.h" 
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h" 
#include "NKTime/NkClock.h" 
#include "NKEvent/NkEventSystem.h" 
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;
using namespace nkentseu::renderer;
 
int nkmain(const NkEntryState &state) 
{ 
    NkWindowConfig config; 
    config.title = "A la main"; 
    config.width = 1280; 
    config.height = 720; 
 
    NkWindow window(config); 
 
    NkContextDesc desc; 
    desc.api = graphics::NkGraphicsApi::NK_GFX_API_OPENGL; 
 
    NkRenderWindow target(window, desc); 
    if (!target.IsValid()) 
        return -1; 
    float x = 0.0f; 
 
    NkClock clock; 
 
    while (window.IsOpen()) 
    { 
        float dt = clock.Tick().delta; 
        while (NkEvent *event = NkEvents().PollEvent())
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                window.Close();
            }
        }
        x += 100.0f * dt; 
        if (x > config.width) 
            x = 0.0f; 
        target.Clear(NkColor2D{18, 18, 24, 255}); 
 
        target.GetRenderer2D().DrawFilledRect( 
            NkRect2f{x, 250.0f, 50.0f, 50.0f}, 
            NkColor2D::Red); 
 
        target.Display(); 
    } 
    return 0; 
}