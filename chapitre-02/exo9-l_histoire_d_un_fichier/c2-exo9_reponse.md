# Histoire d'un fichier du moteur : NkMat.cpp

## Fichier choisi

J'ai choisi le fichier :
```
Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp
```
Puis vérifie que Git fonctionne avec la commande :
```
git status
```
ensuite pour pouvoir reconstruire le fichier il faut voir l historique des derniers commits j ai donc utiliser la commande 
```
git log --follow --stat --oneline -- "Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp"
``` 
ce qui me donne :
```
bdda350a style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
 Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)
d557314e update
 {Modules => Kernel}/Foundation/NKMath/src/NKMath/NkMat.cpp | 0
 1 file changed, 0 insertions(+), 0 deletions(-)
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
 Modules/Foundation/NKMath/src/NKMath/NkMat.cpp | 7 +++++++
 1 file changed, 7 insertions(+)
```
Et pour avoir les modifications détaillées j ai utilise :
```
git log --follow -p -- "Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp"
```
ce qui me donne :
```
commit bdda350a054705f217f0daf5a54ab02bcb9c56ef
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Thu Jul 9 16:53:52 2026 +0100

    style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
    
    Applique le .clang-format maison a tout l'arbre source C++ :
    - indentation par namespace (NamespaceIndentation: All)
    - public/private/protected indentes sous class (IndentAccessModifiers)
    - une ligne vide entre definitions (SeparateDefinitionBlocks)
    - une instruction par ligne, accolades attachees, tabs
    
    1748 fichiers (.h/.cpp/.inl/.mm). Verifie : NKGptTrain 25/25 et renderdemo 28/28 buildent OK apres reformatage.

diff --git a/Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp b/Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp
index fa653800..4e539ef6 100644
--- a/Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp
+++ b/Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp
@@ -1,7 +1,5 @@
 #include "NkMat.h"
 
 namespace nkentseu {
-    namespace math {
-        
-    }
-}
\ No newline at end of file
+       namespace math {}
```
Maintenant on veut identifier les 3 moments ou il a le plus change pour ca on doit afficher l historique complet avec la commande :
```
git log --follow --format="%H | %ad | %s" --date=short -- "Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp"
```
ce qui me donne :
```
bdda350a054705f217f0daf5a54ab02bcb9c56ef | 2026-07-09 | style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
d557314e707baf17e53029b9d9cae2c5164dd417 | 2026-05-05 | update
9c49f79fc1d5eabac6df981bfd6996abe1e7f4bf | 2026-03-21 | bug fix vulkan opengl dx11 current bug software and dx12
```
ensuite je tape :
```
git show --stat --summary 9c49f79fc1d5eabac6df981bfd6996abe1e7f4bf -- "Modules\Foundation\NKMath\src\NKMath\NkMat.cpp"
```
ce qui me donne :
```
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Sat Mar 21 03:25:48 2026 +0100

    bug fix vulkan opengl dx11 current bug software and dx12

 Modules/Foundation/NKMath/src/NKMath/NkMat.cpp | 7 +++++++
 1 file changed, 7 insertions(+)
 create mode 100644 Modules/Foundation/NKMath/src/NKMath/NkMat.cpp
```
pour pouvoir bien vrifier la date de creation.

## Date de création du fichier

Le fichier a été créé le **21 mars 2026** dans le commit :
```9c49f79fc1d5eabac6df981bfd6996abe1e7f4bf
```
Message du commit :
```
> bug fix vulkan opengl dx11 current bug software and dx12
```
Le commit indique que ce changement correspond à une correction de bug concernant Vulkan, OpenGL, DX11, le mode software et DX12.

Le fichier a ete cree dans :
```
Modules/Foundation/NKMath/src/NKMath/NkMat.cpp
```

Le commit ajoute **7 lignes** et Git indique explicitement :
```
create mode 100644 Modules/Foundation/NKMath/src/NKMath/NkMat.cpp
```

## Les trois moments ou le fichier a le plus changé

### 1. 21 mars 2026 

ce Commit a pour identifiant : 9c49f79f

Le fichier est créé et 7 lignes sont ajoutées.

Le message du commit indique que le but est de corriger un problème concernant : Vulkan, OpenGL, DX11, software et DX12.

### 2. 5 mai 2026 

ce Commit a pour identifiant : d557314e
son message est:
```
update
```
Le fichier est déplacé de :
```
Modules/Foundation/NKMath/src/NKMath/NkMat.cpp
```
vers :
```
Kernel/Foundation/NKMath/src/NKMath/NkMat.cpp
```

### 3. 9 juillet 2026 

ce Commit a pour identifiant : bdda350a
son message est:
```
style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
```
## conclusion

L'histoire de NkMat.cpp montre trois étapes : sa création le 21 mars 2026, son déplacement le 5 mai, puis son reformatage le 9 juillet. Les messages de commit permettent donc de distinguer les raisons des changements.