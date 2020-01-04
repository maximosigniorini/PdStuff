# 2DMovie 
## Bibliothèque Pure Data pour l'animation en 2D

- Version : 1.7 
- Langue : Français
- Date: 12/10/2015
- Contact : htbf@orange.fr
- Licence : GNU/GPL v3

![alt tag](https://github.com/Pertuit/2DMovie/blob/master/2DMovie/data/rmimg1.png)
![alt tag](https://github.com/Pertuit/2DMovie/blob/master/2DMovie/data/rmimg2.png)
![alt tag](https://github.com/Pertuit/2DMovie/blob/master/2DMovie/data/rmimg3.png)

### INTRODUCTION

2DMovie est une bibliothèque conçue pour simplifier la réalisation d'animations 2D avec Pure Data. Elle permet d'afficher des images fixes ou animées (tableaux d'images) en appelant un simple objet, de rendre facilement les images affichées sensibles ou non à la souris, de les positionner et de les animer à l'aide de variables et de fonctions.

Elle se base sur les éléments courants de GEM (pix_image, pix_multiimage, text3d, etc.) et s'inspire librement des classes d'animation utilisées en ActionScript bien qu'il ne soit question ici que d'images bitmap (pas de vectoriel).

Ce projet universitaire a pour objet de faciliter la création d'images afin de se concentrer sur l'aspect algorithmique de leur manipulation. Tous les patches sont documentés en français et des exemples simples d'application sont disponibles.

Merci de m'informer si cette bibliothèque a été utile dans vos applications ou de suggérer des modifications à lui apporter. 

### INSTALLATION

2DMovie a été conçue avec les bibliothèques standards de Pd-extended.

Comme toutes les bibliothèques externes, le dossier 2DMovie doit être installé dans le répertoire Pd (à créer, s'il n'existe pas) se trouvant dans :
- sur Mac : /Users/monNom/Library/Pd
- sur PC : C:\Program Files\Common Files\Pd
- sur UNIX : /usr/local/lib/pd-externals

Il faut alors ajouter le path dans les préférences :
- sur Mac : /Users/monNom/Library/Pd/2DMovie
- sur PC : C:\Program Files\Common Files\Pd\2DMovie
- sur UNIX : /usr/local/lib/pd-externals/2DMovie

### CONTENU DE LA BIBLIOTHEQUE

#### Modules graphiques :

- GemManager : gestionnaire de fenêtre GEM
- SimpleImage : affichage d’une image (fond d’écran ou image à positionner)
- MovieClip : affichage d’images animées (tableau d’images lues en boucle)
- VideoClip : affichage d’une vidéo
- Label : affichage d’une chaîne de caractères
- Zone : affichage d’une surface rectangulaire (zone sensible à la souris)

#### Modules sonores :

- SoundPlayer : lecture simple d’un fichier son
- SoundControl : lecture contrôlée d’un fichier son

#### Boîte à outils :

La bibliothèque contient également des fonctions de test des collisions entre deux objets graphiques 2DMovie, des fonctions de conversion entre l'espace GEM et la fenêtre en pixels, des fonctions de déplacement des images et d'autres fonctions de traitement des valeurs numériques.

Ces fonctions sont récapitulées dans la fiche 2DMovieCard.pdf se trouvant dans le répertoire doc. Mais surtout, les exemples détaillés sont à consulter dans l'aide de chaque module.


