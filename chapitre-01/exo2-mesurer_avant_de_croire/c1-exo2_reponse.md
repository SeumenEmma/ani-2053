## commande de compilation de mes fichiers sources 
```
$src = Get-ChildItem -Recurse -File | Where-Object {
    $_.Extension -in '.cpp','.c','.cc','.cxx','.h','.hpp','.hh','.hxx','.inl','.ipp'
}

$lines = 0
foreach ($f in $src) {
    $lines += (Get-Content -LiteralPath $f.FullName | Measure-Object -Line).Lines
}

"Fichiers sources : $($src.Count)"
"Lignes : $lines"
```

Et j ai obtenue comme fichier sources : 5209
et lignes totales : 2635332

J ai obtenue 5209 fichiers sources et 2635332 lignes alors que celui du chapitre est 2641 fichiers sorces et 1193385 lignes ce qui donne un ecart de 2568 pour les fichiers sources et 1441947 lignes il y as cet ecart parce  que il y as beaucoup plus d extensions supplementaire avec les fichier en tete chez moi et pas que les .cpp et .h comme ceux dans le chapitre 

## Pour la mesure des extentions 

J ai utilise la commande :
```
Get-ChildItem -Recurse -File |
Where-Object {
    $_.Extension -in '.cpp','.c','.cc','.cxx','.h','.hpp','.hh','.hxx','.inl','.ipp'
} |
Group-Object Extension |
Sort-Object Name |
Select-Object Name, Count
```
j ai obtenue 

- .c =    313
- .cc =   219
- .cpp = 1713
- .h  =  2864
- .hpp =  68
- .inl =   33

## Comptage sans les en-tetes

J ai utilise la commande :
```
$src = Get-ChildItem -Recurse -File | Where-Object {
    $_.Extension -in '.cpp','.c','.cc','.cxx'
}

$lines = 0
foreach ($f in $src) {
    $lines += (Get-Content -LiteralPath $f.FullName | Measure-Object -Line).Lines
}

"Fichiers sources sans en-têtes : $($src.Count)"
"Lignes sans en-têtes : $lines"
```
J ai trouve :
- Fichiers sources sans en-têtes : 2245
- Lignes sans en-têtes : 1203895