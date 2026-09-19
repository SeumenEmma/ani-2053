## Mesurer la place du depot

Pour commencer j'ai ouvert mon dossier TestGit ensuite j'ai tape :

```
git status
```
ce qui me donne :
```
On branch test-taille
Your branch is ahead of 'origin/test-taille' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
```
Cela signifie que je suis actuellement sur la branche test-taille et que mon espace de travail est propre.
Ensuite j'ai mesure la taille du dossier .git avant de faire les trois commits.
J'ai utilise la commande :
```
"{0:N4} Ko" -f ((Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1KB)
```
Le resultat obtenu est :
```
33,7627 Ko
```
## Creation de la branche
J'ai ensuite cree une nouvelle branche avec :
```
git switch -c test-taille
```
ce qui me donne :
```
Switched to a new branch 'test-taille'
```
Ensuite j'ai verifie les branches avec :
```
git branch
```
ce qui me donne :
```
* test-taille
  master
```
"*" L'etoile indique que je suis actuellement sur la branche test-taille.

## Premier commit

J'ai modifie fichier1.txt puis j'ai tape :
```
git status
```
ce qui me montre que le fichier a ete modifie.

Ensuite j'ai tape :
```
git add fichier1.txt
```
puis 
```
git commit -m "Premier commit de test"
```
Le premier commit a donc ete cree sur la branche test-taille.

## Deuxieme commit

J'ai modifie encore une fois fichier1.txt puis j'ai tape :
```
git status
```
ce qui me montre que le fichier a ete modifie.
Ensuite j'ai tape :
```
git add fichier1.txt
```
puis 
```
git commit -m "Deuxieme commit de test"
```
## Troisieme commit
J'ai modifie encore une fois fichier1.txt puis j'ai tape :
```
git status
```
Ensuite j'ai tape :
```
git add fichier1.txt
```
puis :
```
git commit -m "troisieme commit de test"
```
## Historique des commits 
Pour verifier l'historique des trois commits, j'ai tape :
```
git log --oneline
```
ce qui me donne :
```
3e9acc6 (HEAD -> test-taille) troisieme commit de test
9aba202 Deuxieme  commit de test
df3a596 Premier commit de test
```
## Taille du fichier de branche 
J'ai commence par afficher les branches presentes dans .git avec :
```
Get-ChildItem .git\refs\heads
```
ce qui me donne notamment :
```
 Get-ChildItem .git\refs\heads

    Répertoire : C:\Users\emmas\One
Drive\Desktop\TestGit-\.git\refs\he
ads

Mode                 LastWriteTime
----                 -------------
-a---          2026-09-17    17:15
```
Ensuite j'ai mesure la taille du fichier qui contient la reference de la branche avec :
```
Get-Item .git\refs\heads\test-taille | Select-Object Name, Length
```
Le resultat est :
```
Name        Length
----        ------
test-taille     41
```
Le fichier test-taille fait donc 41 octets.

J'ai ensuite affiche son contenu avec :
```
Get-Content .git\refs\heads\test-taille
```
ce qui me donne :
```
b6f09c8ac374fc55527fc2204e433a554bc12fbd
```
il s agit du commit ou la branche pointe actuellement

## Conclusion

J'ai donc cree une branche test-taille et effectue trois commits sur cette branche.

La mesure en Ko donne :
```
33,7627 Ko
```
La branche test-taille elle-meme ne fait que :
```
41 octets
```
