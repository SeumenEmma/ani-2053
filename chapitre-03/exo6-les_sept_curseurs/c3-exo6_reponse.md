# Curseur selon la zone de la fenêtre
Dans cet exercice ont doit découper la fenêtre en sept zones et changer la forme du curseur selon la zone survolée. Et de faire une deuxième expérience : définir le curseur une seule fois au démarrage du programme et observer ce qui se passe lorsque la souris se déplace ensuite dans les différentes zones.

## 1. Les sept zones

J'ai choisi de découper la fenêtre en sept zones verticales de largeur approximativement égale.

La fenêtre est donc organisée de cette manière :

```
┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
│ Zone 1 │ Zone 2 │ Zone 3 │ Zone 4 │ Zone 5 │ Zone 6 │ Zone 7 │
│        │        │        │        │        │        │        │
└────────┴────────┴────────┴────────┴────────┴────────┴────────┘
```
J'ai récupéré la taille de la fenêtre avec :
```
auto taille = window.GetSize();
```
Puis j'ai calculé la largeur d'une zone :
```
uint32 largeurZone = taille.x / 7;
```
Pour déterminer dans quelle zone se trouve la souris, j'utilise sa position horizontale x :
```
uint32 zone = (x * 7) / taille.x;
```
J'ai associé une forme de curseur différente à chaque zone qui sont :
```
- Arrow
- TextInput
- Hand
- ResizeNS
- ResizeWE
- ResizeNWSE
- ResizeNESW
```
Ensuite j ai utilise le code 
```
if (e->Is<NkMouseMoveEvent>()) {
    auto* mouse = e->As<NkMouseMoveEvent>();

    int x = mouse->GetX();
    int y = mouse->GetY();

    auto taille = window.GetSize();
    uint32 largeurZone = taille.x / 7;

    uint32 zone = (x * 7) / taille.x;
}
```
pour pouvoir recuperer la position de la souris et j utilise NkMouseMoveEvent pour detecter le deplacement de la souris.
Ensuite j ai utilise SetCursor() pour associer une forme differentes a chaque zone: 
```
switch (zone) {
    case 0:
        window.SetCursor(NkWindow::NkCursorType::Arrow);
        break;

    case 1:
        window.SetCursor(NkWindow::NkCursorType::TextInput);
        break;

    case 2:
        window.SetCursor(NkWindow::NkCursorType::Hand);
        break;

    case 3:
        window.SetCursor(NkWindow::NkCursorType::ResizeNS);
        break;

    case 4:
        window.SetCursor(NkWindow::NkCursorType::ResizeWE);
        break;

    case 5:
        window.SetCursor(NkWindow::NkCursorType::ResizeNWSE);
        break;

    case 6:
        window.SetCursor(NkWindow::NkCursorType::ResizeNESW);
        break;
}
```
Le changement du curseur est effectué lorsqu'un événement NkMouseMoveEvent est reçu.

## 2. Commande de compilation 
pour compiler j ai utilise la commande :
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
│  ✓ Build Successful            Time: 1.73s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED          
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1.73s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
puis j ai fait un 
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

[2026-09-26 15:43:33.374] [INF] [default] [main.cpp:41 in nkmain] -> Window: 1278x1278 | Display: 1278x1278 | DPI Scale: 1278

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (9.10s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
J'ai également utilisé une recherche pour retrouver les fonctions et événements disponibles dans ma version de Nkentseu pour trouver les fonctions liees au curseur et a la souris. j ai utilise :
```
Get-ChildItem -Recurse -Include *.h,*.hpp | Select-String "SetCursor|Cursor|Mouse.*Position|Mouse.*Pos"
```
```
Get-ChildItem -Recurse -Include *.h,*.hpp | Select-String "NkCursorType"
```
```
Get-ChildItem -Recurse -Include *.h,*.hpp | Select-String "NkMouseMoveEvent"
```
## 3. Experience avec SetCursor()

Après avoir vérifié que les sept zones fonctionnaient J'ai placé un seul appel à SetCursor() au démarrage de la fenêtre qui est :
```
window.SetCursor(NkWindow::NkCursorType::Hand);
```
J'ai ensuite retiré le switch qui modifiait le curseur lors des déplacements de la souris.

## 4. Ce que j'ai réellement observé

### Première expérience

Lorsque le changement de curseur était effectué dans NkMouseMoveEvent, le curseur changeait lorsque je déplaçais la souris d'une zone à une autre.

En déplaçant la souris progressivement de gauche à droite, j'observais les différentes formes de curseur correspondant aux sept zones. Les sept zones fonctionnaient donc correctement.

### Deuxième expérience

J'ai ensuite placé :
```
window.SetCursor(NkWindow::NkCursorType::Hand);
```
une seule fois au démarrage.

Après cela, j'ai déplacé la souris dans les sept zones. J'ai constaté que le curseur restait sous la forme d'une main dans les différentes zones. Il ne changeait plus automatiquement lorsque je passais d'une zone à une autre. Cela montre que le curseur conserve la forme qui lui a été attribuée tant qu'un autre appel à SetCursor() ne vient pas la modifier.

## Formes des curseurs sur la fenetre 
```
| Zone  | Ce que tu dois voir        |
| ----- | -------------------------- |
| 1 | ➤ curseur normal/flèche       |
| 2 | curseur texte `I`              |
| 3 | ✋ main                        |
| 4 | ↕ redimensionnement vertical   |
| 5 | ↔ redimensionnement horizontal |
| 6 | ↘ redimensionnement diagonal   |
| 7 | ↗ redimensionnement diagonal   |
```