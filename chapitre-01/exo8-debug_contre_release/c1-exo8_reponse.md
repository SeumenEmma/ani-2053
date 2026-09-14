## Comparaison Debug / Release

| Configuration | Taille du binaire | Temps de construction |
|---|---:|---:|
| Debug | 140 636 octets | 59,8268195 s |
| Release | 130 764 octets | 81,719061 s |

Ici Release est environ plus petit que Debug en terme de la taille du binaire mais Debug est plus rapide que Release.

## Explication des quatres nombres 

Dans MonEssai.jenga les differences sont expliquees par les filtres de configurations qui sont :
```
    with filter("config:Debug"):
        defines(["_DEBUG"]); optimize("Off"); symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"]); optimize("Speed"); symbols(False)
``` 
Dans Debug l optimization est desactivee et les symboles de debogage sont actives alors que dans Release l optimization est activee et les symboles de debogage sont desactives.