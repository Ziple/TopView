Ce dossier contient l'impl�mentation en C++ de l'algorithme de Levenberg-Marquardt.

Le fichier d'en-t�te � pr�senter � LabView pour r�aliser l'interfa�age est disponible dans include/ .

Ce projet n�cessite un compilateur C++, CMake ainsi que la biblioth�que Eigen ( eigen.tuxfamily.org ).
Si Eigen se trouve dans extlibs/eigen, elle sera d�tect�e automatique par le script cmake se trouvant dans cmake/Modules/FindEigen3.cmake .


Pour construire les versions 64 bits:
 - penser � faire une nouvelle config, pas � partir de la version 32 bits.

Ne pas oubliez de passer le runtime en static!
