## Graphe des commits d'un dépôt réel

1. Vérification de l'état initial du dépôt

J'ai commencé par vérifier l'état de mon dépôt avec
```
git status
```
ce qui donne :
```
On branch exercice-11
nothing to commit, working tree clean
```

Le dépôt était propre et j'étais déjà positionné sur la branche exercice-11.

2. Observation de l'historique initial

J'ai ensuite affiché l'historique des commits avec le graphe avec :
```
git log --oneline --graph --all
```
ce qui donne :
```
* b94ca2a (HEAD -> exercice-11, origin/test-taille, origin/HEAD, test-taille) Modification de la partie A
* 235c899 Modification de la partie B
* ec78e4f Modification de la partie A
*   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
|\
| *   1f6ce32 Resolution du conflit
| |\
| * | 464464e le conflic
| | | * 1b07f44 (exercice-10) Suppression du fichier de 10 Mo
| | | * 46370c2 Ajout du fichier de 10 Mo
| | | * 4a27abd Suppression du fichier de 10 Mo
| | | * 5d22a3d Ajout du fichier de 10 Mo
| | | * 1e61343 (integration-rebase) Modification sur integration pour
```
3. Création de la branche secondaire

À partir de exercice-11, j'ai créé une nouvelle branche appelée demo-branche avec la commande :
```
git switch -c demo-branche
```
ce qui donne :
```
Switched to a new branch 'demo-branche'
```

À ce moment-là, les deux branches partaient du même commit. Ce commit commun constitue le point de départ.

4. Premier commit sur demo-branche

J'ai modifié fichier1.txt, puis j'ai ajouté le fichier à l'index.
```
git add fichier1.txt
```
J'ai ensuite créé le premier commit spécifique à demo-branche.
```
git commit -m "demo: modification sur la branche"
```
ce qui donne :
```
[demo-branche 1a8f27e] demo: modification sur la branche
 1 file changed, 3 insertions(+), 1 deletion(-)
```
Le commit 1a8f27e appartient donc à la branche demo-branche.

5. Retour sur la branche principale

 Je suis donc revenu sur la branche principale utilisée pour cet exercice : exercice-11.
```
git switch exercice-11
```
ce qui me donne :
```
Switched to branch 'exercice-11'
```
6. Deuxième commit sur exercice-11

J'ai effectué une modification différente dans fichier1.txt sur exercice-11.
```
git add fichier1.txt
```
Puis j'ai créé le deuxième commit.
```
git commit -m "demo: modification sur exercice-11"
```
ce qui me donne :
```
[exercice-11 9a72d3b] demo: modification sur exercice-11
 1 file changed, 3 insertions(+), 1 deletion(-)
```
Nous avons maintenant deux commits différents :
```
1a8f27e sur demo-branche ;
```
et 
```
9a72d3b sur exercice-11.
```
Les deux branches ont donc divergé à partir de leur commit commun.

7. Vérification de la branche principale avant la fusion

J'ai vérifié que j'étais bien sur exercice-11 avec la commande :
```
git switch exercice-11
```
ce qui me donne :
```
Already on 'exercice-11'
```

8. Fusion de demo-branche dans exercice-11

J'ai ensuite demandé à Git de fusionner demo-branche dans la branche principale exercice-11 avec la commande :
```
git merge demo-branche
```
ce qui me donne :
```
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
Automatic merge failed; fix conflicts and then commit the result.
```
Git a détecté un conflit parce que les deux branches avaient modifié une même partie de fichier1.txt.

9. Vérification du conflit

J'ai utilisé git status pour voir l'état de la fusion.
ce qui me donne :
```
On branch exercice-11
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   fichier1.txt

no changes added to commit (use "git commit -a")
```
Git indique que fichier1.txt a été modifié sur les deux branches et qu'il faut résoudre le conflit avant de terminer la fusion.

10. Lecture des marqueurs de conflit

J'ai affiché le contenu de fichier1.txt.
```
Get-Content fichier1.txt
```
ce qui donne :
```
Modification de la partie A
Modification de la partie 1
Modification du fichier 1
```

Ajout d une phrase sur Git 


Ajout d une phrase sur Unity

Premier commit sur la branche test-taille.

Deuxieme commit sur la branche test-taille

Troisieme commit sur la branche test-taille

Bonjour Git 

Modification de la partie B

<<<<<<< HEAD
Modification faite sur exercice-11
=======
Modification de la branche demo
>>>>>>> demo-branche

Les marqueurs indiquent les deux versions en conflit :

<<<<<<< HEAD correspond à la version présente sur exercice-11 ;

======= sépare les deux versions ;

>>>>>>> demo-branche correspond à la version provenant de demo-branche.

J'ai ouvert le fichier afin de résoudre le conflit avec :
```
notepad fichier1.txt
```
J'ai conservé les deux modifications et supprimé les marqueurs de conflit.

11. Validation de la résolution et création du commit de fusion

Après avoir résolu le conflit dans fichier1.txt, j'ai ajouté le fichier.
```
git add fichier1.txt
```
J'ai ensuite terminé la fusion avec un commit avec la commande :
```
git commit -m "Merge demo-branche dans exercice-11"
```
ce qui donne :
```
[exercice-11 8839fd9] Merge demo-branche dans exercice-11
```
Le commit 8839fd9 est donc le commit de fusion.

12. Affichage du graphe final 

J'ai finalement affiché l'historique complet avec son graphe avec la commande :
```
git log --oneline --graph --all
```
ce qui donne :
```
*   8839fd9 (HEAD -> exercice-11) Merge demo-branche dans exercice-11
|\
| * 1a8f27e (demo-branche) demo: modification sur la branche
* | 9a72d3b demo: modification sur exercice-11
|/
* b94ca2a (origin/test-taille, origin/HEAD, test-taille) Modificationde la partie A
* 235c899 Modification de la partie B
* ec78e4f Modification de la partie A
*   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
|\
| *   1f6ce32 Resolution du conflit
| |\
| * | 464464e le conflic
```

13. Correspondance entre le dessin et git log --graph

La partie importante du graphe final est :
```
*   8839fd9 (HEAD -> exercice-11) Merge demo-branche dans exercice-11
|\
| * 1a8f27e (demo-branche) demo: modification sur la branche
* | 9a72d3b demo: modification sur exercice-11
|/
* b94ca2a (origin/test-taille, origin/HEAD, test-taille) Modificationde la partie A
```
On peut la représenter au tableau de manière simplifiée :
```
                         1a8f27e
                        /       \
                       /         \
b94ca2a ---------------           8839fd9
                       \         /
                        \       /
                         9a72d3b
```
Avec les branches :
```
                         1a8f27e
                      demo-branche
                            |
                            *
                           / \
                          /   \
                         /     * 8839fd9
                        /     /
b94ca2a ---------------*----- 
                       \
                        * 9a72d3b
                          |
                     exercice-11
```

## Conclusion

Cet exercice m'a permis de créer et d'observer une divergence entre deux branches réelles. La branche exercice-11 a reçu un commit différent de celui de demo-branche. Lors de la fusion, Git a détecté un conflit dans fichier1.txt, que j'ai résolu avant de créer le commit de fusion 8839fd9. Le résultat de git log --oneline --graph --all permet de retrouver visuellement la même histoire que celle représentée au tableau : divergence avec | * et * |, séparation avec |\, puis réunion des branches avec /.
