#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Q1.h"

/*---------------------------------------------------------------------------------------------------------------*/

/*i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
já tenha sido cadastrado na árvore de cursos. */

void converternome(char *nome) {
    int i = 0;
    // Converte cada caractere para maiuscula enquanto não encontrar o caractere de terminação '\0'
    while (nome[i] != '\0') {
        nome[i] = toupper(nome[i]);
        i++;
    }
}

void cadaluno(Alunos **a, int mat, char *nome, int codcurso) {
    Alunos *novo = (Alunos*) malloc(sizeof(Alunos));
    novo->prox = NULL;
    novo->matricula = mat;
    char *aux_nome = strdup(nome);
    converternome(aux_nome);
    strcpy(novo->nome, aux_nome);
    novo->codcurso = codcurso;
    novo->nota = NULL;
    novo->mat = NULL;

    // Se a lista estiver vazia, insere o primeiro aluno
    if (*a == NULL) {
        *a = novo;
    }
    else {
        // Verifica se o novo nome deve ser inserido na primeira posição
        if (strcmp(aux_nome, (*a)->nome) < 0) {
            novo->prox = *a;
            *a = novo;
        }
        else {
            Alunos *aux = *a;
            // Percorre a lista e encontra a posição correta
            while (aux->prox != NULL && strcmp(aux_nome, aux->prox->nome) > 0) {
                aux = aux->prox;
            }
            // Insere o novo aluno na posição correta
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

// Função para verificar se um idcurso ja está em uso ou para procurar algum curso.
void buscacurso(Cursos *curso, int idcurso, int *enc){
    if(curso == NULL)
        *enc = 0;
    else{
        if(curso->idcurso == idcurso)
            *enc = 1;
        else{
            if(idcurso < curso->idcurso)
                buscacurso(curso->esq, idcurso, enc);
            else
                buscacurso(curso->dir, idcurso, enc);
        }
    }
}

void cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos){
    if(*curso == NULL){
        Cursos *novo = (Cursos*)malloc(sizeof(Cursos));
        novo->idcurso = idcurso;
        strcpy(novo->nomecurso, nomecurso);
        novo->qntdperiodos = qntperiodos;
        novo->disc = NULL;
        novo->dir = NULL;
        novo->esq = NULL;
        *curso = novo;
    }
    else{
        if(idcurso < (*curso)->idcurso)
            cadcurso(&((*curso)->esq), idcurso, nomecurso, qntperiodos);
        else
            cadcurso(&((*curso)->dir), idcurso, nomecurso, qntperiodos);
    }
}

void exibircurso(Cursos *c){
    printf("CURSOS CADASTRADOS\n");
    if(c != NULL){
        exibircurso(c->esq);
        printf("%d %s %d\n", c->idcurso, c->nomecurso, c->qntdperiodos);
        exibircurso(c->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90. */

/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */

void cadmatricula(Matricula **m, int codigo){
    if(*m == NULL){
        Matricula *novo = (Matricula*)malloc(sizeof(Matricula));
        novo->coddisc = codigo;
        novo->esq = NULL;
        novo->dir = NULL;
        *m = novo;
    }
    else{
        if(codigo < (*m)->coddisc)
            cadmatricula(&((*m)->esq), codigo);
        else
            cadmatricula(&((*m)->dir), codigo);
    }
}

void buscamat(Matricula *m, int codigo, int *enc){
    if(m == NULL)
        *enc = 0;
    else{
        if(m->coddisc == codigo)
            *enc = 1;
        else{
            if(codigo < m->coddisc)
                buscamat(m->esq, codigo, enc);
            else
                buscamat(m->dir, codigo, enc);
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas.*/

// Essa buscamat vai mudar de lugar, para o main quando este for criado. Isto para otimizar
void cadnota(Matricula **m, Notas **n, int cod, int semestre, int notafinal){
    int enc;
    // buscamat(&m, cod, &enc);
    
    if(enc == 1){
        if(*n == NULL){
            Notas *novo = (Notas*)malloc(sizeof(Notas));
            novo->coddisc = cod;
            novo->semestre = semestre;
            novo->notafinal = notafinal;
            novo->esq = NULL;
            novo->dir = NULL;
            *n = novo;
            rmvmatricula(m, cod);
        }
        else{
            if(cod < (*n)->coddisc)
                cadnota(m, &((*n)->esq), cod, semestre, notafinal);
            else
                cadnota(m, &((*n)->dir), cod, semestre, notafinal);
        }
    }
}

Matricula* menorDireita(Matricula *no, Matricula **filho){
    Matricula *aux;
    aux = NULL;

    if(no != NULL){
        aux = menorDireita(no->esq, filho);
        if(!aux){
            aux = no;
            *filho = no->dir;
        }
    }
    return aux;
}

void rmvmatricula(Matricula **m, int cod){
    int temp;

    if((*m)){
        if(cod < (*m)->coddisc)
            rmvmatricula(&(*m)->esq, cod);
        else if(cod > (*m)->coddisc)
            rmvmatricula(&(*m)->dir, cod);
        else{
            Matricula *aux = *m;
            if((*m)->esq == NULL && (*m)->dir == NULL){
                free(aux);
                *m = NULL;
            }
            /* Só tem o filho da direita */
            else if((*m)->esq == NULL){
                (*m) = (*m)->dir;
                aux->dir = NULL;
                free(aux);
                aux = NULL;
            }
            /* Só tem o filho da esquerda */
            else if((*m)->dir == NULL){
                (*m) = (*m)->esq;
                aux->esq = NULL;
                free(aux);
                aux = NULL;
            }
            /* O nó mais a direita da sub-árvore à esquerda */
            else{
                Matricula *filho;
                aux = menorDireita((*m)->dir, &filho);
                aux->esq = (*m)->esq;
                aux->dir = (*m)->dir;
                (*m)->esq = (*m)->dir = NULL;
                free(*m);
                *m = aux;
                aux = NULL;
            }
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

// Essa buscacurso vai mudar de lugar, para o main quando este for criado. Isto para otimizar
void alunosporcurso(Alunos **a, Cursos **c, int codcurso){
    int enc;
    // buscacurso(c, codcurso, &enc);

    if(enc == 1){
        while((*a) != NULL && (*a)->codcurso == codcurso){
            printf("%s\n", (*a)->nome);
            *a = (*a)->prox;
        }
    }
    else
        printf("Curso nao encontrado!\n");
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vii) Mostrar todos os cursos do Campus. */ 
void exibir_cursos(Cursos *curso) {
    if (curso != NULL) {
        printf("ID: %d\n", curso->idcurso);
        printf("Nome: %s\n", curso->nomecurso);
        printf("Quantidade de períodos: %d\n", curso->qntdperiodos);
        printf("\n");
        exibir_cursos(curso->esq);
        exibir_cursos(curso->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* viii) Mostrar todas as disciplinas de um determinado curso. */
void exibir_disc_curso(Cursos *curso, int idcurso) {
    if (curso != NULL) {
        if (curso->idcurso == idcurso) {
            Disciplina *disc = curso->disc;
            while (disc != NULL) {
                printf("Código: %d\n", disc->cod_disciplina);
                printf("Nome: %s\n", disc->nomedisc);
                printf("Carga horária: %d\n", disc->cargah);
                printf("Período: %d\n", disc->periodo);
                printf("\n");
                disc = disc->dir;
            }
        }
        else if (idcurso < curso->idcurso) {
            exibir_disc_curso(curso->esq, idcurso);
        }
        else {
            exibir_disc_curso(curso->dir, idcurso);
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// ix) Mostrar todas as disciplinas de um determinado período de um curso. 
void exibir_disc_periodo(Cursos *curso, int idcurso, int periodo){
    if(curso != NULL){
        if(curso->idcurso == idcurso){
            Disciplina *disc = curso->disc;
            while(disc != NULL){
                if(disc->periodo == periodo){
                    printf("Código: %d\n", disc->cod_disciplina);
                    printf("Nome: %s\n", disc->nomedisc);
                    printf("Carga horária: %d\n", disc->cargah);
                    printf("Período: %d\n", disc->periodo);
                    printf("\n");
                }
                disc = disc->dir; // Add this line to avoid infinite loop
            }
        }
        else if(idcurso < curso->idcurso){
            exibir_disc_periodo(curso->esq, idcurso, periodo);
        }
        else{
            exibir_disc_periodo(curso->dir, idcurso, periodo);
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

void notasdiscperiodoaluno(Alunos *a, int periodo, int mat){
    if(a == NULL){
        printf("Nao existe alunos cadastrados\n");
    }
    else{
        if(a->nota != NULL){
            if(a->nota->semestre == periodo){
                // printf("EXIBINDO NOTAS DO SEMESTRE %d\n", a->nota->semestre);
                // printf("%d %.2f", a->nota->coddisc, a->nota->notafinal);
                // notasdiscperiodoaluno((*a)->nota->esq, periodo, mat);
                // notasdiscperiodoaluno((*a)->nota->dir, periodo, mat);
            }
        }
        else
            printf("Nota nao encontrada\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */
void notadiscporaluno(Alunos *a, int matricula, int coddisc){
    if(a != NULL){
        while(a != NULL){
            if(a->matricula == matricula){
                while(a->nota != NULL){
                    if(a->nota->coddisc == coddisc){
                        printf("Aluno: %s\nDisciplina: %d\nNota Final: %.2f\nSemestre: %d\n", a->nome, coddisc, a->nota->notafinal, a->nota->semestre);
                    }
                    if(coddisc < a->nota->coddisc){
                        a->nota = a->nota->esq;
                    } 
                    else{
                        a->nota = a->nota->dir;
                    }
                }
            }
            a = a->prox;
        }
    }
    else{
        printf("Nao ha alunos cadastrados.\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */

/*---------------------------------------------------------------------------------------------------------------*/

/* xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. */
void rmvmatdealuno(Alunos **a, Matricula *m, int matricula, int coddisc){
    int enc = 0;
    if((*a) != NULL){
        while((*a) != NULL && (*a)->matricula == matricula){
            printf("Aluno %s\n", (*a)->nome);
            *a = (*a)->prox;
        }
    }

    buscamat((*a)->mat, coddisc, &enc);

    if(enc == 1){
        rmvmatricula(&(*a)->mat, coddisc);
    }
    else{
        printf("Matricula nao encontrada para o aluno %s\n", (*a)->nome);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

/*---------------------------------------------------------------------------------------------------------------*/