# Revue de code 

## Contexte

Dans le cadre de cet exercice, chaque groupe devait échanger une branche avec un autre groupe afin de réaliser une revue de code.

L'objectif de la revue était de vérifier :

- ce que fait la branche ;
- si les commits sont lisibles et compréhensibles ;
- ce qui fonctionne correctement ;
- ce qui manque ;
- ce qui ne devrait pas être présent ;
- et les améliorations possibles.

J'ai travaillé sur la branche :
```
tests-addition-soustractio
```

# Travail réalisé par moi

## Branche : `tests-addition-soustraction`

Ma partie consistait à ajouter des tests concernant les opérations d'addition et de soustraction L'objectif était de vérifier que les fonctions d'addition et de
soustraction produisent bien les résultats attendus.

### Ce que j'ai réalisé

- Création des tests pour l'addition.
- Création des tests pour la soustraction.
- Vérification des résultats obtenus avec les résultats attendus.
- Organisation des modifications dans des commits.
- Création d'une branche dédiée à cette fonctionnalité.
- Création d'une Pull Request afin de proposer les modifications.

### Objectif des tests

Les tests permettent de vérifier automatiquement que les opérations fonctionnent correctement.

Par exemple :

- addition de deux nombres positifs ;
- addition avec zéro ;
- soustraction de deux nombres ;
- soustraction donnant un résultat négatif.

Cela permet de détecter plus facilement une erreur dans le code.

# Revue des branches des autres membres

Après avoir travaillé sur ma propre branche, j'ai également observé
les branches réalisées par les autres membres du groupe.
J'ai notamment regardé :
- le nom des branches ;
- les modifications réalisées ;
- les messages des commits ;
- l'organisation du code ;
- les Pull Requests ;
- les tests présents.

# Ce que j'ai remarqué

## Les branches

Les branches sont séparées selon les fonctionnalités.

J'ai pu observer différentes branches correspondant notamment à :

- l'addition ;
- la soustraction ;
- la multiplication ;
- les tests unitaires ;
- les tests d'addition et de soustraction.
Cette organisation permet de travailler sur plusieurs fonctionnalités
sans modifier directement la branche principale.

## Les commits

Les commits permettent de suivre les différentes modifications réalisées dans les branches. J'ai remarqué que certains commits sont suffisamment explicites pour comprendre rapidement ce qui a été modifié. Cependant, certains messages pourraient être plus précis.
Par exemple, au lieu d'utiliser un message très général comme :
```
modification
```
il serait préférable d'utiliser un message comme :

```
Ajout des tests de multiplication
```
Cela permet de comprendre immédiatement le contenu du commit.

# Ce qui est bien

Plusieurs éléments sont positifs dans le travail réalisé :

- Les fonctionnalités sont séparées dans différentes branches.
- Les branches permettent de travailler indépendamment.
- Des Pull Requests sont utilisées pour proposer les modifications.
- Les fonctionnalités sont accompagnées de tests.
- Les modifications peuvent être relues avant leur intégration dans la branche principale.

Cette organisation facilite le travail en groupe et permet de mieux suivre les modifications.

# Ce qui pourrait être amélioré

## Messages des commits

Les messages des commits devraient être suffisamment précis pour
décrire clairement la modification effectuée.

## Organisation

Il faut également veiller à garder une organisation cohérente entre les différentes branches.

Par exemple :

`feature-addition`

`feature-soustraction`

`feature-multiplication`

Cela rendrait les branches plus faciles à identifier.

## Tests

Les tests pourraient être complétés avec davantage de cas particuliers,
par exemple :

- addition avec zéro ;
- soustraction avec zéro ;
- résultats négatifs ;
- valeurs identiques ;
- valeurs plus grandes ou plus petites.

# Ce qui ne devrait pas être présent

Lors d'une revue de code, il faut également vérifier qu'il n'y a pas de fichiers inutiles ou de modifications qui ne concernent pas la fonctionnalité de la branche.
Une branche dédiée à une fonctionnalité devrait principalement contenir les fichiers nécessaires à cette fonctionnalité.

Il faut éviter d'ajouter :

- des fichiers temporaires ;
- des fichiers générés automatiquement ;
- des fichiers personnels ;
- des modifications sans rapport avec la fonctionnalité.

# Conclusion

Cette revue m'a permis de mieux comprendre l'intérêt du travail collaboratif avec
les branches et les Pull Requests. J'ai constaté que le découpage du travail en plusieurs branches permet à chaque membre de travailler sur une fonctionnalité précise.