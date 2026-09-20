# Fichier de 10Mo

## Création de la branche

Avant de creer la branche j ai d abors fait un 
```
git status
```
pour voir si c etais propre 
et ca me donne :
```
On branch integration-rebase
nothing to commit, working tree clean
```
J'ai ensuite créé une nouvelle branche pour l'exercice avec la commande :

```
git switch -c exercice-10
```
ce qui me donne :
```
Switched to a new branch 'exercice-10'
```
ensuite je voulais verifier la branche actuelle j ai donc taper la commande :

```
git branch --show-current
```
ce qui me donne :

```
exercice-10
```
La branche utilisée pour l'exercice est donc :
```
exercice-10
```

## Mesure initiale de .git

Avant de créer le fichier de 10 Mo, j'ai mesuré la taille du dossier .git avec la commande :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```
Et ca me donne comme resulat :
```
52 955 octets = 51,71 Ko = 0,05 Mo
```
La taille initiale de .git est donc = 0,05 Mo

## Création du fichier de 10 Mo

J'ai créé un fichier-10Mo.bin d'une taille de 10 MiB avec la commande :

```
$bytes = New-Object byte[] (10 * 1024 * 1024)
[IO.File]::WriteAllBytes(".\fichier-10Mo.bin", $bytes)
```
J'ai ensuite vérifié la taille du fichier avec :

```
Get-Item .\fichier-10Mo.bin | Select-Object Name, Length
```
ce qui me donne :

```
Name               Length
----               ------
fichier-10Mo.bin   10485760
```
Le fichier possède donc :

```
10 485 760 octets = 10 MiB
```

## Ajout du fichier dans Git

J'ai vérifié l'état du dépôt avec :

```
git status
```
ce qui me donne :

```
On branch exercice-10
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        fichier-10Mo.bin

nothing added to commit but untracked files present (use "git add" totrack)
```
J'ai ensuite ajouté le fichier avec :
```
git add fichier-10Mo.bin
```

Puis j'ai vérifié son état avec :

```
git status
```
ce qui me donne :

```
On branch exercice-10
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   fichier-10Mo.bin
```

Le fichier était donc prêt à être enregistré dans un commit.

## Premier commit 

J'ai créé le premier commit avec :

```
git commit -m "Ajout du fichier de 10 Mo"
```
ce qui me donne :

```
[exercice-10 5d22a3d] Ajout du fichier de 10 Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier-10Mo.bin
```
donc le commit a bien été créé. Dont son identifiant court est : 5d22a3d.

## Mesure de .git après le premier commit

Après avoir fait le premier commit le fichier de 10 Mo, j'ai mesuré à nouveau la taille de .git avec la commande :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```
ce qui me donne :

```
99 034 octets = 96,71 Ko = 0,09 Mo
```
La taille de .git est donc quitter de :
```
Avant : 52 955 octets
Après : 99 034 octets
```

## Suppression du fichier

J'ai ensuite supprimé le fichier avec la commande :

```
git rm fichier-10Mo.bin
```
ce qui me donne :

```
rm 'fichier-10Mo.bin'
```
J'ai vérifié l'état du dépôt avec :
```
git status
```
ca me donne :
```
On branch exercice-10
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        deleted:    fichier-10Mo.bin

```
La suppression était donc prête à être enregistrée dans un nouveau commit.

## Deuxième commit : suppression du fichier

J'ai créé le deuxième commit avec :

```
git commit -m "Suppression du fichier de 10 Mo"
```
ce qui me donne :

```
[exercice-10 4a27abd] Suppression du fichier de 10 Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 fichier-10Mo.bin
```
Le deuxième commit a donc bien été créé. Dont son identifiant est : 4a27abd

## Mesure finale de .git

Après la suppression du fichier et la création du deuxième commit, il faut mesurer une dernière fois la taille de .git j ai utilise la commande :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```

### Résultat final

apres avoir taper la commande .git ne change pas de mesure ca mesure final est :
```
99 544 octets = 97,21 Ko = 0,09 Mo
```
soit 0,09 Mo

### Conclusion 
Supprimer un fichier ne signifie pas supprimer son historique. C'est pourquoi les fichiers volumineux peuvent continuer à occuper de l'espace dans .git même après leur suppression du projet. Cet exercice permet également de comprendre pourquoi il faut éviter de commiter accidentellement de gros fichiers dans un dépôt Git.
