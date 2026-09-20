## Creation d un depot vide 
j ai cree mon depot vide avec la commande 
```
Mkdir TestGit 
```
ce qui me donne :
```

    Répertoire : C:\Users\emmas\OneDrive\Desktop\c++ Exercices\ani-2053\chapitre-02


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        2026-09-16     12:09                TestGit
```

j ai tape 
```
cd TestGit 
```
pour etre dans le dossier d essai ensuite j ai fait :
```
git init 
```
ce qui me donne :
```
Initialized empty Git repository in C:/Users/emmas/OneDrive/Desktop/c++ Exercices/ani-2053/chapitre-02/TestGit/.git/
```

pour pouvoir initialiser le dossier et le transforme en dopot github.

Et j ai ensuite cree trois fichiers :
- fichier1.txt
- fichier2.txt
- fichier3.txt

## Ajout des trois fichiers avec les trois commits
Pour ajouter le premier fichier j'ai utilise la commande 
```
git add fichier1.txt
```
puis un :
```
git commit -m "Ajout du fichier 3"
```
pour pouvoir mettre les differents commits ce qui me donne :
```
[master d0da1cf] Ajout du fichier 1
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode fichier1.txt
```
j ai fait pareil pour les deux autres fichiers j ai utilise :
```
git add fichier2.txt
```
puis un 
```
git commit -m "Ajout du fichier 2"
```
ce qui me donne :
```
[master 54d9025] Ajout du fichier 2
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode fichier2.txt
```
et pour le fichier3.txt je fais :
```
git add fichier3.txt
```
puis un 
```
git commit -m "Ajout du fichier 3"
```
ce qui me donne :
```
[master 2438020] Ajout du fichier 3
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode fichier3.txt
```
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
Ou on peut aussi tape 
```
git log --oneline --graph --all --decorate
```
pour que le graphe soit encore plus detaille avec les references et branches et l effet visuel est encore plus jolie.