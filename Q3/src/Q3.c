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
    int res = -1, altesq, altdir;
    if(raiz){
        altesq = alturaDisc(raiz->esq);
        altdir = alturaDisc(raiz->dir);
        res = 1 + (altesq > altdir ? altesq : altdir);
    }

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

void validacurso(AVLCurso *cursos, int codcurso, int *enc){
    if (cursos != NULL){
        if (cursos->info->idcurso == codcurso){
            *enc = 1;
        } else {
            validacurso(cursos->esq, codcurso, enc);
            validacurso(cursos->dir, codcurso, enc);
        }
    }
}

int cadaluno(Alunos **aluno, AVLCurso *cursos, int mat, char *nome, int codcurso) {
    int sucesso = 0, enc = 0;
    // Se a lista estiver vazia ou o ponto de inserção for alcançado
    if (*aluno == NULL) {
        validacurso(cursos, codcurso, &enc);
        if (enc == 1) {
            *aluno = criar_aluno(mat, nome, codcurso);
            sucesso = 1;
        }
    } else {
        if ((*aluno)->matricula == mat)
            sucesso = 0; 
        // Verifica se o novo aluno deve ser inserido antes do aluno atual (ordenado por nome)
        else if (strcmp(nome, (*aluno)->nome) < 0) {
            validacurso(cursos, codcurso, &enc);
            if (enc == 1) {
                Alunos *novo = criar_aluno(mat, nome, codcurso);  
                novo->prox = *aluno; 
                *aluno = novo;
                sucesso = 1;
            }
        } else 
            sucesso = cadaluno(&(*aluno)->prox, cursos, mat, nome, codcurso);
    }
    
    return sucesso; 
}


/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

