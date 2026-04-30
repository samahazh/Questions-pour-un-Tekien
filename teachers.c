#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teachers.h"
#define TEACHER_MDP "tekien2025"
#define TAILLE_MAX 256
void createQCM();
void removeNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}
void launchTeacherMode() {
    char input[TAILLE_MAX];

    printf("\n=== MODE ENSEIGNANT - AUTHENTIFICATION ===\n");
    printf("Veuillez entrer le mot de passe : ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        removeNewline(input);
        if (strcmp(input, TEACHER_MDP) == 0) {
            printf("\n>> Authentification reussie. Bienvenue.\n");
            createQCM();
            
        } else {
            printf("\n>> Mot de passe incorrect. Retour au menu principal.\n");
        }
    }
}
void createQCM() {
    char nomqcm[TAILLE_MAX];
    char nomfichier[TAILLE_MAX];
    char input[TAILLE_MAX];
    
    int negPoints = 0;
    int multreponses = 0;
    int seqMode = 0;
    int numQuestions = 0;

    printf("\n--- CREATION D'UN NOUVEAU QCM ---\n");

    printf("Nom du QCM (ATTENTION: evitez les espaces et caracteres speciaux) : ");
    fgets(nomqcm, sizeof(nomqcm), stdin);
    removeNewline(nomqcm);

    snprintf(nomfichier, sizeof(nomfichier), "%s.txt", nomqcm);

    printf("\n--- PARAMETRES DU QCM ---\n");

    printf("1. Activer les points negatifs pour les mauvaises reponses ? (1 = Oui, 0 = Non) : ");
    fgets(input, sizeof(input), stdin);
    negPoints = atoi(input);

    printf("2. Autoriser plusieurs reponses vraies par question ? (1 = Oui, 0 = Non) : ");
    fgets(input, sizeof(input), stdin);
    multAnswers = atoi(input);

    printf("3. Mode sequentiel (impossible de passer une question) ? (1 = Oui, 0 = Non) : ");
    fgets(input, sizeof(input), stdin);
    seqMode = atoi(input);

    printf("4. Combien de questions ce QCM contiendra-t-il ? : ");
    fgets(input, sizeof(input), stdin);
    numQuestions = atoi(input);

    FILE *fichier = fopen(nomfichier, "w");
    if (fichier == NULL) {
        printf("\n>> Erreur critique : Impossible de creer le fichier %s.\n", nomfichier);
        return; 
    }

    fprintf(fichier, "NOM_QCM:%s\n", qcmName);
    fprintf(fichier, "PARAM_NEG_POINTS:%d\n", negPoints);
    fprintf(fichier, "PARAM_MULT_REPONSES:%d\n", multreponses);
    fprintf(fichier, "PARAM_SEQ_MODE:%d\n", seqMode);
    fprintf(fichier, "TOTAL_QUESTIONS:%d\n", numQuestions);

    for (int i = 0; i < numQuestions; i++) {
        char questionText[TAILLE_MAX];
        int numChoix = 0;

        printf("\n--- REDACTION DE LA QUESTION %d ---\n", i + 1);
        printf("Intitule de la question : ");
        fgets(questionText, sizeof(questionText), stdin);
        removeNewline(questionText);

    fprintf(file, "\nQUESTION:%s\n", questionText);

    printf("Combien de propositions (choix) pour cette question ? : ");
    fgets(input, sizeof(input), stdin);
    numChoix = atoi(input);
    fprintf(file, "TOTAL_CHOIX:%d\n", numChoix);
      
    for (int j = 0; j < numChoix; j++) {
            char choixText[TAILLE_MAX];
            int Correct = 0;

            printf("  > Proposition %d : ", j + 1);
            fgets(choixText, sizeof(choixText), stdin);
            removeNewline(choixText);

            printf("  > Cette proposition est-elle VRAIE ? (1 = Oui, 0 = Non) : ");
            fgets(input, sizeof(input), stdin);
            Correct = atoi(input);

            fprintf(file, "CHOIX:%d:%s\n", Correct, choixText);
        }
    }

  
    fclose(file);
    printf("\n>> SUCCES : Le QCM '%s' a ete sauvegarde avec succes dans le fichier '%s' !\n", qcmName, filename);
    }
