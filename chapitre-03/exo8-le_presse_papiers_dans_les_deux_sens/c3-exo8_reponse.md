# Presse-papiers texte et image
Dans cet exercice il faut utiliser uniquement `NKWindow` pour manipuler le presse-papiers.

Le programme doit :

* lire le texte du presse-papiers ;
* transformer ce texte en majuscules ;
* remettre le texte transformé dans le presse-papiers ;
* lire une image du presse-papiers ;
* inverser ses composantes de couleur ;
* ne pas modifier son alpha ;
* remettre l'image modifiée dans le presse-papiers.

## 2. Recherche des fonctions dans `NkWindow.h`

Les fonctions du presse-papiers sont déclarées dans l'en-tête de 
```
NkWindow
```
J'ai recherché les fonctions liées au presse-papiers avec :

```
Get-ChildItem -Recurse -Filter "NkWindow.h" | Select-String -Pattern "Clipboard"
```

J'ai trouvé notamment :

```
void SetClipboardText(const NkString &text);
NkString GetClipboardText() const;

bool SetClipboardImage(const NkClipboardImage &image);
bool GetClipboardImage(NkClipboardImage &out) const;
bool HasClipboardImage() const;
```
La structure utilisée pour les images est :

```
struct NkClipboardImage {
    uint32 width = 0;
    uint32 height = 0;
    NkVector<uint8> pixels;

    bool IsValid() const {
        return width > 0 &&
               height > 0 &&
               pixels.Size() ==
                   static_cast<usize>(width) * height * 4u;
    }
};
```

L'image est stockée en RGBA8.
Cela signifie qu'il y a quatre composantes par pixel :

* R : rouge ;
* G : vert ;
* B : bleu ;
* A : alpha.

## 3. Traitement du texte

Le programme commence par lire le texte présent dans le presse-papiers :

```c
NkString texte = window.GetClipboardText();

logger.Info("Texte du presse-papiers avant : {}", texte);

texte = texte.ToUpper();

window.SetClipboardText(texte);

logger.Info("Texte remis dans le presse-papiers : {}", texte);
```

```
GetClipboardText()
``` 
récupère le contenu texte.

Ensuite :

```
texte = texte.ToUpper();
```
transforme le texte en majuscules.

Ensuite :

```
window.SetClipboardText(texte);
```

replace le texte transformé dans le presse-papiers.

## 4. Résultat réel du test du texte

Avant le lancement du programme, le texte présent dans le presse-papiers était :

```
Bonjour Nkentseu
```
Le programme a affiché :

```
Texte du presse-papiers avant : Bonjour Nkentseu
Texte remis dans le presse-papiers : BONJOUR NKENTSEU
```
ce que j ai obtenue avec jenga run :
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

