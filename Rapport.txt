ALETRUT Thibaut
GADEFAIT Etienne
HORION-COUDENE Claire
4-AE-SE-TP2
2025-2026

Rapport BE C++

Nous avons conçu une "borne arcade" comportant trois jeux : 1 puissance 4, 1 puissance 4 version retro et 1 jeu d'échecs. 
Pour ce faire, nous avons utilisé une carte ProMicro avec cinq boutons : quatre pour les déplacements sur l'écran et un bouton central pour la sélection. Le Serial Monitor de l'IDE Arduino permet l'affichage du jeu. 

Pour concevoir ce projet, nous avons chacun conçu un jeu selon nos envies, puis nous avons mis en commun le travail et créé l'interface pour la sélection du jeu. Pour démarrer le projet, il est nécessaire de téléverser le code du fichier "borne_arcade.ino" sur la carte. Puis, de sélectionner le jeu souhaité. Une fois le jeu terminé, il est possible de le réinitiliaser en appuyant sur le bouton central. Il y a également la possibilité de revenir au menu principal en appuyant sur les cinq boutons en simultané. 

Difficultés rencontrées : 
- Nous avons eu des diffiultés avec l'utilisation de la librairie standard STL. En effet, l'ajout de la librairie STL provoquait des erreurs de compilation, du fait d'une double déclaration. Pour résoudre ce problème, nous avons téléchargé la librairie STL dans notre propre dossier Arduino > libraries, puis nous avons retiré le fichier "new_handler.cpp". Avant cela, nous avons essayé de rajouter la librairie STL directement au projet, pour faciliter à la personne qui télécharge le jeu son utilisation. Malheureusement, cette méthode ne fonctionnait pas, car le compilateur ne trouvait pas la librairie concernée. 

- Concernant les exceptions, nous avons essayé de les implanter sur notre carte ProMicro. Malheureusement, cette carte prend difficilement en compte les exceptions. Pour cela, il aurait fallu modifier le fichier "platform.txt", mais cet ajout des exceptions aurait pu poser un problème de mémoire à la carte. C'est la raison pour laquelle, nous n'avons pas ajouté d'exceptions sur la version finale du projet. En revanche, nous avons tout de même compris l'utilisation des exceptions, car lors de tests en amont, nous avons utilisé la carte ESP8266 fournie et nous avons réussi à utiliser les exceptions. 
