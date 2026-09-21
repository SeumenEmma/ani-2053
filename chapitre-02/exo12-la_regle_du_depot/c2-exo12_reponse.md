# Règles Git du projet

Le projet est réalisé par un groupe de quatre étudiants. Pour éviter les conflits, les pertes de travail et les erreurs sur le projet, les règles suivantes doivent être respectées par tous les membres du groupe.

# Organisation des branches

La branche 
```
main
```
contient la version stable du projet. Aucun étudiant ne doit travailler directement dessus Chaque étudiant doit travailler sur une branche correspondant à la tâche qu'il réalise.Les noms des branches doivent respecter cette forme :
```
feature/nom-fonctionnalite
fix/nom-du-bug
docs/nom-documentation
test/nom-du-test
```

Avant de commencer une nouvelle tâche, il faut récupérer la dernière version de 
```
main
``` 
et créer sa branche à partir de cette version.

```
git switch main
```
```
git pull
```
```
git switch -c feature/ma-tache
```

Il faut éviter de garder une branche trop longtemps sans la mettre à jour.

* Ce qu'il faut faire
- Utiliser une branche pour chaque fonctionnalité ou correction importante.
- Donner aux branches des noms courts et explicites.
- Supprimer sa branche lorsqu'elle n'est plus nécessaire, après accord du groupe.

# Contenu d'un commit

Un commit doit correspondre à une modification précise et cohérente.

Avant de faire un commit, il faut vérifier les modifications avec :

```
git status
```
```
git diff
```
Le message du commit doit expliquer clairement ce qui a été fait.

Exemples :

```
Ajout du menu principal
Correction du calcul des scores
Ajout des tests
Mise à jour de la documentation
```

Il faut éviter les messages comme :

```
modif
test
aaa
changement
final
```

Il ne faut pas mettre dans un commit des fichiers inutiles, des fichiers temporaires, des mots de passe ou des informations confidentielles, faire des commits réguliers, utiliser des messages précis.

# Relecture du travail

Avant de fusionner une modification importante dans 
```
main
```
elle doit être relue par un autre étudiant.

Les quatre étudiants doivent faire les relectures à tour de rôle afin que chacun puisse vérifier le travail des autres.

Le relecteur doit vérifier :

* que la modification correspond à la tâche demandée ;
* que le projet fonctionne correctement ;
* que les tests nécessaires fonctionnent ;
* qu'aucun fichier inutile n'a été ajouté ;
* que la modification ne casse pas une autre partie du projet.

Une modification ne doit donc pas être fusionnée directement sans avoir été vérifiée par un autre membre du groupe.

# Ce qui est interdit

Il est interdit de :

* travailler directement sur main ;
* pousser directement sur main sans relecture ;
* utiliser git push --force sur main ;
* supprimer le travail d'un autre étudiant sans son accord ;
* modifier le travail d'un camarade sans le prévenir ;
* fusionner du code qui n'a pas été testé ;
* ajouter des mots de passe ou des informations confidentielles dans Git ;
* utiliser une commande Git dont on ne comprend pas les conséquences sur le dépôt commun.

# Si quelqu'un casse la branche principale

Si une modification casse main, il ne faut pas essayer de supprimer rapidement le commit ou de cacher l'erreur.

La personne qui remarque le problème doit prévenir les autres étudiants.

Le groupe vérifie ensuite l'état du dépôt et l'historique :

```
git status
git log --oneline
```

La correction doit être faite sur une branche séparée, par exemple :

```
fix/correction-main
```

La correction doit ensuite être testée et relue par un autre étudiant avant d'être fusionnée dans main.

Il ne faut pas utiliser git push --force pour essayer de faire disparaître le problème ni supprimer l'historique du projet.

# Règle générale du groupe

Les quatre étudiants doivent respecter les mêmes règles. Chaque étudiant travaille sur sa propre branche, fait des commits clairs, vérifie son travail et demande une relecture avant la fusion. En cas de problème, il faut prévenir rapidement le groupe et corriger le problème sans supprimer l'historique.Le but est de garder main stable et de permettre aux quatre étudiants de travailler ensemble sans perdre le travail de quelqu'un.