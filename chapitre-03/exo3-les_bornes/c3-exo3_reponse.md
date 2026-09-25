# Taille minimale de la fenetre 

J'ai lancé le programme puis j'ai essayé de réduire la fenêtre progressivement à l'aide de la souris. J ai utilise :
```
 cfg.minHeight = 60;
    cfg.minWidth = 60;
```
jusqu a pour atteindre la taille minimale 
je tapais la commande :
```
jenga build 
```
puis 
```
jenga run
```
a chaque fois pour voir l execution. Donc pour ma fenetre la largeur minimale demandée est donc de 60 pixels et la hauteur minimale demandée est de 60 pixels.
La fenêtre reste redimensionnable grâce à :
```
cfg.resizable = true;
```
J'ai essayé de passer en dessous de la limite de 60 × 60 pixels afin de vérifier le comportement de la fenêtre.

## Observation

La plus petite taille que j'ai pu obtenir est :
```
Largeur : 60
Hauteur : 60
```
Lorsque j'essaie de réduire davantage la fenêtre, elle ne descend plus en dessous de cette taille.

## Conclusion

La configuration :

```
cfg.minWidth = 60;
cfg.minHeight = 60;
```
permet de définir une taille minimale pour la fenêtre. Le redimensionnement reste possible, mais la fenêtre ne peut pas être réduite en dessous de la limite imposée par ces bornes.
