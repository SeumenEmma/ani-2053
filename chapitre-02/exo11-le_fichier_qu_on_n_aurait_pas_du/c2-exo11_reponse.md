# Ajout puis suppression d'un fichier de 10 Mo

#  Création de la branche

Avant de commencer l'expérience, j'ai vérifié que mon dépôt était propre avec :

```
git status
```

J'ai obtenu :

```
On branch integration-rebase
nothing to commit, working tree clean
```

Le dépôt ne contenait donc aucune modification non enregistrée.

J'ai ensuite créé une nouvelle branche dédiée à l'exercice :

```
git switch -c exercice-10
```
ce qui me donne :

```
Switched to a new branch 'exercice-10'
```

Pour vérifier la branche actuelle, j'ai utilisé :

```
git branch --show-current
```
ce qui me donne  :

```text
exercice-10
```

# Mesure initiale de .git

Avant de créer le fichier de 10 Mo, j'ai mesuré la taille du dossier .git avec :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```
ce qui me donne :

```
99 544 octets = 97,21 Ko = 0,09 Mo
```

La taille initiale de .git était donc de : 0,09 Mo.

# Création du fichier de 10 Mo

Pour cette nouvelle expérience, j'ai créé un fichier contenant des données aléatoires.

J'ai utilisé les commandes suivantes :

```
$bytes = New-Object byte[] (10 * 1024 * 1024)
[System.Security.Cryptography.RandomNumberGenerator]::Fill($bytes)
[IO.File]::WriteAllBytes(".\fichier-10Mo.bin", $bytes)
```

elle écrit réellement le contenu du tableau dans le fichier :

```
fichier-10Mo.bin
```
Cette dernière ligne est importante car elle permet de créer physiquement le fichier sur le disque.

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
Le fichier possède donc exactement :

```
10 485 760 octets
```

soit 10 MiB.

# Ajout du fichier dans Git

J'ai vérifié l'état du dépôt avec :

```
git status
```
ce qui donne :

```
On branch exercice-10
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        fichier-10Mo.bin

nothing added to commit but untracked files present
```
Je l'ai ajouté avec :

```
git add fichier-10Mo.bin
```
Puis j'ai vérifié son état :

```
git status
```
ce qui me donne :

```
On branch exercice-10
Changes to be committed:

        new file:   fichier-10Mo.bin
```

Le fichier était donc prêt à être enregistré dans un commit.

# Premier commit : ajout du fichier

J'ai créé le premier commit avec :

```
git commit -m "Ajout du fichier de 10 Mo"
```

Résultat :

```
[exercice-10 46370c2] Ajout du fichier de 10 Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier-10Mo.bin
```
Le premier commit a donc bien été créé.

Son identifiant est : 46370c2

# Mesure de .git après le premier commit

Après avoir enregistré le fichier dans Git, j'ai mesuré à nouveau la taille de .git avec :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```
ce qui me donne :

```
10 589 278 octets = 10 341,09 Ko = 10,10 Mo
```

La taille de .git est donc passée de :

```
Avant l'ajout : 99 544 octets
Après l'ajout : 10 589 278 octets
```
La différence est :

```
10 589 278 - 99 544 = 10 489 734 octets
```

On constate donc que l'enregistrement du fichier aléatoire de 10 MiB a bien fait augmenter fortement la taille du dépôt.

# Suppression du fichier

Après avoir enregistré le fichier dans le premier commit, je l'ai supprimé avec :

```
git rm fichier-10Mo.bin
```
ce qui me donne :

```
rm 'fichier-10Mo.bin'
```

J'ai ensuite vérifié l'état du dépôt :

```
git status
```
ce qui me donne :

```
On branch exercice-10
Changes to be committed:

        deleted:    fichier-10Mo.bin
```

La suppression a bien ete effectuer.

# Deuxième commit : suppression du fichier

J'ai créé le deuxième commit avec :

```
git commit -m "Suppression du fichier de 10 Mo"
```
ce qui me donne :

```
[exercice-10 1b07f44] Suppression du fichier de 10 Mo
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 fichier-10Mo.bin
```

Le deuxième commit a donc bien été créé.
Son identifiant  est : 1b07f44

# Mesure finale de .git

Après la suppression du fichier et la création du deuxième commit, j'ai mesuré une dernière fois la taille de .git :

```
$tailleGit = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N0} octets = {1:N2} Ko = {2:N2} Mo" -f $tailleGit, ($tailleGit/1KB), ($tailleGit/1MB)
```
ce qui donne :

```
10 589 788 octets = 10 341,59 Ko = 10,10 Mo
```

La taille finale de .git est donc de : 10,10 Mo.

# Comparaison des trois mesures

| Étape                                      |  Taille de .git |
| ------------------------------------------ | ----------------: |
| Avant l'ajout                              |     99 544 octets |
| Après le commit du fichier                 | 10 589 278 octets |
| Après la suppression et le deuxième commit | 10 589 788 octets |

Entre la deuxième et la troisième mesure :

```
10 589 788 - 10 589 278 = 510 octets
```

Il y a donc 510 octets supplémentaires après le commit de suppression. La suppression du fichier n'a donc pas retiré les données de 10 Mo du dépôt.

# Conclusion

Cette expérience montre que supprimer un fichier du projet ne signifie pas supprimer son contenu de l'historique Git.

Le fichier fichier-10Mo.bin a d'abord été enregistré dans le commit :

```
46370c2
```
Puis il a été supprimé dans le commit :
```
1b07f44
```
Cependant, la version précédente du fichier reste présente dans l'historique Git. C'est pourquoi la taille de .git est passée de :

```
99 544 octets
```
à :
```
10 589 278 octets
```
après l'ajout du fichier, puis est restée pratiquement identique après sa suppression :
```
10 589 788 octets
```
La différence de seulement 510 octets entre les deux dernières mesures correspond aux données supplémentaires nécessaires au nouveau commit et à ses objets associés ; elle ne correspond pas à une récupération des 10 Mo du fichier. Un fichier volumineux peut continuer à occuper de l'espace dans `.git` même après avoir été supprimé de la version actuelle du projet.
