#  Taille minimale de la fenêtre

Dans cet exercice ont doit fixer une taille minimale à la fenêtre, puis essayer de la réduire en dessous de cette limite.

## 1. Première expérience : avec une taille minimale configurée

Pour la première expérience, j'ai configuré une taille minimale de 60 × 60 :

```
    cfg.width  = 1280;
    cfg.height = 720;
```
J'ai également ajouté l'événement NkWindowResizeEvent afin d'afficher la taille réelle de la fenêtre lors de chaque redimensionnement :
```
if (e->Is<NkWindowResizeEvent>()) {
    auto size = window.GetSize();

    logger.Info(
        "Taille de la fenetre : {} x {}",
        size.x,
        size.y
    );
}
```
Cela permet de mesurer directement la taille donnée par le programme.

# Code utilisé pour la première expérience
```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"


using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;
    
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) {
        while(NkEvent* e = NkEvents().PollEvent()) {
            if (e->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            if (e->Is<NkWindowResizeEvent>()) {
                auto size = window.GetSize();
                logger.Info(
                    "Taille de la fenetre : {} x {}",
                    size.x,
                    size.y
                );
            }
        }
    }
    return 0;
}
```
puis je compile avec 
```
jenga build
```
ce qui me donne :
```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Exercice1_chap3 [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Exercice1_chap3                                                 Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.88s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.88s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis un 
```
jenga run
```
ce qui me donne :
```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Exercice1_chap3.exe
     C:\Users\emmas\OneDrive\Documents\Exercice_1\Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-26 17:13:49.021] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 1278 x 1278
[2026-09-26 17:13:53.493] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.494] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.494] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.494] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.495] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.496] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.497] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.497] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.497] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.499] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.499] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.499] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.499] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.500] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.500] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.501] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.502] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.502] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.503] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.503] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.504] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.504] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.504] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.505] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.505] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.505] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.505] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.506] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.506] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.507] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.507] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.507] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.508] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.508] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.510] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.510] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.512] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.512] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.512] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.513] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.513] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.514] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.514] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.514] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.515] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.516] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.516] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.517] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.517] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.517] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.518] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.518] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.518] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.519] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.519] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.519] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.520] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.520] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.520] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.522] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.522] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.522] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.522] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.524] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.524] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.525] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.525] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.525] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.526] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.526] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.527] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.527] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.528] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.528] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.528] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.529] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.529] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.530] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.531] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.531] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.532] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.532] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.533] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.534] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.534] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.535] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.535] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.536] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.536] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.537] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.537] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.537] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.538] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.539] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.539] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.540] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.541] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.541] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.542] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.542] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.543] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.544] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.544] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.545] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.546] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.546] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.546] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.547] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.547] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.549] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.549] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.550] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.551] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.551] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.552] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.553] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.553] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.553] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.554] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.555] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.555] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.556] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.556] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.557] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.557] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.558] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.558] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.559] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.560] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.560] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.561] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.561] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.562] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.562] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.564] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.565] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.565] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.566] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.566] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.567] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.567] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.569] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.569] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.570] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.570] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.571] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.571] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.571] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.572] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.572] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.573] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.573] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.574] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.574] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.575] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.575] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.575] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.576] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.576] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.577] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.578] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.578] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.578] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.579] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.579] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.580] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.580] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.581] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.581] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.581] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.582] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.582] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.583] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.583] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.583] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.584] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.584] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.584] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.585] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.586] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.586] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.587] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.587] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.589] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.590] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.590] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:53.591] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.943] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.943] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.943] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.944] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.944] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.944] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.944] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.944] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.946] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.946] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.946] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.947] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.947] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.947] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.947] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.948] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.948] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.948] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.949] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.949] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.949] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.949] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.949] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.950] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.951] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.951] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.952] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.953] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.953] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.953] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.954] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.954] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.954] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.956] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.957] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.961] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.961] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.962] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.962] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.963] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.963] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.964] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.965] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.965] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.966] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.966] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.966] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.967] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.968] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.969] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.969] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.970] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.972] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.972] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.972] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.973] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.973] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.973] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.973] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.973] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.974] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.974] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.974] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.975] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.975] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.975] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.975] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.975] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.976] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.976] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.976] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.978] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.979] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.979] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.979] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.979] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.980] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.980] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.980] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.981] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.981] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.982] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.982] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.983] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.983] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.984] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.984] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.985] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.985] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.986] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.986] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.987] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.987] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.988] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.990] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.990] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.990] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.991] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.991] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.992] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.993] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.994] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.994] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.995] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.995] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.996] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.996] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.997] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.997] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.998] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:13:59.999] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.000] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.000] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.001] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.001] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.001] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.001] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.003] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.003] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.004] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.004] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.005] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.005] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.006] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.007] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.007] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.007] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.008] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.008] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.010] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.010] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.011] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.012] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.012] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.012] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.014] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.014] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.014] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.015] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.015] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.016] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.016] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.017] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.018] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.018] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.019] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.019] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.020] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.020] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.020] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.021] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.022] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.022] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.023] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.023] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.024] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.024] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.026] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.027] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.028] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.028] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.029] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.029] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.029] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.030] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.031] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.031] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.032] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.032] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.033] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.034] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.035] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.035] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.036] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:00.036] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.328] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.330] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.330] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.331] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.331] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.331] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.331] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.331] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.332] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.332] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.332] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.332] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.333] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.333] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.333] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.333] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:14:13.334] [INF] [default] [main.cpp:33 in nkmain] -> Taille de la fenetre : 148 x 148

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (26.30s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
Taille de la fenetre : 148 x 148

## 2. Deuxième expérience : sans taille minimale configurée

Pour la deuxième expérience, j'ai retiré les deux paramètres :
```
    cfg.width  = 1280;
    cfg.height = 720;
```
J'ai conservé l'écoute de NkWindowResizeEvent afin de continuer à mesurer directement la taille de la fenêtre.
# Code utilisé pour la deuxieme expérience
```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"


using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable =  true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) {
        while(NkEvent* e = NkEvents().PollEvent()) {
            if (e->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            if (e->Is<NkWindowResizeEvent>()) {
                auto size = window.GetSize();
                logger.Info(
                    "Taille de la fenetre : {} x {}",
                    size.x,
                    size.y
                );
            }
        }
    }
    return 0;
}
```
puis j ai compile avec 
```
jenga build
```
ce qui me donne 
```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Exercice1_chap3 [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Exercice1_chap3                                                 Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 2.00s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.00s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis j execute avec un :
```
jenga run 
```
ce qui me donne :
```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Exercice1_chap3.exe
     C:\Users\emmas\OneDrive\Documents\Exercice_1\Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-26 17:19:11.791] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 1278 x 1278
