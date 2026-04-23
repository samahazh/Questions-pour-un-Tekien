#ifndef QCM_H
#define QCM_H

typedef struct {
    int points_negatifs;
    int reponses_multiples;
    int mode_sequentiel;
} Parametres; 

typedef struct {
    char enonce[256];
    char propositions[4][256];
    int reponses_correctes[4];
    int nb_propositions;
} Question;

typedef struct {
    char nom[128];
    Parametres regles;
    Question questions[50];
    int nb_questions;
}QCM;

#endif

