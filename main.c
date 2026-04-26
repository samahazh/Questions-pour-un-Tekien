#include <stdio.h>
#include <stdlib.h>
#include "qcm.h"
#include "teachers.h"
#include "student.h"

int main() {
  int choix;
  char saisie[50];

  do {
      printf("          QUESTIONS POUR UN TEKIEN\n"); 
      printf("1 - Mode Enseignant (Créer / Gérer QCM)\n");
      printf("2 - Mode Étudiant (Passer un QCM)\n");
      printf("3 - Quitter l'application\n");
      printf("Veuillez entrer votre choix (1 à 3) : ");

      fgets(saisie, sizeof(saisie), stdin);
      choix = atoi(saisie);

      switch (choix) {
          case 1:
              printf(">> Lancement du Mode Enseignant.\n");
              launchTeacherMode();
              break;

          case 2:
              printf(">> Lancement du Mode Étudiant.\n");
              launchStudentMode();
              break;

          case 3:
              printf("Fermeture de l'application.");
              break;

          default:
              printf(" Erreur : saisie invalide ! Veuillez entrer un chiffre entre 1 et 3.\n");
              break;
      }
  } while (choix != 3);

  return 0;
} 



