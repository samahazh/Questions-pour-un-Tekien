void launchStudentMode() {
    QCM monQuiz;
    char nomFichier[100];
    float scoreFinal = 0;

    printf("\n--- BIENVENUE AU TEST ---\n");
    printf("Nom du fichier QCM à ouvrir (ex: test.bin) : ");
    scanf("%s", nomFichier);

    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("Erreur : Impossible de trouver le fichier %s\n", nomFichier);
        return;
    }
    fread(&monQuiz, sizeof(QCM), 1, f);
    fclose(f);

    // --- DEROULEMENT DU TEST ---
    for (int i = 0; i < monQuiz.nbTotalQuestions; i++) {
        int choixEleve;
        printf("\nQuestion %d : %s\n", i + 1, monQuiz.listeQuestions[i].enonce);
        
        for (int j = 0; j < NB_CHOIX; j++) {
            printf("  %d) %s\n", j + 1, monQuiz.listeQuestions[i].propositions[j]);
        }

        printf("Votre réponse (1-4) : ");
        scanf("%d", &choixEleve);

        if (monQuiz.listeQuestions[i].reponsesVraies[choixEleve - 1] == 1) {
            printf("Bravo ! C'est juste.\n");
            scoreFinal += 1;
        } else {
            printf("Dommage, c'est faux.\n");
            if (monQuiz.parametres.pointsNegatifs == 1) {
                scoreFinal -= 0.5;
                printf("(Pénalité de -0.5 appliquée)\n");
            }
        }
    }

    // --- AFFICHAGE DE LA CORRECTION ---
    printf("\n--- RECAPITULATIF DES BONNES REPONSES ---\n");
    for (int i = 0; i < monQuiz.nbTotalQuestions; i++) {
        printf("Q%d : %s\n", i + 1, monQuiz.listeQuestions[i].enonce);
        printf("   => La bonne réponse était : ");
        
        for (int j = 0; j < NB_CHOIX; j++) {
            if (monQuiz.listeQuestions[i].reponsesVraies[j] == 1) {
                printf("%s\n", monQuiz.listeQuestions[i].propositions[j]);
            }
        }
    }

    // --- RESULTAT FINAL ---
    float noteSur20 = (scoreFinal / monQuiz.nbTotalQuestions) * 20;
    if (noteSur20 < 0) noteSur20 = 0;

    printf("\n--- RESULTAT ---\n");
    printf("Votre note finale : %.2f / 20\n", noteSur20);
    printf("--------------------------------\n\n");
}
}
