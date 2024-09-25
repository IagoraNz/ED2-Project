#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Q1.h"

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

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

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
    if(c != NULL){
        exibircurso(c->esq);
        printf("%d %s %d\n", c->idcurso, c->nomecurso, c->qntdperiodos);
        exibircurso(c->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90. */

void validar_cargahoraria(int *validar, int cargahoraria){
    if (cargahoraria % 15 == 0 && (cargahoraria >= 30 && cargahoraria <= 90))
        *validar = 1;
}

void validar_periodo(Cursos *curso,int *validar, int periodo){
    if (curso->qntdperiodos < periodo && periodo >= 1)
        *validar = 1;
}

int insere_disc(Disciplina **disc, Disciplina *No){
    int insere = 0;
    if (*disc == NULL){
        *disc = No;
        No->esq = NULL;
        No->dir = NULL;
    }
    else if (No->cod_disciplina < (*disc)->cod_disciplina)
            insere_disc(&((*disc)->esq), No);
    else if (No->cod_disciplina > (*disc)->cod_disciplina)
            insere_disc(&((*disc)->dir), No);
    else
        insere = 1;
    
    return insere;
}

int caddisc(Cursos **curso, Disciplina *No, int idcurso){
    int validar_h = 0, validar_p = 0, validar_cod = 0;
    // Função para validar se a carga horaria e múltiplo de 15 é se varia entre 30 e 90.
    validar_cargahoraria(&validar_h, No->cargah);
    if(validar_h == 1){
        if (*curso != NULL){
            if((*curso)->idcurso == idcurso){
                // Função para validar se o periodo está no intervalo do periodo do curso.
                validar_periodo(*curso, &validar_p, No->periodo);
                if (validar_p == 1)
                    validar_cod = insere_disc(&((*curso)->disc), No);
            }
            else{
                if(idcurso < (*curso)->idcurso)
                    caddisc((*curso)->esq, No, idcurso);
                else
                    caddisc((*curso)->dir, No, idcurso);
            }
        }
    }

    return validar_cod;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */

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

void exibirmat(Matricula *m){
    if(m != NULL){
        exibirmat(m->esq);
        printf("%d\n", m->coddisc);
        exibirmat(m->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas.*/

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

Matricula* menorDireita(Matricula *no, Matricula **filho){
    Matricula *aux;
    aux = NULL;

    if(no != NULL){
        aux = menorDireita(no->esq, filho);
        if(!aux){
            aux = no;
            *filho = no->dir;
        }
    }
    return aux;
}

void rmvmatricula(Matricula **m, int cod){
    int temp;

    if((*m)){
        if(cod < (*m)->coddisc)
            rmvmatricula(&(*m)->esq, cod);
        else if(cod > (*m)->coddisc)
            rmvmatricula(&(*m)->dir, cod);
        else{
            Matricula *aux = *m;
            if((*m)->esq == NULL && (*m)->dir == NULL){
                free(aux);
                *m = NULL;
            }
            /* Só tem o filho da direita */
            else if((*m)->esq == NULL){
                (*m) = (*m)->dir;
                aux->dir = NULL;
                free(aux);
                aux = NULL;
            }
            /* Só tem o filho da esquerda */
            else if((*m)->dir == NULL){
                (*m) = (*m)->esq;
                aux->esq = NULL;
                free(aux);
                aux = NULL;
            }
            /* O nó mais a esquerda da sub-árvore à direita */
            else {
                Matricula *no = NULL;
                Matricula *subs = (*m)->dir;

                while(subs->esq != NULL){
                    no = subs;
                    subs = subs->esq;
                }

                if(no != NULL){
                    no->esq = subs->dir;
                } 
                else{
                    (*m)->dir = subs->dir;
                }

                (*m)->coddisc = subs->coddisc;
                free(subs);
            }
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

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

/*---------------------------------------------------------------------------------------------------------------*/

/* vii) Mostrar todos os cursos do Campus. */ 
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

/*---------------------------------------------------------------------------------------------------------------*/

/* viii) Mostrar todas as disciplinas de um determinado curso. */
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

/*---------------------------------------------------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */
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
    } else
        exibir_disc_aluno(aluno->prox, cursos, matricula);
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

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

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */
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

/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */
int ehfolhadisc(Disciplina *disc){
    int folha = 0;
    if (disc != NULL){
        if (disc->dir == NULL && disc->esq == NULL)
            folha = 1;
    }
    return folha;
}

Disciplina* soumfilhodisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc != NULL){
        if (disc->dir != NULL)
            aux = disc->dir;
        else
            aux = disc->esq;
    }
    return aux;
}

Disciplina* menorfilhoesq(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc != NULL){
        if (disc->esq != NULL){
            aux = menorfilhoesq(disc->esq);
        }
    }
    return aux;
}

int rmvdisc(Disciplina **disc, int cod_disc){
    int remove = 0;
    if ((*disc != NULL)){    
        Disciplina *aux;
        Disciplina *endfilho;
        Disciplina *endmenorfilho;
        if ((*disc)->cod_disciplina == cod_disc){
            if(ehfolhadisc(disc)){
            aux = *disc;
            *disc = NULL;
            free(aux);
            } else if((endfilho = soumfilhodisc(*disc)) != NULL){
                aux = *disc;
                *disc = endfilho;  
                free(aux); 
            } else {
                endmenorfilho = menorfilhoesq((*disc)->dir);
                (*disc)->cod_disciplina = endmenorfilho->cod_disciplina;
                (*disc)->cargah = endmenorfilho->cargah;
                (*disc)->periodo = endmenorfilho->periodo;
                strcpy((*disc)->nomedisc, endmenorfilho->nomedisc);
                rmvdisc(&(*disc)->dir, endmenorfilho->cod_disciplina);
            }
            remove = 1;
        }
        else if ((*disc)->cod_disciplina < cod_disc)
            remove = rmvdisc(&(*disc)->dir, cod_disc);
        else 
            remove = rmvdisc(&(*disc)->esq, cod_disc);
    }
    return remove;
}

void validar_rmv_disciplina(Alunos *alunos, int cod_disc, int *validar_disc){
    int enc = 0;
    if(alunos != NULL){
        buscamat(alunos->mat, cod_disc, &enc);
        if(enc != 0)
            *validar_disc = 1;
        validar_rmv_disciplina(alunos->prox, cod_disc, validar_disc);
    }
}

int rmvdisc_curso(Cursos **cursos, Alunos *alunos, int idcurso, int cod_disc){
    int remove = 0, validar_disc = 0;
    if ((*cursos)){
        validar_rmv_disciplina(alunos, cod_disc, &validar_disc);
        if (validar_disc != 0){
            if ((*cursos)->idcurso == idcurso)
                remove = rmvdisc(&(*cursos)->disc, cod_disc);   
            else if (idcurso < (*cursos)->idcurso)
                remove = rmvdisc_curso(&(*cursos)->esq, alunos, idcurso, cod_disc);
            else
                remove = rmvdisc_curso(&(*cursos)->dir, alunos, idcurso, cod_disc);
        }
    }
    return remove;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. */
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

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

/*---------------------------------------------------------------------------------------------------------------*/

/* extra) Função agregadas, associadas ou adicionais para complementar a coesão do software */

/*---------------------------------------------------------------------------------------------------------------*/