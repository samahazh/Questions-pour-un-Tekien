#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "student.h"

void launchStudentMode() {
    QCM monQuiz;
    char nomFichier[100];
    float scoreFinal = 0;

    printf("\n==========================================\n");
    printf("              MODE ETUDIANT\n");
    printf("==========================================\n");
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    scanf("%s", nomFichier);

    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("\nERREUR : Impossible de trouver le fichier '%s'\n", nomFichier);
        while (getchar() != '\n'); 
        return;
    }
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    for (int i = 0; i < monQuiz.num_questions; i++) {
        int choixEleveTableau[MAX_OPTIONS] = {0};

        printf("\n------------------------------------------\n");
        printf("Question %d : %s\n", i + 1, monQuiz.questions[i].statement);
        
        if (monQuiz.rules.multiple_answers == 1) {
            printf("(Plusieurs reponses possibles)\n");
        }

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.questions[i].options[j]);
        }

        if (monQuiz.rules.multiple_answers == 1) {
            int nbChoix;
            printf("\nCombien de propositions voulez-vous cocher ? ");
            scanf("%d", &nbChoix);
            for (int k = 0; k < nbChoix; k++) {
                int rep;
                printf("  Choix %d : ", k + 1);
                scanf("%d", &rep);
                if (rep >= 1 && rep <= MAX_OPTIONS) {
                    choixEleveTableau[rep - 1] = 1;
                }
            }
        } else {
            int choixEleve;
            do {
                printf("\nVotre reponse : ");
                if (scanf("%d", &choixEleve) != 1) {
                    printf("Saisie invalide ! Veuillez taper un chiffre.");
                    while (getchar() != '\n'); 
                    choixEleve = 0;
                }
                if (choixEleve < 1 || choixEleve > MAX_OPTIONS) {
                    printf("Erreur : Choisissez un chiffre entre 1 et %d uniquement.", MAX_OPTIONS);
                }
            } while (choixEleve < 1 || choixEleve > MAX_OPTIONS);
            choixEleveTableau[choixEleve - 1] = 1;
        }

        int correct = 1;
        for (int j = 0; j < MAX_OPTIONS; j++) {
            if (choixEleveTableau[j] != monQuiz.questions[i].correct_answers[j]) {
                correct = 0;
                break;
            }
        }

        if (correct == 1) {
            printf("Bravo ! C'est juste.\n");
            scoreFinal += 1;
        } else {
            printf("Dommage, c'est faux.\n");
            if (monQuiz.rules.negative_points == 1) {
                scoreFinal -= 0.5;
                printf("(Point retire : -0.5)\n");
            }
        }
    }

    printf("\n==========================================\n");
    printf("      RECAPITULATIF DES BONNES REPONSES\n");
    printf("==========================================\n");
    for (int i = 0; i < monQuiz.num_questions; i++) {
        printf("Q%d : %s\n", i + 1, monQuiz.questions[i].statement);
        printf("   => La bonne reponse etait : ");
        for (int j = 0; j < MAX_OPTIONS; j++) {
            if (monQuiz.questions[i].correct_answers[j] == 1) {
                printf("[%s] ", monQuiz.questions[i].options[j]);
            }
        }
        printf("\n");
    }

    float noteSur20 = (scoreFinal / monQuiz.num_questions) * 20;
    if (noteSur20 < 0) noteSur20 = 0;

    printf("\n------------------------------------------\n");
    printf("              RESULTAT FINAL\n");
    printf("------------------------------------------\n");
    printf("Votre note : %.2f / 20\n", noteSur20);
    printf("==========================================\n\n");

    while (getchar() != '\n'); 
    printf("Appuyez sur Entree pour revenir au menu");
    getchar();
}
  
