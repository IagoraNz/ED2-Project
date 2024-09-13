#pragma once

typedef struct cursos {
    int idcurso;
    char nomecurso[50];
    int qntdperiodos;
    struct cursos *esq;
    struct cursos *dir;
    Disciplina *disc;
} Cursos;

typedef struct disciplina {
    int cod_disciplina;
    char nomedisc[50];
    int cargah;
    int periodo;
    struct disciplina *esq;
    struct disciplina *dir;
} Disciplina;

typedef struct notas {
    int coddisc;
    int semestre;
    int notafinal;
    struct notas *esq;
    struct notas *dir;
} Notas;

typedef struct matricula {
    int coddisc;
    struct matricula *esq;
    struct matricula *dir;
} Matricula;

typedef struct alunos {
    int matricula;
    char nome[50];
    int codcurso;
    struct alunos *prox;
    Notas *nota;
    Matricula *mat;
} Alunos;