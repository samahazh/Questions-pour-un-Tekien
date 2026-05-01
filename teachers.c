#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Indispensable pour utiliser strcmp()
#include "qcm.h"
#include "teachers.h"

void launchTeacherMode() {
    // ==========================================
    // AJOUT : VÉRIFICATION DU MOT DE PASSE
    // ==========================================
    char motDePasseSaisi[50];
    const char vraiMotDePasse[] = "prof123"; // Le mot de passe à deviner

    printf("\n--- ACCES SECURISE ENSEIGNANT ---\n");
    printf("Mot de passe requis : ");
    
    fgets(motDePasseSaisi, sizeof(motDePasseSaisi), stdin);
    
    // On retire le '\n' (touche Entrée) aspiré par fgets, 
    // exactement comme ton camarade l'a fait plus bas dans son code !
    motDePasseSaisi[strcspn(motDePasseSaisi, "\n")] = 0;

    // Si la comparaison est différente de 0, ça veut dire que les mots de passe ne correspondent pas
    if (strcmp(motDePasseSaisi, vraiMotDePasse) != 0) {
        printf("\n[ALERTE] Mot de passe incorrect. Retour au menu principal...\n");
        return; // Le mot-clé "return" stoppe immédiatement la fonction et te renvoie au main !
    }
    // ==========================================

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
    while (getchar() != '\n')
    printf("Appuyez sur Entrée pour revenir au menu");
    getchar();
}
