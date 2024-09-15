#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q1.h"

// Função para verificar se um idcurso ja está em uso ou para procurar algum curso.
void buscaCurso(Cursos *curso, int idcurso, int *enc){
    if(curso == NULL)
        *enc = 0;
    else{
        if(curso->idcurso == idcurso)
            *enc = 1;
        else{
            if(idcurso < curso->idcurso)
                buscamat(&(curso->esq), idcurso, enc);
            else
                buscamat(&(curso->dir), idcurso, enc);
        }
    }
}

void cadcurso(Cursos **curso, int idcurso, const char nomecurso, int qntperiodos){
    if(*curso == NULL){
        (*curso)->idcurso = idcurso;
        strcpy((*curso)->nomecurso, nomecurso);
        (*curso)->qntdperiodos = qntperiodos;
        (*curso)->disc = NULL; // Inicializando Arvore Binaria de Disciplinas como Nulo.
        // Orientação da arvore binario
        (*curso)->dir = NULL;
        (*curso)->esq = NULL;
    }
    else{
        if(idcurso < (*curso)->idcurso)
            cadmatricula(&((*curso)->esq), idcurso);
        else
            cadmatricula(&((*curso)->dir), idcurso);
    }
}

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
                buscamat(&(m->esq), codigo, enc);
            else
                buscamat(&(m->dir), codigo, enc);
        }
    }
}

Matricula* menor(Matricula *m){
    Matricula *atual = m;
    while(atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

void rmvmatricula(Matricula **m, int cod){
    int temp;
    // Primeiro caso: árvore vazia
    if(*m == NULL)
        return;

    // Segundo caso: código menor que o nó
    if(cod < (*m)->coddisc)
        rmvmatricula(&((*m)->esq), cod);
    // Terceiro caso: código maior que o nó
    else if(cod > (*m)->coddisc)
        rmvmatricula(&((*m)->dir), cod);
    // Quarto caso: código igual
    else{
        // 4.1: nó folha
        if((*m)->esq == NULL && (*m)->dir == NULL){
            free((*m));
            (*m) = NULL;
        }
        // 4.2 nó com 1 filho
        else if((*m)->esq == NULL){
            Matricula *aux = (*m)->dir;
            free((*m));
            (*m) = aux;
        }
        else if((*m)->dir == NULL){
            Matricula *aux = (*m)->esq;
            free((*m));
            (*m) = aux;
        }
        // 4.3 nó com 2 filhos
        else{
            Matricula *aux = menor((*m)->dir);
            (*m)->coddisc = aux->coddisc;
            rmvmatricula(&((*m)->dir), aux->coddisc);
        }
    }
}

// Essa buscamat vai mudar de lugar, para o main quando este for criado. Isto para otimizar
void cadnota(Matricula **m, Notas **n, int cod, int semestre, int notafinal){
    int enc;
    buscamat(m, cod, &enc);
    
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