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
void exibircurso(Cursos *c);
int buscacurso(Cursos *curso, int idcurso);
void exibir_cursos(Cursos *curso);

/*---------------------------------------------------------------------------------------------------------------*/

/* ii. MATRÍCULA */
void buscamat(Matricula *m, int codigo, int *enc);
int cadmatricula(Alunos **a, int codigo, int mat);
void exibirmat(Matricula *m);
void rmvmatricula(Matricula **m, int cod, int *remove) ;

/*---------------------------------------------------------------------------------------------------------------*/

/* iii. DISCIPLINA */

void validar_periodo(Cursos *curso,int *validar, int periodo);
void validar_cargahoraria(int *validar, int cargahoraria);
void insere_disc(Disciplina **disc, Disciplina *No, int *insere);
int caddisc(Cursos **curso, Disciplina *No, int idcurso);
void exibir_disc_curso(Disciplina *disc);
void exibir_disc_periodo(Disciplina *disc, int periodo);
void exibir_disc_curso_main(Cursos *curso, int idcurso);
void exibir_disc_periodo_main(Cursos *curso, int idcurso, int periodo);
void exibir_disc_aluno_main(Alunos *aluno, Cursos *cursos, int matricula);
int rmvmatdealuno(Alunos **a, Matricula *m, int matricula, int coddisc);
int rmvdisc_curso(Cursos **cursos, Alunos *alunos, int idcurso, int cod_disc);

/*---------------------------------------------------------------------------------------------------------------*/

/* iv. ALUNO */

void converternome(char *nome);
int cadaluno(Alunos **a, Cursos *curso, int mat, char *nome, int codcurso);
void alunosporcurso(Alunos *a, int codcurso);
void exibiralunos(Alunos *a);

/*---------------------------------------------------------------------------------------------------------------*/

/* v. NOTA */

int cadnota(Alunos **a, int mat, int cod, int semestre, float notafinal);
void notasdiscperiodoaluno(Alunos *a, int periodo, int mat);
void notadiscporaluno(Alunos *a, Cursos *c, int matricula, int coddisc);
void exibir_hist_aluno(Alunos *aluno, Cursos *curso, int mat_aluno);

/*---------------------------------------------------------------------------------------------------------------*/

/* vi. EXTRAS */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc);
void gerarIdCurso(int qntperiodos, int *idcurso);
void gerarMatriculaAluno(int idcurso, int *matricula);
void liberar_notas(Notas *n);
void liberar_disciplinas(Disciplina *d);
void liberar_cursos(Cursos **c);
void liberar_alunos(Alunos *a);
void liberar_matriculas(Matricula *m);

/*---------------------------------------------------------------------------------------------------------------*/
#endif