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
void exibir_disc_curso(Disciplina *disc) {
    if (disc != NULL) {
        exibir_disc_curso(disc->esq);
        printf("Código: %d\n", disc->cod_disciplina);
        printf("Nome: %s\n", disc->nomedisc);
        printf("Carga horária: %d\n", disc->cargah);
        printf("Período: %d\n", disc->periodo);
        printf("\n");
        exibir_disc_curso(disc->dir);
    }
}

void exibir_disc_curso_main(Cursos *curso, int idcurso) {
    if (curso != NULL) {
        if (curso->idcurso == idcurso) {
            Disciplina *disc = curso->disc;
            exibir_disc_curso(disc);
        }
        else if (idcurso < curso->idcurso)
            exibir_disc_curso_main(curso->esq, idcurso);
        else
            exibir_disc_curso_main(curso->dir, idcurso);
       
    }
}

// ix) Mostrar todas as disciplinas de um determinado período de um curso. 
void exibir_disc_periodo(Disciplina *disc, int periodo) {
    if (disc != NULL) {
        exibir_disc_periodo(disc->esq, periodo);
        if (disc->periodo == periodo) {
            printf("Código: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horária: %d\n", disc->cargah);
            printf("Período: %d\n", disc->periodo);
            printf("\n");
        }
        exibir_disc_periodo(disc->dir, periodo);
    }
}

void exibir_disc_periodo_main(Cursos *curso, int idcurso, int periodo){
    if(curso != NULL){
        if(curso->idcurso == idcurso){
            exibir_disc_periodo(curso->disc, periodo);
        }
        else if(idcurso < curso->idcurso)
            exibir_disc_periodo_main(curso->esq, idcurso, periodo);
        else
            exibir_disc_periodo_main(curso->dir, idcurso, periodo);
    }
}

// x) Mostrar todas as disciplinas que um determinado aluno está matriculado 
void exibir_disc(Cursos *curso, int idcurso) {
    if (curso != NULL) {
        if (curso->idcurso == idcurso) {
            Disciplina *disc = curso->disc;
            printf("Código: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horária: %d\n", disc->cargah);
            printf("Período: %d\n", disc->periodo);
            printf("\n");
        }
        else if (idcurso < curso->idcurso)
            exibir_disc(curso->esq, idcurso);
        else
            exibir_disc(curso->dir, idcurso);
    }
}

void exibir_disc_aluno(Matricula *mat, Cursos *cursos, int codcurso){
    if (mat != NULL){
        exibir_disc(cursos, mat->coddisc);
        exibir_disc_aluno(mat->esq, cursos, codcurso);
        exibir_disc_aluno(mat->dir, cursos, codcurso);
    }
}

void exibir_disc_aluno_main(Alunos *aluno, Cursos *cursos, int matricula){
    if(aluno != NULL){
        if(aluno->matricula == matricula){
            exibir_disc_matriculadas(aluno->mat, cursos, aluno->codcurso);
        }
    }
}