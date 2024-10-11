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

int cadcurso(AVLCurso **curso, Cursos *c);
void exibircurso(AVLCurso *curso);
void exibir_cursos(AVLCurso *curso);

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */

int cadmatricula(Alunos **aluno, AVLCurso *curso, int codigo, int mat);

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */


void exibir_disc_aluno_main(Alunos *aluno, AVLCurso *cursos, int matricula);
void exibir_disc_periodo_main(AVLCurso *curso, int idcurso, int periodo);
void exibir_disc_curso_main(AVLCurso *curso, int idcurso);

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

int cadaluno(Alunos **a, AVLCurso *cursos, int mat, char *nome, int codcurso);
void rmvmatdealuno(Alunos **a, AVLMatricula *m, int matricula, int coddisc);
void exibir_hist_aluno(Alunos *a, AVLCurso *c, int matricula);
void alunosporcurso(Alunos *a, int codcurso);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

int cadnota(Alunos **a, int mat, Notas *n);
void notadiscporaluno(Alunos *a, AVLCurso *c, int matricula, int coddisc);
void notasdiscperiodoaluno(Alunos *a, int periodo, int mat);

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc);
void gerarIdCurso(int qntperiodos, int *idcurso);
void gerarMatriculaAluno(int idcurso, int *matricula);

/*---------------------------------------------------------------------------------------------------------------*/
#endif