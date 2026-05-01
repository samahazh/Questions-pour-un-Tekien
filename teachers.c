#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "teachers.h"

void launchTeacherMode() {
    char motDePasseSaisi[50];
    const char vraiMotDePasse[] = "prof123";
    
    // Notre "panier" magique pour sécuriser toutes les saisies de chiffres
    char bufferSaisie[MAX_TEXT]; 

    printf("\n==========================================\n");
    printf("             MODE ENSEIGNANT\n");
    printf("==========================================\n");
    printf("Mot de passe requis : ");
    
    fgets(motDePasseSaisi, sizeof(motDePasseSaisi), stdin);
    motDePasseSaisi[strcspn(motDePasseSaisi, "\n")] = 0;

    if (strcmp(motDePasseSaisi, vraiMotDePasse) != 0) {
        printf("\n[ALERTE] Mot de passe incorrect. Retour au menu principal...\n");
        return; 
    }

    QCM nouveauQCM;
    char nomFichier[100];

    printf("\n------------------------------------------\n");
    printf("           CONFIGURATION DU QCM\n");
    printf("------------------------------------------\n");
    
    printf("Nom du fichier a creer (ex: quizz.bin) : ");
    fgets(nomFichier, sizeof(nomFichier), stdin);
    nomFichier[strcspn(nomFichier, "\n")] = 0; // On retire le '\n'

    printf("Nombre de questions : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.num_questions = atoi(bufferSaisie);

    printf("Activer les points negatifs ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.negative_points = atoi(bufferSaisie);

    printf("Activer les reponses multiples ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.multiple_answers = atoi(bufferSaisie);

    printf("Activer le mode sequentiel ? (1=Oui, 0=Non) : ");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
    nouveauQCM.rules.sequential_mode = atoi(bufferSaisie);

    for (int i = 0; i < nouveauQCM.num_questions; i++) {
        printf("\nQuestion %d :\n", i + 1);
        printf("  Enonce : ");
        fgets(nouveauQCM.questions[i].statement, MAX_TEXT, stdin);
        nouveauQCM.questions[i].statement[strcspn(nouveauQCM.questions[i].statement, "\n")] = 0;

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQCM.questions[i].options[j], MAX_TEXT, stdin);
            nouveauQCM.questions[i].options[j][strcspn(nouveauQCM.questions[i].options[j], "\n")] = 0;
            
            printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
            fgets(bufferSaisie, sizeof(bufferSaisie), stdin);
            nouveauQCM.questions[i].correct_answers[j] = atoi(bufferSaisie);
        }
    }

    FILE *f = fopen(nomFichier, "wb");
    if (f != NULL) {
        fwrite(&nouveauQCM, sizeof(QCM), 1, f);
        fclose(f);
        printf("\n>> SUCCES : Le QCM a ete sauvegarde dans '%s' !\n\n", nomFichier);
    } else {
        printf("Erreur lors de la creation du fichier.\n");
    }

    printf("Appuyez sur Entree pour revenir au menu");
    fgets(bufferSaisie, sizeof(bufferSaisie), stdin); // Fait une pause propre sans bug
<<<<<<< HEAD
}
=======
}
>>>>>>> bb211f7200a805430c57fcd4d6e4babc10eca7c1
