# Modification du même fichier par deux personnes

## 1. Modification de la partie A

Pour simuler le travail de la personne A, j'ai utilisé une copie du dépôt située dans :

```
C:\Users\emmas\OneDrive\Desktop\TestGit-
```
Au départ, le dépôt contenait une modification non validée dans 
```
fichier1.txt
```

J'ai vérifié l'état du dépôt avec :

```
git status
```

Résultat :

```text
On branch test-taille
Your branch is up to date with 'origin/test-taille'.

Changes not staged for commit:
  modified:   fichier1.txt

no changes added to commit
```

Comme cette modification provenait d'un ancien essai et ne devait pas être conservée, je l'ai annulée avec :

```
git restore fichier1.txt
```

Puis j'ai vérifié à nouveau :

```
git status
```
ce qui me donne :

```
On branch test-taille
Your branch is up to date with 'origin/test-taille'.

nothing to commit, working tree clean
```

J'ai ensuite ouvert 
```
fichier1.txt
``` 
avec :

```
notepad fichier1.txt
```

J'ai effectué une modification dans la partie A du fichier.

J'ai ensuite ajouté le fichier avec :

```
git add fichier1.txt
```

Puis j'ai créé le commit :

```
git commit -m "Modification de la partie A"
```
ce qui me donne :

```
[test-taille b94ca2a] Modification de la partie A
 1 file changed, 1 insertion(+)
```
Enfin, j'ai envoyé la modification sur le dépôt distant avec :

```
git push
```
ce qui me donne :

```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 341 bytes | 341.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/SeumenEmma/TestGit-
   235c899..b94ca2a  test-taille -> test-taille
```

La modification de la personne A était donc maintenant présente sur GitHub.

## 2. Modification de la partie B

Pour simuler le travail de la personne B, j'ai utilisé une autre copie du dépôt située dans :

```
C:\Users\emmas\OneDrive\Documents\TestGit
```

Dans cette copie, j'ai ouvert le même fichier :

```
notepad fichier1.txt
```

J'ai effectué une modification à un autre endroit du fichier, dans la partie B.

J'ai ensuite ajouté le fichier :

```
git add fichier1.txt
```

Puis j'ai créé le commit :

```
git commit -m "Modification de la partie B"
```
ce qui me donne :

```
[test-taille cb92305] Modification de la partie B
 1 file changed, 3 insertions(+), 1 deletion(-)
```
J'ai ensuite envoyer la modification sur GitHub avec :

```
git push
```
Mais Git a refusé le push :

```
To https://github.com/SeumenEmma/TestGit-.git
 ! [rejected]        test-taille -> test-taille (fetch first)
error: failed to push some refs to 'https://github.com/SeumenEmma/TestGit-.git'
hint: Updates were rejected because the remote contains work that youdo not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

Cela signifie que le dépôt contenait déjà la modification de la personne A, alors que ma copie locale ne l'avait pas encore récupérée.

## 3. Récupération des modifications de A

Pour récupérer les modifications présentes sur le dépôt distant, j'ai exécuté :

```
git pull
```
Git a récupéré la modification de A, mais il a rencontré un conflit dans fichier1.txt :

```
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
Automatic merge failed; fix conflicts and then commit the result.
```

J'ai vérifié l'état du dépôt avec :

```powershell
git status
```

Git indiquait :

```text
On branch test-taille
Your branch and 'origin/test-taille' have diverged,
and have 2 and 5 different commits each, respectively.

You have unmerged paths.

Unmerged paths:
        both modified:   fichier1.txt
```

Le conflit concernait donc bien le même fichier qui avait été modifié par les deux personnes.

## 4. Résolution du conflit

J'ai ouvert le fichier avec :

```
notepad fichier1.txt
```

J'ai supprimé les marqueurs de conflit et conservé les modifications des deux parties.
Après avoir enregistré le fichier, j'ai indiqué à Git que le conflit était résolu avec :

```
git add fichier1.txt
```

Puis j'ai créé le commit de fusion :

```
git commit -m "Fusion des modifications A et B"
```

ce qui me donne :

```text
[test-taille e8f5c15] Fusion des modifications A et B
```

## 5. Envoi de la fusion sur GitHub

J'ai ensuite envoyé la fusion vers le dépôt distant avec :

```
git push
```

Le push a réussi :

```text
Enumerating objects: 13, done.
Counting objects: 100% (13/13), done.
Delta compression using up to 12 threads
Compressing objects: 100% (9/9), done.
Writing objects: 100% (9/9), 980 bytes | 980.00 KiB/s, done.
Total 9 (delta 3), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (3/3), completed with 2 local objects.
To https://github.com/SeumenEmma/TestGit-.git
   b94ca2a..e8f5c15  test-taille -> test-taille
```

## 6. Vérification de l'historique

Pour voir l'historique sous forme de graphe, j'ai utilisé :

```
git log --oneline --graph --decorate -5
```
ce qui me donne :

```
*   e8f5c15 (HEAD -> test-taille, origin/test-taille, origin/HEAD) Fusion des modifications A et B
|\
| * b94ca2a Modification de la partie A
| * 235c899 Modification de la partie B
| * ec78e4f Modification de la partie A
| *   7647a31 Merge branch 'test-taille' of https://github.com/SeumenEmma/TestGit- into test-taille
| |\
```
On voit le commit de fusion :

```
e8f5c15 Fusion des modifications A et B
```
ainsi que les commits correspondant aux modifications.

## 7. Vérification finale

Enfin, j'ai vérifié l'état du dépôt avec :

```
git status
```
ce qui me donne :
```
On branch test-taille
Your branch is up to date with 'origin/test-taille'.

nothing to commit, working tree clean
```
Le dépôt local est donc propre et synchronisé avec le dépôt distant.

## Conclusion

Dans cet exercice, deux personnes ont modifié le même fichier fichier1.txt à des endroits différents.

La personne A a créé le commit :

```
b94ca2a Modification de la partie A
```

La personne B a ensuite créé :

```
cb92305 Modification de la partie B
```

Lorsque B a essayé de faire 
```git push
```
Git a refusé l'envoi car le dépôt distant contenait déjà la modification de A.

Après 
```
git pull
```
Git a détecté un conflit dans fichier1.txt. J'ai donc dû résoudre manuellement le conflit, puis créer le commit de fusion :

```
e8f5c15 Fusion des modifications A et B
```

Enfin, le 
```
git push
``` 
a réussi et le dépôt est revenu à un état propre.

Cet exercice montre donc que Git permet d'intégrer le travail de deux personnes sur un même fichier.