[2026-09-26 17:19:19.169] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.169] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.171] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.172] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.172] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.197] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.198] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.199] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.199] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.199] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.200] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.200] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.201] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.201] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.202] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.202] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.203] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.203] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.204] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.204] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.204] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.204] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.204] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.205] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.205] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.205] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.205] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.206] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.206] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.206] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.206] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.206] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.208] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.208] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.208] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.208] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.208] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.210] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.212] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.213] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.214] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.215] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.216] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.216] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.216] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.216] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.216] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.217] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.217] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.217] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.217] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.217] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.218] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.218] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.218] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.218] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.218] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.219] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.219] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.221] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.221] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.221] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.222] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.222] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.223] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.223] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.223] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.223] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.224] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.224] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.225] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.225] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.226] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.226] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.226] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.227] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.227] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.228] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.228] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.229] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.229] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.229] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.230] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.231] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.231] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.231] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.232] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.232] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.233] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.233] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.234] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.234] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.235] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.235] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.235] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.236] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.236] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.236] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.237] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.237] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.238] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.238] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.238] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.239] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.239] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.240] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.240] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.241] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.241] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.242] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.242] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.243] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.243] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.243] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.244] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.244] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.245] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.245] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.246] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.246] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.247] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.247] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.248] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.248] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.249] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.249] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.250] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.250] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.251] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.251] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.251] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.252] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.252] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.252] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.252] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.253] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.254] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.254] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.255] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.255] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.255] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.256] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.256] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.257] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.258] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.258] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.259] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.259] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.260] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.261] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.263] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.263] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.264] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.264] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.265] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.265] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.266] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:19.266] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.111] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.111] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.111] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.112] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.112] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.112] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.112] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.113] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.113] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.113] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.113] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.113] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.114] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.114] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.114] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.114] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.114] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.115] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.115] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.115] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.115] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.115] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.116] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.116] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.116] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.118] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.118] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.118] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.118] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.119] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.121] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.121] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.121] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.121] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.122] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.122] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.122] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.123] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.123] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.126] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.127] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.127] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.127] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.128] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.128] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.129] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.129] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.129] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.131] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.131] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.132] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.132] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.133] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.133] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.134] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.134] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.135] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.135] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.136] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.136] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.136] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.137] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.137] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.138] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.138] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.139] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.140] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.140] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.140] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.141] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.141] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.141] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.143] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.143] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.144] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.144] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.144] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.145] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.145] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.146] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.146] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.147] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.147] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.147] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.148] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.148] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.150] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.150] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.151] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.151] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.152] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.152] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.152] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.154] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.154] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.154] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.155] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.155] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.155] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.156] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.156] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.157] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.157] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.158] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.159] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.160] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.160] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.161] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.161] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.162] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.162] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.163] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.163] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.164] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.164] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.165] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.165] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.166] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.166] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.166] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.167] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.167] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.168] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148
[2026-09-26 17:19:23.169] [INF] [default] [main.cpp:31 in nkmain] -> Taille de la fenetre : 148 x 148

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (16.30s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
J'ai de nouveau réduit progressivement la fenêtre jusqu'à la limite que le système acceptait.
Taille de la fenetre : 148 x 148

## 3. Comparaison des deux expériences

| Expérience  | Taille configurée | Plus petite taille observée | Durée   |
| ----------- | -------------------------- | --------------------------- | ------- |
| Avec bornes | 1280 x  720                   | 148 × 148                   | 26.30 s |
| Sans bornes | Aucune                     | 148 × 148                   | 16.30 s |

La mesure obtenue est donc la même dans les deux expériences : 148 × 148.
