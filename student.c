#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"      // Pour utiliser les structures Parameters, Question, QCM
#include "student.h"  // Pour que le fichier soit relié à son header

// Cette fonction est celle appelée par le main.c (choix 2)
void launchStudentMode() {
    char filename[128];
    QCM currentQuiz;

    printf("\n--- MODE ETUDIANT ---\n");
    printf("Voici les QCM disponibles (entrez le nom exact du fichier) : ");
    // Note : Idéalement, il faudrait lister les fichiers, mais pour rester simple :
    scanf("%s", filename);

    // 1. OUVERTURE ET LECTURE DU FICHIER
    FILE *file = fopen(filename, "rb"); // "rb" pour lire un fichier binaire
    if (file == NULL) {
        printf("\033[1;31mErreur : Le fichier '%s' n'existe pas.\033[0m\n", filename);
        return;
    }

    // On lit toute la structure QCM d'un coup
    fread(&currentQuiz, sizeof(QCM), 1, file);
    fclose(file);

    // 2. LANCEMENT DU QUIZ
    printf("\nDemarrage du QCM : %s\n", currentQuiz.name);
    
    float totalPoints = 0;
    int answer;

    for (int i = 0; i < currentQuiz.num_questions; i++) {
        printf("\nQuestion %d : %s\n", i + 1, currentQuiz.questions[i].statement);
        
        // Affichage des 4 options
        for (int j = 0; j < 4; j++) {
            printf("  %d) %s\n", j + 1, currentQuiz.questions[i].options[j]);
        }

        // Saisie de l'élève
        printf("Votre choix (1-4) : ");
        scanf("%d", &answer);

        // Gestion du Mode Séquentiel (Obligation de répondre)
        if (currentQuiz.rules.sequential_mode == 1 && (answer < 1 || answer > 4)) {
            printf("Saisie invalide. Vous DEVEZ repondre pour continuer.\n");
            i--; // On décrémente pour rester sur la même question
            continue;
        }

        // Verification de la réponse (on regarde dans le tableau correct_answers)
        // On fait -1 car l'élève tape 1-4 mais le tableau va de 0-3
        if (answer >= 1 && answer <= 4 && currentQuiz.questions[i].correct_answers[answer - 1] == 1) {
            printf("\033[1;32mJuste !\033[0m\n");
            totalPoints += 1.0;
        } else {
            printf("\033[1;31mFaux !\033[0m\n");
            // Gestion des points négatifs
            if (currentQuiz.rules.negative_points == 1) {
                totalPoints -= 0.5;
            }
        }
    }

    // 3. CALCUL ET AFFICHAGE DE LA NOTE FINALE SUR 20
    float finalGrade = (totalPoints / currentQuiz.num_questions) * 20;
    if (finalGrade < 0) finalGrade = 0; // On ne descend pas en dessous de 0/20

    printf("\n------------------------------\n");
    printf("SCORE FINAL : %.2f / 20\n", finalGrade);
    printf("------------------------------\n");
}
