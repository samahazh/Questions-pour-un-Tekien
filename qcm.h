#ifndef QCM_H
#define QCM_H

#define MAX_QUESTIONS 50
#define MAX_OPTIONS 4
#define MAX_TEXT 256

typedef struct {
    int negative_points;  
    int multiple_answers;
    int sequential_mode;       
} Parameters;

typedef struct {
    char statement[MAX_TEXT];           
    char options[MAX_OPTIONS][MAX_TEXT]; 
    int correct_answers[MAX_OPTIONS];        
} Question;

typedef struct {
    char name[MAX_TEXT];            
    Parameters rules;                   
    Question questions[MAX_QUESTIONS]; 
    int num_questions;
} QCM;

#endif