Ce dossier contient l'implémentation en C++ de l'algorithme de Levenberg-Marquardt.

Le fichier d'en-tête à présenter à LabView pour réaliser l'interfaçage est disponible dans include/ .

Ce projet nécessite un compilateur C++, CMake ainsi que la bibliothèque Eigen ( eigen.tuxfamily.org ).
Si Eigen se trouve dans extlibs/eigen, elle sera détectée automatique par le script cmake se trouvant dans cmake/Modules/FindEigen3.cmake .


Pour construire les versions 64 bits:
 - penser à faire une nouvelle config, pas à partir de la version 32 bits.

Ne pas oubliez de passer le runtime en static!
