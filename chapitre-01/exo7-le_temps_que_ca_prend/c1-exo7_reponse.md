## 1 ere Compilation 

Pour la premiere compilation j ai utilise la commande :
```
Measure-Command { jenga build }
```
pour mesurer directement le temps pour le resultat j ai obtenue :
```
155,34 secondes.
```
## 2 eme Compilation 

J ai utilise la meme commande pour le 2 eme et j ai obtenue :
```
53,551 secondes
```
## Comparaison

| Compilation | Temps |
|-------------|-------|
| 1ère        | 155,34 s|
| 2ème        | 53,551 s |

L ecart est donc de :
```
101,792 s
```
Alors la deuxieme compilation est 101,792 s plus rapide que celle de la premiere. Elle s explique par le fait que la premiere compilation les fichiers deja construits peuvent etre reutilises lorsque aucune modification n as ete faite donc ce qui evite a la deuxieme compilation de rfaire tout le travail. 