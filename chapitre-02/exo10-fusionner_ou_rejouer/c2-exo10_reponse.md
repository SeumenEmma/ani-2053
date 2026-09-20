## Comparaison entre merge et rebase

L'objectif est donc de réaliser deux intégrations du même type de
travail :
- une première fois avec git merge ;
- une deuxième fois avec git rebase ;
- comparer les deux graphes Git ;
- donner une préférence personnelle avec un argument.

### Préparation pour l'intégration avec merge

j ai taper la commande :
```
git status
```
ce qui me donne :
```
On branch exercice-8
Your branch is ahead of 'origin/exercice-8' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
```
ce qui veut dire que le depot est propre.
Ensuite pour pouvoir voir les branches disponibles j ai tape la commande :
```
git branch
```
ce qui me donne :
```
* exercice-8
  test-taille
```
qui nous montre que l on a deux branches actuellements et que l on est sur la branche exercice-8.
Ensuite pour pouvoir aller sur la branche test-taille j ai utilise la commande :
```
git switch test-taille
```
ce qui me donne :
```
Switched to branch 'test-taille'
Your branch is ahead of 'origin/test-taille' by 1 commit.
 (use "git push" to publish your local commits)
```
#### Première intégration avec merge

j ai donc créer la branche integration-merge avec la commande :
```
git switch -c integration-merge
```
ce qui me donne :
```
Switched to a new branch 'integration-merge'
```
Cette branche représentere la branche principale dans notre première
expérience avec merge.
ensuite j ai tape :
```
git status
```
ce qui me donne :
```
On branch integration-merge
nothing to commit, working tree clean
```
j ai créer la branche de travail travail-merge avec la commande :
```
git switch -c travail-merge
```

ce qui me donne :
```
Switched to a new branch 'travail-merge'
```
c est pour une deuxième branche qui représente le travail effectué
séparément et que nous allons ensuite intégrer dans integration-merge.
j ai ensuite modifier le fichier1.txt puis j ai verifie avec la commande :
```
git status
```
ce qui me donne :
```
On branch travail-merge
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
Git détecte que fichier1.txt a été modifié, mais la modification n'est
pas encore préparée pour un commit.
puis j ai fait un :
```
git add fichier1.txt
```
ensuite un :
```
git commit -m "Travail a integrer"
```
ce qui me donne :
```
[travail-merge 6c8ba50] Travail a integrer
 1 file changed, 3 insertions(+), 1 deletion(-)
```

Donc la modification est maintenant enregistrée dans un commit appelé
Travail a integrer.
puis j ai verifier le graphe avec :
```
git log --oneline --graph --all --decorate -5
```
ce qui me donne :
```
* 6c8ba50 (HEAD -> travail-merge) Travail a integrer
| * a1af17d (exercice-8) Commit perdu
| | * fbcdce4 (refs/stash) On exercice-8: protection avant reflog
| |/| 
| | * 34a2667 index on exercice-8: b8f0113 Revert "Commit pousse a annuler"
| |/  
| * b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
```
apres je retourne sur la branche integration-merge avec la commande :
```
git switch integration-merge
```
ce qui me donne :
```
Switched to branch 'integration-merge'
```
et j ai tape un :
```
git status
```
ce qui me donne :
```
On branch integration-merge
nothing to commit, working tree clean
```
On revient sur la branche qui recevra le travail de travail-merge.

ensuite je faire une autre modification sur la branche principale puis je tape :
```
git status
```
ce qui me donne :
```
On branch integration-merge
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
Donc la branche integration-merge possède maintenant sa propre modification
de fichier1.txt.
apres je tape la commande :
```
git add fichier1.txt
```
puis 
```
git commit -m "Modification sur integration"
```

ce qui me donne :
```
[integration-merge 36efd46] Modification sur integration
 1 file changed, 4 insertions(+), 1 deletion(-)
```
Nous avons maintenant deux branches qui ont chacune leur propre
modification :
- integration-merge → 36efd46
- travail-merge → 6c8ba50

