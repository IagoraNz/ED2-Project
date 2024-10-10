#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "Q3.h"

/*---------------------------------------------------------------------------------------------------------------*/

/* inicio) Funções de balanceamento da árvore AVL */

/* AVL DISCIPLINA */

int fator(AVLDisc *raiz){
    return alturaDisc(raiz->esq) - alturaDisc(raiz->dir);
}

void balancearDisc(AVLDisc **raiz){
    int fb;
    AVLDisc *aux = (AVLDisc*)malloc(sizeof(AVLDisc));
    fb = fator(*raiz);

    if(fb >= 2){
        aux = (*raiz)->esq;
        fb = fator(aux);

        if(fator((*raiz)->esq) < 0)
            giroEsqDisc(&(*raiz)->esq);

        giroDirDisc(raiz);
    }
    else if(fb <= -2){
        aux = (*raiz)->dir;
        fb = fator(aux);

        if(fator((*raiz)->dir) > 0)
            giroDirDisc(&(*raiz)->dir);

        giroEsqDisc(raiz);
    }
}

int alturaDisc(AVLDisc *raiz){
    int altura = -1, esq, dir;

    if(raiz != NULL){
        esq = alturaDisc(raiz->esq);
        dir = alturaDisc(raiz->dir);
        if(esq > dir)
            altura = esq + 1;
        else
            altura = dir + 1;
    }
}

void giroEsqDisc(AVLDisc **raiz){
    AVLDisc *aux = (AVLDisc*)malloc(sizeof(AVLDisc));
    if(*raiz != NULL){
        aux = (*raiz)->dir;
        (*raiz)->dir = aux->esq;
        aux->esq = (*raiz);

        (*raiz)->altura = alturaDisc(*raiz);
        aux->altura = alturaDisc(aux);

        *raiz = aux;
    }
}

void giroDirDisc(AVLDisc **raiz){
    AVLDisc *aux = (AVLDisc*)malloc(sizeof(AVLDisc));
    if(*raiz != NULL){
        aux = (*raiz)->esq;
        (*raiz)->esq = aux->dir;
        aux->dir = (*raiz);

        (*raiz)->altura = alturaDisc(*raiz);
        aux->altura = alturaDisc(aux);

        *raiz = aux;
    }
}

/* AVL CURSOS */

int fator(AVLCurso *raiz){
    return alturaDisc(raiz->esq) - alturaDisc(raiz->dir);
}

void balancearCurso(AVLCurso **raiz){
    int fb;
    AVLCurso *aux = (AVLCurso*)malloc(sizeof(AVLDisc));
    fb = fator(*raiz);

    if(fb >= 2){
        aux = (*raiz)->esq;
        fb = fator(aux);

        if(fator((*raiz)->esq) < 0)
            giroEsqDisc(&(*raiz)->esq);

        giroDirDisc(raiz);
    }
    else if(fb <= -2){
        aux = (*raiz)->dir;
        fb = fator(aux);

        if(fator((*raiz)->dir) > 0)
            giroDirDisc(&(*raiz)->dir);

        giroEsqDisc(raiz);
    }
}

int alturaCurso(AVLCurso *raiz){
    int altura = -1, esq, dir;

    if(raiz != NULL){
        esq = alturaCurso(raiz->esq);
        dir = alturaCurso(raiz->dir);
        if(esq > dir)
            altura = esq + 1;
        else
            altura = dir + 1;
    }
}

void giroEsqCurso(AVLCurso **raiz){
    AVLDisc *aux = (AVLDisc*)malloc(sizeof(AVLDisc));
    if(*raiz != NULL){
        aux = (*raiz)->dir;
        (*raiz)->dir = aux->esq;
        aux->esq = (*raiz);

        (*raiz)->altura = alturaCurso(*raiz);
        aux->altura = alturaCurso(aux);

        *raiz = aux;
    }
}

