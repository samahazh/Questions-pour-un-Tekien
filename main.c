#include <stdio.h>    // Nécessaire pour printf et fgets
#include <stdlib.h>   // Nécessaire pour atoi
#include "qcm.h"      // Ta structure
#include "teachers.h" // Pour launchTeacherMode
#include "student.h"  // Pour launchStudentMode

int main() {
    int choix;
    char saisie[50];

    do {
        // Espaces et séparateurs pour la clarté
        printf("\n==========================================\n");
        printf("          QUESTIONS POUR UN TEKIEN\n"); 
        printf("==========================================\n");
        printf(" 1 - Mode Enseignant (Créer / Gérer QCM)\n");
        printf(" 2 - Mode Étudiant (Passer un QCM)\n");
        printf(" 3 - Quitter l'application\n");
        printf("------------------------------------------\n");
        printf("Veuillez entrer votre choix (1 à 3) : ");

        if (fgets(saisie, sizeof(saisie), stdin) != NULL) {
            choix = atoi(saisie);
        } else {
            choix = 0;
        }

        switch (choix) {
            case 1:
                printf("\n[Lancement du Mode Enseignant...]\n");
                launchTeacherMode();
                break;

            case 2:
                printf("\n[Lancement du Mode Étudiant...]\n");
                launchStudentMode();
                break;

            case 3:
                printf("\nAu revoir ! Merci d'avoir utilisé l'application.\n\n");
                break;

            default:
                printf("\n--- ERREUR : Saisie invalide ! ---\n");
                printf("--- Veuillez entrer un chiffre entre 1 et 3. ---\n\n");
                break;
        }
    } while (choix != 3);

    return 0;
}

