#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
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

void exibircurso(Cursos *c){
    printf("CURSOS CADASTRADOS\n");
    if(c != NULL){
        exibircurso(c->esq);
        printf("%d %s %d\n", c->idcurso, c->nomecurso, c->qntdperiodos);
        exibircurso(c->dir);
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
                buscamat(m->esq, codigo, enc);
            else
                buscamat(m->dir, codigo, enc);
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

// i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
// já tenha sido cadastrado na árvore de cursos. 
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

// vii) Mostrar todos os cursos do Campus. 
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

// viii) Mostrar todas as disciplinas de um determinado curso. 
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
                // printf("%d %.2f", a->nota->coddisc, a->nota->notafinal);
                // notasdiscperiodoaluno((*a)->nota->esq, periodo, mat);
                // notasdiscperiodoaluno((*a)->nota->dir, periodo, mat);
            }
        }
        else
            printf("Nota nao encontrada\n");
    }
}

// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
// disciplina. 
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

// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.
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