[2026-09-28 01:52:58.298] [INF] [default] [main.cpp:45 in nkmain] -> Texte du presse-papiers avant : Bonjour Nkentseu
[2026-09-28 01:52:58.301] [INF] [default] [main.cpp:48 in nkmain] -> Texte remis dans le presse-papiers : BONJOUR NKENTSEU

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (3.49s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Le résultat montre donc que le texte a bien été :

1. lu 
2. transformé en majuscules 
3. remis dans le presse-papiers.

## 5. Vérification du presse-papiers image

Le programme vérifie d'abord si une image est déjà présente :

```
logger.Info("Image présente : {}", window.HasClipboardImage());
```

Lors du test, le résultat était :

```
Image présente : false
```
Cela signifie qu'aucune image n'a été récupérée depuis le presse-papiers avant notre test.
Pour vérifier le fonctionnement de l'API `NKWindow`, j'ai donc créé une petite image de test avec :

```
NkClipboardImage imageTest;

imageTest.width = 2;
imageTest.height = 2;

imageTest.pixels.Resize(16);

imageTest.pixels[0] = 255;
imageTest.pixels[1] = 0;
imageTest.pixels[2] = 0;
imageTest.pixels[3] = 255;
```

L'image possède :

* largeur : 2 pixels ;
* hauteur : 2 pixels ;
* 4 composantes par pixel ;
* format RGBA8 ;
* 32 bits par pixel.

## 6. Écriture et lecture de l'image

L'image est envoyée dans le presse-papiers avec :

```
bool imageEcrite = window.SetClipboardImage(imageTest);

logger.Info("Image ecrite : {}", imageEcrite);
```
Ensuite, elle est relue :

```
NkClipboardImage image;

bool imageLue = window.GetClipboardImage(image);

logger.Info("Image lue : {}", imageLue);
```

Le résultat obtenu est :

```
Image ecrite : true
Image lue : true
```
Cela prouve que 
```
NKWindow
``` 
a réussi à écrire puis à relire l'image.
voici ce qui me donne avec jenga run :
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

[2026-09-28 02:15:20.182] [INF] [default] [main.cpp:45 in nkmain] -> Texte du presse-papiers avant : logger.Info("Image ecrite : {}", imageEcrite);
[2026-09-28 02:15:20.187] [INF] [default] [main.cpp:48 in nkmain] -> Texte remis dans le presse-papiers : LOGGER.INFO("IMAGE ECRITE : {}", IMAGEECRITE);
[2026-09-28 02:15:20.188] [INF] [default] [main.cpp:49 in nkmain] -> Image presente : false
[2026-09-28 02:15:20.196] [INF] [default] [main.cpp:59 in nkmain] -> Image ecrite : true
[2026-09-28 02:15:20.200] [INF] [default] [main.cpp:62 in nkmain] -> Image lue : true

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (4.34s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## 7. Dimensions et nombre de bits par pixel

Le programme affiche les caractéristiques de l'image :

```
logger.Info(
    "Image : {} x {} | 32 bits par pixel",
    image.width,
    image.height
);
```

Le résultat réel est :

```
Image : 2 x 2 | 32 bits par pixel
```

## 8. Inversion des couleurs

L'exercice demande d'inverser les couleurs sans inverser l'alpha.

Le programme utilise :

```
for (usize i = 0; i + 3 < image.pixels.Size(); i += 4) {
    image.pixels[i]     = 255 - image.pixels[i];
    image.pixels[i + 1] = 255 - image.pixels[i + 1];
    image.pixels[i + 2] = 255 - image.pixels[i + 2];
}
```

Chaque pixel contient quatre valeurs :

```
R G B A
```

Les trois premières composantes sont inversées :

```
R → 255 - R
G → 255 - G
B → 255 - B
```

La composante alpha A n'est pas modifiée.

C'est important car inverser l'alpha pourrait modifier la transparence de l'image et rendre l'image invisible ou transparente à des endroits où elle ne devrait pas l'être.

## 9. Remise de l'image inversée

Après l'inversion des couleurs, l'image est remise dans le presse-papiers :

```
bool imageRemise = window.SetClipboardImage(image);

logger.Info(
    "Image remise dans le presse-papiers : {}",
    imageRemise
);
```

Le résultat obtenu est :
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

[2026-09-28 02:17:54.780] [INF] [default] [main.cpp:45 in nkmain] -> Texte du presse-papiers avant : 
????????????????????????????????????????????????????????????????????
?                                                                  ?
?                ???????????????   ??? ???????  ??????             ?
?                ????????????????  ??????????? ????????            ?
?                ?????????  ?????? ??????  ????????????            ?
?           ??   ?????????  ?????????????   ???????????            ?
?           ??????????????????? ??????????????????  ???            ?
?            ?????? ???????????  ????? ??????? ???  ???            ?
?                                                                  ?
?             Multi-platform C/C++ Build System v2.8.2             ?
?                                                                  ?
????????????????????????????????????????????????????????????????????


????????????????????????????????????????????????????????????????????????????????
  ?  EXECUTION  -  Exercice1_chap3.exe
     C:\Users\emmas\OneDrive\Documents\Exercice_1\Build\Bin\Debug-Windows\Exercice1_chap3\Exercice1_chap3.exe
????????????????????????????????????????????????????????????????????????????????

[2026-09-28 02:15:20.182] [INF] [default] [main.cpp:45 in nkmain] -> Texte du presse-papiers avant : logger.Info("Image ecrite : {}", imageEcrite);
[2026-09-28 02:15:20.187] [INF] [default] [main.cpp:48 in nkmain] -> Texte remis dans le presse-papiers : LOGGER.INFO("IMAGE ECRITE : {}", IMAGEECRITE);
[2026-09-28 02:15:20.188] [INF] [default] [main.cpp:49 in nkmain] -> Image presente : false
[2026-09-28 02:15:20.196] [INF] [default] [main.cpp:59 in nkmain] -> Image ecrite : true
[2026-09-28 02:15:20.200] [INF] [default] [main.cpp:62 in nkmain] -> Image lue : true

????????????????????????????????????????????????????????????????????????????????
  ?  FIN D'EXECUTION  -  termine normalement  (4.34s)
????????????????????????????????????????????????????????????????????????????????
[2026-09-28 02:17:54.787] [INF] [default] [main.cpp:48 in nkmain] -> Texte remis dans le presse-papiers : 
????????????????????????????????????????????????????????????????????
?                                                                  ?
?                ???????????????   ??? ???????  ??????             ?
?                ????????????????  ??????????? ????????            ?
?                ?????????  ?????? ??????  ????????????            ?
?           ??   ?????????  ?????????????   ???????????            ?
?           ??????????????????? ??????????????????  ???            ?
?            ?????? ???????????  ????? ??????? ???  ???            ?
?                                                                  ?
?             MULTI-PLATFORM C/C++ BUILD SYSTEM V2.8.2             ?
?                                                                  ?
????????????????????????????????????????????????????????????????????


????????????????????????????????????????????????????????????????????????????????
  ?  EXECUTION  -  EXERCICE1_CHAP3.EXE
     C:\USERS\EMMAS\ONEDRIVE\DOCUMENTS\EXERCICE_1\BUILD\BIN\DEBUG-WINDOWS\EXERCICE1_CHAP3\EXERCICE1_CHAP3.EXE
????????????????????????????????????????????????????????????????????????????????

[2026-09-28 02:15:20.182] [INF] [DEFAULT] [MAIN.CPP:45 IN NKMAIN] -> TEXTE DU PRESSE-PAPIERS AVANT : LOGGER.INFO("IMAGE ECRITE : {}", IMAGEECRITE);
[2026-09-28 02:15:20.187] [INF] [DEFAULT] [MAIN.CPP:48 IN NKMAIN] -> TEXTE REMIS DANS LE PRESSE-PAPIERS : LOGGER.INFO("IMAGE ECRITE : {}", IMAGEECRITE);
[2026-09-28 02:15:20.188] [INF] [DEFAULT] [MAIN.CPP:49 IN NKMAIN] -> IMAGE PRESENTE : FALSE
[2026-09-28 02:15:20.196] [INF] [DEFAULT] [MAIN.CPP:59 IN NKMAIN] -> IMAGE ECRITE : TRUE
[2026-09-28 02:15:20.200] [INF] [DEFAULT] [MAIN.CPP:62 IN NKMAIN] -> IMAGE LUE : TRUE

????????????????????????????????????????????????????????????????????????????????
  ?  FIN D'EXECUTION  -  TERMINE NORMALEMENT  (4.34S)
????????????????????????????????????????????????????????????????????????????????
[2026-09-28 02:17:54.790] [INF] [default] [main.cpp:49 in nkmain] -> Image presente : false
[2026-09-28 02:17:54.797] [INF] [default] [main.cpp:59 in nkmain] -> Image ecrite : true
[2026-09-28 02:17:54.801] [INF] [default] [main.cpp:62 in nkmain] -> Image lue : true
[2026-09-28 02:17:54.802] [INF] [default] [main.cpp:63 in nkmain] -> Image : 2 x 2 | 32 bits par pixel

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (4.74s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\emmas\OneDrive\Documents\Exercice_1> 
```

Cela confirme que l'image modifiée a bien été remise dans le presse-papiers.

## 13. Preuve finale de fonctionnement

La dernière exécution a donné :

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

[2026-09-28 02:26:17.683] [INF] [default] [main.cpp:45 in nkmain] -> Texte du presse-papiers avant : Bonjour Nkentseu
[2026-09-28 02:26:17.687] [INF] [default] [main.cpp:48 in nkmain] -> Texte remis dans le presse-papiers : BONJOUR NKENTSEU
[2026-09-28 02:26:17.688] [INF] [default] [main.cpp:49 in nkmain] -> Image presente : false
[2026-09-28 02:26:17.696] [INF] [default] [main.cpp:59 in nkmain] -> Image ecrite : true
[2026-09-28 02:26:17.701] [INF] [default] [main.cpp:62 in nkmain] -> Image lue : true
[2026-09-28 02:26:17.704] [INF] [default] [main.cpp:63 in nkmain] -> Image : 2 x 2 | 32 bits par pixel
[2026-09-28 02:26:17.747] [INF] [default] [main.cpp:70 in nkmain] -> Image remise dans le presse-papiers : true
[2026-09-28 02:26:17.758] [INF] [default] [main.cpp:73 in nkmain] -> Image finale relue : true

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (3.56s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\emmas\OneDrive\Documents\Exercice_1> 
```

## 14. Conclusion

L'exercice a été réalisé en utilisant les fonctions publiques de NKWindow pour manipuler le presse-papiers.
Pour le texte, le programme a réellement lu :

```
Bonjour Nkentseu
```
et l'a remis sous la forme :

```
BONJOUR NKENTSEU
```
Pour l'image, aucune image n'était présente dans le presse-papiers au début du test :

```
Image présente : false
```