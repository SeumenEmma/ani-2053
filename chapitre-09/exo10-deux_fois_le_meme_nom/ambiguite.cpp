#include <iostream>

namespace dames {
    enum class NkMode {
        NK_CONTRE_ORDI,
        NK_A_DEUX,
        NK_IA_CONTRE_IA
    };
}

namespace nkref {
    enum class NkMode {
        Idle,
        Pan,
        DragItems,
        ScaleCorner,
        Rotate,
        RectSelect,
        Draw
    };
}

using namespace dames;
using namespace nkref;

int main() {
    // NkMode mode;
    // Erreur : NkMode est ambigu, car les deux espaces de noms
    // définissent un type portant le même nom.

    dames::NkMode modeJeu = dames::NkMode::NK_A_DEUX;
    nkref::NkMode modeInteraction = nkref::NkMode::Pan;

    std::cout << "Mode de jeu : "
              << static_cast<int>(modeJeu) << '\n';

    std::cout << "Mode d'interaction : "
              << static_cast<int>(modeInteraction) << '\n';

    return 0;
}