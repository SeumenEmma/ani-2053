# État du programme dans le titre de la fenêtre

Dans cet exercice il est question d'afficher dans le titre de la fenêtre :
* le nom du document ;
* un `*` lorsque le document est considéré comme modifié ;
* la taille courante de la fenêtre.
Le titre doit être mis à jour uniquement lorsqu'une information change, et non à chaque image.

## 1. Vérification du projet
J'ai commencé par ouvrir le fichier `main.cpp` de mon projet.
Le projet utilise notamment :

```
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
```
La fenêtre est initialisée avec le titre :
```
cfg.title = "MonDocument";
```
et avec une taille initiale de :
```
cfg.width = 1280;
cfg.height = 720;
```

## 2. Création de l'état du document

J'ai ajouté une variable permettant de savoir si le document a été modifié :

```
bool documentModifie = false;
```
Au démarrage, sa valeur est 
```
false
```
Le titre ne contient donc pas d'astérisque.

## 3. Création de la fonction de mise à jour du titre

J'ai créé une fonction 
```
mettreAJourTitre()
```
Cette fonction récupère la taille actuelle de la fenêtre, construit le titre à partir du nom du document et ajoute `*` lorsque documentModifie vaut true.

```
auto mettreAJourTitre = [&]() {
    auto taille = window.GetSize();

    NkString titre = cfg.title;

    if (documentModifie)
        titre += "*";

    titre += " - ";
    titre += NkString::Fmtf("%u x %u", taille.x, taille.y);

    window.SetTitle(titre);
};
```
Le titre obtenu au démarrage est par exemple :

```
MonDocument - 1280 x 720
```

## 4. Mise à jour du titre au démarrage

J'appelle la fonction une première fois après la création de la fenêtre :

```
mettreAJourTitre();
```
Cela permet d'afficher immédiatement le nom du document et la taille initiale de la fenêtre.

## 5. Gestion du redimensionnement

J'ai ensuite ajouté la détection de l'événement 
```
NkWindowResizeEvent
```

Lorsque la taille de la fenêtre change, la fonction de mise à jour du titre est appelée :

```
if (e->Is<NkWindowResizeEvent>()) {
    mettreAJourTitre();
}
```
Ainsi, si la fenêtre passe par exemple de :

```
1280 x 720
```

à :

```
1000 x 600
```

le titre est automatiquement actualisé :

```
MonDocument - 1000 x 600
```

La mise à jour ne se fait donc pas à chaque image, mais lorsqu'un événement de redimensionnement est reçu.

## 6. Gestion de l'état modifié

Pour tester l'affichage de l'astérisque, j'ai utilisé l'événement clavier 
```
NkKeyPressEvent
```
La documentation présente bien `NkKeyPressEvent` comme l'événement correspondant à une touche pressée. J'ai donc utilisé cet événement pour modifier l'état du document.
J'ai ajouté :
```
if (e->Is<NkKeyPressEvent>()) {
    documentModifie = true;
    mettreAJourTitre();
}
```
Lorsqu'une touche est pressée, 
```
documentModifie
```
passe donc de false à true.

Le titre devient alors par exemple :
```
MonDocument* - 1280 x 720
```

## 7. Boucle principale
La gestion des événements dans mon programme est donc organisée ainsi :
```
while(NkEvent* e = NkEvents().PollEvent()) {
    if (e->Is<NkWindowCloseEvent>()) {
        window.Close();
    }

    if (e->Is<NkWindowResizeEvent>()) {
        mettreAJourTitre();
    }

    if (e->Is<NkKeyPressEvent>()) {
        documentModifie = true;
        mettreAJourTitre();
    }
}
```
La fonction mettreAJourTitre() n'est donc pas appelée continuellement dans la boucle principale.

## 8. Commandes utilisées

Pour construire et tester le programme, j'ai utilisé la commande Jenga depuis le dossier du projet :

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
║  Project: Exercice1_chap3      Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful            Time: 2.27s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED          
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2.27s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis j execute avec un 
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

[2026-09-26 12:07:14.786] [INF] [default] [main.cpp:40 in nkmain] -> Window: 1278x1278 | Display: 1278x1278 | DPI Scale: 1278

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (14.57s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Pour rechercher dans les fichiers du projet le nom de l'événement clavier disponible, j'ai utilisé :

```
Get-ChildItem -Recurse -Include *.h,*.hpp | Select-String "NkKey.*Event|Key.*Event"
```
Cette recherche m'a permis de confirmer la présence de NkKeyPressEvent dans les fichiers d'en-tête du projet.

## 10. Conclusion
Cet exercice m'a permis de mettre en place un titre de fenêtre contenant l'état du programme.
Le titre contient maintenant :

```
Nom du document + état de modification + largeur x hauteur
```
La mise à jour est déclenchée par les événements concernés :

* au lancement du programme ;
* lors d'un redimensionnement de la fenêtre ;
* lors d'une modification de l'état du document.

La mise à jour du titre n'est donc pas effectuée à chaque image, ce qui respecte la consigne de l'exercice.
