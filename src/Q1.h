#ifndef Q1_H
#define Q1_H

typedef struct disciplina {
    int cod_disciplina;
    char nomedisc[50];
    int cargah;
    int periodo;
    struct disciplina *esq, *dir;
} Disciplina;

typedef struct cursos {
    int idcurso;
    char nomecurso[50];
    int qntdperiodos;
    struct cursos *esq, *dir;
    Disciplina *disc;
} Cursos;

typedef struct notas {
    int coddisc;
    int semestre;
    float notafinal;
    struct notas *esq, *dir;
} Notas;

typedef struct matricula {
    int coddisc;
    struct matricula *esq, *dir;
} Matricula;

typedef struct alunos {
    int matricula;
    char nome[50];
    int codcurso;
    struct alunos *prox;
    Notas *nota;
    Matricula *mat;
} Alunos;

// ### CURSO ###
void cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos);
void exibircurso(Cursos *c);

#endif