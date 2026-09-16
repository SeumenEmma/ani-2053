## Creation d un depot vide
Apres la creation de mon depot j ai cree trois fichiers :
- fichier1.txt
- fichier2.txt
- fichier3.txt

## Ajout des trois fichiers avec les trois commits

j ai utilise la commande 
```
git add nom du fichier 
```
pour pouvoir ajouter les trois fichiers et j ai utilise la commande 
```
git commit -m "message"
```
pour pouvoir mettre les differents commits 

## Historique des commits 

Pour pouvoir afficher l historique en une ligne par commit j ai utilise la commande 
```
git log --oneline
```
### Resultat
```
2438020 (HEAD -> master) Ajout du fichier 3
54d9025 Ajout du fichier 2
d0da1cf Ajout du fichier 1
```
## Graphe

Pour pouvoir afficher la representation graphique de l historique j ai utilise la commande :
```
git log --oneline --graph
```
### Resultat
```
* 2438020 (HEAD -> master) Ajout du fichier 3
* 54d9025 Ajout du fichier 2
* d0da1cf Ajout du fichier 1
```