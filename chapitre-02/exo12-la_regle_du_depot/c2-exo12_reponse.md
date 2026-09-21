# Règles Git du projet

## Organisation et nommage des branches

La branche principale du projet est 
```
main
```
Elle doit toujours contenir une version fonctionnelle et vérifiable du projet. Chaque étudiant travaille sur sa propre branche et ne modifie pas directement main. Les branches sont nommées selon le modèle :

* feature/nom-de-la-fonctionnalite pour ajouter une fonctionnalité ;
* fix/nom-du-probleme pour corriger un problème ;
* docs/nom-du-document pour modifier uniquement la documentation.

Le nom doit être court, compréhensible et lié au travail réalisé. Une branche terminée ne doit pas rester ouverte inutilement : après sa fusion et la vérification du projet, elle peut être supprimée.

## Règles concernant les commits

Un commit doit correspondre à une modification précise et cohérente. Nous évitons de mélanger plusieurs travaux différents dans le même commit. Le message du commit doit permettre de comprendre rapidement ce qui a été réalisé. Nous utilisons un préfixe simple :

* feat: pour une nouvelle fonctionnalité ;
* fix: pour une correction ;
* docs: pour la documentation ;
* refactor: pour une réorganisation du code sans changement de fonctionnalité.

Exemple :
```
feat: ajout du système de sauvegarde`
```
Avant de créer un commit, l'étudiant vérifie les fichiers modifiés afin de ne pas enregistrer accidentellement des fichiers temporaires, des fichiers personnels ou des modifications qui ne concernent pas son travail. Un commit doit être suffisamment petit pour pouvoir être compris et, si nécessaire, annulé facilement.

## Relecture du travail

Aucun étudiant ne valide seul une modification destinée à main.
Lorsqu'un étudiant termine son travail, il demande une relecture à un autre membre du groupe. Le relecteur vérifie notamment :

* que la modification correspond à ce qui était demandé ;
* que le projet fonctionne après la modification ;
* qu'aucun fichier inutile n'a été ajouté ;
* que le travail ne crée pas volontairement de conflit avec celui des autres ;
* que le changement est suffisamment clair pour être maintenu par un autre membre du groupe.

Pour éviter que toujours les mêmes personnes se relisent, les relectures sont réparties entre les quatre étudiants. Si une modification est importante, deux membres peuvent la relire. L'auteur de la modification reste responsable de répondre aux remarques du relecteur et de corriger les problèmes signalés avant la fusion.

## Ce qui est interdit

Les règles suivantes s'appliquent à tous les membres du groupe :

* Il est interdit de travailler directement sur main.
* Il est interdit de fusionner son propre travail sans relecture.
* Il est interdit de supprimer ou modifier le travail d'un autre étudiant sans en discuter avec lui.
* Il est interdit d'ajouter des mots de passe, clés privées, fichiers personnels ou informations confidentielles dans le dépôt.
* Il est interdit de modifier l'historique partagé de main avec des opérations destructives.
* Il est interdit de créer volontairement des commits inutiles uniquement pour augmenter le nombre de commits.
* Il est interdit de déclarer une tâche terminée sans avoir vérifié que le projet fonctionne.
* Il est interdit de conserver dans le dépôt des fichiers générés automatiquement lorsqu'ils ne sont pas nécessaires au projet.

En cas de désaccord entre deux étudiants, la modification est mise en pause et le groupe décide ensemble de la solution avant de continuer.

## Que faire si quelqu'un casse main ?

Si une modification provoque un problème sur main, la priorité est de remettre le projet dans un état fonctionnel. La personne qui constate le problème prévient immédiatement les autres membres du groupe. On identifie ensuite la dernière modification introduite et on vérifie si elle est réellement responsable du problème. Si nécessaire, la modification problématique est annulée avec une procédure Git adaptée, sans supprimer l'historique du projet. Une fois main rétablie, le groupe teste le projet pour confirmer que la branche fonctionne de nouveau.
La modification pourra ensuite être retravaillée sur une branche séparée, testée à nouveau et relue avant d'être proposée pour une nouvelle fusion.

## Règle commune

Ces règles s'appliquent aux quatre membres de manière identique. Le but est de garder un historique compréhensible, de protéger le travail de chacun et de permettre à un étudiant de reprendre le travail d'un autre sans avoir besoin de lui demander toutes les explications. Toute modification destinée au projet doit donc passer par une branche de travail, être vérifiée et relue avant d'arriver dans main.
