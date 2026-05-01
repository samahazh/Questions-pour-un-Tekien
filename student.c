#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "student.h"

void launchStudentMode() {
    QCM monQuiz;
    char bufferSaisie[MAX_TEXT]; // Notre panier magique pour aspirer les textes et les chiffres !

    printf("\n==========================================\n");
    printf("              MODE ETUDIANT\n");
    printf("==========================================\n");
    
    printf("Entrez le nom du fichier QCM a ouvrir (ex: quizz.bin) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    bufferSaisie[strcspn(bufferSaisie, "\n")] = 0; // On retire le 'Entree'

    FILE *f = fopen(bufferSaisie, "rb");
    if (f == NULL) {
        printf("\n[ERREUR] Impossible de trouver le fichier '%s'\n", bufferSaisie);
        printf("Appuyez sur Entree pour revenir au menu");
        fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
        return;
    }
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    float scoreFinal = 0;

    for (int i = 0; i < monQuiz.num_questions; i++) {
        int choixEleveTableau[MAX_OPTIONS] = {0}; // Tableau pour stocker ce que l'eleve coche

        printf("\n------------------------------------------\n");
        printf("Question %d : %s\n", i + 1, monQuiz.questions[i].statement);
        
        if (monQuiz.rules.multiple_answers == 1) {
            printf("(ATTENTION : Plusieurs reponses possibles)\n");
        }

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.questions[i].options[j]);
        }

        /* --- SI C'EST UNE QUESTION A CHOIX MULTIPLES --- */
        if (monQuiz.rules.multiple_answers == 1) {
            int nbChoix = 0;
            do {
                printf("\nCombien de reponses voulez-vous donner ? (1 a %d) : ", MAX_OPTIONS);
                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
                nbChoix = atoi(bufferSaisie);
            } while (nbChoix < 1 || nbChoix > MAX_OPTIONS);

            for (int k = 0; k < nbChoix; k++) {
                int rep = 0;
                do {
                    printf("  Donnez votre choix n%d : ", k + 1);
                    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
                    rep = atoi(bufferSaisie);
                } while (rep < 1 || rep > MAX_OPTIONS);
                choixEleveTableau[rep - 1] = 1; // On enregistre la case cochee
            }
        } 
        /* --- SI C'EST UNE QUESTION A CHOIX UNIQUE --- */
        else {
            int choixEleve = 0;
            do {
                printf("\nVotre reponse (1 a %d) : ", MAX_OPTIONS);
                fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
                choixEleve = atoi(bufferSaisie);
                if (choixEleve < 1 || choixEleve > MAX_OPTIONS) {
                    printf("Erreur : Choisissez un chiffre valide.\n");
                }
            } while (choixEleve < 1 || choixEleve > MAX_OPTIONS);
            choixEleveTableau[choixEleve - 1] = 1; // On enregistre la case cochee
        }

        // VERIFICATION DES REPONSES
        int correct = 1;
        for (int j = 0; j < MAX_OPTIONS; j++) {
            if (choixEleveTableau[j] != monQuiz.questions[i].correct_answers[j]) {
                correct = 0; // L'eleve s'est trompe sur au moins une case
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

    float noteSur20 = 0;
    if (monQuiz.num_questions > 0) { // Securite pour eviter la division par zero
        noteSur20 = (scoreFinal / monQuiz.num_questions) * 20;
    }
    if (noteSur20 < 0) noteSur20 = 0;

    printf("\n------------------------------------------\n");
    printf("              RESULTAT FINAL\n");
    printf("------------------------------------------\n");
    printf("Votre note : %.2f / 20\n", noteSur20);
    printf("==========================================\n\n");

    printf("Appuyez sur Entree pour revenir au menu");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin); // Pause finale propre
}
