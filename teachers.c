#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "teachers.h"

#define TEACHER_MDP "tekien2025"

void removeNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}

void createQCM();

void launchTeacherMode() {
    char input[TAILLE_TEXTE];

    printf("\n=== MODE ENSEIGNANT - AUTHENTIFICATION ===\n");
    printf("Veuillez entrer le mot de passe : ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        removeNewline(input);
        if (strcmp(input, TEACHER_MDP) == 0) {
            printf("\n>> Authentification reussie. Bienvenue.\n");
            createQCM();
        } else {
            printf("\n>> Mot de passe incorrect.\n");
        }
    }
}

void createQCM() {
    QCM nouveauQuiz; // On utilise la structure de qcm.h
    char nomFichier[TAILLE_TEXTE];
    char temp[TAILLE_TEXTE];

    printf("\n--- CREATION D'UN NOUVEAU QCM ---\n");

    printf("Titre du QCM : ");
    fgets(nouveauQuiz.titre, TAILLE_TEXTE, stdin);
    removeNewline(nouveauQuiz.titre);

    // Paramètres (on utilise les noms de qcm.h)
    printf("Points negatifs ? (1=Oui, 0=Non) : ");
    fgets(temp, sizeof(temp), stdin);
    nouveauQuiz.parametres.pointsNegatifs = atoi(temp);

    printf("Mode force (sequentiel) ? (1=Oui, 0=Non) : ");
    fgets(temp, sizeof(temp), stdin);
    nouveauQuiz.parametres.modeForce = atoi(temp);

    printf("Nombre de questions : ");
    fgets(temp, sizeof(temp), stdin);
    nouveauQuiz.nbTotalQuestions = atoi(temp);

    for (int i = 0; i < nouveauQuiz.nbTotalQuestions; i++) {
        printf("\n--- QUESTION %d ---\n", i + 1);
        printf("Enonce : ");
        fgets(nouveauQuiz.listeQuestions[i].enonce, TAILLE_TEXTE, stdin);
        removeNewline(nouveauQuiz.listeQuestions[i].enonce);

        for (int j = 0; j < NB_CHOIX; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQuiz.listeQuestions[i].propositions[j], TAILLE_TEXTE, stdin);
            removeNewline(nouveauQuiz.listeQuestions[i].propositions[j]);

            printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
            fgets(temp, sizeof(temp), stdin);
            nouveauQuiz.listeQuestions[i].reponsesVraies[j] = atoi(temp);
        }
    }

    // Sauvegarde BINAIRE pour être compatible avec student.c
    snprintf(nomFichier, sizeof(nomFichier), "%s.bin", nouveauQuiz.titre);
    FILE *fichier = fopen(nomFichier, "wb"); // wb = write binary
    if (fichier == NULL) {
        printf("Erreur de creation du fichier.\n");
        return;
    }

    fwrite(&nouveauQuiz, sizeof(QCM), 1, fichier);
    fclose(fichier);

    printf("\n>> SUCCES : Le QCM a ete sauvegarde dans '%s' !\n", nomFichier);
}
