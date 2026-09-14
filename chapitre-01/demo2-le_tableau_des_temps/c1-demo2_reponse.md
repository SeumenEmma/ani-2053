## Construction complete a froid

J ai utiliser la commande :
```
Measure-Command { jenga build }
```
### Resultat
```
Days              : 0
Hours             : 0
Minutes           : 2
Seconds           : 17
Milliseconds      : 826
```
Construction complète à froid = 17s

## Construction complète à chaud

J ai utiliser la commande :
```
Measure-Command { jenga build }
```
### Resultat
```
Days              : 0
Hours             : 0
Minutes           : 1
Seconds           : 29
Milliseconds      : 815
```
Construction complète à chaud = 29s

## construction d'un seul module

Le module que j utilise est NKMath. J ai tape la commande :
```
Measure-Command { jenga build --target NKMath }
```

### Resultat
```
Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 11
Milliseconds      : 242
```
Construction d'un seul module : 11s

## Modification d'un seul fichier source .cpp

J ai tape la commande :
```
notepad ".\Kernel\Foundation\NKMath\src\NKMath\NkMat.cpp"
```
Pour pouvoir ouvrir NKMath.cpp
Apres j ai tape :
```
Measure-Command { jenga build --target NKMath }
```
### Resultat 
```
Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 7
Milliseconds      : 111
```
Modification d'un seul fichier source .cpp = 7s

## Modification d'un seul fichier .h

J ai tape la commande :
```
notepad ".\Kernel\Foundation\NKMath\src\NKMath\NkMat.h"
```
pour ouvrir NKMath.h
apres 
```
Measure-Command { jenga build --target NKMath }
```
### Resultat
```
Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 4
Milliseconds      : 606
```
Modification d'un seul fichier .h : 4s

