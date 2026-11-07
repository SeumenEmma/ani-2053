#include "D:/Nkentseu/Applications/NkRef/src/NkRef/NkRefView.h"

int main() {
    const nkref::NkRefView vue{};

    vue.PixelToWorld({100.0f, 100.0f}, {800.0f, 600.0f});
    vue.GridSpacing(20.0f);
    //vue.PanByPixels(1.0f, 0.0f);

    return 0;
}