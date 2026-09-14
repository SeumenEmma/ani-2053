## Les differentes dependances de NKCanvas 

```
- NKContainers
- NKCore
- NKEvent
- NKFileSystem
- NKFont
- NKGlad
- NKImage
- NKLogger
- NKMath
- NKMemory
- NKPlatform
- NKStream
- NKThreading
- NKTime
- NKWindow
```
15 Projets doivent etre construits avant NKCanvas

## Les dependances directs 
```
- NKWindow
- NKFont
- NKImage
- NKStream
- NKTime
- NKGlad
- NKThreading
```
## Le Graphes
```
NKCanvas
│
├── NKWindow
│   ├── NKContainers
│   ├── NKCore
│   ├── NKEvent
│   ├── NKFileSystem
│   ├── NKLogger
│   ├── NKMath
│   ├── NKMemory
│   ├── NKPlatform
│   ├── NKThreading
│   └── NKTime
│
├── NKFont
│   ├── NKContainers
│   ├── NKCore
│   ├── NKLogger
│   ├── NKMath
│   ├── NKMemory
│   ├── NKPlatform
│   └── NKThreading
│
├── NKImage
│   ├── NKContainers
│   ├── NKCore
│   ├── NKFileSystem
│   ├── NKLogger
│   ├── NKMath
│   ├── NKMemory
│   ├── NKPlatform
│   ├── NKStream
│   └── NKThreading
│
├── NKStream
│   ├── NKContainers
│   ├── NKCore
│   ├── NKFileSystem
│   ├── NKLogger
│   ├── NKMemory
│   ├── NKPlatform
│   └── NKThreading
│
├── NKTime
│   ├── NKContainers
│   ├── NKCore
│   ├── NKLogger
│   ├── NKMemory
│   ├── NKPlatform
│   └── NKThreading
│
├── NKGlad
│   └── aucune dépendance
│
└── NKThreading
    ├── NKContainers
    ├── NKCore
    ├── NKMemory
    └── NKPlatform
```

## Nombre de projet a construire avant NKCanvas 

Lors de la commande :
```
jenga build --target NKCanvas 
```
jenga affiche un ordre de construction de 16 projets en enlevant NKCanvas il y as la construction de 15 projets 