Alors les deux branches ont donc divergé.
apres je tape la commande pour afficher le graph :
```
git log --oneline --graph --all --decorate -8
```
ce qui me donne :
```
* 36efd46 (HEAD -> integration-merge) Modification sur integration
| * 6c8ba50 (travail-merge) Travail a integrer
|/  
| * a1af17d (exercice-8) Commit perdu
| | * fbcdce4 (refs/stash) On exercice-8: protection avant reflog
| |/| 
| | * 34a2667 index on exercice-8: b8f0113 Revert "Commit pousse a annuler"
| |/  
| * b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
| * b385871 Commit pousse a annuler
|/  
* b6f09c8 (test-taille) Modification de la partie A
```
maintenant nous allons maintenant réunir les deux branches avec merge.
puis j ai lance la fusion avec la commande :
```
git merge travail-merge
```
ce qui me donne :
```
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
Automatic merge failed; fix conflicts and then commit the result.
```
ce qui as cree un conflict. j ai verifier l etat du conflit avec la commande :
```
git status
```
ce qui me montre :
```
On branch integration-merge
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
ici git indique que fichier1.txt a été modifié sur les deux branches. Le
fichier doit être corrigé avant de terminer la fusion.
j ai meme afficher le fichier et repérer le conflit avec la commande :
```
Get-Content .\fichier1.txt
```
ce qui me donne 
```
<<<<<<< HEAD
Modification sur la branche principale
=======
Modification pour integrations
>>>>>>> travail-merge
```
pour pouvoir resoudre le conflit j ai utilise la commande :
```
notepad .\fichier1.txt
```
j ai corrige le fichier en conservant les deux modifications j ai verifie avec la commande :
```
Get-Content .\fichier1.txt
```
ce qui donne :
```
Modification sur la branche principale
Modification pour integrations
```
Explication

ce qui nous montre que le conflit est résolu en gardant les deux lignes.
puis je fait un 
```
git status
```
ce qui me donne :
```
On branch integration-merge
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
pour pouvoir montrer que le conflit est résolu je tape la commande :
```
git add fichier1.txt
```

Puis :
```
git status
```
ce qui me donne :
```
On branch integration-merge
All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   fichier1.txt
```

Git confirme maintenant que tous les conflits sont résolus. Il reste
seulement à créer le commit de fusion.
puis je tape la commande :
```
git commit -m "Fusion de travail-merge"
```
ce qui me donne :
```
[integration-merge 4a49c77] Fusion de travail-merge
```

donc la fusion est terminée. Git a créé un commit spécial de fusion qui est :
```
4a49c77
```

Ce commit relie les deux branches.
apres j ai tape pour voir le graphe :
```
git log --oneline --graph --all --decorate -8
```
ce qui me donne :
```
*   4a49c77 (HEAD -> integration-merge) Fusion de travail-merge
|\  
| * 6c8ba50 (travail-merge) Travail a integrer
* | 36efd46 Modification sur integration
|/  
| * a1af17d (exercice-8) Commit perdu
| | * fbcdce4 (refs/stash) On exercice-8: protection avant reflog
| |/| 
| | * 34a2667 index on exercice-8: b8f0113 Revert "Commit pousse a annuler"
| |/  
| * b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
| * b385871 Commit pousse a annuler
|/  
```
## Préparation pour l'intégration avec rebase 

puis retourner sur test-taille avec :
```
git switch test-taille
```

ce qui me donne :
```
Switched to branch 'test-taille'
Your branch is ahead of 'origin/test-taille' by 1 commit.
```
puis je créer la branche integration-rebase avec la commande :
```

git switch -c integration-rebase
```
ce qui me donne :
```
Switched to a new branch 'integration-rebase'
```
Cette branche servira de branche principale pour l'expérience avec
rebase. puis j ai cree la branche avec :
```
git switch -c travail-rebase
```

ce qui me donne :
```
Switched to a new branch 'travail-rebase'
```
apres je modifie le fichier puis je tape :
```
git status
```

ce qui me donne :
```
On branch travail-rebase
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

Une modification a été faite dans fichier1.txt sur la branche de
travail.
puis j ai créer le commit de travail avec les commandes :
```
git add fichier1.txt
```
puis 
```
git commit -m "Travail a rejouer"
```
apres je retourner sur integration-rebase avec la commande :
```
git switch integration-rebase
```
et je Vérifie avec :
```
git status
```
et je fait une modification sur integration-rebase puis :
```
git status
```
apres je fait un :
```
git add fichier1.txt
```
puis
```
git commit -m "Modification sur integration pour rebase"
```
ce qui me donne :
```
[integration-rebase 9e66ab1] Modification sur integration pour rebase
 1 file changed, 3 insertions(+), 1 deletion(-)
