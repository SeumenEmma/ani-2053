## Presnetation d un fichier 

### Introduction
Bonjour je vais vous presenter le fichier NKContainers.jenga 

Pour cette presentation j ai choisi le fichier 
```
NKContainers.jenga 
```
Dans ce fichier on trouve :
- ce que le projet declare
- les fichiers qu il utilise
- Les dependances 

Je vais vous presenter ce que NKContainers.jenga declare, ce qu il filtre et ce qu il delegue 


Pour le commencement du fichier 
```
from Jenga import *
from jengaconfig import *
```

Pour declarer le projet
```
with project("NKContainers"):
```

Pour le language utilise est en C++17
```
    language("C++")
    cppdialect("C++17")
    location(".")
```

pour les differents module qu il utilise NKCore, NKPlateform et NKMelory
```
    nkentseudependson(
        ["NKCore", "NKPlatform", "NKMemory"],
        selfexport="NKContainers",
        extra_includes=["src", "pch"],
        extra_defines=["NK_USE_STD_INITIALIZER_LIST"],
    )
```

    pchheader("pch/pch.h")
    pchsource("pch/pch.cpp")

Pour les fichiers sources 
```
    files([
        "src/NKContainers/**.cpp",
    ])
```
Ceux si est imcomprehensible je ne comprend pas
```
    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")
```
Pour les fichiers qui contiennent des filtres selon le systeme utilise
```
    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS)
    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang")
    with filter("system:Linux"):
        links(["pthread"])
    with filter("system:macOS"):
        usetoolchain("clang-native")
    with filter("system:Android"):
        # Workaround: disable PCH on Android (NDK r27 + clang 18 + libc++)
        pchheader("")
        pchsource("")
        usetoolchain("android-ndk")
        links(["log"])
    with filter("system:HarmonyOS"):
        # PCH desactive (NDK OHOS clang, meme contrainte qu'Android)
        pchheader("")
        pchsource("")
        usetoolchain("ohos-ndk")
        links(["hilog_ndk.z"])
    with filter("system:Web"):
        usetoolchain("emscripten")
    with filter("system:XboxSeries || system:XboxOne"):
        usetoolchain("xbox-clang")
```
Pour des filtres pour les configurations Debug et Release 
```
    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG", "NKENTSEU_DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)

    with filter("(system:Linux || system:macOS || (system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne)) && !system:Android && !system:iOS || system:Web"):
```
Pour le filtre permettant de definir les tests du module 
```
        with test():
            testfiles(["tests/**.cpp"])
```

Le fichier delegue notamment la gestion des dependances a :
```
nkentseudependson(...)
```
Il delegue egalement le choix du toolchain selon le systeme 
```
usetoolchain(...)
```
Et la gestion de l edition des liens avec 
```
links(...)
```
## Ou est decide NKContainers est une bibliotheque statique 

Il est determinee par :
```
with project("NKContainers"):
```
## Ce que NKContainers declare

Il declare :
- Le projet NKContainers
- le languages c++
- l emplacement
- les dependances
- les diffferents fichiers sources
- les configurations 

## Les filtres

Les filtres selon le systeme il y as :
- Windowz
- UWP
- Linux 
- macOS
- Android
- HarmonyOS
- Web
- Xbox 
- Les deux configurations 

## Ce qu il delegue 

Il ne compile pas de lui meme les fichiers .cpp
il laisse jenga organiser la construction 
jenga utilise les toolchains pars exemples
```
clang-native
android-ndk
```


