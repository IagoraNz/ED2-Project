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

int alturaDisc(AVLDisc *raiz){
    int res;
    if(raiz != NULL)
        res = 1 + (alturaDisc(raiz->esq) > alturaDisc(raiz->dir) ? alturaDisc(raiz->esq) : alturaDisc(raiz->dir));
    else
        res -1;
    return res;
}

int fatorDisc(AVLDisc *raiz){
    return alturaDisc(raiz->esq) - alturaDisc(raiz->dir);
}

void giroEsqDisc(AVLDisc **raiz){
    AVLDisc *aux;
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
    AVLDisc *aux;
    if(*raiz != NULL){
        aux = (*raiz)->esq;
        (*raiz)->esq = aux->dir;
        aux->dir = (*raiz);

        (*raiz)->altura = alturaDisc(*raiz);
        aux->altura = alturaDisc(aux);

        *raiz = aux;
    }
}

void balancearDisc(AVLDisc **raiz){
    int fb;
    AVLDisc *aux;
    fb = fatorDisc(*raiz);

    if(fb >= 2){
        aux = (*raiz)->esq;
        fb = fatorDisc(aux);

        if(fatorDisc((*raiz)->esq) < 0)
            giroEsqDisc(&(*raiz)->esq);

        giroDirDisc(raiz);
    }
    else if(fb <= -2){
        aux = (*raiz)->dir;
        fb = fatorDisc(aux);

        if(fatorDisc((*raiz)->dir) > 0)
            giroDirDisc(&(*raiz)->dir);

        giroEsqDisc(raiz);
    }
}

/* AVL CURSOS */

int alturaCurso(AVLCurso *raiz){
    int res = -1, altesq, altdir;

    if(raiz){
        altesq = alturaCurso(raiz->esq);
        altdir = alturaCurso(raiz->dir);
        res = 1 + (altesq > altdir ? altesq : altdir);
    }

    return res;
}

int fatorCurso(AVLCurso *raiz){
    return alturaCurso(raiz->esq) - alturaCurso(raiz->dir);
}

void giroEsqCurso(AVLCurso **raiz){
    AVLCurso *aux;
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
    AVLCurso *aux;
    if(*raiz != NULL){
        aux = (*raiz)->esq;
        (*raiz)->esq = aux->dir;
        aux->dir = (*raiz);

        (*raiz)->altura = alturaCurso(*raiz);
        aux->altura = alturaCurso(aux);

        *raiz = aux;
    }
}

void balancearCurso(AVLCurso **raiz){
    int fb;
    AVLCurso *aux;
    fb = fatorCurso(*raiz);

    if(fb >= 2){
        aux = (*raiz)->esq;
        fb = fatorCurso(aux);

        if(fatorCurso((*raiz)->esq) < 0)
            giroEsqCurso(&(*raiz)->esq);

        giroDirCurso(raiz);
    }
    else if(fb <= -2){
        aux = (*raiz)->dir;
        fb = fatorCurso(aux);

        if(fatorCurso((*raiz)->dir) > 0)
            giroDirCurso(&(*raiz)->dir);

        giroEsqCurso(raiz);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
já tenha sido cadastrado na árvore de cursos. */

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

int cadcurso(AVLCurso **curso, Cursos *c){
    int sucesso = 0;
    if(*curso == NULL){
        *curso = (AVLCurso*)malloc(sizeof(AVLCurso));
        (*curso)->info = c;
        (*curso)->esq = NULL;
        (*curso)->dir = NULL;
        (*curso)->altura = 0;
        sucesso = 1;    
    }
    else{
        if(c->idcurso < (*curso)->info->idcurso)
            sucesso = cadcurso(&((*curso)->esq), c);
        else 
            sucesso = cadcurso(&((*curso)->dir), c);
        balancearCurso(curso);
        (*curso)->altura = alturaCurso(*curso);
    }
    return sucesso;
}

void exibircurso(AVLCurso *curso){
    if(curso != NULL){
        exibircurso(curso->esq);
        printf("%d %s %d %d\n", curso->info->idcurso, curso->info->nomecurso, curso->info->qntdperiodos, curso->altura);
        exibircurso(curso->dir);
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