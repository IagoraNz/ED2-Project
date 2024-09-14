#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q1.h"

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
            // Implementar aqui a remoção da árvore de matrícula confome especificado
        }
        else{
            if(cod < (*n)->coddisc)
                cadnota(m, &((*n)->esq), cod, semestre, notafinal);
            else
                cadnota(m, &((*n)->dir), cod, semestre, notafinal);
        }
    }
}