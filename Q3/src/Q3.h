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
    AVLDisc *disc;
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

int cadcurso(AVLCurso **curso, Cursos *no);
void exibircurso(AVLCurso *curso);
void exibir_cursos(AVLCurso *curso);
void exibirAlturaCurso(AVLCurso *curso);
AVLCurso* buscar_curso(AVLCurso *curso, int idcurso);
int rmvdisc_curso(AVLCurso **cursos, Alunos *alunos, int idcurso, int cod_disc);

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */

int cadmatricula(Alunos **aluno, AVLCurso *curso, int codigo, int mat);
void exibirAlturaMatriculaMain(Alunos *aluno, int matricula);

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */

int insere_disc(AVLDisc **disc, Disciplina *no);
int caddisc(AVLCurso **curso, Disciplina *no, int idcurso);
void exibir_disc_aluno_main(Alunos *aluno, AVLCurso *cursos, int matricula);
void exibir_disc_periodo_main(AVLCurso *curso, int idcurso, int periodo);
void exibir_disc_curso_main(AVLCurso *curso, int idcurso);
void exibirAlturaDisciplinaMain(AVLCurso *curso, int idcurso);
AVLDisc* buscar_disciplina(AVLDisc *disc, int cod_disc);

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

int cadaluno(Alunos **aluno, AVLCurso *cursos, int mat, char *nome, int codcurso);
void rmvmatdealuno(Alunos **aluno, int matricula, int coddisc);
void exibir_hist_aluno(Alunos *aluno, AVLCurso *curso, int matricula);
void alunosporcurso(Alunos *aluno, int codcurso);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

int cadnota(Alunos **aluno, int mat, Notas *no);
void notadiscporaluno(Alunos *aluno, AVLCurso *curso, int matricula, int coddisc);
void notasdiscperiodoaluno(Alunos *aluno, int periodo, int mat);
void exibirAlturaNotasMain(Alunos *aluno, int matricula);
AVLNotas* buscar_nota(AVLNotas *nota, int cod_disc);

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc);
void gerarIdCurso(int qntperiodos, int *idcurso);
void gerarMatriculaAluno(int idcurso, int *matricula);
void liberarAVLDisc(AVLDisc **raiz);
void liberarAVLCurso(AVLCurso **raiz);
void liberarAVLNotas(AVLNotas **raiz);
void liberarAVLMatricula(AVLMatricula **raiz);
void liberarAlunos(Alunos **aluno);

/*---------------------------------------------------------------------------------------------------------------*/
#endif