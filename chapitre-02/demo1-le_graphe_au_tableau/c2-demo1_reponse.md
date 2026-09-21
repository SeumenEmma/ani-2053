# Graphe des commits d'un dépôt réel

Pour réaliser cet exercice, j'ai utilisé mon dépôt réel 
```
TestGit-
```

## Chemin d'accès au dépôt

Le dépôt utilisé pour cet exercice se trouve dans :

```
C:\Users\emmas\OneDrive\Desktop\TestGit-
```
J'ai ensuite vérifié que le dossier était bien un dépôt Git avec la commande :

```
git status
```
ce qui me donne :
```
On branch exercice-11
nothing to commit, working tree clean
```

J'étais sur la branche :
```
exercice-11
```
et l'arbre de travail était propre.

## Commande utilisée pour afficher le graphe

Une fois dans le dépôt, j'ai utilisé la commande :

```
git log --oneline --graph --all
```
ce qui me donne :

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
| | | * 1e61343 (integration-rebase) Modification sur integration pour rebase
| | | * 44e7727 (travail-rebase) Travail a rejouer
| |_|/  
|/| |   
| | | *   4a49c77 (integration-merge) Fusion de travail-merge
| | | |\  
```

Cette commande permet d'afficher l'historique des commits sous forme de graphe. L'option --oneline permet d'afficher chaque commit sur une seule ligne, --graph permet de représenter graphiquement les différentes branches et les fusions, et --all permet d'afficher les différentes références disponibles dans le dépôt.

## Partie du graphe utilisée pour l'exercice

La partie intéressante de mon historique est :

```
*   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
|\
| *   1f6ce32 Resolution du conflit
| |\
| * | 464464e le conflic
* | b6f09c8 Modification de la partie A
```

Cette partie montre deux lignes de développement qui partent d'un même historique puis sont réunies par une fusion.

## Vérification du commit de fusion

Pour vérifier que 
```
7647a31
``` 
est bien un commit de fusion, j'ai utilisé :

```
git show --no-patch --pretty=raw 7647a31
```

J'ai obtenu :

```
commit 7647a3185fb8b88e734ca5632c5e0517c7bcd6f8
tree 9ec5ede3b91f1e15de37c78d1d5082114fa87316
parent b6f09c8ac374fc55527fc2204e433a554bc12fbd
parent 1f6ce32b442ccbd5741e4a3959d27e643c356cd9
author marilee emmanuelle seumen tchapoya <emmaseumen@gmail.com>
committer marilee emmanuelle seumen tchapoya <emmaseumen@gmail.com>

    Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
```
Le commit 
```
7647a31
``` 
possède donc deux parents :

```
b6f09c8
1f6ce32
```
Cela confirme qu'il s'agit d'un commit de fusion.

## Recherche du point de divergence

J'ai ensuite utilisé la commande :
```
git merge-base b6f09c8 1f6ce32
```
Le résultat obtenu est :
```
c8cdac512a77e549afb92e88ecf6be8dcb3293c6
```
Le point commun avant la divergence est donc :

```
c8cdac5
```
Ce commit correspond à :
```
c8cdac5 le conflic
```
## Vérification des relations entre les commits

J'ai utilisé la commande :

```
git show --no-patch --pretty=format:"%h %s%nParents: %P" c8cdac5 b6f09c8 464464e 1f6ce32 7647a31
```
J'ai obtenu les relations suivantes :
```
c8cdac5 le conflic
Parents: 3e9acc68b0895c62ae1ef65521809e11a7ff4be4
b6f09c8 Modification de la partie A
Parents: c8cdac512a77e549afb92e88ecf6be8dcb3293c6
464464e le conflic
Parents: 3e9acc68b0895c62ae1ef65521809e11a7ff4be4
1f6ce32 Resolution du conflit
Parents: 464464e6d06fccf2b204aacdb532233ca0d57e04 c8cdac512a77e549afb92e88ecf6be8dcb3293c6
7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
Parents: b6f09c8ac374fc55527fc2204e433a554bc12fbd 1f6ce32b442ccbd5741e4a3959d27e643c356cd9
```
Ces informations permettent de voir précisément comment les commits sont liés.

## Graphe dessiné au tableau

À partir de ces informations, le graphe peut être représenté simplement comme ceci :

```
                         b6f09c8
                         Modification de la partie A
                        /        \
                       /          \
