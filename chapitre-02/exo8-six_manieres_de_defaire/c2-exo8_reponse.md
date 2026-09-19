### 1. Une modification non voulue

J'ai modifié `fichier1.txt` volontairement et puis j ai tape la commande 
```
git status
``` 
et ca donne :
```
On branch exercice-8
Changes not staged for commit:
        modified:   fichier1.txt
```
puis j ai utilise la commande :
```
git stash push -m "travail precedent avant exercice 8"
```
ce qui donne 
```
Saved working directory and index state On exercice-8: travail precedent avant exercice 8
```
puis un 
```
git stash list
```
ce qui donne :
```
stash@{0}: On exercice-8: travail precedent avant exercice 8
```

Pour annuler cette modification, j'ai utilisé :
```
git restore fichier1.txt
```

Puis 
```git status
``` 
ce qui donne :
```
On branch exercice-8
nothing to commit, working tree clean
```

La modification non voulue a donc été annulée.

### 2. Un add de trop

J'ai modifié fichier1.txt, puis effectué un 
```git add fichier1.txt
```
puis un 
```git status
``` 
ce qui donne :
```
On branch exercice-8
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   fichier1.txt
```

Pour annuler uniquement le add, j'ai utilisé :
```
git restore --staged fichier1.txt
```
puis un:
```git status
``` 
ce qui me donne :
```
On branch exercice-8
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

La modification est donc conservée, mais elle n'est plus dans le staging.

### 3. Un commit de trop

J'ai créé volontairement un commit supplémentaire qui est Commit de trop.
avec :
```
git commit -m "Commit de trop"
```
ce qui donne 
```
[exercice-8 bd33d6c] Commit de trop
 1 file changed, 3 insertions(+), 1 deletion(-)
```
apres j affiche l historique pour voir si c est bien la avec
```
git log --oneline -3
```
ce qui me donne 
```
bd33d6c (HEAD -> exercice-8) Commit de trop
b6f09c8 (test-taille) Modification de la partie A
c8cdac5 (origin/test-taille, origin/HEAD) le conflic
```

Son identifiant est :
```
bd33d6c
```
Pour annuler ce commit, j'ai utilisé :
```
git reset HEAD~1
```
ce qui me donne :
```
Unstaged changes after reset:
M       fichier1.txt
```

Après cette commande je tape 
```git status
``` 
ce qui me donne 
```
On branch exercice-8
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
alors Le commit bd33d6c a également disparu de l'historique voici la preuve en tapant
```
git log --oneline -3
```
ce qui donne 
```
b6f09c8 (HEAD -> exercice-8, test-taille) Modification de la partie A
c8cdac5 (origin/test-taille, origin/HEAD) le conflic
3e9acc6 troisieme commit de test
```

### 4. Un commit poussé qu'il faut annuler

j ai tape un 
```
git add fichier1.txt
```
apres J'ai créé le commit avec :
```
git commit -m "Commit pousse a annuler"
```
ce qui me donne 
```
[exercice-8 b385871] Commit pousse a annuler
 1 file changed, 3 insertions(+), 1 deletion(-)
```
j ai affiche l historique des commits avec :
```
git log --oneline -3
```
ce qui donne :
```
b385871 (HEAD -> exercice-8) Commit pousse a annuler
b6f09c8 (test-taille) Modification de la partie A
c8cdac5 (origin/test-taille, origin/HEAD) le conflic
```

Je l'ai ensuite poussé sur GitHub avec :
```
git push -u origin exercice-8
```
ce qui me donne :
```
Enumerating objects: 40, done.
Counting objects: 100% (40/40), done.
Delta compression using up to 12 threads
Compressing objects: 100% (30/30), done.
Writing objects: 100% (40/40), 3.78 KiB | 968.00 KiB/s, done.
Total 40 (delta 10), reused 30 (delta 7), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (10/10), done.
remote: 
remote: Create a pull request for 'exercice-8' on GitHub by visiting:
remote:      https://github.com/SeumenEmma/TestGit-/pull/new/exercice-8
remote: 
To https://github.com/SeumenEmma/TestGit-
 * [new branch]      exercice-8 -> exercice-8
branch 'exercice-8' set up to track 'origin/exercice-8'.
```

Pour annuler un commit déjà poussé, j'ai utilise :
```
git revert b385871
```
ce qui donne :
```
[exercice-8 b8f0113] Revert "Commit pousse a annuler"
 1 file changed, 1 insertion(+), 3 deletions(-)
```
Enfin, j'ai poussé le revert avec :
```
git push
```
ce qui donne :
```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 370 bytes | 370.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/SeumenEmma/TestGit-
   b385871..b8f0113  exercice-8 -> exercice-8
```
puis je fait un 
```git status
``` 
ce qui me donne :
```
On branch exercice-8
Your branch is up to date with 'origin/exercice-8'.

nothing to commit, working tree clean
```

