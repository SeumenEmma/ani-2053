## Ouverture d une fenetre 

Pour ouvrir ma fenetre je suis aller dans mon dossier Nkentseu puis j ai tape la commande :
```
jenga build --target NKWindow --plateform windows --config Debug
```
ce qui me donne :
```
════════════════════════════════════════════════════════════════════════════════
Projects Built:  11/11
Time:           25.28s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis je tape la commande :
```
jenga kit --target NKWindow --output  "C:\Users\emmas\OneDrive\Documents\Test_Nkentseu" --platform windows --config Debug 
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
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.
============================= Jenga kit - Nkentseu =============================


Ce que le kit va contenir
------------------------------------------------------------
Nom          : NkentseuKit
Dossier      : C:\Users\emmas\OneDrive\Documents\Test_Nkentseu
Modules      : 11
Ordre de lien: NKWindow NKEvent NKTime NKFileSystem NKLogger NKMath NKThreading NKContainers NKMemory NKCore NKPlatform
Configurations : Debug
Plateformes    : Windows



Kit ecrit
------------------------------------------------------------
Cible           Bibliotheques   Dossier          
=================================================
Debug-Windows   11              lib/Debug-Windows

En-tetes copies : 297
Taille du kit   : 15.9 Mo

Kit pret : C:\Users\emmas\OneDrive\Documents\Test_Nkentseu

Pour l'utiliser depuis un autre workspace :

    with workspace("MonJeu"):
        useconfig("NkentseuKit/NkentseuKit.jenga")

        with project("Jeu"):
            consoleapp()
            files(["src/**.cpp"])
            usenkentseukit()
```
ce qui me genere le kit
puis je part cree le workspace :
```
jenga workspace
```
ce qui me donne :
```

Create workspace? [Y/n] [y]: y
Workspace 'Exercice_1' created at C:\Users\emmas\OneDrive\Documents\Exercice_1\Exercice_1.jenga
Project 'Exercice1_chap3' created in 'Exercice1_chap3/'.
✓ Workspace 'Exercice_1' is ready!
ℹ Next: cd C:\Users\emmas\OneDrive\Documents\Exercice_1 && Jenga build
```
puis je copy le path du kit et je le met dans mon projet 
puis j ecrit le code de mon main.cpp et j ajoute certaine ligne de code comme :
```
useconfig("Exercice1_chap3/Test_Nkentseu/NkentseuKit.jenga")
```
ensuite je compile avec :
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
│  ✓ Build Successful                                                             Time: 7.05s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           7.05s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis je fait un 
```
jenga run 
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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Exercice1_chap3.exe
     C:\Users\emmas\OneDrive\Documents\Exercice_1\Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (10.27s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
qui me donne ca et ouvre ma fenetre.

## Version de jenga 
Mon jenga build et mon jenga run utilise tout les deux la versions 2.8.2

## Comparaison 

Mon programme permet d'ouvrir une fenêtre, de la garder ouverte et de terminer proprement le programme.

Le code de mon main.cpp est le suivant :
```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkSink.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"

#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}
```
Le programme du chapitre est plus petit que mon programme.

Dans mon programme, les éléments suivants sont ajoutés par rapport au chapitre :

#include "NKLogger/NkSink.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"

J'ai également ajouté :

using namespace nkentseu;

En revanche, la partie principale du programme est la même que dans le chapitre :

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}

Mon code main.cpp : 25 lignes 
Le code main.cpp du chapitre : 17 lignes 

## Conclusion

Les instructions principales nécessaires à l'ouverture, au maintien et à la fermeture propre de la fenêtre sont présentes dans le programme du chapitre. Mon programme reprend cette structure en y ajoutant des éléments supplémentaires liés aux fonctionnalités utilisées dans mon projet.