#ifndef Q1_H
#define Q1_H

/*---------------------------------------------------------------------------------------------------------------*/

/* ESTRUTURAS DE DADOS */

typedef struct disciplina {
    int cod_disciplina; /*Gerada pelo ano, pela cargah, periodo e 5 numeros aleatório
    no formato AAAACCPNNNNN*/
    char nomedisc[50];
    int cargah;
    int periodo;
    struct disciplina *esq, *dir;
} Disciplina;

typedef struct cursos {
    int idcurso; /* Gerada pela quantidade de períodos, periodo * 3, periodo * 5, ano, e 4 numeros aleatorios no
    formato PPPAAAANNNN, a quantidade de P pode variar de acordo com os múltiplos de 3 e 5 se forem de mais de um dígito*/
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
    int matricula; /* Gerada pela ano atual, 4 números aleatóris, pelo codcurso e por 3 nímeros aleatórios
    no formato AAAANNNNCNNN*/
    // C representa PPPAAAANNNN
    char nome[50];
    int codcurso;
    struct alunos *prox;
    Notas *nota;
    Matricula *mat;
} Alunos;

/*---------------------------------------------------------------------------------------------------------------*/

/* i. CURSO */

int cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos);
void exibir_cursos(Cursos *curso);

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */
void buscamat(Matricula *mat, int codigo, int *enc);
int cadmatricula(Alunos **aluno, int codigo, int mat);
void exibirmat(Matricula *mat);
void rmvmatricula(Matricula **mat, int cod, int *remove) ;

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */

void validarPeriodo(Cursos *curso,int *validar, int periodo);
void validarCargahoraria(int *validar, int cargahoraria);
void inseredisc(Disciplina **disc, Disciplina *No, int *insere);
int caddisc(Cursos **curso, Disciplina *No, int idcurso);
void exibirDiscCurso(Cursos *curso, int idcurso);
void exibirDiscPeriodo(Cursos *curso, int idcurso, int periodo);
void exibirDiscAluno(Alunos *aluno, Cursos *cursos, int matricula);
int rmvmatdealuno(Alunos **aluno, Matricula *mat, int matricula, int coddisc);
int rmvDiscCurso(Cursos **cursos, Alunos *alunos, int idcurso, int cod_disc);

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

void converternome(char *nome);
int cadaluno(Alunos **aluno, Cursos *curso, int mat, char *nome, int codcurso);
void alunosporcurso(Alunos *aluno, int codcurso);
void exibiralunos(Alunos *aluno);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

int cadnota(Alunos **aluno, int mat, int cod, int semestre, float notafinal);
void notasdiscperiodoaluno(Alunos *aluno, int periodo, int mat);
void notadiscporaluno(Alunos *aluno, Cursos *curso, int matricula, int coddisc);
void exibir_hist_aluno(Alunos *aluno, Cursos *curso, int mat_aluno);

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc);
void gerarIdCurso(int qntperiodos, int *idcurso);
void gerarMatriculaAluno(int idcurso, int *matricula);
void liberar_notas(Notas **nota);
void liberar_disciplinas(Disciplina **disc);
void liberar_cursos(Cursos **curso);
void liberar_alunos(Alunos **aluno);
void liberar_matriculas(Matricula **mat);

/*---------------------------------------------------------------------------------------------------------------*/
#endif