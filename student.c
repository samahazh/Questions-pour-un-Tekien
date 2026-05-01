#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "student.h"

void launchStudentMode() {
    QCM monQuiz;
    char nomFichier[100];
    float scoreFinal = 0;

    printf("\n--- MODE ÉTUDIANT ---\n");
    
    // On demande le nom directement sans lister
    printf("Entrez le nom du fichier QCM à ouvrir (ex: Sciences.bin) : ");
    scanf("%s", nomFichier);

    // 1. OUVERTURE DU FICHIER
    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("\nERREUR : Impossible de trouver le fichier '%s'\n", nomFichier);
        // Nettoyage du buffer avant de quitter
        while (getchar() != '\n'); 
        return;
    }
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    // 2. DÉROULEMENT DU TEST
    for (int i = 0; i < monQuiz.nbTotalQuestions; i++) {
        int choixEleve;
        printf("\n------------------------------------------\n");
        printf("Question %d : %s\n", i + 1, monQuiz.listeQuestions[i].enonce);
        
        for (int j = 0; j < NB_CHOIX; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.listeQuestions[i].propositions[j]);
        }

        // --- BOUCLE DE SÉCURITÉ POUR LA SAISIE (Bloque le "6") ---
        do {
            printf("\nVotre réponse (1-4) : ");
            if (scanf("%d", &choixEleve) != 1) {
                printf("Saisie invalide ! Veuillez taper un chiffre.");
                while (getchar() != '\n'); // Nettoie le buffer en cas de lettres
                choixEleve = 0;
            }
            if (choixEleve < 1 || choixEleve > 4) {
                printf("Erreur : Choisissez un chiffre entre 1 et 4 uniquement.");
            }
        } while (choixEleve < 1 || choixEleve > 4);

        // --- VÉRIFICATION DE LA RÉPONSE ---
        if (monQuiz.listeQuestions[i].reponsesVraies[choixEleve - 1] == 1) {
            printf("Bravo ! C'est juste.\n");
            scoreFinal += 1;
        } else {
            printf("Dommage, c'est faux.\n");
            if (monQuiz.parametres.pointsNegatifs == 1) {
                scoreFinal -= 0.5;
                printf("(Point retiré : -0.5 appliqué)\n");
            }
        }
    }

    // 3. AFFICHAGE DE LA CORRECTION
    printf("\n==========================================\n");
    printf("      RECAPITULATIF DES BONNES REPONSES\n");
    printf("==========================================\n");
    for (int i = 0; i < monQuiz.nbTotalQuestions; i++) {
        printf("Q%d : %s\n", i + 1, monQuiz.listeQuestions[i].enonce);
        printf("   => La bonne réponse était : ");
        for (int j = 0; j < NB_CHOIX; j++) {
            if (monQuiz.listeQuestions[i].reponsesVraies[j] == 1) {
                printf("[%s]\n", monQuiz.listeQuestions[i].propositions[j]);
            }
        }
    }

    // 4. RÉSULTAT FINAL
    float noteSur20 = (scoreFinal / monQuiz.nbTotalQuestions) * 20;
    if (noteSur20 < 0) noteSur20 = 0;

    printf("\n--- RESULTAT FINAL ---\n");
    printf("Votre note : %.2f / 20\n", noteSur20);
    printf("----------------------\n\n");

    // Nettoyage final pour que le menu principal s'affiche correctement
    while (getchar() != '\n'); 
    printf("Appuyez sur Entrée pour revenir au menu...");
    getchar();
}