c8cdac5 ---------------            7647a31
le conflic                           Merge
                       \            /
                        \          /
                         464464e
                         le conflic
                            |
                         1f6ce32
                         Resolution du conflit
```

Le point 
```
c8cdac5
``` 
représente le point commun avant la divergence.

Une branche mène vers 
```
b6f09c8
```

L'autre branche passe par 
```
464464e
```
puis 
```
1f6ce32
```
Les deux branches sont ensuite réunies dans 
```
7647a31
```

## Correspondance ligne par ligne 

La première partie :

```
*   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
```

correspond au commit de fusion 
```
7647a31
```
Le fait que ce commit possède deux parents explique la présence de :
```
|\
```
Les lignes :
```
| *   1f6ce32 Resolution du conflit
| |\
| * | 464464e le conflic
```
correspondent à l'autre ligne de développement.
La ligne :
```
* | b6f09c8 Modification de la partie A
```
correspond à l'autre branche issue du point commun.
Le point commun avant la divergence est :
```
c8cdac5
```
Il n'apparaît pas directement dans cet extrait, mais il a été identifié avec :

```
git merge-base b6f09c8 1f6ce32
```

## Explication du point de divergence

Le commit 
```
c8cdac5
``` 
est le point commun à partir duquel les deux historiques se séparent. Une première évolution mène à :
```
b6f09c8 Modification de la partie A
```
Une deuxième évolution mène à :
```
464464e le conflic
```
puis à :
```
1f6ce32 Resolution du conflit
```
Les deux historiques ont donc évolué séparément à partir d'un même commit.

## Fusion des deux historiques

Les deux évolutions sont finalement réunies dans :
```
7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
```
Ce commit possède deux parents :

```
b6f09c8
1f6ce32
```
Il représente donc la fusion des deux lignes de développement. On peut également remarquer que 1f6ce32 est lui-même un commit de fusion puisqu'il possède deux parents :
```
464464e
c8cdac5
```
Cela montre que l'historique de mon dépôt contient plusieurs opérations de fusion.
## Autres branches présentes dans le dépôt

Le résultat de :

```
git log --oneline --graph --all
```
montre également d'autres branches, par exemple :

```
1b07f44 (exercice-10) Suppression du fichier de 10 Mo
46370c2 Ajout du fichier de 10 Mo
4a27abd Suppression du fichier de 10 Mo
5d22a3d Ajout du fichier de 10 Mo
1e61343 (integration-rebase) Modification sur integration pour rebase
44e7727 (travail-rebase) Travail a rejouer
4a49c77 (integration-merge) Fusion de travail-merge
6c8ba50 (travail-merge) Travail a integrer
```
Ces branches correspondent à d'autres travaux réalisés dans mon dépôt. Cependant, pour l'exercice demandé, la partie la plus utile est celle qui permet de voir clairement une divergence et une fusion :

```text
c8cdac5
   |
   +---- b6f09c8
   |
   +---- 464464e
             |
          1f6ce32
             \ 
              7647a31
```

## Conclusion

J'ai utilisé mon dépôt réel TestGit- pour observer le graphe de ses commits.

La commande :

```
git log --oneline --graph --all
```
permet de visualiser graphiquement les différentes lignes de développement et les fusions.
Dans la partie étudiée :

* c8cdac5 représente le point commun avant la divergence ;
* b6f09c8 représente une première évolution ;
* 464464e représente une deuxième évolution ;
* 1f6ce32 poursuit cette deuxième ligne et correspond également à une fusion ;
* 7647a31 réunit finalement les deux lignes de développement.

Le graphe dessiné au tableau correspond donc aux relations entre les commits affichées par Git avec
```
git log --oneline --graph --all
```
