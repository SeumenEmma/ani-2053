## Compilation 
J ai utilise comme commande de compilation :
```
Get-Content ".\Kernel\Foundation\NKContainers\NKContainers.jenga"
```
Pour pouvoir trouver le contenue de NKContainers

## Contenue de NKContenaires
```
from Jenga import *
from jengaconfig import *


with project("NKContainers"):
    language("C++")
    cppdialect("C++17")
    location(".")

    nkentseudependson(
        ["NKCore", "NKPlatform", "NKMemory"],
        selfexport="NKContainers",
        extra_includes=["src", "pch"],
        extra_defines=["NK_USE_STD_INITIALIZER_LIST"],
    )

    pchheader("pch/pch.h")
    pchsource("pch/pch.cpp")

    files([
        "src/NKContainers/**.cpp",
    ])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

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

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG", "NKENTSEU_DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)

    with filter("(system:Linux || system:macOS || (system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne)) && !system:Android && !system:iOS || system:Web"):
        with test():
            testfiles(["tests/**.cpp"])
```
## Annotation Ligne par ligne
```
1. from Jenga import *
2. from jengaconfig import *
```
1. Il importe les fonctions de Jenga utilisees pour definir le projet
2. Il importe la configuration du projet notamment les variables

```
3. with project("NKContainers"):
4.    language("C++")
5.    cppdialect("C++17")
6.    location(".")
```
3. Il declare le NKContainers
4. Pour dire que le projet est en C++
5. Pour dire que l on utilise la version 17 de c++
6. Pour dire que le dossier du projet est dans le dossier courant 

```
7.  nkentseudependson(
8.        ["NKCore", "NKPlatform", "NKMemory"],
9.       selfexport="NKContainers",
10.        extra_includes=["src", "pch"],
11.        extra_defines=["NK_USE_STD_INITIALIZER_LIST"],
    )
```
7. et 8. c est pour dire que NKContainers depend de NKCore, NKPlateform et NKMemory
9. Il indique ce que le module exporte
10. Il permet d ajouter les chemins d inclusion
11. C est pour ajouter cette definition au projet 

```
12.pchheader("pch/pch.h")
13.    pchsource("pch/pch.cpp")
14.
15.    files([
        "src/NKContainers/**.cpp",
16.    ])
```

12. C est pour les fichier d en tete
13. C est pour les fichiers sources
15. C est pour inclure les fichiers .cpp present dans NKContainers

```
17. objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
18.    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")
```
17. C est pour definir le dossier ou seront places les fichiers objtes 
18. C est pour definir le dossier de sortie de la bibliotheque 

```
19. with filter("system:Windows && options:windows-runtime=uwp"):
20.        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
21.        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")
22.
23.    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
24.        usetoolchain(TC_WINDOWS)
25.    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
26.        usetoolchain("xbox-clang")
```
19. ?? je ne comprend pas 
20. ?? je ne comprend pas 
22. ?? je ne comprend pas 
23. ?? je ne comprend pas 
24. ?? je ne comprend pas 
25. ?? je ne comprend pas 
26. ?? je ne comprend pas 

```
27. with filter("system:Linux"):
28.        links(["pthread"])
```
27. et 28. C est pour dire que sur linux le projet utilise la bibliotheque pthread

```
29. with filter("system:macOS"):
30.        usetoolchain("clang-native")
```
29. et 30. C est pour dire que sur macOS, utilisation de la toolchain clang-native

```
31.   with filter("system:Android"):
32.        # Workaround: disable PCH on Android (NDK r27 + clang 18 + libc++)
33.        pchheader("")
34.        pchsource("")
35.        usetoolchain("android-ndk")
36.        links(["log"])
```
31. C est la configuration pour android
33. et 34.  Il permet de desactiver le PCH pour android 
35.  et 36. C est pour dire que ca utilise Android NDK 