## Modification d un meme fichier  

J ai modifier le fichier A et le fichier B a deux endroit eloignes. Dans A modification en Haut et dans B modification en bas.

### Modification de A

J ai modifier le fichier A puis j ai fait un 
```
git commit -m "Modification de la partie A"
```
ce qui donne :
```
On branch test-taille
Your branch is ahead of 'origin/test-taille' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
```
puis je fais un 
```
git push
```
ce qui donne :
```
 ! [rejected]        test-taille ->test-taille (fetch first)
error: failed to push some refs to 'https://github.com/SeumenEmma/TestGit-'
hint: Updates were rejected becausethe remote contains work that you do not
hint: have locally. This is usuallycaused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

### Modification de B

J ai modifier le fichier B puis j ai fait un 
```
git commit -m "Modification de la partie B"
```
ce qui me donne :
```
On branch test-taille
Your branch is up to date with 'origin/test-taille'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
puis je fais un 
```
git pull
```
ce qui donne :
```
Everything up-to-date
```

Enfin j ai fais un 
```
git log --online 
```
ce qui donne pour A 
```
b6f09c8 (HEAD -> test-taille) Modification de la partie A
```
Et pour B
```
4d62c0f (HEAD -> test-taille) Modification de la partie B
```