int cadcurso(AVLCurso **curso, Cursos *no) {
    int sucesso = 0;
    if (*curso == NULL) {
        *curso = (AVLCurso*)malloc(sizeof(AVLCurso));
        (*curso)->info = no;
        (*curso)->esq = NULL;
        (*curso)->dir = NULL;
        (*curso)->altura = 0;
        sucesso = 1;    
    }
    else {
        if (no->idcurso == (*curso)->info->idcurso)
            sucesso = 0;
        else if (no->idcurso < (*curso)->info->idcurso)
            sucesso = cadcurso(&((*curso)->esq), no);
        else 
            sucesso = cadcurso(&((*curso)->dir), no);
        
        if (sucesso == 1) {
            balancearCurso(curso);
            (*curso)->altura = alturaCurso(*curso);
        }
    }
    return sucesso;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90. */

int validar_ch(int cargahoraria){
    int validar = 0;
    if (cargahoraria % 15 == 0 && cargahoraria >= 30 && cargahoraria <= 90)
        validar = 1;
    return validar;
}

int validar_periodo(AVLCurso *curso, int periodo){
    int validar = 0;
    if (periodo >= 1 && periodo <= curso->info->qntdperiodos)
        validar = 1;
    return validar;
}

int insere_disc(AVLDisc **disc, Disciplina *no) {
    int suc = 0;
    if ((*disc) == NULL) {
        *disc = (AVLDisc*)malloc(sizeof(AVLDisc));
        (*disc)->info = no;
        (*disc)->esq = NULL;
        (*disc)->dir = NULL;
        (*disc)->altura = 0;
        suc = 1;
    } 
    else {
        if (no->cod_disciplina < (*disc)->info->cod_disciplina)
            suc = insere_disc(&(*disc)->esq, no);
        else if (no->cod_disciplina > (*disc)->info->cod_disciplina)
            suc = insere_disc(&(*disc)->dir, no);
        else
            suc = 0;

        if (suc == 1) {
            balancearDisc(disc);
            (*disc)->altura = alturaDisc(*disc);
        }
    }

    return suc;
}

int caddisc(AVLCurso **curso, Disciplina *no, int idcurso) {
    int sucesso = 0;

    if(validar_ch(no->cargah)){
        if(*curso != NULL){
            if((*curso)->info != NULL && (*curso)->info->idcurso == idcurso){
                if(validar_periodo(*curso, no->periodo))
                    sucesso = insere_disc(&(*curso)->info->disc, no);
            } 
            else{
                if(idcurso < (*curso)->info->idcurso)
                    sucesso = caddisc(&(*curso)->esq, no, idcurso);
                else
                    sucesso = caddisc(&(*curso)->dir, no, idcurso);
            }
        }
    }

    return sucesso;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */
int alturaMatricula(AVLMatricula *raiz) {
    int res;

    if (raiz != NULL) {
        int esq = alturaMatricula(raiz->esq);  // Altura da subárvore esquerda
        int dir = alturaMatricula(raiz->dir);  // Altura da subárvore direita
        res = 1 + (esq > dir ? esq : dir);  // A altura do nó é a maior altura dos filhos + 1
    } else
        res = -1;  // Caso base: árvore vazia tem altura -1

    return res;
}


int fbMatricula(AVLMatricula *mat) {
    return alturaMatricula(mat->esq) - alturaMatricula(mat->dir);  // Fator de balanceamento
}

void rotacaoEsqMatricula(AVLMatricula **mat) {
    AVLMatricula *aux = (*mat)->dir;
    if (aux != NULL) {
    (*mat)->dir = aux->esq;
    aux->esq = (*mat);
    (*mat)->altura = alturaMatricula(*mat);
    aux->altura = alturaMatricula(aux);
    *mat = aux;
    }
}

void rotacaoDirMatricula(AVLMatricula **mat) {
    AVLMatricula *aux = (*mat)->esq;
    if (aux != NULL) {
        (*mat)->esq = aux->dir;
        aux->dir = (*mat);
        (*mat)->altura = alturaMatricula(*mat);
        aux->altura = alturaMatricula(aux);
        *mat = aux;
    }
}

void BalanceamentoAVLMatricula(AVLMatricula **mat) {
    int fb = fbMatricula(*mat);
    if (fb == -2) {
        if (fbMatricula((*mat)->dir) > 0)
            rotacaoDirMatricula(&(*mat)->dir);
        rotacaoEsqMatricula(mat);
    } else if (fb == 2) {
        if (fbMatricula((*mat)->esq) < 0) 
            rotacaoEsqMatricula(&(*mat)->esq);
        rotacaoDirMatricula(mat);
    }
}

void inserirMatricula(AVLMatricula **mat, int codigo, int *igual) {
    if (*mat == NULL) {
        *mat = (AVLMatricula*) malloc(sizeof(AVLMatricula));  
        Matricula *novo = (Matricula*) malloc(sizeof(Matricula));  
        novo->coddisc = codigo;
        (*mat)->info = novo;
        (*mat)->altura = 0;
        (*mat)->esq = NULL;
        (*mat)->dir = NULL;
        *igual = 1;
    } else {
        if (codigo < (*mat)->info->coddisc)
            inserirMatricula(&(*mat)->esq, codigo, igual);
        else if (codigo > (*mat)->info->coddisc) 
            inserirMatricula(&(*mat)->dir, codigo, igual);
        else 
            *igual = 0;  

        if (*igual == 1) {
            (*mat)->altura = alturaMatricula(*mat);  // Atualiza a altura do nó
            BalanceamentoAVLMatricula(mat);  // Balanceia a árvore após a inserção
        }
    }
}

void buscarDisciplina(AVLDisc *disc, int cod_disc, int *enc){
    if(disc != NULL){
        if(disc->info->cod_disciplina == cod_disc)
            *enc = 1; 
        else if(cod_disc < disc->info->cod_disciplina)
            buscarDisciplina(disc->esq, cod_disc, enc);
        else
            buscarDisciplina(disc->dir, cod_disc, enc);
    }
}

void buscarDisciplinaMain(AVLCurso *curso, int cod_disc, int idcurso, int *encontrou) {
    if (curso != NULL) {
        if (curso->info->idcurso == idcurso)
            buscarDisciplina(curso->info->disc, cod_disc, encontrou);
        else {
            buscarDisciplinaMain(curso->esq, cod_disc, idcurso, encontrou);
            buscarDisciplinaMain(curso->dir, cod_disc, idcurso, encontrou);
        }
    }
}

int cadmatricula(Alunos **aluno, AVLCurso *curso, int codigo, int mat){
    int sucesso = 0, enc = 0;
    if (*aluno != NULL) {
        if ((*aluno)->matricula == mat) {
            AVLCurso *aux = curso;
            buscarDisciplinaMain(aux, codigo, (*aluno)->codcurso, &enc);
            if (enc == 1)
                inserirMatricula(&(*aluno)->mat, codigo, &sucesso);
        } else
            sucesso = cadmatricula(&(*aluno)->prox, curso, codigo, mat);
    }
    return sucesso;
}


/*---------------------------------------------------------------------------------------------------------------*/

/* v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas.*/

int AlturaAVlNotas(AVLNotas *notas) {
    int res;
    if (notas != NULL) {
        int esq = AlturaAVlNotas(notas->esq);
        int dir = AlturaAVlNotas(notas->dir);
        res = 1 + (esq > dir ? esq : dir);
    } else
        res = -1;
    return res;
}

int fbNotas(AVLNotas *notas) {
    return AlturaAVlNotas(notas->esq) - AlturaAVlNotas(notas->dir);
}

void rotacaoEsqNotas(AVLNotas **notas) {
    AVLNotas *aux = (*notas)->dir;
    if (aux != NULL) {
        (*notas)->dir = aux->esq;
        aux->esq = (*notas);
        (*notas)->altura = AlturaAVlNotas(*notas);
        aux->altura = AlturaAVlNotas(aux);
        *notas = aux;
    }
}

void rotacaoDirNotas(AVLNotas **notas) {
    AVLNotas *aux = (*notas)->esq;
    if (aux != NULL) {
        (*notas)->esq = aux->dir;
        aux->dir = (*notas);
        (*notas)->altura = AlturaAVlNotas(*notas);
        aux->altura = AlturaAVlNotas(aux);
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

void busca_disc(AVLMatricula *mat, int cod, int *enc) { 
    if (mat != NULL) {
        if (mat->info->coddisc == cod)
            *enc = 1;
        else if (cod < mat->info->coddisc)
            busca_disc(mat->esq, cod, enc);
        else
            busca_disc(mat->dir, cod, enc);
    }
}

int ehfolhamat(AVLMatricula *mat) {
    return (mat->esq == NULL && mat->dir == NULL);
}

AVLMatricula* soumfilhomat(AVLMatricula *mat) {
    AVLMatricula *aux;
    aux = NULL;
    if (mat->esq == NULL)
        aux = mat->dir;
    else if (mat->dir == NULL)
        aux = mat->esq;

    return aux;
}

AVLMatricula* menorfilhoesqmat(AVLMatricula *mat) {
    AVLMatricula *aux;
    aux = NULL;
    if (mat) {
        aux = menorfilhoesqmat(mat->esq);
        if (!aux)
            aux = mat;
    }
    return aux;
}

void rmvmatricula(AVLMatricula **mat, int cod) {
    if (*mat != NULL) {
        // Se encontrou o nó a ser removido
        if ((*mat)->info->coddisc == cod) {
            AVLMatricula *aux;
            
            // Caso 1: O nó é uma folha (sem filhos)
            if (ehfolhamat(*mat)) {
                aux = *mat;
                free(aux);
                *mat = NULL;
            } 
            // Caso 2: O nó tem apenas um filho
            else if ((aux = soumfilhomat(*mat)) != NULL) {
                AVLMatricula *temp;
                temp = *mat;
                free(temp);
                *mat = aux;  // Substitui o nó pelo seu único filho
            } 
            else {
                AVLMatricula *menorfilho = menorfilhoesqmat((*mat)->dir);
                (*mat)->info->coddisc = menorfilho->info->coddisc;
                rmvmatricula(&(*mat)->dir, menorfilho->info->coddisc);
            }
        } 
        // Se o código é menor, continua na subárvore esquerda
        else if (cod < (*mat)->info->coddisc)
            rmvmatricula(&(*mat)->esq, cod);
        // Se o código é maior, continua na subárvore direita
        else
            rmvmatricula(&(*mat)->dir, cod);
        
        if (*mat != NULL) {
            BalanceamentoAVLMatricula(mat);  
            (*mat)->altura = alturaMatricula(*mat);
        }
    }
}


int inserenota(AVLNotas **nota, Notas *no) {
    int sucesso = 1;
    if (*nota == NULL) {
        AVLNotas *novo = (AVLNotas*)malloc(sizeof(AVLNotas)); 
        novo->info = no;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;  
        *nota = novo;
    } else {
        if (no->coddisc == (*nota)->info->coddisc)
            sucesso = 0;  
        else {
            if (no->coddisc < (*nota)->info->coddisc)
                sucesso = inserenota(&((*nota)->esq), no);
            else 
                sucesso = inserenota(&((*nota)->dir), no);
        }

        if (sucesso == 1) {
            BalanceamentoAVLNotas(nota);
            (*nota)->altura = AlturaAVlNotas(*nota);
        }
    }
    return sucesso;
}


int cadnota(Alunos **aluno, int mat, Notas *no){
    int enc = 0;
    if (*aluno != NULL) {
        if ((*aluno)->matricula == mat) {
            int enc_disc = 0;
            busca_disc((*aluno)->mat, no->coddisc, &enc_disc);
            if (enc_disc == 1) {
                if (inserenota(&(*aluno)->nota, no) == 1) {
                    rmvmatricula(&(*aluno)->mat, no->coddisc);
                    enc = 1;
                }
            }
        } else
            enc = cadnota(&(*aluno)->prox, mat, no);
    }
    return enc; 
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

void alunosporcurso(Alunos *aluno, int codcurso) {
    if (aluno != NULL) {
        if (aluno->codcurso == codcurso) {
            printf("Matricula: %d\n", aluno->matricula);
            printf("Nome: %s\n", aluno->nome);
            printf("\n");
        }
        alunosporcurso(aluno->prox, codcurso);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vii) Mostrar todos os cursos do Campus. */

void exibir_cursos(AVLCurso *curso) {
    if (curso != NULL) {
        printf("ID: %d\n", curso->info->idcurso);
        printf("Nome: %s\n", curso->info->nomecurso);
        printf("Quantidade de períodos: %d\n", curso->info->qntdperiodos);
        printf("\n");
        exibir_cursos(curso->esq);
        exibir_cursos(curso->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* viii) Mostrar todas as disciplinas de um determinado curso. */

void exibir_disc_curso(AVLDisc *disc){
    if(disc != NULL){
        exibir_disc_curso(disc->esq);
        printf("Codigo: %d\n", disc->info->cod_disciplina);
        printf("Nome: %s\n", disc->info->nomedisc);
        printf("Carga horaria: %d\n", disc->info->cargah);
        printf("Periodo: %d\n", disc->info->periodo);
        printf("\n");
        exibir_disc_curso(disc->dir);
    }
}

void exibir_disc_curso_main(AVLCurso *curso, int idcurso) {
    if(curso != NULL){
        if(curso->info->idcurso == idcurso){
            AVLDisc *disc = curso->info->disc;
            exibir_disc_curso(disc);
        }
        else if (idcurso < curso->info->idcurso)
            exibir_disc_curso_main(curso->esq, idcurso);
        else
            exibir_disc_curso_main(curso->dir, idcurso);
       
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// ix) Mostrar todas as disciplinas de um determinado período de um curso. 

void exibir_disc_periodo(AVLDisc *disc, int periodo) {
    if (disc != NULL) {
        exibir_disc_periodo(disc->esq, periodo);
        if (disc->info->periodo == periodo) {
            printf("Codigo: %d\n", disc->info->cod_disciplina);
            printf("Nome: %s\n", disc->info->nomedisc);
            printf("Carga horaria: %d\n", disc->info->cargah);
            printf("Periodo: %d\n", disc->info->periodo);
            printf("\n");
        }
        exibir_disc_periodo(disc->dir, periodo);
    }
}

void exibir_disc_periodo_main(AVLCurso *curso, int idcurso, int periodo){
    if(curso != NULL){
        if(curso->info->idcurso == idcurso)
            exibir_disc_periodo(curso->info->disc, periodo);
        else if(idcurso < curso->info->idcurso)
            exibir_disc_periodo_main(curso->esq, idcurso, periodo);
        else
            exibir_disc_periodo_main(curso->dir, idcurso, periodo);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */

void exibir_disciplinas(AVLDisc *disc, int cod_disc) {
    if (disc != NULL) {
        if (disc->info->cod_disciplina == cod_disc) {
            printf("Codigo: %d\n", disc->info->cod_disciplina);
            printf("Nome: %s\n", disc->info->nomedisc);
            printf("Carga horaria: %d\n", disc->info->cargah);
            printf("Periodo: %d\n", disc->info->periodo);
            printf("\n");
        }
        else if (cod_disc < disc->info->cod_disciplina)
            exibir_disciplinas(disc->esq, cod_disc);
        else
            exibir_disciplinas(disc->dir, cod_disc);
    }
}

void exibir_disc(AVLCurso *curso, int cod_disc, int idcurso) {
    if (curso != NULL) {
        if (curso->info->idcurso == idcurso) {
            if (curso->info->disc != NULL)
                exibir_disciplinas(curso->info->disc, cod_disc);
        }
        else if (idcurso < curso->info->idcurso)
            exibir_disc(curso->esq, cod_disc, idcurso);
        else
            exibir_disc(curso->dir, cod_disc, idcurso);
    }
}

void exibir_disc_aluno(AVLMatricula *mat, AVLCurso *cursos, int codcurso){
    if (mat != NULL){
        exibir_disc(cursos, mat->info->coddisc, codcurso);
        exibir_disc_aluno(mat->esq, cursos, codcurso);
        exibir_disc_aluno(mat->dir, cursos, codcurso);
    }
}

void exibir_disc_aluno_main(Alunos *aluno, AVLCurso *cursos, int matricula){
    if (aluno != NULL){
        if (aluno->matricula == matricula)
            exibir_disc_aluno(aluno->mat, cursos, aluno->codcurso);
        else
            exibir_disc_aluno_main(aluno->prox, cursos, matricula);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

void exibirNotasPeriodo(AVLNotas *nota, int periodo){
    if(nota != NULL){
        if(nota->info->semestre == periodo){
            printf("Codigo: %d\n", nota->info->coddisc);
            printf("Nota Final: %.2f\n", nota->info->notafinal);
            printf("Semestre: %d\n", nota->info->semestre);
            printf("\n");
        }
        exibirNotasPeriodo(nota->esq, periodo);
        exibirNotasPeriodo(nota->dir, periodo);
    }
}

void notasdiscperiodoaluno(Alunos *aluno, int periodo, int mat) {
    if (aluno != NULL) {
        if (aluno->matricula == mat)
            exibirNotasPeriodo(aluno->nota, periodo);
        else
            notasdiscperiodoaluno(aluno->prox, periodo, mat);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */

AVLCurso* buscar_curso(AVLCurso *curso, int idcurso) {
    AVLCurso *aux;
    aux = NULL;
    if (curso != NULL) {
        if (curso->info->idcurso == idcurso)
            aux = curso;
        else if (idcurso < curso->info->idcurso)
            aux = buscar_curso(curso->esq, idcurso);
        else
            aux = buscar_curso(curso->dir, idcurso);
    }
    return aux;
}

AVLDisc* buscar_disciplina(AVLDisc *disc, int cod_disc) {
    AVLDisc *aux;
    aux = NULL;
    if (disc != NULL) {
        if (disc->info->cod_disciplina == cod_disc)
            aux = disc;
        else if (cod_disc < disc->info->cod_disciplina)
            aux = buscar_disciplina(disc->esq, cod_disc);
        else
            aux = buscar_disciplina(disc->dir, cod_disc);
    }
    return aux;
}

AVLNotas* buscar_nota(AVLNotas *nota, int cod_disc) {
    AVLNotas *aux;
    aux = NULL;
    if (nota != NULL) {
        if (nota->info->coddisc == cod_disc)
            aux = nota;
        else if (cod_disc < nota->info->coddisc)
            aux = buscar_nota(nota->esq, cod_disc);
        else
            aux = buscar_nota(nota->dir, cod_disc);
    }
    return aux;
}


void notadiscporaluno(Alunos *aluno, AVLCurso *curso, int matricula, int coddisc){
    if(aluno != NULL){
        if(aluno->matricula == matricula){
            AVLCurso *c = buscar_curso(curso, aluno->codcurso);
            AVLDisc *d = buscar_disciplina(c->info->disc, coddisc);
            AVLNotas *n = buscar_nota(aluno->nota, coddisc);
            if(d != NULL && n != NULL){
                printf("Codigo: %d\n", d->info->cod_disciplina);
                printf("Nome: %s\n", d->info->nomedisc);
                printf("Carga horaria: %d\n", d->info->cargah);
                printf("Nota Final: %.2f\n", n->info->notafinal);
                printf("Semestre: %d\n", n->info->semestre);
            }
        }
        else
            notadiscporaluno(aluno->prox, curso, matricula, coddisc);
    }
}


/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */

int ehfolhadisc(AVLDisc *disc){
    return (disc->esq == NULL && disc->dir == NULL);
}

AVLDisc* soumfilhodisc(AVLDisc *disc){
    AVLDisc *aux;
    aux = NULL;
    if (disc->dir == NULL)
        aux = disc->esq;
    else if (disc->esq == NULL)
        aux = disc->dir;
    return aux;
}

AVLDisc* menorfilhoesqdisc(AVLDisc *disc){
    AVLDisc *aux;
    aux = NULL;
    if (disc != NULL)
        aux = menorfilhoesqdisc(disc->esq);
        if (!aux)
            aux = disc;
    return aux;
}

void rmvdisc(AVLDisc **disc, int cod_disc, int *remove){
    if ((*disc != NULL)){    
        AVLDisc *aux;
        AVLDisc *endfilho;
        AVLDisc *endmenorfilho;
        if ((*disc)->info->cod_disciplina == cod_disc){
            if(ehfolhadisc(*disc)){
                aux = *disc;
                free(aux);
                *disc = NULL;
            } else if((endfilho = soumfilhodisc(*disc)) != NULL){
                aux = *disc;
                free(aux); 
                *disc = endfilho;  
            } else {
                endmenorfilho = menorfilhoesqdisc((*disc)->dir);
                (*disc)->info->cod_disciplina = endmenorfilho->info->cod_disciplina;
                (*disc)->info->cargah = endmenorfilho->info->cargah;
                (*disc)->info->periodo = endmenorfilho->info->periodo;
                strcpy((*disc)->info->nomedisc, endmenorfilho->info->nomedisc);
                rmvdisc(&(*disc)->dir, endmenorfilho->info->cod_disciplina, remove);
            }
            *remove = 1;
        }
        else if (cod_disc < (*disc)->info->cod_disciplina)
            rmvdisc(&(*disc)->esq, cod_disc, remove);
        else 
            rmvdisc(&(*disc)->dir, cod_disc, remove);

        if (*disc != NULL){
            balancearDisc(disc);
            (*disc)->altura = alturaDisc(*disc);
        }
    }
}

void buscamat(AVLMatricula *mat, int codigo, int *enc) {
    if (mat == NULL)
        *enc = 0;
    else if (mat->info->coddisc == codigo)
        *enc = 1;
    else if (codigo < mat->info->coddisc)
        buscamat(mat->esq, codigo, enc);
    else
        buscamat(mat->dir, codigo, enc);
}

void validar_rmv_disciplina(Alunos *alunos, int cod_disc, int *validar_disc) {
    int enc = 0;
    if (alunos != NULL && *validar_disc == 0) { // Pare se já estiver validado
        buscamat(alunos->mat, cod_disc, &enc);
        if (enc == 0)
            *validar_disc = 1;
        else
            validar_rmv_disciplina(alunos->prox, cod_disc, validar_disc);
    }
}


int rmvdisc_curso(AVLCurso **cursos, Alunos *alunos, int idcurso, int cod_disc){
    int remove = 0, validar_disc = 0;
    if ((*cursos) != NULL){
        validar_rmv_disciplina(alunos, cod_disc, &validar_disc);
        if (validar_disc != 0){
            if ((*cursos)->info->idcurso == idcurso)
                rmvdisc(&(*cursos)->info->disc, cod_disc, &remove);  
            else if (idcurso < (*cursos)->info->idcurso)
                remove = rmvdisc_curso(&(*cursos)->esq, alunos, idcurso, cod_disc);
            else
                remove = rmvdisc_curso(&(*cursos)->dir, alunos, idcurso, cod_disc);
        }
    }
    return remove;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. */

void rmvmatdealuno(Alunos **aluno, int matricula, int coddisc) {
    if (*aluno != NULL) {
        if ((*aluno)->matricula == matricula)
            rmvmatricula(&(*aluno)->mat, coddisc);
        else
            rmvmatdealuno(&(*aluno)->prox, matricula, coddisc);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

void exibir_disciplina(AVLDisc *disc, int cod_disciplina) {
    if (disc != NULL) {
        if (disc->info->cod_disciplina == cod_disciplina)
            printf("Disciplina: %s\n", disc->info->nomedisc);
        else if (cod_disciplina < disc->info->cod_disciplina)
            exibir_disciplina(disc->esq, cod_disciplina);
        else
            exibir_disciplina(disc->dir, cod_disciplina);
    }
}

void exibir_notas(AVLNotas *nota, AVLDisc *disc, int periodo) {
    if (nota != NULL) {
        if (nota->info->semestre == periodo) {
            exibir_disciplina(disc, nota->info->coddisc);
            printf("Nota: %.2f\n", nota->info->notafinal);
            printf("Semestre: %d\n\n", nota->info->semestre);
        }
        exibir_notas(nota->esq, disc, periodo);
        exibir_notas(nota->dir, disc, periodo);
    }
}

int exibir_nome_curso(AVLCurso *curso, int idcurso) {
    int qntperiodos = 0;
    if (curso != NULL) {
        if (curso->info->idcurso == idcurso) {
            printf("Curso: %s\n", curso->info->nomecurso);
            qntperiodos = curso->info->qntdperiodos;
        } else if (idcurso < curso->info->idcurso)
            qntperiodos = exibir_nome_curso(curso->esq, idcurso);
        else
            qntperiodos = exibir_nome_curso(curso->dir, idcurso);
    }
    return qntperiodos;
}

void exibir_hist_aluno(Alunos *aluno, AVLCurso *curso, int matricula) {
    if (aluno != NULL) {
        if (aluno->matricula == matricula) {
            printf("Aluno: %s\n", aluno->nome);
            printf("Matricula: %d\n", aluno->matricula);
            int qntperiodos = 0;
            qntperiodos = exibir_nome_curso(curso, aluno->codcurso);
            printf("Historico:\n");
            for (int i = 1; i <= qntperiodos; i++)
                exibir_notas(aluno->nota, curso->info->disc, i);
        } else
            exibir_hist_aluno(aluno->prox, curso, matricula);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* extra) Função agregadas, associadas ou adicionais para complementar a coesão do software */

// Outros



// Gerar os códigos

void gerarCodDisciplina(int cargah, int periodo, int *coddisc) {
    // Passo 1: obtendo o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int anoatual = tm.tm_year + 1900;

    int num5 = rand() % 100000; // Gera um número entre 0 e 99999

    // Passo 3: gerando o código no formato AAAACCPNNNNN como número inteiro
    *coddisc = anoatual * 100000000 + cargah * 1000000 + periodo * 100000 + num5;
}

void gerarIdCurso(int qntperiodos, int *idcurso) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano = tm.tm_year + 1900;

    int num4 = rand() % 10000;

    // Combina os componentes no formato PPPAAAANNNN como um único número inteiro.
    *idcurso = qntperiodos * 100000000 + (qntperiodos * 3) * 1000000 + (qntperiodos * 5) * 10000 + ano * 10000 + num4;
}

void gerarMatriculaAluno(int idcurso, int *matricula) {
    // Passo 1: obtendo o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano = tm.tm_year + 1900;

    int num4 = rand() % 1000;  // Gera um número entre 000 e 999 para reduzir o tamanho

    // Passo 3: Garantindo que o idcurso tenha no máximo 3 dígitos
    int idcursoModificado = idcurso % 1000;  // Reduzir o número de dígitos do curso para no máximo 3

    // Passo 4: combinando tudo em um número no formato AAAANNNCC
    *matricula = ano * 100000 + num4 * 1000 + idcursoModificado;
}

void exibirAlturaCurso(AVLCurso *curso){
    if(curso != NULL){
        exibirAlturaCurso(curso->esq);
        printf("ID: %d\n", curso->info->idcurso);
        printf("Altura: %d\n", curso->altura);
        exibirAlturaCurso(curso->dir);
    }
}

void exibirAlturaDisciplina(AVLDisc *disc){
    if(disc != NULL){
        exibirAlturaDisciplina(disc->esq);
        printf("Codigo: %d\n", disc->info->cod_disciplina);
        printf("Altura: %d\n", disc->altura);
        exibirAlturaDisciplina(disc->dir);
    }
}

void exibirAlturaDisciplinaMain(AVLCurso *curso, int idcurso){
    if(curso != NULL){
        if(curso->info->idcurso == idcurso)
            exibirAlturaDisciplina(curso->info->disc);
        else if(idcurso < curso->info->idcurso)
            exibirAlturaDisciplinaMain(curso->esq, idcurso);
        else
            exibirAlturaDisciplinaMain(curso->dir, idcurso);
    }
}

void exibirAlturaMatricula(AVLMatricula *mat){
    if(mat != NULL){
        exibirAlturaMatricula(mat->esq);
        printf("Codigo: %d\n", mat->info->coddisc);
        printf("Altura: %d\n", mat->altura);
        exibirAlturaMatricula(mat->dir);
    }
}

void exibirAlturaMatriculaMain(Alunos *aluno, int matricula) {
    if (aluno != NULL) {
        if (aluno->matricula == matricula)
            exibirAlturaMatricula(aluno->mat);
        else
            exibirAlturaMatriculaMain(aluno->prox, matricula);
    }
}

void exibirAlturaNotas(AVLNotas *nota){
    if(nota != NULL){
        exibirAlturaNotas(nota->esq);
        printf("Codigo: %d\n", nota->info->coddisc);
        printf("Altura: %d\n", nota->altura);
        exibirAlturaNotas(nota->dir);
    }
}

void exibirAlturaNotasMain(Alunos *aluno, int matricula) {
    if (aluno != NULL) {
        if (aluno->matricula == matricula)
            exibirAlturaNotas(aluno->nota);
        else
            exibirAlturaNotasMain(aluno->prox, matricula);
    }
}

// Liberar estruturas com base nas novas configurações

void liberarAVLDisc(AVLDisc **raiz){
    if(*raiz != NULL){
        liberarAVLDisc(&(*raiz)->esq);
        liberarAVLDisc(&(*raiz)->dir);
        free((*raiz)->info);
        free(*raiz);
        *raiz = NULL;
    }
}

void liberarAVLCurso(AVLCurso **raiz){
    if(*raiz != NULL){
        liberarAVLCurso(&(*raiz)->esq);
        liberarAVLCurso(&(*raiz)->dir);
        liberarAVLDisc(&(*raiz)->info->disc);
        free((*raiz)->info);
        free(*raiz);
        *raiz = NULL;
    }
}

void liberarAVLNotas(AVLNotas **raiz){
    if(*raiz != NULL){
        liberarAVLNotas(&(*raiz)->esq);
        liberarAVLNotas(&(*raiz)->dir);
        free((*raiz)->info);
        free(*raiz);
        *raiz = NULL;
    }
}

void liberarAVLMatricula(AVLMatricula **raiz){
    if(*raiz != NULL){
        liberarAVLMatricula(&(*raiz)->esq);
        liberarAVLMatricula(&(*raiz)->dir);
        free((*raiz)->info);
        free(*raiz);
        *raiz = NULL;
    }
}

void liberarAlunos(Alunos **aluno) {
    if (*aluno != NULL) {
        liberarAlunos(&(*aluno)->prox);
        liberarAVLMatricula(&(*aluno)->mat);
        liberarAVLNotas(&(*aluno)->nota);
        free(*aluno);
        *aluno = NULL;
    }
}

/*---------------------------------------------------------------------------------------------------------------*/