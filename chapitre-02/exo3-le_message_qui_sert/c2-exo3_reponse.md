## Les commits du moteur 

J ai analyse trois commits de Nkentseu afin de verifier si leur message indique clairement ce qu ils font.

### Commit 1

pour trouver les differents commits j ai tape 
```
git log --online -n 10 
```
Et ca m as envoye plusieurs commits que parmis lesquels j ai choisi 3 qui sont :
```
9c3fad33 (HEAD -> main, origin/transit, origin/main, origin/HEAD) transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)
```
#### Dit il ce qu il fait ?
Ici de maniere generale on peut dire que le message indique que huit chantiers ont ete fusionner et que le resultat est pret pour la relecture.

#### Pourquoi ??

Le message donne une information sur l objectif du commit et l etat de travail qui est 226/226 mais n indique pas les modifications des differents fichiers.

#### Porte t il un seul sujet ?

Non le commit regroupe plusieurs modifications grace a la commande 
```
git show --stat --oneline 9c3fad33 
```
il montre des modifications dans de nombreux fichiers du projet.

### commit 2

Pour le deuxieme commits j ai choisi :
```
07845c6c (origin/chantier/banc-coherence-registre) Garde des chemins partages rapatriee vers main : et elle rougit VRAI
```
#### Dit il ce qu il fait ?

ici le commit concerne plus la gestion des chemins partages et leurs repartitions dans le main.

#### Pourquoi ??

Il montre directement le sujet principal du commit. Grace au 
```
git show --stat --oneline 07845c6c
```
Il confirme que les modifications concernent les chemins partages notamment :
-  config/chemins_partages.list
- contre_epreuve_chemins.sh  
-  verif_chemins.sh 

#### Porte t il un seul sujet ?
oui puisse que les modifications dans le commit sont juste centree sur la gestion des chemins partages.

### commit 3
```
6fb634fc NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle
```
#### Dit il ce qu il fait ?

Le message ici indique aue le travail effectuer sur NKCode passe a la phrase 14 avec une echeance reelle.

#### Pourquoi ??

Grace a la commande 
```
git show --stat --oneline 6fb634fc
```
Il montre que le commit modifie uniquement Applications/NKCode/ROADMAP.md. Le message correspond donc au sujet visible dans ce fichier.

#### Porte t il un seul sujet ?

oui puisse que il concerne uniquement le roadmap de NKCode et le passage a la phase 14. 

## Message qui parait le plus faible 

Le message qui me parait le plus faible ici est: 
```
9c3fad33 (HEAD -> main, origin/transit, origin/main, origin/HEAD) transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)
```
Parce que lui il donne une indication generale sur le commit et il regroupe plusieurs modifications donc le message ne permet pas de savoir exactement auelles modifications ont ete appaortees.

## Reecriture proposee

### Ancien message 
```
(HEAD -> main, origin/transit, origin/main, origin/HEAD) transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89)
```

### Nouveau message 
```
Regroupe les huits chantiers termines avant relecture
```
Ce nouveau message indique l idee principale du commit.