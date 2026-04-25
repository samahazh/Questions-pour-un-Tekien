#ifndef QCM_H
#define QCM_H

typedef struct {
    int negative_points;
    int multiple_answers;
    int sequential_mode;
} Parameters; 

typedef struct {
    char statement[256];
    char options[4][256];
    int correct_answers[4];
    int num_options;
} Question;

typedef struct {
    char name[128];
    Parameters rules;
    Question questions[50];
    int num_questions;
}QCM;

#endif

