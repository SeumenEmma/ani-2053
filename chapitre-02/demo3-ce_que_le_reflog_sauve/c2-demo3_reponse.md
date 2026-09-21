# Détruire un travail avec reset --hard et le retrouver avec reflog

L'objectif de cet exercice est de provoquer volontairement la perte d'un travail avec :

```
git reset --hard
```
Puis de constater la disparition du travail et de montrer qu'il est possible de le retrouver grâce à :
```
git reflog
```
Enfin, le travail sera récupéré à partir du commit retrouvé.

## Vérification de l'état initial
Avant de commencer, j'ai vérifié l'état du dépôt :
```
git status
```
ce qui donne :

```
On branch exercice-11
nothing to commit, working tree clean
```
Le dépôt était donc propre. J'ai ensuite affiché les derniers commits :

```
git log --oneline --graph --all -5
```
ce qui me donne :

```
*   e82a9af (HEAD -> exercice-11) Resolution du conflit
|\
| * 30f6c23 (conflit-demo) demo: modification concurrente sur conflit-demo
* | 11c3ec1 demo: modification concurrente sur exercice-11
|/
* d24dfd7 demo: modification pour conflit
*   8839fd9 Merge demo-branche dans exercice-11
|\
```
Le dernier commit de la branche exercice-11 était donc :

```
e82a9af Resolution du conflit
```

## Création du travail à détruire

Pour avoir un travail identifiable, j'ai ajouté une phrase dans fichier1.txt :

```
Add-Content fichier1.txt "Travail important avant reset"
```

J'ai ensuite enregistré cette modification dans Git avec :

```
git add fichier1.txt
git commit -m "travail important avant reset"
```
ce qui donne :

```
[exercice-11 23460a8] travail important avant reset
 1 file changed, 1 insertion(+), 1 deletion(-)
```
Le commit contenant le travail important est donc :
```
23460a8 travail important avant reset
```
Ce commit va volontairement être retiré de l'historique de la branche.

## Vérification avant le `reset --hard`

J'ai vérifié l'historique avant de provoquer la perte :

```
git log --oneline --graph --all -5
```
ce qui donne :

```
* 23460a8 (HEAD -> exercice-11) travail important avant reset
*   e82a9af Resolution du conflit
|\
| * 30f6c23 (conflit-demo) demo: modification concurrente sur conflit-demo
* | 11c3ec1 demo: modification concurrente sur exercice-11
|/
* d24dfd7 demo: modification pour conflit
```
Le commit 23460a8 était bien le dernier commit de exercice-11.

## Destruction volontaire avec reset --hard
J'ai ensuite utilisé :

```
git reset --hard e82a9af
```
ce qui donne :

```
HEAD is now at e82a9af Resolution du conflit
```
Cette commande a déplacé HEAD de :
```
23460a8
```
vers :

```
e82a9af
```
Le commit 23460a8 n'était donc plus le commit courant de la branche exercice-11.

## Constat de la perte

Après le reset --hard, j'ai affiché l'historique :

```
git log --oneline --graph --all -5
```
ce qui donne :

```
*   e82a9af (HEAD -> exercice-11) Resolution du conflit
|\
| * 30f6c23 (conflit-demo) demo: modification concurrente sur conflit-demo
* | 11c3ec1 demo: modification concurrente sur exercice-11
|/
* d24dfd7 demo: modification pour conflit
*   8839fd9 Merge demo-branche dans exercice-11
|\
```
Le commit :
```
23460a8 travail important avant reset
```
n'apparaissait plus dans l'historique de exercice-11.

J'ai également vérifié le contenu de fichier1.txt :

```
Get-Content fichier1.txt
```
Le contenu affiché ne contenait plus :

```
Travail important avant reset
```
Le travail avait donc bien disparu de l'état courant de la branche.

## Utilisation du reflog

Pour retrouver la trace du commit perdu, j'ai utilisé :

```
git reflog
```
ce qui donne :

```
e82a9af (HEAD -> exercice-11) HEAD@{0}: reset: moving to e82a9af
23460a8 HEAD@{1}: commit: travail important avant reset
e82a9af (HEAD -> exercice-11) HEAD@{2}: commit (merge): Resolution du conflit
11c3ec1 HEAD@{3}: checkout: moving from conflit-demo to exercice-11
30f6c23 (conflit-demo) HEAD@{4}: commit: demo: modification concurrente sur conflit-demo
d24dfd7 HEAD@{5}: checkout: moving from exercice-11 to conflit-demo
11c3ec1 HEAD@{6}: commit: demo: modification concurrente sur exercice-11
d24dfd7 HEAD@{7}: merge conflit-demo: Fast-forward
8839fd9 HEAD@{8}: checkout: moving from conflit-demo to exercice-11
d24dfd7 HEAD@{9}: commit: demo: modification pour conflit
8839fd9 HEAD@{10}: checkout: moving from exercice-11 to conflit-demo
8839fd9 HEAD@{11}: commit (merge): Merge demo-branche dans exercice-11
```
La ligne importante est :
```
23460a8 HEAD@{1}: commit: travail important avant reset
```
Le reflog permet donc de retrouver le commit 23460a8, même après le reset --hard.

## Récupération du travail

J'ai créé une nouvelle branche à partir du commit retrouvé :

```
git branch recuperation-reset 23460a8
```
Puis je me suis placé sur cette branche :

```
git switch recuperation-reset
``` 
ce qui donne :

```
Switched to branch 'recuperation-reset'
```
La branche recuperation-reset pointe maintenant directement vers le commit qui avait été retiré de exercice-11.

## Vérification de la récupération

J'ai vérifié l'historique :

```
git log --oneline --graph --all -5
```
ce qui me donne :

```
* 23460a8 (HEAD -> recuperation-reset) travail important avant reset
*   e82a9af (exercice-11) Resolution du conflit
|\
| * 30f6c23 (conflit-demo) demo: modification concurrente sur conflit-demo
* | 11c3ec1 demo: modification concurrente sur exercice-11
|/
* d24dfd7 demo: modification pour conflit
```
Le commit 23460a8 est de nouveau accessible par la branche :

```
recuperation-reset
```
J'ai ensuite vérifié le contenu du fichier :

```
Get-Content fichier1.txt
```
À la fin du fichier, on retrouve :
```
Modification faite sur conflit-demo - branche secondairesTravail important avant reset
```
La phrase :
```
Travail important avant reset
```
a donc bien été récupérée.

## Conclusion

Cet exercice montre qu'un git reset --hard peut faire disparaître un travail de l'état courant de la branche et supprimer les modifications présentes dans l'arbre de travail.Que reset --hard peut faire disparaître un travail de la branche, mais que git reflog permet souvent de retrouver le commit auquel ce travail était encore accessibleS.