void giroDirCurso(AVLCurso **raiz){
    AVLCurso *aux = (AVLCurso*)malloc(sizeof(AVLCurso));
    if(*raiz != NULL){
        aux = (*raiz)->esq;
        (*raiz)->esq = aux->dir;
        aux->dir = (*raiz);

        (*raiz)->altura = alturaCurso(*raiz);
        aux->altura = alturaCurso(aux);

        *raiz = aux;
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
já tenha sido cadastrado na árvore de cursos. */

void converternome(char *nome) {
    int i = 0;
    // Converte cada caractere para maiuscula enquanto não encontrar o caractere de terminação '\0'
    while (nome[i] != '\0') {
        nome[i] = toupper(nome[i]);
        i++;
    }
}

Alunos* criar_aluno(int mat, char *nome, int codcurso) {
    Alunos *novo = (Alunos*) malloc(sizeof(Alunos));
    novo->matricula = mat;
    char *aux_nome = strdup(nome);  
    converternome(aux_nome);       
    strcpy(novo->nome, aux_nome);
    novo->codcurso = codcurso;
    novo->nota = NULL;
    novo->mat = NULL;
    novo->prox = NULL;
    return novo;
}

void buscarCurso(AVLCurso *cursos, int mat, int *enc){
    if (cursos != NULL){
        if (cursos->info->idcurso == mat){
            *enc = 1;
        } else {
            buscarCurso(cursos->esq, mat, enc);
            buscarCurso(cursos->dir, mat, enc);
        }
    }
}

int cadaluno(Alunos **a, AVLCurso *cursos, int mat, char *nome, int codcurso) {
    int sucesso = 0, enc = 0;
    // Se a lista estiver vazia ou o ponto de inserção for alcançado
    if (*a == NULL) {
        buscarCurso(cursos, mat, &enc);
        if (enc == 1){
            *a = criar_aluno(mat, nome, codcurso);
            sucesso = 1;
        }
    }
    else {
        if ((*a)->matricula == mat)
            sucesso = 0; 
        // Verifica se o novo aluno deve ser inserido antes do aluno atual (ordenado por nome)
        else if (strcmp(nome, (*a)->nome) < 0) {
            Alunos *novo = criar_aluno(mat, nome, codcurso);  
            novo->prox = *a; 
            *a = novo;
            sucesso = 1;
        }
        else 
            sucesso = cadaluno(&(*a)->prox, cursos, mat, nome, codcurso);
    }
    
    return sucesso; 
}

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

/*---------------------------------------------------------------------------------------------------------------*/

/* iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90. */

/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */

void AlturaAVlMatricula(AVLMatricula **mat){
    int esq, dir;
    if(*mat != NULL){
        AlturaAVlMatricula(&(*mat)->esq);
        AlturaAVlMatricula(&(*mat)->dir);
        if(esq > dir)
            (*mat)->altura = esq + 1;
        else
            (*mat)->altura = dir + 1;
    }
}

int fbMatricula(AVLMatricula *mat){
    return mat->esq->altura - mat->dir->altura;
}

void rotacaoEsqMatricula(AVLMatricula **mat){
    AVLMatricula *aux = (AVLMatricula*)malloc(sizeof(AVLMatricula));
    if(*mat != NULL){
        aux = (*mat)->dir;
        (*mat)->dir = aux->esq;
        aux->esq = (*mat);
        AlturaAVlMatricula(mat);
        AlturaAVlMatricula(&aux);
        *mat = aux;
    }
}

void rotacaoDirMatricula(AVLMatricula **mat){
    AVLMatricula *aux = (AVLMatricula*)malloc(sizeof(AVLMatricula));
    if(*mat != NULL){
        aux = (*mat)->esq;
        (*mat)->esq = aux->dir;
        aux->dir = (*mat);
        AlturaAVlMatricula(mat);
        AlturaAVlMatricula(&aux);
        *mat = aux;
    }
}

void BalanceamentoAVLMatricula(AVLMatricula **mat){
    int fb;
    fb = fbMatricula(*mat);
    if (fb == -2){
        if (fbMatricula((*mat)->dir) > 0)
            rotacaoDirMatricula(&(*mat)->dir);
        rotacaoEsqMatricula(mat);
    } 
    else if (fb == 2){
        if (fbMatricula((*mat)->esq) < 0)
            rotacaoEsqMatricula(&(*mat)->esq);
        rotacaoDirMatricula(mat);
    }
}

void inserirMatricula(AVLMatricula **mat, int codigo, int *igual){
    if(*mat == NULL){
        Matricula *novo = (Matricula*)malloc(sizeof(Matricula));
        novo->coddisc = codigo;
        (*mat)->info = novo;
        (*mat)->altura = 0;
        (*mat)->esq = NULL;
        (*mat)->dir = NULL;
        *igual = 1;
    } 
    else {
        if(codigo < (*mat)->info->coddisc)
            inserirMatricula(&(*mat)->esq, codigo, igual);
        else{
            if(codigo > (*mat)->info->coddisc)
                inserirMatricula(&(*mat)->dir, codigo, igual);
            else
                *igual = 0;
            BalanceamentoAVLMatricula(mat);
            AlturaAVlMatricula(mat);
        }
    }
}

void buscarDisciplina(AVLDisc *disciplina, int cod_disc, int *encontrou) {
    if (disciplina != NULL) {
        if (disciplina->info->cod_disciplina == cod_disc) {
            *encontrou = 1;
        }
        else if (cod_disc < disciplina->info->cod_disciplina)
            buscarDisciplina(disciplina->esq, cod_disc, encontrou);
        else
            buscarDisciplina(disciplina->dir, cod_disc, encontrou);
    }
}

int cadmatricula(Alunos **aluno, AVLCurso *curso, int codigo, int mat){
    int sucesso = 0, enc = 0;
    if (*aluno != NULL){
        if ((*aluno)->matricula == mat){
            buscarDisciplina(curso->info->disc, codigo, &enc);
            if (enc == 1)
                inserirMatricula(&(*aluno)->mat, codigo, &sucesso);
        }
        else
            sucesso = cadmatricula(&(*aluno)->prox, curso, codigo, mat);
    }
    return sucesso;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas.*/

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

/*---------------------------------------------------------------------------------------------------------------*/

/* vii) Mostrar todos os cursos do Campus. */

/*---------------------------------------------------------------------------------------------------------------*/

/* viii) Mostrar todas as disciplinas de um determinado curso. */

/*---------------------------------------------------------------------------------------------------------------*/

// ix) Mostrar todas as disciplinas de um determinado período de um curso. 

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */

/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */

/*---------------------------------------------------------------------------------------------------------------*/

/* xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. */

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

/*---------------------------------------------------------------------------------------------------------------*/

/* extra) Função agregadas, associadas ou adicionais para complementar a coesão do software */