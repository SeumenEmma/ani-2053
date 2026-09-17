### Le conflit

Dans le repertoire A j ai modifie une ligne et j ai modifie le repertoire B j ai utilise les commandes :
```
- git add nom du fichier
- git push
- git commit -m "message"
```
quand j ai fait le push sur le repertoire A le push a reussi :
```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 333 bytes | 333.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/SeumenEmma/TestGit-
   3e9acc6..c8cdac5  test-taille ->test-taille
```
### Le refus
quand j ai fais le push sur le repertoire B le push a echoue et ca donne :
```
 ! [rejected]        test-taille -> test-taille (fetch first)
error: failed to push some refs to 'https://github.com/SeumenEmma/TestGit-.git'
hint: Updates were rejected because the remote contains work that youdo not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```
### Le conflit

J ai fais un 
```
git pull
```
Et j ai obtenue comme resultat :
```
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 1), reused 3 (delta 1), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 313 bytes | 39.00 KiB/s, done.
From https://github.com/SeumenEmma/TestGit-
   3e9acc6..c8cdac5  test-taille -> origin/test-taille
Auto-merging fichier1.txt
CONFLICT (content): Merge conflict in fichier1.txt
Automatic merge failed; fix conflicts and then commit the result.
```
## Regarder le conflit 

Pour regarder le conflit j ai tape :
```
Get-Content fichier1.txt
```
dans le repertoire B et ca me donne comme resultat :
```
Modification du fichier 


Ajout d une phrase sur Git 


Ajout d une phrase sur Unity

Premier commit sur la branche test-taille.

Deuxieme commit sur la branche test-taille

Troisieme commit sur la branche test-taille

<<<<<<< HEAD
Bonjour Git
=======
Bonjour Git 
>>>>>>> c8cdac512a77e549afb92e88ecf6be8dcb3293c6
```
### Resoudre le conflit

Pour resoudre le conflit j ai mis la modification sur la meme ligne dans les deux repertoires. Ensuite j ai fais un 
```
git status
```
puis un 
```
git add fichier1.txt
```
puis je reverifie encore avec un 
```
git status
```
qui montre que le fichier a ete modifier

### Commit de resolution 

J ai fais un dernier commit pour dire que tout a ete resolue j ai tape
```
git commit -m "Resolution du conflit"
```
Enfin j ai fais un dernier push de fin pour voir si ca a reussi. J ai tape :
```
git push
```
ce qui me donne comme resultat :
```
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 12 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 520 bytes | 520.00 KiB/s, done.
Total 4 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/SeumenEmma/TestGit-.git
   c8cdac5..1f6ce32  test-taille -> test-taille
```
## Verification finale

Je tape un 
```
git status 
```
puis un 
```
git log --oneline
```
pour voir l historique des commit qui est :
```
1f6ce32 (HEAD -> test-taille, origin/test-taille, origin/HEAD) Resolution du conflit
464464e le conflic
c8cdac5 le conflic
```
