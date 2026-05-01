#ifndef TEACHERS_H
#define TEACHERS_H

#include "qcm.h" // Nécessaire car on utilise la structure QCM

/**
 * Fonction principale du mode enseignant :
 * - Gère l'authentification par mot de passe
 * - Appelle la création de QCM si le mot de passe est bon
 */
void launchTeacherMode();

/**
 * Fonction de création de QCM :
 * - Saisie du titre et des paramètres
 * - Saisie des questions et des bonnes réponses
 * - Sauvegarde dans un fichier .bin
 */
void createQCM();

#endif