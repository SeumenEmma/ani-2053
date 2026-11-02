#include "NKWindow/Core/NkMain.h"
#include "NKCanvas/App/NkCanvasApp.h"

#include <fstream>
#include <iomanip>
#include <cstddef>

namespace nkentseu::renderer {

class MonJeu final : public NkCanvasApp {
private:
    std::ofstream fichier;
    std::size_t compteur = 0;
    std::size_t image = 0;

    void noter(const char* methode) {
        if (!fichier.good()) {
            return;
        }

        ++compteur;

        fichier << compteur
                << " | " << methode
                << " | Image : " << image
                << " | Temps : "
                << std::fixed << std::setprecision(3)
                << Time() << " s\n";

        fichier.flush();
    }

protected:
    // Premier point d'intervention : avant l'ouverture de la fenêtre.
    NkOptional<int> OnCommandLine(
        const NkVector<NkString>& arguments
    ) override {
        (void)arguments;

#ifdef NDEBUG
        fichier.open("crochets-release.log");
#else
        fichier.open("crochets-debug.log");
#endif

        noter("OnCommandLine");
        return NkOptional<int>();
    }

    // Initialisation de l'application.
    bool OnInit() override {
        noter("OnInit");
        return true;
    }

    // Traitement des images successives.
    void OnUpdate(float32 deltaTime) override {
        (void)deltaTime;

        ++image;

        if (image <= 5) {
            noter("OnUpdate");
        }

        if (image == 5) {
            Quit();
        }
    }

    // Affichage de l'image courante.
    void OnRender(NkRenderWindow& cible) override {
        (void)cible;

        if (image <= 5) {
            noter("OnRender");
        }
    }

    // Nettoyage avant la fin du programme.
    void OnShutdown() override {
        noter("OnShutdown");

        if (fichier.is_open()) {
            fichier.close();
        }
    }

    // Événements transmis par le système.
    bool OnEvent(const NkEvent& evenement) override {
        (void)evenement;
        noter("OnEvent");
        return false;
    }

    // Interactions avec le pointeur.
    bool OnPointer(const NkPointer& pointeur) override {
        (void)pointeur;
        noter("OnPointer");
        return false;
    }

    // Appui sur une touche.
    bool OnKeyPress(const NkKeyPressEvent& evenement) override {
        (void)evenement;
        noter("OnKeyPress");
        return false;
    }

    // Modification des dimensions ou de la disposition.
    void OnLayout(const NkLayoutInfo& disposition) override {
        (void)disposition;
        noter("OnLayout");
    }

    // Traitement d'une demande de fermeture.
    bool OnCloseRequested() override {
        noter("OnCloseRequested");
        return true;
    }

    // Mise en pause.
    void OnPause() override {
        noter("OnPause");
    }

    // Retour au premier plan.
    void OnResume() override {
        noter("OnResume");
    }
};

} // namespace nkentseu::renderer

int nkmain(const NkEntryState& state) {
    return nkentseu::renderer::NkCanvasApp::Run<
        nkentseu::renderer::MonJeu
    >(state);
}