```
Nous avons maintenant deux commits différents sur les deux branches.
apres je voit le graph avec :
```
git log --oneline --graph --all --decorate -8
```
ce qui donne :
```
* 9e66ab1 (HEAD -> integration-rebase) Modification sur integration pour rebase
| * 44e7727 (travail-rebase) Travail a rejouer
|/  
| *   4a49c77 (integration-merge) Fusion de travail-merge
| |\  
| | * 6c8ba50 (travail-merge) Travail a integrer
| |/  
|/|   
| * 36efd46 Modification sur integration
|/  
| * a1af17d (exercice-8) Commit perdu
| | * fbcdce4 (refs/stash) On exercice-8: protection avant reflog
| |/| 
| | * 34a2667 index on exercice-8: b8f0113 Revert "Commit pousse a annuler"
| |/  
```
Comme avec merge, les deux branches ont divergé.

La différence est que cette fois nous allons utiliser rebase pour
replacer le travail de la branche principale au-dessus de
travail-rebase.

### Le rebase 

je lance le rebase avec la commande
```
git rebase travail-rebase
```
ce qui me donne :
```
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
error: could not apply 9e66ab1... Modification sur integration pour rebase
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
Could not apply 9e66ab1... # Modification sur integration pour rebase
```
Un conflit apparaît également avec rebase.
pour afficher le conflit j ai tape la commande :
```
Get-Content .\fichier1.txt
```
ce qui me donne :
```
<<<<<<< HEAD
Modification pour rebase
=======
Modification sur integration pour rebase
>>>>>>> 9e66ab1 (Modification sur integration pour rebase)
```
pour résoudre le conflit le fichier a été corrigé pour conserver les deux modifications.

puis je verifie avec :
```
Get-Content .\fichier1.txt
```
ce qui me donne :
```
Modification pour rebase
Modification sur integration pour rebase
```
Les deux modifications sont conservées et les marqueurs de conflit sont
supprimés.

Marquer le conflit comme résolu

je continue le rebase avec la commande :
```
git rebase --continue
```

ce qui me donne :
```

[detached HEAD 1e61343] Modification sur integration pour rebase
 1 file changed, 2 insertions(+), 1 deletion(-)
Successfully rebased and updated refs/heads/integration-rebase.
```
ce qui veut dire que le rebase est terminé avec succès.

Le commit original :
```
9e66ab1
```
a été rejoué et devient un nouveau commit :
```
1e61343
```
Le contenu est conservé, mais l'identifiant du commit change parce que
Git a recréé le commit dans une nouvelle position de l'historique.

## Comparaison des deux graphes

Afficher le graphe final
```
git log --oneline --graph --all --decorate -15
```
ce qui donne :
```
* 1e61343 (HEAD -> integration-rebase) Modification sur integration pour rebase
* 44e7727 (travail-rebase) Travail a rejouer
| *   4a49c77 (integration-merge) Fusion de travail-merge
| |\  
| | * 6c8ba50 (travail-merge) Travail a integrer
| |/  
|/|   
| * 36efd46 Modification sur integration
|/  
| * a1af17d (exercice-8) Commit perdu
| | * fbcdce4 (refs/stash) On exercice-8: protection avant reflog
| |/| 
| | * 34a2667 index on exercice-8: b8f0113 Revert "Commit pousse a annuler"
| |/  
| * b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
| * b385871 Commit pousse a annuler
|/  
* b6f09c8 (test-taille) Modification de la partie A
* c8cdac5 (origin/test-taille, origin/HEAD) le conflic
* 3e9acc6 troisieme commit de test
* 9aba202 Deuxieme  commit de test
* df3a596 Premier commit de test
```
Graphe obtenu avec merge

La partie importante du graphe est :
```

*   4a49c77 (integration-merge) Fusion de travail-merge
|\
| * 6c8ba50 (travail-merge) Travail a integrer
* | 36efd46 Modification sur integration
|/
```

Graphe obtenu avec rebase

La partie importante du graphe est :

* 1e61343 (integration-rebase) Modification sur integration pour rebase
* 44e7727 (travail-rebase) Travail a rejouer

Le graphe est linéaire.

Il n'y a pas de commit de fusion. Le commit 9e66ab1 a été rejoué et
est devenu 1e61343.

Différence entre merge et rebase

merge                             rebase

Crée un commit de fusion            Ne crée pas de commit de fusion

Le graphe possède une bifurcation   Le graphe est linéaire
puis une réunion

Les branches sont visibles dans     L'historique paraît plus simple et
l'historique                        chronologique

Le commit de fusion est 4a49c77   Le commit rejoué est 1e61343

Préférence de lecture

Je préfère lire le graphe obtenu avec rebase, car son historique est
linéaire et il est plus facile de suivre l'ordre des modifications sans
avoir à suivre une branche de fusion.
Avec merge, Git a créé le commit de fusion :
```
4a49c77 Fusion de travail-merge
```
Avec rebase, Git a rejoué le commit de la branche principale et a créé
:

1e61343 Modification sur integration pour rebase

Dans les deux méthodes, un conflit a été rencontré dans fichier1.txt.
Le conflit a été résolu en conservant les deux modifications.

La principale différence visible dans les graphes est que merge
conserve la bifurcation et ajoute un commit de fusion, tandis que
rebase produit un historique linéaire.