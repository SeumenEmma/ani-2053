#include <iostream>
#include <cmath>
#include "NkRef/NkRefView.h"

using namespace nkref;

const NkVec2f viewport{800.0f, 600.0f};
const float32 tolerance = 0.001f;

bool proche(float32 a, float32 b)
{
    return std::fabs(a - b) <= tolerance;
}

bool aller_retour()
{
    NkRefView camera;
    camera.center = {25.0f, -12.0f};
    camera.zoom = 2.5f;

    NkVec2f pixel{123.0f, 456.0f};

    NkVec2f monde = camera.PixelToWorld(pixel, viewport);
    NkVec2f resultat = camera.WorldToPixel(monde, viewport);

    return proche(resultat.x, pixel.x)
        && proche(resultat.y, pixel.y);
}

bool point_fixe()
{
    NkRefView camera;

    NkVec2f pixel{150.0f, 220.0f};
    NkVec2f avant = camera.PixelToWorld(pixel, viewport);

    camera.ZoomAtPixel(2.0f, pixel, viewport);

    NkVec2f apres = camera.PixelToWorld(pixel, viewport);

    return proche(avant.x, apres.x)
        && proche(avant.y, apres.y);
}

bool bornes()
{
    NkRefView camera;

    camera.ZoomAtPixel(1000.0f, {400.0f, 300.0f}, viewport);

    bool maximum = camera.zoom <= NkRefView::kZoomMax
                && camera.zoom >= NkRefView::kZoomMin;

    camera.ZoomAtPixel(0.00001f, {400.0f, 300.0f}, viewport);

    bool minimum = camera.zoom >= NkRefView::kZoomMin
                && camera.zoom <= NkRefView::kZoomMax;

    return maximum && minimum;
}

bool grille()
{
    NkRefView camera;

    camera.zoom = 4.0f;
    float32 avant = camera.GridSpacing(32.0f);

    camera.ZoomAtPixel(0.5f, {400.0f, 300.0f}, viewport);

    float32 apres = camera.GridSpacing(32.0f);

    return apres >= avant;
}

bool origine()
{
    NkRefView camera;

    camera.ZoomAtPixel(3.0f, {200.0f, 150.0f}, viewport);
    camera.PanByPixels(50.0f, -30.0f);
    camera.Reset();

    return proche(camera.center.x, 0.0f)
        && proche(camera.center.y, 0.0f)
        && proche(camera.zoom, 1.0f);
}

int main()
{
    std::cout << "TEST aller_retour : "
              << (aller_retour() ? "OK" : "ECHEC") << '\n';

    std::cout << "TEST point_fixe : "
              << (point_fixe() ? "OK" : "ECHEC") << '\n';

    std::cout << "TEST bornes : "
              << (bornes() ? "OK" : "ECHEC") << '\n';

    std::cout << "TEST grille : "
              << (grille() ? "OK" : "ECHEC") << '\n';

    std::cout << "TEST origine : "
              << (origine() ? "OK" : "ECHEC") << '\n';

    return 0;
}