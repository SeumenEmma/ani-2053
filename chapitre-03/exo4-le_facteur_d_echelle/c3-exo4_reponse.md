# Le facteur d echelle
Dans cet exercice on doit afficher côte à côte :

- la taille rendue par la fenêtre ;
- la taille rendue par la cible de rendu ;
- le facteur d'échelle.

Le but est ensuite d'observer les valeurs obtenues sur mon système.

## 1. Configuration de la fenêtre

J'ai créé une fenêtre avec une taille initiale de :

- largeur : 1280 pixels ;
- hauteur : 720 pixels.

La fenêtre est également configurée pour être redimensionnable.

## 2. Récupération des informations

Après la création de la fenêtre, j'ai récupéré les informations nécessaires avec :

```
auto size = window.GetSize();
auto displaySize = window.GetDisplaySize();
float32 scale = window.GetDpiScale();
````
Puis je les ai affichées sur une seule ligne avec :

```
logger.Info(
    "Window: {}x{} | Display: {}x{} | DPI Scale: {}",
    size.x, size.y,
    displaySize.x, displaySize.y,
    scale
);
```

La première valeur correspond à la taille de la fenêtre. La deuxième correspond à la taille de la cible de rendu. La troisième correspond au facteur d'échelle.

## 3. Compilation
j ai d abord fait un
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
║  Project: Exercice1_chap3                                                 Kind: CONSOLE_APP ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 18.08s │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           18.08s
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

[2026-09-25 16:39:44.815] [INF] [default] [main.cpp:25 in nkmain] -> Window: 1278x1278 | Display: 1278x1278 | DPI Scale: 1278

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (3.88s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Le programme a affiché :

```
Window: 1278x1278 | Display: 1278x1278 | DPI Scale: 1278
```

## 5. Résultat

Les valeurs observées sont donc :

| Élément                     |      Valeur |
| --------------------------- | ----------: |
| Taille de la fenêtre        | 1278 × 1278 |
| Taille de la cible de rendu | 1278 × 1278 |
| Facteur d'échelle           |        1278 |

## 6. Observation

La taille de la fenêtre et celle de la cible de rendu sont identiques lors de mon test.

Le programme affiche également une valeur de `1278` pour le facteur d'échelle.

Ce résultat correspond à la valeur affichée par le programme lors de l'exécution sur mon système.

## 7. Conclusion

Cet exercice m'a permis d'utiliser les fonctions de `NkWindow` permettant de récupérer :

```
window.GetSize()
```

```
window.GetDisplaySize()
```

```
window.GetDpiScale()
```

J'ai ensuite affiché ces trois informations côte à côte dans la console afin de pouvoir comparer la taille de la fenêtre, la taille de la cible de rendu et le facteur d'échelle.

