#include <stdio.h>
#include <stdlib.h>
#include "qcm.h"

void launchStudentMode() {
    QCM monQuiz;
    char nomFichier[100];
    float scoreFinal = 0;

    printf("\n--- BIENVENUE AU TEST ---\n");
    printf("Nom du fichier QCM à ouvrir : ");
    scanf("%s", nomFichier);

    // 1. Lecture du fichier
    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("Erreur : Impossible de trouver le fichier %s\n", nomFichier);
        return;
    }
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    // 2. Déroulement des questions
    for (int i = 0; i < monQuiz.nbTotalQuestions; i++) {
        int choixEleve;
        printf("\nQuestion %d : %s\n", i + 1, monQuiz.listeQuestions[i].enonce);
        
        for (int j = 0; j < NB_CHOIX; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.listeQuestions[i].propositions[j]);
        }

        printf("Votre réponse (1-4) : ");
        scanf("%d", &choixEleve);

        // 3. Vérification simple (on regarde si l'index choisi est marqué comme vrai)
        // On fait -1 car l'ordinateur compte de 0 à 3, mais l'élève voit 1 à 4
        if (monQuiz.listeQuestions[i].reponsesVraies[choixEleve - 1] == 1) {
            printf("Bravo ! C'est juste.\n");
            scoreFinal += 1;
        } else {
            printf("Dommage, c'est faux.\n");
            if (monQuiz.parametres.pointsNegatifs == 1) {
                scoreFinal -= 0.5;
            }
        }
    }

    // 4. Calcul de la note sur 20
    float noteSur20 = (scoreFinal / monQuiz.nbTotalQuestions) * 20;
    if (noteSur20 < 0) noteSur20 = 0; // On évite les notes négatives

    printf("\n--- RESULTAT ---\n");
    printf("Votre note finale : %.2f / 20\n", noteSur20);
}