### 5. Un travail en cours qu'il faut mettre de côté

J'ai effectué une modification sur fichier1.txt pour simuler un travail en cours.
je tape :
```git status
```
ce qui me donne :
```
On branch exercice-8
Your branch is up to date with 'origin/exercice-8'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
apres je tape un :
```
git stash push -m "travail en cours situation 5"
```
ce qui me donne :
```
Saved working directory and index state On exercice-8: travail en cours situation 5
```
Après cette commande je tape 
```
git status
``` 
ce qui me donne :
```
On branch exercice-8
Your branch is up to date with 'origin/exercice-8'.

nothing to commit, working tree clean
```

J'ai vérifié les stash avec :
```
git stash list
```
ce qui donne :
```
stash@{0}: On exercice-8: travail en cours situation 5
stash@{1}: On exercice-8: travail precedent avant exercice 8
```
Le nouveau stash apparaissait avec le message :
stash@{0}: On exercice-8: travail en cours situation 5

Pour récupérer ce travail, j'ai utilisé :
```
git stash pop "stash@{0}"
```
La modification de fichier1.txt a été restaurée et le stash a été supprimé.

### 6. Un commit perdu 

pour commencer j ai fait un 
```
git add fichier1.txt
```
ensuite un 
```
git commit -m "Commit perdu"
```
ce qui donne 
```
[exercice-8 a1af17d] Commit perdu
 1 file changed, 4 insertions(+), 1 deletion(-)
```
je verifie l historique des commit avec :
```
git log --oneline -4
```
ce qui montre 
```
a1af17d (HEAD -> exercice-8) Commit perdu
b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
b385871 Commit pousse a annuler
b6f09c8 (test-taille) Modification de la partie A
```

Le commit a retrouver était donc :
```
a1af17d Commit perdu
```

Pour faire disparaître ce commit de l'historique de la branche j'ai utilisé :
```
git reset --hard b8f0113
```
ce qui me donne :
```
HEAD is now at b8f0113 Revert "Commit pousse a annuler"
```

Puis je fais un :
```
git log --oneline -4
```
ce qui me donne :
```
b8f0113 (HEAD -> exercice-8, origin/exercice-8) Revert "Commit poussea annuler"
b385871 Commit pousse a annuler
b6f09c8 (test-taille) Modification de la partie A
c8cdac5 (origin/test-taille, origin/HEAD) le conflic
```

Le commit a1af17d n'apparaissait plus dans le git log.

J'ai ensuite utilisé la commande :
```
git reflog
```
ce qui me donne :
```
b8f0113 (HEAD -> exercice-8, origin/exercice-8) HEAD@{0}: reset: moving to b8f0113
a1af17d HEAD@{1}: commit: Commit perdu
b8f0113 (HEAD -> exercice-8, origin/exercice-8) HEAD@{2}: reset: moving to HEAD
b8f0113 (HEAD -> exercice-8, origin/exercice-8) HEAD@{3}: reset: moving to HEAD
b8f0113 (HEAD -> exercice-8, origin/exercice-8) HEAD@{4}: revert: Revert "Commit pousse a annuler"
b385871 HEAD@{5}: commit: Commit pousse a annuler
b6f09c8 (test-taille) HEAD@{6}: reset: moving to HEAD~1
bd33d6c HEAD@{7}: commit: Commit de trop
b6f09c8 (test-taille) HEAD@{8}: reset: moving to HEAD
b6f09c8 (test-taille) HEAD@{9}: checkout: moving from test-taille to exercice-8
b6f09c8 (test-taille) HEAD@{10}: reset: moving to HEAD~1
c8aa0ef HEAD@{11}: commit: Commit de test en trop
b6f09c8 (test-taille) HEAD@{12}: commit: Modification de la partie A
c8cdac5 (origin/test-taille, origin/HEAD) HEAD@{13}: commit: le conflic
3e9acc6 HEAD@{14}: clone: from https://github.com/SeumenEmma/TestGit-
```

La ligne importante était :
```
a1af17d HEAD@{1}: commit: Commit perdu
```

Le reflog m'a donc permis de retrouver l'identifiant a1af17d. J'ai ensuite restauré le commit avec :
```
git reset --hard a1af17d
```
ce qui me donne :
```
HEAD is now at a1af17d Commit perdu
```

Enfin un :
```
git log --oneline -4
```
qui me donne :
```
a1af17d (HEAD -> exercice-8) Commit perdu
b8f0113 (origin/exercice-8) Revert "Commit pousse a annuler"
b385871 Commit pousse a annuler
b6f09c8 (test-taille) Modification de la partie A
```
Le commit a1af17d a donc été retrouvé grâce au reflog, puis restauré.