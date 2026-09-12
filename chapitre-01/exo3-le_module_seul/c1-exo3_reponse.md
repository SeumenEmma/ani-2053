## Build Order (5 projects):
```
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)
```
pour construire NKMath j ai utilise la commande
```
jenga build --target NKMath
```
Jenga a detecte 5 projets pour la construction de l arbre dans l ordre suivant :
```
NKPlatform, NKCore, NKMemory, NKContainers, NKMath
```
Mais etant donne que l on a demande de mettre ce qui vient en premier en bas et NKMath en haut alors l ordre est :

```
NKMath  
   |  
NKContainers  
   |  
NKMemory  
   |  
NKCore  
   |  
NKPlateform
```

## Les dependances 
```
NKMath
|_____NKContenaires 
|          |___NKMemory
|          |
|          |___NKCore
|          |
|          |___NKPlateform
|  
|_____NKCore
|        |
|        |____NKPlateform
|         
|_____NkMemory
```

