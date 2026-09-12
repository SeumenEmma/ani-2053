## commande de compilation de mes fichiers sources 
$ext = @("*.cpp","*.c","*.cc","*.cxx","*.h","*.hpp","*.hh","*.hxx","*.inl","*.ipp"); $src = Get-ChildItem -Recurse -File -Include $ext | Where-Object { $_.FullName -notmatch '\\Build\\' }; "Fichiers sources : $($src.Count)"; "Lignes totales : $((Get-Content -LiteralPath $src.FullName | Measure-Object -Line).Lines)"

Et j ai obtenue comme fichier sources : 5209
et lignes totales : 2635332

J ai obtenue 5209 fichiers sources et 2635332 lignes alors que celui du chapitre q 2641 fichiers sorces et 1193385 lignes ce qui donne un ecart de 2568 pour les fichiers sorces et 1441947 lignes il y as cet ecart parce  que il y as beaucoup plus d extensions supplementaire avec les fichier en tete chez moi et pas que les .cpp et .h comme ceux dans le chapitre 