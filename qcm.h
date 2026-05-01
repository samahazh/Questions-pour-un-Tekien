#ifndef QCM_H
#define QCM_H

// On définit des tailles fixes pour que ce soit facile à enregistrer
#define NB_QUESTIONS_MAX 50
#define NB_CHOIX 4
#define TAILLE_TEXTE 256

typedef struct {
    int pointsNegatifs;  // 1 pour Oui, 0 pour Non
    int modeForce;       // 1 si on doit obligatoirement répondre (séquentiel)
} Regles;

typedef struct {
    char enonce[TAILLE_TEXTE];           // La question posée
    char propositions[NB_CHOIX][TAILLE_TEXTE]; // Les 4 réponses possibles
    int reponsesVraies[NB_CHOIX];        // 1 si la réponse est juste, 0 sinon
} Question;

typedef struct {
    char titre[TAILLE_TEXTE];            // Nom du quiz
    Regles parametres;                   // Les options choisies par le prof
    Question listeQuestions[NB_QUESTIONS_MAX]; 
    int nbTotalQuestions;
} QCM;

#endif
