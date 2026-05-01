#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qcm.h"
#include "teachers.h"

void launchTeacherMode() {
    QCM nouveauQCM;
    char nomFichier[100];

    printf("\n--- CONFIGURATION DU QCM ---\n");
    printf("Nom du fichier à créer (ex: quizz.bin) : ");
    scanf("%s", nomFichier);

    printf("Nombre de questions : ");
    scanf("%d", &nouveauQCM.nbTotalQuestions);

    printf("Activer les points négatifs ? (1=Oui, 0=Non) : ");
    scanf("%d", &nouveauQCM.parametres.pointsNegatifs);

    for (int i = 0; i < nouveauQCM.nbTotalQuestions; i++) {
        printf("\nQuestion %d :\n", i + 1);
        printf("  Énoncé : ");
        getchar(); // Consomme le retour ligne précédent
        fgets(nouveauQCM.listeQuestions[i].enonce, TAILLE_TEXTE, stdin);
        nouveauQCM.listeQuestions[i].enonce[strcspn(nouveauQCM.listeQuestions[i].enonce, "\n")] = 0;

        for (int j = 0; j < NB_CHOIX; j++) {
            printf("  Proposition %d : ", j + 1);
            fgets(nouveauQCM.listeQuestions[i].propositions[j], TAILLE_TEXTE, stdin);
            nouveauQCM.listeQuestions[i].propositions[j][strcspn(nouveauQCM.listeQuestions[i].propositions[j], "\n")] = 0;
            
            printf("  Est-elle vraie ? (1=Oui, 0=Non) : ");
            scanf("%d", &nouveauQCM.listeQuestions[i].reponsesVraies[j]);
            getchar(); // Consomme le retour ligne
        }
    }

    FILE *f = fopen(nomFichier, "wb");
    if (f != NULL) {
        fwrite(&nouveauQCM, sizeof(QCM), 1, f);
        fclose(f);
        printf("\n>> SUCCES : Le QCM a ete sauvegarde dans '%s' !\n\n", nomFichier);
    } else {
        printf("Erreur lors de la création du fichier.\n");
    }

    // NETTOYAGE DU BUFFER (pour le menu principal)
    while (getchar() != '\n');
}