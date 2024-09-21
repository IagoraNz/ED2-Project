#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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