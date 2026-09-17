## Objectif 

C est de modifier deux choses differentes dans le meme fichier puis enregistrer dans deux commits avec :
```
git add -p
```

## Realisation 

J ai effectue deux modifications differentes dans le fichier.txt qui sont :
- une modification concernant Git 
- une modification concernant Unity 

j ai utilise 
```
git add -p 
```
pour pouvoir separer les deux mondifications

### Resultat

Lors de l utilisation de git add -p j ai choisi :
```
diff --git a/fichier1.txt b/fichier1.txt
index 2c86502..ef39642 100644
--- a/fichier1.txt
+++ b/fichier1.txt
@@ -1,5 +1,38 @@
 Modification du fichier 
+
+
 Ajout d une phrase sur Git 
 
-Ajout d une deuxieme phrase sur Git 
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+Ajout d une phrase sur Unity
 
(1/1) Stage this hunk [y,n,q,a,d,s,e,p,P,?]? s
Split into 2 hunks.
@@ -1,3 +1,5 @@
 Modification du fichier 
+
+
 Ajout d une phrase sur Git 
 
(1/2) Stage this hunk [y,n,q,a,d,k,K,j,J,g,/,e,p,P,?]? y
@@ -2,4 +4,35 @@
 Ajout d une phrase sur Git 
 
-Ajout d une deuxieme phrase sur Git 
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+Ajout d une phrase sur Unity
 
(2/2) Stage this hunk [y,n,q,a,d,K,J,g,/,e,p,P,?]? n
```

## Commit 

J ai cree un premier commit avec 
```
git commit -m "message"
```
ce qui donne :
```
[master f2655ff] Ajout d'une modification sur Git
 1 file changed, 2 insertions(+)
```

J ai ensuite ajouter les modifications restante avec
```
git add fichiers 
```
puis j ai cree le deuxieme commit et ca a donne :
```
[master bbbdeca] Ajout d'une modification sur Unity
 1 file changed, 32 insertions(+), 1 deletion(-)
```
Apres j ai tape 
```
git status
```
Et ca donne :
```
On branch master
nothing to commit, working tree clean
```
Et j ai affiche l historique avec :
```
git log --online
```
et ca donne 
```
bbbdeca (HEAD -> master) Ajout d'une modification sur Unity
f2655ff Ajout d'une modification sur Git
488eb6a Ajout d une phrase sur Git
7d91d07 Modification du fichier 1
2438020 Ajout du fichier 3
54d9025 Ajout du fichier 2
d0da1cf Ajout du fichier 1
``` 
