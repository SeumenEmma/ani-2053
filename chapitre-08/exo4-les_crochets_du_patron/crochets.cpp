
#include "NKWindow/Core/NkMain.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include <fstream>
#include <string>
#include <iomanip>

namespace nkentseu {
namespace renderer {

class MonJeu : public NkCanvasApp {
private:
    std::ofstream fichier;
    unsigned int compteurAppels = 0;
    unsigned int numeroImage = 0;

    void enregistrer(const std::string& fonction) {
        if (!fichier.good()) {
            return;
        }

        compteurAppels++;

        fichier << std::setw(3) << compteurAppels
                << " | " << fonction
                << " | Image = " << numeroImage
                << " | Temps = " << std::fixed
                << std::setprecision(3) << Time()
                << " s" << '\n';

        fichier.flush();
    }

protected:

    NkOptional<int> OnCommandLine(
        const NkVector<NkString>& arguments
    ) override {
        (void)arguments;

#ifdef NDEBUG
        fichier.open("crochets-release.log");
#else
        fichier.open("crochets-debug.log");
#endif

        enregistrer("OnCommandLine");
        return NkOptional<int>();
    }

    bool OnInit() override {
        enregistrer("OnInit");
        return true;
    }

    void OnUpdate(float32 tempsEcoule) override {
        (void)tempsEcoule;

        numeroImage++;
        enregistrer("OnUpdate");

        if (numeroImage == 5) {
            Quit();
        }
    }

    void OnRender(NkRenderWindow& fenetre) override {
        (void)fenetre;
        enregistrer("OnRender");
    }

    void OnShutdown() override {
        enregistrer("OnShutdown");

        fichier.close();
    }

    bool OnEvent(const NkEvent& evenement) override {
        (void)evenement;

        enregistrer("OnEvent");
        return false;
    }

    bool OnPointer(const NkPointer& pointeur) override {
        (void)pointeur;

        enregistrer("OnPointer");
        return false;
    }

    bool OnKeyPress(const NkKeyPressEvent& touche) override {
        (void)touche;

        enregistrer("OnKeyPress");
        return false;
    }

    void OnLayout(const NkLayoutInfo& disposition) override {
        (void)disposition;

        enregistrer("OnLayout");
    }

    bool OnCloseRequested() override {
        enregistrer("OnCloseRequested");
        return true;
    }

    void OnPause() override {
        enregistrer("OnPause");
    }

    void OnResume() override {
        enregistrer("OnResume");
    }
};

} // namespace renderer
} // namespace nkentseu

int nkmain(const nkentseu::NkEntryState& informations) {
    using Application = nkentseu::renderer::NkCanvasApp;
    using Jeu = nkentseu::renderer::MonJeu;

    return Application::Run<Jeu>(informations);
}
