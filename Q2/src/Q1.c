#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
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

void ValidarCurso(Cursos *cursos, int codcurso, int *enc){
    if(cursos != NULL){
        if(cursos->idcurso == codcurso)
            *enc = 1;
        ValidarCurso(cursos->esq, codcurso, enc);
        ValidarCurso(cursos->dir, codcurso, enc);
    }
}

int cadaluno(Alunos **a, Cursos *curso, int mat, char *nome, int codcurso) {
    int sucesso = 0, enc = 0;
    
    // Se a lista estiver vazia ou o ponto de inserção for alcançado
    if (*a == NULL) {
        ValidarCurso(curso, codcurso, &enc);
        if (enc == 1) {
            *a = criar_aluno(mat, nome, codcurso);
            sucesso = 1;
        }
    }
    else {
        if ((*a)->matricula == mat)
            sucesso = 0; 
        // Verifica se o novo aluno deve ser inserido antes do aluno atual (ordenado por nome)
        else if (strcmp(nome, (*a)->nome) < 0) {
            ValidarCurso(curso, codcurso, &enc);
            if (enc == 1) {
            Alunos *novo = criar_aluno(mat, nome, codcurso);  
            novo->prox = *a; 
            *a = novo;
            sucesso = 1;
            }
        }
        else 
            sucesso = cadaluno(&(*a)->prox, curso, mat, nome, codcurso);
    }
    
    return sucesso; 
}

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

int cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos){
    int sucesso = 0;
    if(*curso == NULL){
        Cursos *novo = (Cursos*)malloc(sizeof(Cursos));
        novo->idcurso = idcurso;
        strcpy(novo->nomecurso, nomecurso);
        novo->qntdperiodos = qntperiodos;
        novo->disc = NULL;
        novo->dir = NULL;
        novo->esq = NULL;
        *curso = novo;
        sucesso = 1;
    }
    else{
        if(idcurso == (*curso)->idcurso)
            sucesso = 0;
        else if(idcurso < (*curso)->idcurso)
            sucesso = cadcurso(&((*curso)->esq), idcurso, nomecurso, qntperiodos);
        else
            sucesso = cadcurso(&((*curso)->dir), idcurso, nomecurso, qntperiodos);
    }
    return sucesso;
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

void validar_cargahoraria(int *validar, int cargahoraria) {
    *validar = 0; // Inicializa como 0
    if (cargahoraria % 15 == 0 && (cargahoraria >= 30 && cargahoraria <= 90))
        *validar = 1;
}

void validar_periodo(Cursos *curso, int *validar, int periodo) {
    *validar = 0; // Inicializa como 0
    if (periodo >= 1 && periodo <= curso->qntdperiodos)
        *validar = 1;
}

void insere_disc(Disciplina **disc, Disciplina *No, int *insere) {
    if (*disc == NULL) {
        *disc = No;
        No->esq = NULL;
        No->dir = NULL;
        *insere = 1; // Insere com sucesso
    }
    else if (No->cod_disciplina == (*disc)->cod_disciplina)
        *insere = 0; // Disciplina já existe
    else if (No->cod_disciplina < (*disc)->cod_disciplina)
        insere_disc(&((*disc)->esq), No, insere); // Vai para a esquerda
    else
        insere_disc(&((*disc)->dir), No, insere); // Vai para a direita
}

int caddisc(Cursos **curso, Disciplina *No, int idcurso) {
    int validar_h = 0, validar_p = 0, sucesso = 0;
    
    // Validação da carga horária
    validar_cargahoraria(&validar_h, No->cargah);
    
    if(validar_h == 1){
        if(*curso != NULL){
            if((*curso)->idcurso == idcurso){
                // Validação do período
                validar_periodo(*curso, &validar_p, No->periodo);
                
                if(validar_p == 1){
                    // Inserir disciplina
                    insere_disc(&((*curso)->disc), No, &sucesso);
                }
            }
            else{
                // Recorre na árvore de cursos
                if(idcurso < (*curso)->idcurso)
                    sucesso = caddisc(&(*curso)->esq, No, idcurso);
                else
                    sucesso = caddisc(&(*curso)->dir, No, idcurso);
            }
        }
    }
    
    return sucesso; // Retorna 1 se a disciplina foi cadastrada, 0 caso contrário
}

/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */

void inserirMatricula(Matricula **mat, int codigo, int *igual){
    if(*mat == NULL){
        Matricula *novo = (Matricula*)malloc(sizeof(Matricula));
        novo->coddisc = codigo;
        novo->esq = NULL;
        novo->dir = NULL;
        *mat = novo;
        *igual = 1;
    } 
    else if(codigo < (*mat)->coddisc)
        inserirMatricula(&(*mat)->esq, codigo, igual);
    else if(codigo > (*mat)->coddisc)
        inserirMatricula(&(*mat)->dir, codigo, igual);
    else
        *igual = 0;
}

int cadmatricula(Alunos **a, int codigo, int mat){
    int igual = 0;
    if (*a != NULL){
        if ((*a)->matricula == mat){
            inserirMatricula(&(*a)->mat, codigo, &igual);
        }
        else
            igual = cadmatricula(&(*a)->prox, codigo, mat);
    }
    return igual;
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

// Verifica se existe a disciplina existe na árvore de matrícula do aluno

void busca_disc(Matricula *m, int cod, int *enc){ 
    if(m != NULL){
        if(m->coddisc == cod)
            *enc = 1;
        else if(cod < m->coddisc)
            busca_disc(m->esq, cod, enc);
        else
            busca_disc(m->dir, cod, enc);
    }
}

int ehfolhamat(Matricula *m){
    return (m->esq == NULL && m->dir == NULL);
}

Matricula* soumfilhomat(Matricula *m){
    Matricula *aux;
    aux = NULL;
    if (m->esq == NULL)
        aux = m->dir;
    else if (m->dir == NULL)
        aux = m->esq;

    return aux;
}

Matricula* menorfilhoesqmat(Matricula *m) {
    Matricula *aux;
    aux = NULL;
    if (m){
        aux = menorfilhoesqmat(m->esq);
        if (!aux)
            aux = m;
    }
    return aux;
}

void rmvmatricula(Matricula **m, int cod, int *remove) {
    if (*m != NULL) {
        // Se encontrou o nó a ser removido
        if ((*m)->coddisc == cod) {
            Matricula *aux;
            
            // Caso 1: O nó é uma folha (sem filhos)
            if (ehfolhamat(*m)) {
                aux = *m;
                free(aux);
                *m = NULL;
                *remove = 1;
            } 
            // Caso 2: O nó tem apenas um filho
            else if ((aux = soumfilhomat(*m)) != NULL) {
                Matricula *temp;
                temp = *m;
                free(temp);
                *m = aux;  // Substitui o nó pelo seu único filho
                *remove = 1;
            } 
            else {
                Matricula *menorfilho = menorfilhoesqmat((*m)->dir);
                (*m)->coddisc = menorfilho->coddisc;
                rmvmatricula(&(*m)->dir, menorfilho->coddisc, remove);
            }
        } 
        // Se o código é menor, continua na subárvore esquerda
        else if (cod < (*m)->coddisc)
            rmvmatricula(&(*m)->esq, cod, remove);
        // Se o código é maior, continua na subárvore direita
        else
            rmvmatricula(&(*m)->dir, cod, remove);
    }
}

int cadnota_nota(Notas **nota, int cod, int semestre, float notafinal){
    int sucesso = 1;
    if (*nota == NULL){
        Notas *novo = (Notas*)malloc(sizeof(Notas));
        novo->coddisc = cod;
        novo->semestre = semestre;
        novo->notafinal = notafinal;
        novo->esq = NULL;
        novo->dir = NULL;
        *nota = novo;
    }
    else{
        if (cod == (*nota)->coddisc)
            sucesso = 0;
        else if(cod < (*nota)->coddisc)
            sucesso = cadnota_nota(&((*nota)->esq), cod, semestre, notafinal);
        else
            sucesso = cadnota_nota(&((*nota)->dir), cod, semestre, notafinal);
    }
    return sucesso;
}

int cadnota(Alunos **a, int mat, int cod, int semestre, float notafinal) {
    int enc = 0, remove = 0;
    if (*a != NULL) {
        if ((*a)->matricula == mat) {
            int enc_disc = 0;
            busca_disc((*a)->mat, cod, &enc_disc);
            if (enc_disc == 1) {
                if (cadnota_nota(&(*a)->nota, cod, semestre, notafinal) == 1){
                    rmvmatricula(&(*a)->mat, cod, &remove);
                    enc = 1;
                }
            }
        } else
            enc = cadnota(&(*a)->prox, mat, cod, semestre, notafinal);
    }
    
    return enc; // Retorna 1 se a nota foi cadastrada, 0 caso contrário
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

void alunosporcurso(Alunos *a, int codcurso){
    if(a != NULL){
        if(a->codcurso == codcurso){
            printf("Matricula: %d\n", a->matricula);
            printf("Nome: %s\n", a->nome);
            printf("\n");
        }
        alunosporcurso(a->prox, codcurso);
    }
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
        printf("Codigo: %d\n", disc->cod_disciplina);
        printf("Nome: %s\n", disc->nomedisc);
        printf("Carga horaria: %d\n", disc->cargah);
        printf("Periodo: %d\n", disc->periodo);
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
            printf("Codigo: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horaria: %d\n", disc->cargah);
            printf("Periodo: %d\n", disc->periodo);
            printf("\n");
        }
        exibir_disc_periodo(disc->dir, periodo);
    }
}

void exibir_disc_periodo_main(Cursos *curso, int idcurso, int periodo){
    if(curso != NULL){
        if(curso->idcurso == idcurso)
            exibir_disc_periodo(curso->disc, periodo);
        else if(idcurso < curso->idcurso)
            exibir_disc_periodo_main(curso->esq, idcurso, periodo);
        else
            exibir_disc_periodo_main(curso->dir, idcurso, periodo);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */

void exibir_disciplinas(Disciplina *disc, int cod_disc) {
    if (disc != NULL) {
        if (disc->cod_disciplina == cod_disc) {
            printf("Codigo: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horaria: %d\n", disc->cargah);
            printf("Periodo: %d\n", disc->periodo);
            printf("\n");
        }
        else if (cod_disc < disc->cod_disciplina)
            exibir_disciplinas(disc->esq, cod_disc);
        else
            exibir_disciplinas(disc->dir, cod_disc);
    }
}

void exibir_disc(Cursos *curso, int cod_disc, int idcurso) {
    if (curso != NULL) {
        if (curso->idcurso == idcurso) {
            if (curso->disc != NULL)
                exibir_disciplinas(curso->disc, cod_disc);
        }
        else if (idcurso < curso->idcurso)
            exibir_disc(curso->esq, cod_disc, idcurso);
        else
            exibir_disc(curso->dir, cod_disc, idcurso);
    }
}

void exibir_disc_aluno(Matricula *mat, Cursos *cursos, int codcurso){
    if (mat != NULL){
        exibir_disc(cursos, mat->coddisc, codcurso);
        exibir_disc_aluno(mat->esq, cursos, codcurso);
        exibir_disc_aluno(mat->dir, cursos, codcurso);
    }
}

void exibir_disc_aluno_main(Alunos *aluno, Cursos *cursos, int matricula){
    if (aluno != NULL){
        if (aluno->matricula == matricula)
            exibir_disc_aluno(aluno->mat, cursos, aluno->codcurso);
        else
            exibir_disc_aluno_main(aluno->prox, cursos, matricula);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

void exibirNotasPeriodo(Notas *nota, int periodo){
    if(nota != NULL){
        if(nota->semestre == periodo){
            printf("Codigo: %d\n", nota->coddisc);
            printf("Nota Final: %.2f\n", nota->notafinal);
            printf("Semestre: %d\n", nota->semestre);
            printf("\n");
        }
        exibirNotasPeriodo(nota->esq, periodo);
        exibirNotasPeriodo(nota->dir, periodo);
    }
}

void notasdiscperiodoaluno(Alunos *a, int periodo, int mat){
    if(a != NULL){
        if(a->matricula == mat)
            exibirNotasPeriodo(a->nota, periodo);
        else
            notasdiscperiodoaluno(a->prox, periodo, mat);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */
Cursos* buscar_curso(Cursos *curso, int idcurso) {
    Cursos *aux;
    aux = NULL;
    if (curso != NULL) {
        if (curso->idcurso == idcurso)
            aux = curso;
        else if (idcurso < curso->idcurso)
            aux = buscar_curso(curso->esq, idcurso);
        else
            aux = buscar_curso(curso->dir, idcurso);
    }
    return aux;
}

Disciplina* buscar_disciplina(Disciplina *d, int coddisc) {
    Disciplina *resultado = NULL;
    if (d != NULL) {
        if (d->cod_disciplina == coddisc)
            resultado = d;
        else if (coddisc < d->cod_disciplina) 
            resultado = buscar_disciplina(d->esq, coddisc);
        else
            resultado = buscar_disciplina(d->dir, coddisc);
    }
    return resultado;
}

Notas* buscar_nota(Notas *nota, int coddisc) {
    Notas *resultado = NULL;
    if (nota != NULL) {
        if (nota->coddisc == coddisc)
            resultado = nota;
        else if (coddisc < nota->coddisc) 
            resultado = buscar_nota(nota->esq, coddisc);
        else 
            resultado = buscar_nota(nota->dir, coddisc);
    }
    return resultado;
}

void notadiscporaluno(Alunos *aluno, Cursos *curso, int matricula, int coddisc) {
    Cursos *c = NULL;
    Disciplina *d = NULL;
    Notas *nota = NULL;
    int sucesso = 0;
    if (aluno != NULL) {
        if (aluno->matricula == matricula) {
            c = buscar_curso(curso, aluno->codcurso);
            if (c != NULL) {
                d = buscar_disciplina(c->disc, coddisc);  // Usando a função recursiva de disciplina
                if (d != NULL) {
                    nota = buscar_nota(aluno->nota, coddisc);  // Usando a função recursiva de nota
                    if (nota != NULL){
                        // printf("Disciplina: %s\n", d->nomedisc);
                        // printf("Nota: %.2f\n", nota->notafinal);
                        // printf("Periodo: %d\n", d->periodo);
                        // printf("Carga Horaria: %d\n", d->cargah);
                        sucesso = 1;
                    }
                }
            }
        } else {
            notadiscporaluno(aluno->prox, curso, matricula, coddisc);  // Recorre ao próximo aluno
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */

int ehfolhadisc(Disciplina *disc){
    return (disc->esq == NULL && disc->dir == NULL);
}

Disciplina* soumfilhodisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc->dir == NULL)
        aux = disc->esq;
    else if (disc->esq == NULL)
        aux = disc->dir;
    return aux;
}

Disciplina* menorfilhoesqdisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc != NULL)
        aux = menorfilhoesqdisc(disc->esq);
        if (!aux)
            aux = disc;
    return aux;
}

void rmvdisc(Disciplina **disc, int cod_disc, int *remove){
    if ((*disc != NULL)){    
        Disciplina *aux;
        Disciplina *endfilho;
        Disciplina *endmenorfilho;
        if ((*disc)->cod_disciplina == cod_disc){
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
                (*disc)->cod_disciplina = endmenorfilho->cod_disciplina;
                (*disc)->cargah = endmenorfilho->cargah;
                (*disc)->periodo = endmenorfilho->periodo;
                strcpy((*disc)->nomedisc, endmenorfilho->nomedisc);
                rmvdisc(&(*disc)->dir, endmenorfilho->cod_disciplina, remove);
            }
            *remove = 1;
        }
        else if (cod_disc < (*disc)->cod_disciplina)
            rmvdisc(&(*disc)->esq, cod_disc, remove);
        else 
            rmvdisc(&(*disc)->dir, cod_disc, remove);
    }
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
                rmvdisc(&(*cursos)->disc, cod_disc, &remove);   
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
int rmvmatdealuno(Alunos **a, int matricula, int coddisc){
    int remove = 0;
    if(*a != NULL){
        if((*a)->matricula == matricula)
            rmvmatricula(&(*a)->mat, coddisc, &remove);
        else
            remove = rmvmatdealuno(&(*a)->prox, matricula, coddisc);
    }
    return remove;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

void exibir_disciplina(Disciplina *d, int cod_disciplina) {
    if(d != NULL) {
        if(d->cod_disciplina == cod_disciplina) 
            printf("Disciplina: %s\n", d->nomedisc);
        else if(cod_disciplina < d->cod_disciplina)
            exibir_disciplina(d->esq, cod_disciplina);
        else
            exibir_disciplina(d->dir, cod_disciplina);
    }
}

void exibir_notas(Notas *nota, Disciplina *d, int periodo) {
    if(nota != NULL) {
        if (nota->semestre == periodo) {
            exibir_disciplina(d, nota->coddisc);
            printf("Nota: %.2f\n", nota->notafinal);
            printf("Semestre: %d\n\n", nota->semestre);
        }
        exibir_notas(nota->esq, d, periodo);
        exibir_notas(nota->dir, d, periodo);
    }
}


int exibir_nome_curso(Cursos *c, int idcurso){
    int qntperiodos = 0;
    if(c != NULL){
        if(c->idcurso == idcurso){
            printf("Curso: %s\n", c->nomecurso);
            qntperiodos = c->qntdperiodos;
        }
        else if(idcurso < c->idcurso)
            qntperiodos = exibir_nome_curso(c->esq, idcurso);
        else
            qntperiodos = exibir_nome_curso(c->dir, idcurso);
    }
    return qntperiodos;
}

void exibir_hist_aluno(Alunos *a, Cursos *c, int matricula){
    if(a != NULL){
        if(a->matricula == matricula){
            printf("Aluno: %s\n", a->nome);
            printf("Matricula: %d\n", a->matricula);
            int qntperiodos = 0;
            qntperiodos = exibir_nome_curso(c, a->codcurso);
            printf("Historico:\n");
            for (int i = 1; i <= qntperiodos; i++)
                exibir_notas(a->nota, c->disc, i);
        }
        else
            exibir_hist_aluno(a->prox, c, matricula);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* extra) Função agregadas, associadas ou adicionais para complementar a coesão do software */

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

void exibiralunos(Alunos *a){
    if(a != NULL){
        printf("Matricula: %d\n", a->matricula);
        printf("Nome: %s\n", a->nome);
        printf("Codigo do Curso: %d\n", a->codcurso);
        printf("\n");
        exibiralunos(a->prox);
    }
}

void liberar_notas(Notas *n){
    if(n != NULL){
        liberar_notas(n->esq);
        liberar_notas(n->dir);
        free(n);
        n = NULL;
    }
}

void liberar_matriculas(Matricula *m){
    if(m != NULL){
        liberar_matriculas(m->esq);
        liberar_matriculas(m->dir);
        free(m);
        m = NULL;
    }
}

void liberar_disciplinas(Disciplina *d){
    if(d != NULL){
        liberar_disciplinas(d->esq);
        liberar_disciplinas(d->dir);
        free(d);
        d = NULL;
    }
}

void liberar_alunos(Alunos *a){
    if(a != NULL){
        liberar_alunos(a->prox);
        liberar_notas(a->nota);
        liberar_matriculas(a->mat);
        free(a);
        a = NULL;
    }
}

void liberar_cursos(Cursos **c){
    if(*c != NULL){
        liberar_cursos(&(*c)->esq);
        liberar_cursos(&(*c)->dir);
        liberar_disciplinas((*c)->disc);
        free(*c);
        *c = NULL;
    }
}

/*---------------------------------------------------------------------------------------------------------------*/