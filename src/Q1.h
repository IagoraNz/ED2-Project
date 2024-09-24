#ifndef Q1_H
#define Q1_H

/*---------------------------------------------------------------------------------------------------------------*/

/* ESTRUTURAS DE DADOS */

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

/*---------------------------------------------------------------------------------------------------------------*/

/* i. CURSO */

void cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos);
void exibircurso(Cursos *c);
void buscacurso(Cursos *curso, int idcurso, int *enc);
void exibir_cursos(Cursos *curso);

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */

Matricula* menorDireita(Matricula *no, Matricula **filho);
void buscamat(Matricula *m, int codigo, int *enc);
void cadmatricula(Matricula **m, int coddisc);
void exibirmat(Matricula *m);
void rmvmatricula(Matricula **m, int cod);

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */

void exibir_disc_curso(Cursos *curso, int idcurso);
void exibir_disc_periodo(Cursos *curso, int idcurso, int periodo);
void rmvmatdealuno(Alunos **a, Matricula *m, int matricula, int coddisc);

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

void converternome(char *nome);
void cadaluno(Alunos **a, int mat, char *nome, int codcurso);
void alunosporcurso(Alunos **a, Cursos **c, int codcurso);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

void cadnota(Matricula **m, Notas **n, int cod, int semestre, int notafinal);
void notasdiscperiodoaluno(Alunos *a, int periodo, int mat);
void notadiscporaluno(Alunos *a, int matricula, int coddisc);

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

/*---------------------------------------------------------------------------------------------------------------*/
#endif