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

void AlturaAVlMatricula(AVLMatricula **mat){
    int esq = 0, dir = 0;
    if(*mat != NULL){
        AlturaAVlMatricula(&(*mat)->esq);
        AlturaAVlMatricula(&(*mat)->dir);

        // Obter alturas dos filhos esquerdo e direito
        if((*mat)->esq != NULL)
            esq = (*mat)->esq->altura;
        if((*mat)->dir != NULL)
            dir = (*mat)->dir->altura;

        // Definir altura do nó atual
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

void AlturaAVlNotas(AVLNotas **notas) {
    int esq = 0, dir = 0;
    if (*notas != NULL) {
        AlturaAVlNotas(&(*notas)->esq);  
        AlturaAVlNotas(&(*notas)->dir); 

        // Obter alturas dos filhos esquerdo e direito
        if ((*notas)->esq != NULL)
            esq = (*notas)->esq->altura;
        if ((*notas)->dir != NULL)
            dir = (*notas)->dir->altura;

        // Definir altura do nó atual
        if (esq > dir)
            (*notas)->altura = esq + 1;
        else
            (*notas)->altura = dir + 1;
    }
}


int fbNotas(AVLNotas *notas){
    return notas->esq->altura - notas->dir->altura;
}

void rotacaoEsqNotas(AVLNotas **notas){
    AVLNotas *aux = (AVLNotas*)malloc(sizeof(AVLNotas));
    if(*notas != NULL){
        aux = (*notas)->dir;
        (*notas)->dir = aux->esq;
        aux->esq = (*notas);
        AlturaAVlMatricula(notas);
        AlturaAVlMatricula(&aux);
        *notas = aux;
    }
}

void rotacaoDirNotas(AVLNotas **notas){
    AVLNotas *aux = (AVLNotas*)malloc(sizeof(AVLNotas));
    if(*notas != NULL){
        aux = (*notas)->esq;
        (*notas)->esq = aux->dir;
        aux->dir = (*notas);
        AlturaAVlMatricula(notas);
        AlturaAVlMatricula(&aux);
        *notas = aux;
    }
}

void BalanceamentoAVLNotas(AVLNotas **notas){
    int fb;
    fb = fbNotas(*notas);
    if (fb == -2){
        if (fbNotas((*notas)->dir) > 0)
            rotacaoDirNotas(&(*notas)->dir);
        rotacaoEsqNotas(notas);
    } 
    else if (fb == 2){
        if (fbNotas((*notas)->esq) < 0)
            rotacaoEsqNotas(&(*notas)->esq);
        rotacaoDirNotas(notas);
    }
}

void busca_disc(AVLMatricula *m, int cod, int *enc){ 
    if(m != NULL){
        if(m->info->coddisc == cod)
            *enc = 1;
        else if(cod < m->info->coddisc)
            busca_disc(m->esq, cod, enc);
        else
            busca_disc(m->dir, cod, enc);
    }
}

int ehfolhamat(AVLMatricula *m){
    return (m->esq == NULL && m->dir == NULL);
}

AVLMatricula* soumfilhomat(AVLMatricula *m){
    AVLMatricula *aux;
    aux = NULL;
    if (m->esq == NULL)
        aux = m->dir;
    else if (m->dir == NULL)
        aux = m->esq;

    return aux;
}

AVLMatricula* menorfilhoesqmat(AVLMatricula *m) {
    AVLMatricula *aux;
    aux = NULL;
    if (m){
        aux = menorfilhoesqmat(m->esq);
        if (!aux)
            aux = m;
    }
    return aux;
}

void rmvmatricula(AVLMatricula **m, int cod) {
    if (*m != NULL) {
        // Se encontrou o nó a ser removido
        if ((*m)->info->coddisc == cod) {
            AVLMatricula *aux;
            
            // Caso 1: O nó é uma folha (sem filhos)
            if (ehfolhamat(*m)) {
                aux = *m;
                free(aux);
                *m = NULL;
            } 
            // Caso 2: O nó tem apenas um filho
            else if ((aux = soumfilhomat(*m)) != NULL) {
                AVLMatricula *temp;
                temp = *m;
                free(temp);
                *m = aux;  // Substitui o nó pelo seu único filho
            } 
            else {
                AVLMatricula *menorfilho = menorfilhoesqmat((*m)->dir);
                (*m)->info->coddisc = menorfilho->info->coddisc;
                rmvmatricula(&(*m)->dir, menorfilho->info->coddisc);
            }
        } 
        // Se o código é menor, continua na subárvore esquerda
        else if (cod < (*m)->info->coddisc)
            rmvmatricula(&(*m)->esq, cod);
        // Se o código é maior, continua na subárvore direita
        else
            rmvmatricula(&(*m)->dir, cod);
        
        BalanceamentoAVLMatricula(m);
        AlturaAVlMatricula(m);
    }
}

int cadnota_nota(AVLNotas **nota, Notas *n){
    int sucesso = 1;
    if (*nota == NULL){
        AVLNotas *novo = (Notas*)malloc(sizeof(Notas));
        novo->info = n;
        novo->esq = NULL;
        novo->dir = NULL;
        *nota = novo;
    }
    else{
        if (n->coddisc == (*nota)->info->coddisc)
            sucesso = 0;
        else{
            if(n->coddisc < (*nota)->info->coddisc)
                sucesso = cadnota_nota(&((*nota)->esq), n);
            else
                sucesso = cadnota_nota(&((*nota)->dir), n);
        }
        
        BalanceamentoAVLNotas(nota);
        AlturaAVlNotas(nota);
    }
    return sucesso;
}

int cadnota(Alunos **a, int mat, Notas *n) {
    int enc = 0;
    if (*a != NULL) {
        if ((*a)->matricula == mat) {
            int enc_disc = 0;
            busca_disc((*a)->mat, n->coddisc, &enc_disc);
            if (enc_disc == 1) {
                if (cadnota_nota(&(*a)->nota, n) == 1){
                    rmvmatricula(&(*a)->mat, n->coddisc);
                    enc = 1;
                }
            }
        } else
            enc = cadnota(&(*a)->prox, mat, n);
    }
    
    return enc; // Retorna 1 se a nota foi cadastrada, 0 caso contrário
}

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