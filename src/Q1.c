#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q1.h"

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

// void exibircurso(Cursos *c, int nivel) {
//     if (c != NULL) {
//         // Imprime o conteúdo do nó atual
//         printf("\%d %s %d\n", c->idcurso, c->nomecurso, c->qntdperiodos);
//         for (int i = 0; i < nivel; i++) {
//             printf("    ");  // 4 espaços para cada nível
//         }
//         // Chama a função recursivamente para o filho esquerdo e direito
//         exibircurso(c->esq, nivel + 1);  // Primeiro exibe o filho esquerdo
//         exibircurso(c->dir, nivel + 1);  // Depois exibe o filho direito
//     }
// }

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

// Essa buscacurso vai mudar de lugar, para o main quando este for criado. Isto para otimizar
void alunosporcurso(Alunos **a, Cursos **c, int codcurso){
    int enc;
    buscacurso(c, codcurso, &enc);

    if(enc == 1){
        while((*a) != NULL && (*a)->codcurso == codcurso){
            printf("%s\n", (*a)->nome);
            *a = (*a)->prox;
        }
    }
    else
        printf("Curso nao encontrado!\n");
}

// void buscanota(Notas *n, int coddisc, int *enc){
//     if(n == NULL)
//         *enc = 0;
//     else{
//         if(n->coddisc == coddisc){
//             *enc = 1;
//         }
//         else{
//             if(coddisc < n->coddisc)
//                 buscanota(&(n->esq), coddisc, enc);
//             else
//                 buscanota(&(n->dir), coddisc, enc);
//         }
//     }
// }

void notasdiscperiodoaluno(Alunos *a, int periodo, int mat){
    if(a == NULL){
        printf("Nao existe alunos cadastrados\n");
    }
    else{
        if(a->nota != NULL){
            if(a->nota->semestre == periodo){
                // printf("EXIBINDO NOTAS DO SEMESTRE %d\n", a->nota->semestre);
                printf("%d %.2f", a->nota->coddisc, a->nota->notafinal);
                notasdiscperiodoaluno(a->nota->esq, periodo, mat);
                notasdiscperiodoaluno(a->nota->dir, periodo, mat);
            }
        }
        else
            printf("Nota nao encontrada\n");
    }
}