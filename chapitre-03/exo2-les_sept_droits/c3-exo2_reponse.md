#  Les sept droits de la fenêtre

Pour cet exercice il faut tester les sept droits disponibles pour la fenêtre.
Pour chaque test, un seul droit est désactivé tandis que les six autres restent activés.
Pour chaque fenêtre, j'observe ensuite ce que l'utilisateur ne peut plus faire.

## 1. Droit resizable

Le droit 
```
resizable
``` 
concerne la possibilité de redimensionner la fenêtre.

Configuration testée :

```
cfg.resizable = false;
```

Observation :
J ai teste la fenetre est sence ne plus se redimentionner mais ca redimentionne.

j ai fait un 
```
jenga build
```
puis un 
```
jenga run
```

## 2. Droit movable

Le droit 
```
movable
``` 
concerne la possibilité de déplacer la fenêtre.

Configuration testée :

```
cfg.movable = false;
```
Observation :

ici j ai teste le fenetre est sence ne pas se deplacer mais ca se deplace toujours.

## 3. Droit closable

Le droit 
```
closable
``` 
concerne la possibilité de fermer la fenêtre avec le bouton de fermeture.

Configuration testée :

```
cfg.closable = false;
```
Observation :
ici il consiste a ferme le fenetre avec le bouton de fermeture je teste mais ca ne fonctionne pas.

## 4. Droit minimizable

Le droit 
```
minimizable
``` 
concerne la possibilité de réduire la fenêtre.

Configuration testée :

```
cfg.minimizable = false;
```
Observation :
J ai teste mais la possibilite de reduire la fenetre ne reduit pas.

## 5. Droit maximizable

Le droit 
```
maximizable
``` 
concerne la possibilité d'agrandir la fenêtre.

Configuration testée :

```
cfg.maximizable = false;
```
Observation :
ici en mettant la valeur a false c est sence ne plus agrandir la fenetre mais ca agrandit toujours la fenetre.

## 6. Droit canFullscreen

Le droit 
```
canFullscreen
``` 
concerne la possibilité de passer la fenêtre en plein écran.

Configuration testée :

```
cfg.canFullscreen = false;
```

Observation :
ici la fenetre doit etre en plein ecran mais en mettant la valeur false c est sence ne plus accepter le plein ecran mais ca accepte toujours.

## 7. Droit modal

Le droit 
```
modal
``` 
concerne le comportement modal de la fenêtre.

Configuration testée :

```
cfg.modal = false;
```

Observation :
En mettant la valeur false ca ne fonctionne toujours pas.

## Conclusion

Les sept tests permettent d'observer l'effet de chaque droit individuellement. Pour chaque expérience, un seul paramètre est désactivé afin de pouvoir identifier précisément son effet sur le comportement de la fenêtre.
