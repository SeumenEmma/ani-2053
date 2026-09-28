# Deux fenêtres et identification des clics
 Dans cet exercice il faut ouvrir deux fenêtres et d'afficher dans le journal quelle fenêtre reçoit chaque clic gauche.
L'exercice demande également d'expliquer ce qui manquerait pour pouvoir dessiner indépendamment dans les deux fenêtres.

## 1. Création des deux fenêtres

J'ai créé deux configurations différentes :

* la première fenêtre est appelée `window` ;
* la deuxième fenêtre est appelée `window2`.

La deuxième fenêtre utilise une taille de `800 x 600`.

```
NkWindowConfig cfg;
NkWindowConfig cfg2;

cfg2.title = "Deuxieme fenetre";
cfg2.width = 800;
cfg2.height = 600;

NkWindow window2(cfg2);
```
Puis j'ai créé la première fenêtre avec la configuration utilisée dans les exercices précédents :

```
cfg.title = "MonDocument";
cfg.width = 1280;
cfg.height = 720;

NkWindow window(cfg);
```

## 2. Récupération des identifiants des fenêtres

Pour savoir quelle fenêtre reçoit un événement, j'ai récupéré son identifiant avec `GetId()`.

```
NkWindowId id2 = window2.GetId();
NkWindowId id1 = window.GetId();

std::cout << "ID fenetre 2 : " << id2 << std::endl;
std::cout << "ID fenetre 1 : " << id1 << std::endl;
```
Les identifiants attribués par le système ont été :

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

ID fenetre 2 : 1
ID fenetre 1 : 2

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (8.87s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

L'ordre des identifiants n'est pas important. Ce qui compte est que chaque objet NkWindow possède son propre identifiant.

## 3. Vérification de l'ouverture des fenêtres

J'ai vérifié que les deux fenêtres ont bien été créées.

Pour la deuxième fenêtre :

```
if (!window2.IsOpen()) {
    logger.Error("[app] creation de la deuxieme fenetre echouee");
    return -1;
}
```

Pour la première fenêtre :

```
if (!window.IsOpen()) {
    logger.Error("[app] creation fenetre echouee");
    return -1;
}
```

## 4. Gestion de la fermeture des deux fenêtres

La boucle principale continue tant qu'au moins une des deux fenêtres est ouverte :

```
while (window.IsOpen() || window2.IsOpen()) {
```
Lorsqu'un événement de fermeture est reçu, je récupère l'identifiant de la fenêtre concernée :

```
if (e->Is<NkWindowCloseEvent>()) {
    auto *event = e->As<NkWindowCloseEvent>();

    if (event->GetWindowId() == id1) {
        window.Close();
    }
    else if (event->GetWindowId() == id2) {
        window2.Close();
    }
}
```
Cela permet de fermer uniquement la fenêtre qui a demandé à être fermée.

## 5. Détection des clics

J'ai ajouté l'en-tête nécessaire pour utiliser les événements de souris :

```
#include "NKEvent/NkMouseEvent.h"
```
J'ai ensuite enregistré pour les événements NkMouseButtonPressEvent :

```
NkEvents().AddEventCallback<NkMouseButtonPressEvent>(
    [&](NkMouseButtonPressEvent *event) {

        if (event->IsLeft()) {

            if (event->GetWindowId() == id1) {
                std::cout << "Clic gauche reçu par la fenêtre 1" << std::endl;
            }
            else if (event->GetWindowId() == id2) {
                std::cout << "Clic gauche reçu par la fenêtre 2" << std::endl;
            }
        }
    }
);
```

Le programme vérifie d'abord que le bouton gauche de la souris a été utilisé avec :

```
event->IsLeft()
```

Puis il récupère l'identifiant de la fenêtre ayant reçu l'événement avec :

```
event->GetWindowId()
```

L'identifiant est ensuite comparé avec `id1` et `id2`.

## 6. Compilation

Pour compiler le projet, j'ai utilisé :

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
✓ All files up to date

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful            Time: 0.11s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED          
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.11s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
La compilation s'est terminée correctement.

## 7. Exécution

J'ai lancé le programme avec :

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

ID fenetre 2 : 1
ID fenetre 1 : 2
Clic gauche re├ºu par la fen├¬tre 1
Clic gauche re├ºu par la fen├¬tre 1
Clic gauche re├ºu par la fen├¬tre 2
Clic gauche re├ºu par la fen├¬tre 2
Clic gauche re├ºu par la fen├¬tre 2

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (14.65s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## 8. Observation

Le résultat montre que l'événement de souris contient suffisamment d'informations pour savoir quelle fenêtre l'a reçu.
```
event->GetWindowId()
```
permet d'identifier la fenêtre concernée. Les deux fenêtres peuvent donc recevoir des clics et le programme peut traiter ces clics séparément.

## 9. Ce qui manquerait pour dessiner dans les deux fenêtres

Pour dessiner indépendamment dans les deux fenêtres, il faudrait en plus disposer d'un moyen d'accéder au contexte ou à la cible de rendu associée à chaque fenêtre.

Il faudrait pouvoir :
1. identifier la fenêtre à dessiner ;
2. sélectionner son contexte ou sa surface de rendu ;
3. effectuer les opérations de dessin dans cette cible ;
4. présenter le résultat dans la bonne fenêtre.

Dans cet exercice, nous savons identifier la fenêtre qui reçoit un événement grâce à son `NkWindowId`, mais nous n'avons pas utilisé de mécanisme permettant de sélectionner une cible de rendu différente pour chaque fenêtre.