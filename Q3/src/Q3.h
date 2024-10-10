#ifndef Q3_H
#define Q3_H

/*---------------------------------------------------------------------------------------------------------------*/

/* ESTRUTURAS DE DADOS */

typedef struct disciplina {
    int cod_disciplina;
    char nomedisc[50];
    int cargah;
    int periodo;
} Disciplina;

typedef struct avldisc {
    Disciplina *info;
    int altura;
    struct avldisc *esq, *dir;
} AVLDisc;

typedef struct cursos {
    int idcurso;
    char nomecurso[50];
    int qntdperiodos;
    Disciplina *disc;
} Cursos;

typedef struct avlcurso {
    Cursos *info;
    int altura;
    struct avlcurso *esq, *dir;
} AVLCurso;

typedef struct notas {
    int coddisc;
    int semestre;
    float notafinal;
} Notas;

typedef struct avlnotas {
    Notas *info;
    int altura;
    struct avlnotas *esq, *dir;
} AVLNotas;

typedef struct matricula {
    int coddisc;
} Matricula;

typedef struct avlmatricula {
    Matricula *info;
    int altura;
    struct avlmatricula *esq, *dir;
} AVLMatricula;

typedef struct alunos {
    int matricula;
    char nome[50];
    int codcurso;
    struct alunos *prox;
    AVLNotas *nota;
    AVLMatricula *mat;
} Alunos;

/*---------------------------------------------------------------------------------------------------------------*/

/* i. CURSO */

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */

int cadmatricula(Alunos **aluno, AVLCurso *curso, int codigo, int mat);

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

int cadaluno(Alunos **a, AVLCurso *cursos, int mat, char *nome, int codcurso);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc);
void gerarIdCurso(int qntperiodos, int *idcurso);
void gerarMatriculaAluno(int idcurso, int *matricula);

/*---------------------------------------------------------------------------------------------------------------*/
#endif