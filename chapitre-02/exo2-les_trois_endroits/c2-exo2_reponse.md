## Modification d un fichier 

Pour ca j ai modifie le fichier1.txt et j ai tape la commande :
```
git status
```
### Resultat 
```
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
#### Sigification

Ce resultat signifie que le fichier.txt a ete modifier depuis le dernier commit mais que je n ai pas encore demander a Git de preparer pour le prochain commit.

## 2 eme etape 

Ensuite j ai fait un 
```
git add fichier1.txt
```
Ensuite j ai fait un 
```
git status
```

### Resultat
```
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier1.txt
```
#### Signification

Ce resultat ca veut dire que grace a git add fichier1.txt la modification est entre dans le staging area et le git status pour nous montrer que la modification est prepare pour le prochain commit.

## 3 eme etape 
Ensuite j ai fait un 
```
git commit -m "Modification du fichier1"
```
Ensuite j ai fait un 
```
git status 
```
### Resultat
```
On branch master 
nothing to commit, working tree clean
```

#### Signification 

Ce resultat veut dire que la modification a ete enregistre dans un commit et qu il n y a plus de modification en attente et elle a ete enregistre dans l historique git.