## Mesurer la place du depot 

Pour commencer j ai ouvert mon dossier TestGit ensuite j ai tape 
```
git status
```
ce qui me donne :
```
On branch master
nothing to commit, working tree clean
```
J ai mesure d abord la taille avant les 3 commits. J ai utilise la commande :
```
"{0:N2} Mo" -f ((Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1MB)
```
pour que ca me donne la taille en Mega octec

La taille est : 0.04 Mo

Ensuite j ai tape :
```
git switch -c test-taille
```
ce qui me donne :
```
Switched to a new branch 'test-taille'
```
Ensuite 
```
git branch
```
ce qui me donne 
```
* test-taille
  master
```
ce qui signifie que je suis actuellement sur la branche test-taille.

### Premier commit 

J ai modifie fichier1.txt et puis j ai tape :
```
git status
```
ce qui me montre que j ai mofifie le fichier.txt

Ensuite je tape :
```
git add fichier1.txt
```
puis 
```
git commit -m "Premier commit de test"
```

### Deuxieme commit 

J ai modifie encore le fichier1.txt et puis j ai tape :
```
git status
```
ce qui me montre que j ai mofifie le fichier.txt

Ensuite je tape :
```
git add fichier1.txt
```
puis 
```
git commit -m "Deuxieme commit de test"
```

### Troisieme commit 

J ai modifie encore une fois le fichier1.txt et puis j ai tape :
```
git status
```
ce qui me montre que j ai mofifie le fichier.txt

Ensuite je tape :
```
git add fichier1.txt
```
puis 
```
git commit -m "troisieme commit de test"
```
Pour verifier le graphe de l historique des commits j ai tape 
```
git log --oneline --graph -3
```
ce qui me donne :
```
* 3e9acc6 (HEAD -> test-taille) troisieme commit de test
* 9aba202 Deuxieme  commit de test
* df3a596 Premier commit de test
```
### Mesurer la taille final 

pour avoir la taille apres les trois commits j utilise la commande :
```
"{0:N2} Mo" -f ((Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1MB)
```
ce qui me donne 
taille = 0.05

### Calcul de la place gagnee

pour trouver la place supplementaire occupee par les commits on calcule :
```
Taille après − Taille avant = espace supplémentaire utilisé
```
donc la taille supplementaire est 

taille = 0.01 Mo 
donc les trois commits ont ajoutes environ 0.01 Mo de stockage Git.  