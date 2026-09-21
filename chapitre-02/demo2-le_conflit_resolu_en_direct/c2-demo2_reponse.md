# Résolution d'un conflit Git

## Vérification de l'état initial

Avant de provoquer le conflit, j'ai vérifié l'historique du dépôt avec :

```
git log --oneline --graph --all -8
```

ce qui me donne :
```
* d24dfd7 (HEAD -> exercice-11, conflit-demo) demo: modification pourconflit
*   8839fd9 Merge demo-branche dans exercice-11
|\
| * 1a8f27e (demo-branche) demo: modification sur la branche
* | 9a72d3b demo: modification sur exercice-11
|/
* b94ca2a (origin/test-taille, origin/HEAD, test-taille) Modificationde la partie A
* 235c899 Modification de la partie B
* ec78e4f Modification de la partie A
*   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
|\
```
Les branches exercice-11 et conflit-demo étaient alors au même commit d24dfd7.

## Première modification sur exercice-11

J'ai modifié fichier1.txt sur la branche exercice-11, puis j'ai créé un commit :

```
git add fichier1.txt
git commit -m "demo: modification concurrente sur exercice-11"
```
ce qui donne :

```
[exercice-11 11c3ec1] demo: modification concurrente sur exercice-11
 1 file changed, 2 insertions(+), 1 deletion(-)
```
La branche exercice-11 possède donc maintenant le commit :
```
11c3ec1 demo: modification concurrente sur exercice-11
```
## Deuxième modification sur conflit-demo

Je suis ensuite passé sur la branche conflit-demo et j'ai modifié la même zone de fichier1.txt, mais avec un contenu différent.
J'ai validé cette modification avec :
```
git commit -m "demo: modification concurrente sur conflit-demo"
```
ce qui donne :

```
[conflit-demo 30f6c23] demo: modification concurrente sur conflit-demo
 1 file changed, 2 insertions(+)
```
Nous avions alors deux modifications différentes à partir du même commit :

```
d24dfd7
├── 11c3ec1  exercice-11
└── 30f6c23  conflit-demo
```

## Provoquer le conflit

Je suis revenu sur exercice-11 et j'ai lancé :

```
git merge conflit-demo
```
Git a détecté un conflit :
```
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
Automatic merge failed; fix conflicts and then commit the result.
```
Le conflit était donc bien provoqué volontairement.

## Lecture des marqueurs

Pour voir précisément le conflit, j'ai utilisé :
```
Get-Content fichier1.txt
```
Git avait inséré les marqueurs suivants :
```
<<<<<<< HEAD

Modification faite sur exercice-11
=======
Modification faite sur conflit-demoModification faite sur conflit-demo

Modification faite sur conflit-demo - branche secondaires
>>>>>>> conflit-demo
```

Les marqueurs ont la signification suivante :

* <<<<<<< HEAD indique le début de la version présente sur la branche courante exercice-11.
* ======= sépare les deux versions.
* >>>>>>> conflit-demo indique la fin de la version provenant de conflit-demo.

J'ai donc pu identifier clairement les deux versions qui entraient en conflit.

## Décision
Après avoir lu le conflit, j'ai décidé de conserver les deux modifications.
La version finale devait donc contenir :

```
Modification faite sur exercice-11
Modification faite sur conflit-demoModification faite sur conflit-demo
Modification faite sur conflit-demo - branche secondaires
```
Cette décision permet de conserver les informations apportées par les deux branches.

## Reconstruction du fichier

J'ai ouvert fichier1.txt avec :

```
notepad fichier1.txt
```

J'ai supprimé les marqueurs de conflit :

```
<<<<<<< HEAD
=======
>>>>>>> conflit-demo
```
et j'ai reconstruit manuellement le contenu final.
J'ai ensuite vérifié le fichier avec :
```
Get-Content fichier1.txt
```
ce qui donne :

```
Modification de la partie A
Modification de la partie 1
Modification du fichier 1


Ajout d une phrase sur Git 


Ajout d une phrase sur Unity

Premier commit sur la branche test-taille.

Deuxieme commit sur la branche test-taille

Troisieme commit sur la branche test-taille

Bonjour Git 

Modification de la partie B

Modification faite sur exercice-11

Modification de la branche demo

Modification faite sur exercice-11
Modification faite sur conflit-demoModification faite sur conflit-demo
Modification faite sur conflit-demo - branche secondaires
```
Les marqueurs de conflit avaient disparu.

## Vérification avant validation

J'ai exécuté :

```
git status
```
ce qui donne :
```
On branch exercice-11
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
Cela signifie que le fichier avait été reconstruit, mais que Git attendait encore que je lui indique que le conflit était résolu.

## Validation de la résolution

J'ai marqué le conflit comme résolu avec :
```
git add fichier1.txt
```
Puis j'ai vérifié l'état du dépôt :
```
git status
```
ce qui donne :

```
On branch exercice-11
All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   fichier1.txt
```

Git confirmait alors que tous les conflits étaient résolus et que le commit de fusion pouvait être créé.

J'ai ensuite validé la fusion avec :

```
git commit -m "Resolution du conflit"
```
Le commit de résolution créé est :
```
e82a9af Resolution du conflit
```

## Vérification finale

J'ai vérifié l'état du dépôt :

```
git status
```
ce qui donne :

```
On branch exercice-11
nothing to commit, working tree clean
```
Le dépôt est donc propre.

## Vérification du graphe Git

J'ai affiché l'historique avec :

```
git log --oneline --graph --all -10
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
| * 1a8f27e (demo-branche) demo: modification sur la branche
* | 9a72d3b demo: modification sur exercice-11
|/
* b94ca2a (origin/test-taille, origin/HEAD, test-taille) Modificationde la partie A
* 235c899 Modification de la partie B
```

Le graphe montre clairement que les deux branches ont divergé :

```
                 11c3ec1
                /       \
d24dfd7 -------           e82a9af
                \       /
                 30f6c23
```

Le commit e82a9af est le commit de fusion qui rassemble les deux branches après la résolution du conflit.

## Vérification du commit de résolution

J'ai également utilisé :

```
git show --stat --oneline HEAD
```
ce qui donne :

```
e82a9af (HEAD -> exercice-11) Resolution du conflit

 fichier1.txt | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
```

Cela confirme que le commit de résolution concerne bien fichier1.txt.

## Conclusion

Cet exercice m'a permis de provoquer volontairement un conflit Git et de le résoudre étape par étape. Le résultat final est un dépôt propre :
```
On branch exercice-11
nothing to commit, working tree clean
```
Le commit e82a9af confirme que la résolution du conflit a été validée.
