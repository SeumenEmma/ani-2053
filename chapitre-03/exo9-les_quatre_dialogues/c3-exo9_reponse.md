# Les quatre dialogues natifs
Dans cet exercice il faut utiliser les quatre dialogues natifs qui sont :

1. Ouvrir un fichier
2. Enregistrer un fichier
3. Choisir un dossier
4. Afficher un message

J'ai recherché les fonctions disponibles dans les fichiers d'en-tête publics de NkWindow.

Le fichier `NkWindow.h` inclut :

```
#include "Core/NkDialogs.h"
```
Les fonctions utilisées sont :

```
static NkDialogResult OpenFileDialog(
    const NkString &filter = "*.*",
    const NkString &title = "Open File"
);

static NkDialogResult SaveFileDialog(
    const NkString &defaultExt = "",
    const NkString &title = "Save File"
);

static NkDialogResult OpenFolderDialog(
    const NkString &title = "Selectionner un dossier"
);

static void OpenMessageBox(
    const NkString &message,
    const NkString &title = "Message",
    int type = 0
);
```

Le résultat des trois premiers dialogues est de type :

```
NkDialogResult
```
Cette structure contient notamment :
```
bool confirmed;
NkString path;
```
`confirmed` permet de savoir si l'utilisateur a validé son choix.

## 3. Dialogue « Ouvrir un fichier »

J'ai utilisé :

```
NkDialogResult ouvrir =
    NkDialogs::OpenFileDialog("*.*", "Ouvrir un fichier");

if (ouvrir.confirmed) {
    logger.Info("Fichier choisi : {}", ouvrir.path);
} else {
    logger.Info("Ouverture du fichier annulee.");
}
```

### Test effectué

J'ai fermé/annulé le dialogue sans sélectionner de fichier.

Résultat obtenu :

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

[2026-09-28 03:57:56.671] [INF] [default] [main.cpp:48 in nkmain] -> Ouverture du fichier annulee.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (112.82s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Le programme s'est terminé normalement.

## 4. Dialogue « Enregistrer un fichier »

J'ai utilisé :

```
NkDialogResult enregistrer =
    NkDialogs::SaveFileDialog("txt", "Enregistrer un fichier");

if (enregistrer.confirmed) {
    logger.Info("Fichier a enregistrer : {}", enregistrer.path);
} else {
    logger.Info("Enregistrement annule.");
}
```


### Test effectué

J'ai annulé le dialogue d'enregistrement.

Résultat obtenu :

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

[2026-09-28 04:05:31.686] [INF] [default] [main.cpp:48 in nkmain] -> Ouverture du fichier annulee.
[2026-09-28 04:05:33.401] [INF] [default] [main.cpp:54 in nkmain] -> Enregistrement annule.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (80.87s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Le programme s'est terminé normalement.

## 5. Dialogue « Choisir un dossier »

J'ai utilisé :

```
NkDialogResult dossier =
    NkDialogs::OpenFolderDialog("Choisir un dossier");

if (dossier.confirmed) {
    logger.Info("Dossier choisi : {}", dossier.path);
} else {
    logger.Info("Selection du dossier annulee.");
}
```


### Test avec sélection d'un dossier

J'ai sélectionné un dossier.

Le programme a affiché :

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

[2026-09-28 04:07:54.702] [INF] [default] [main.cpp:48 in nkmain] -> Ouverture du fichier annulee.
[2026-09-28 04:07:56.501] [INF] [default] [main.cpp:54 in nkmain] -> Enregistrement annule.
[2026-09-28 04:08:20.937] [INF] [default] [main.cpp:58 in nkmain] -> Dossier choisi : C:\Users\emmas\OneDrive\Pi?s jointes\c++jeux?????

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (63.85s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

Certains caractères accentués apparaissent incorrectement dans le terminal, mais le programme a bien récupéré et affiché un chemin.

### Test avec annulation

J'ai ensuite fermé/annulé le dialogue sans sélectionner de dossier.

Résultat :

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

[2026-09-28 04:09:11.046] [INF] [default] [main.cpp:48 in nkmain] -> Ouverture du fichier annulee.
[2026-09-28 04:09:12.327] [INF] [default] [main.cpp:54 in nkmain] -> Enregistrement annule.
[2026-09-28 04:09:15.077] [INF] [default] [main.cpp:60 in nkmain] -> Selection du dossier annulee.
```

Le programme s'est terminé normalement.

## 6. Dialogue « Afficher un message »

Pour le quatrième dialogue, j'ai utilisé :

```
NkDialogs::OpenMessageBox(
    "Test du dialogue de message.",
    "Message"
);
```

Contrairement aux trois premiers dialogues, OpenMessageBox ne renvoie pas de NkDialogResult.
Le but du test était donc de vérifier que la boîte de message pouvait être affichée puis fermée sans provoquer de plantage.

### Test effectué

J'ai affiché puis fermé la boîte de message.

Le programme s'est terminé normalement :

```
FIN D'EXECUTION — termine normalement
```

## 8. Vérification de l'annulation

Les trois dialogues qui retournent un `NkDialogResult` ont été testés avec une annulation :

| Dialogue               | Annulation testée | Résultat       |
| ---------------------- | ----------------- | -------------- |
| Ouvrir un fichier      | Oui               | Aucun plantage |
| Enregistrer un fichier | Oui               | Aucun plantage |
| Choisir un dossier     | Oui               | Aucun plantage |
| Afficher un message    | Fermeture testée  | Aucun plantage |

Les différents tests ont montré que la fermeture ou l'annulation des dialogues ne provoque pas de plantage du programme.


## 10. Conclusion

Cet exercice m'a permis d'utiliser les quatre dialogues natifs :

* ouverture d'un fichier ;
* enregistrement d'un fichier ;
* sélection d'un dossier ;
* affichage d'un message.

Pour les dialogues de fichier et de dossier, j'ai utilisé `confirmed` afin de distinguer une validation d'une annulation. J'ai vérifié en particulier que l'utilisateur peut fermer ou annuler les boîtes de dialogue sans faire planter le programme. 
Une sélection réelle de fichier dans le dialogue « Ouvrir un fichier » n'a pas pu être vérifiée dans mon dernier test, car la boîte de dialogue ne m'a pas permis d'afficher/sélectionner les fichiers de ma machine. 
