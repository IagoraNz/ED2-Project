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
int buscacurso(Cursos *curso, int idcurso){
    int enc = 0;
    if (curso != NULL){
        if(curso->idcurso == idcurso)
            enc = 1;
        else{
            if(idcurso < curso->idcurso)
                buscacurso(curso->esq, idcurso);
            else
                buscacurso(curso->dir, idcurso);
        }
    }
    return enc;
}

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
        if(idcurso < (*curso)->idcurso)
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

void validar_cargahoraria(int *validar, int cargahoraria){
    if (cargahoraria % 15 == 0 && (cargahoraria >= 30 && cargahoraria <= 90))
        *validar = 1;
}

void validar_periodo(Cursos *curso, int *validar, int periodo){
    if(periodo >= 1 && periodo <= curso->qntdperiodos)
        *validar = 1;
}

void insere_disc(Disciplina **disc, Disciplina *No, int *insere){
    if (*disc == NULL){
        *disc = No;
        No->esq = NULL;
        No->dir = NULL;
        *insere = 1;
    }
    else if (No->cod_disciplina < (*disc)->cod_disciplina)
        insere_disc(&((*disc)->esq), No, insere);
    else if (No->cod_disciplina > (*disc)->cod_disciplina)
        insere_disc(&((*disc)->dir), No, insere);
}

int caddisc(Cursos **curso, Disciplina *No, int idcurso) {
    int validar_h = 0, validar_p = 0, sucesso = 0;

    // Validação da carga horária
    validar_cargahoraria(&validar_h, No->cargah);
    if (validar_h == 1) {
        if(*curso != NULL){
            if((*curso)->idcurso == idcurso){
                // Validação do período
                validar_periodo(*curso, &validar_p, No->periodo);
                if (validar_p == 1) {
                    // Inserir disciplina
                    insere_disc(&((*curso)->disc), No, &sucesso);
                    if(sucesso != 0)
                        sucesso = 1;
                } 
            }
            else{
                if (idcurso < (*curso)->idcurso)
                    sucesso = caddisc(&(*curso)->esq, No, idcurso);
                else
                    sucesso = caddisc(&(*curso)->dir, No, idcurso);
            }
        }
    }
    
    return sucesso;
}


/*---------------------------------------------------------------------------------------------------------------*/

/* iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
uma disciplina do curso do aluno. */

void inserirMatricula(Matricula **mat, int codigo, int *igual){ //Iago alterei o tipo da função para void e botei a variavel igual por passagem de referencia.
    if(*mat == NULL){
        Matricula *novo = (Matricula *)malloc(sizeof(Matricula));
        novo->coddisc = codigo;
        novo->esq = NULL;
        novo->dir = NULL;
        *mat = novo;
    } 
    else if(codigo < (*mat)->coddisc){
        inserirMatricula(&(*mat)->esq, codigo, igual);
    }
    else if(codigo > (*mat)->coddisc){
        inserirMatricula(&(*mat)->dir, codigo, igual);
    }
    else{
        *igual = -1;
    }
}

void cadmatricula(Alunos **a, int codigo, int mat){ //Alterei a logica de inicio do cadmatricula
    if (*a != NULL){
        if ((*a)->matricula == mat){
            int igual = 0;
            inserirMatricula(&(*a)->mat, codigo, &igual);
        }
        else
            cadmatricula(&(*a)->prox, codigo, mat);
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

// Verifica se existe a disciplina existe na árvore de matrícula do aluno

int busca_disc(Matricula *m, int cod){ // Iago Alterei o nome da função de verificadisc para busca_disc.
    int enc = 0;
    if(m != NULL){
        if(m->coddisc == cod)
            enc = 1;
        else{
            if(cod < m->coddisc)
                enc = busca_disc(m->esq, cod);
            else
                enc = busca_disc(m->dir, cod);
        }
    }
    return enc;
}

int ehfolhamat(Matricula *m){
    int folha = 0;
    if (m != NULL){
        if (m->dir == NULL && m->esq == NULL)
            folha = 1;
    }
    return folha;
}

Matricula* soumfilhomat(Matricula *m){
    Matricula *aux = NULL;
    if (m->esq != NULL)
        aux = m->esq;
    else
        aux = m->dir;
    return aux;
}

Matricula* menorfilhoesqmat(Matricula *m){
    Matricula *aux;
    aux = NULL;
    if (m != NULL){
        if (m->esq != NULL)
            aux = menorfilhoesqmat(m->esq);
    }
    return aux;
}

void rmvmatricula(Matricula **m, int cod){
    if((*m != NULL)){
        if ((*m)->coddisc == cod){
            Matricula *aux, *endfilho, *endmenorfilho;
            if (ehfolhamat(*m)){
                aux = *m;
                *m = NULL;
                free(aux);
            } else if ((endfilho = soumfilhomat(*m)) != NULL){
                *m = endfilho;
                free(endfilho);
            } else {
                endmenorfilho = menorfilhoesqmat((*m)->dir);
                (*m)->coddisc = endmenorfilho->coddisc;
                rmvmatricula(&(*m)->dir, endmenorfilho->coddisc);
            }
        }
        else if(cod < (*m)->coddisc)
            rmvmatricula(&(*m)->esq, cod);
        else
            rmvmatricula(&(*m)->dir, cod);
    }
}

int cadnota_nota(Notas **nota, int cod, int semestre, int notafinal){
    if(*nota != NULL){
        if (cod < (*nota)->coddisc)
            cadnota_nota(&((*nota)->esq), cod, semestre, notafinal);
        else
            cadnota_nota(&((*nota)->dir), cod, semestre, notafinal);
    }
    return 1;
}


int cadnota(Alunos **a, int mat, int cod, int semestre, int notafinal){
    int enc; 
    if ((*a) != NULL){
        enc = busca_disc((*a)->mat, cod);
        if(enc == 1){
            if ((*a)->matricula == mat){ // Coloquei isso por que não estava vendo o uso do "int mat" na função.
                if((*a)->nota == NULL){
                    Notas *novo = (Notas*)malloc(sizeof(Notas));
                    novo->coddisc = cod;
                    novo->semestre = semestre;
                    novo->notafinal = notafinal;
                    novo->esq = NULL;
                    novo->dir = NULL;
                    (*a)->nota = novo;
                    rmvmatricula(&(*a)->mat, cod);
                }
                else{
                    if(cod < (*a)->nota->coddisc)
                        cadnota_nota(&((*a)->nota), cod, semestre, notafinal);
                    else
                        cadnota_nota(&((*a)->nota), cod, semestre, notafinal);
                }
            }
            else
                cadnota(&(*a)->prox, mat, cod, semestre, notafinal);
        }
    }
    return enc; // Iago alterei para retornar o valor de enc para retirar o printf da função cadnota.
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
} // IAGO ARRUME!

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
void exibir_disc(Cursos *curso, int cod_disc, int idcurso) {
    if (curso != NULL) {
        if (curso->idcurso == idcurso) {
            if (curso->disc != NULL) {
                Disciplina *disc = curso->disc;
                while (disc != NULL) {
                    if (disc->cod_disciplina == cod_disc) {
                        printf("Código: %d\n", disc->cod_disciplina);
                        printf("Nome: %s\n", disc->nomedisc);
                        printf("Carga horária: %d\n", disc->cargah);
                        printf("Período: %d\n", disc->periodo);
                        printf("\n");
                    }
                    if (cod_disc < disc->cod_disciplina)
                        disc = disc->esq;
                    else 
                        disc = disc->dir;
                }
            }
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
        if (aluno->matricula == matricula){
            printf("Encontrado!\n");
            exibir_disc_aluno(aluno->mat, cursos, aluno->codcurso);
        }
        else{
            printf("Nao encontrado!\n");
            exibir_disc_aluno_main(aluno->prox, cursos, matricula);
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

void exibirNotasPeriodo(Notas *nota, int periodo){
    if(nota != NULL){
        exibirNotasPeriodo(nota->esq, periodo);
        if(nota->semestre == periodo){
            printf("Codigo: %d\n", nota->coddisc);
            printf("Nota Final: %d\n", nota->notafinal);
            printf("Semestre: %d\n", nota->semestre);
            printf("\n");
        }
        exibirNotasPeriodo(nota->dir, periodo);
    }
}

void notasdiscperiodoaluno(Alunos *a, int periodo, int mat){
    if(a != NULL){
        if(a->matricula == mat){
            exibirNotasPeriodo(a->nota, periodo);
        } 
        else{
            notasdiscperiodoaluno(a->prox, periodo, mat);
        }
    }
} // IAGO ARRUME!

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
    if (disc != NULL)
        if (disc->dir == NULL && disc->esq == NULL)
            folha = 1;
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

Disciplina* menorfilhoesqdisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc != NULL)
        if (disc->esq != NULL)
            aux = menorfilhoesqdisc(disc->esq);
    return aux;
}

int rmvdisc(Disciplina **disc, int cod_disc){
    int remove = 0;
    if ((*disc != NULL)){    
        Disciplina *aux;
        Disciplina *endfilho;
        Disciplina *endmenorfilho;
        if ((*disc)->cod_disciplina == cod_disc){
            if(ehfolhadisc(*disc)){
            aux = *disc;
            *disc = NULL;
            free(aux);
            } else if((endfilho = soumfilhodisc(*disc)) != NULL){
                aux = *disc;
                *disc = endfilho;  
                free(aux); 
            } else {
                endmenorfilho = menorfilhoesqdisc((*disc)->dir);
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
void rmvmatdealuno(Alunos **a, Matricula *m, int matricula, int *coddisc){
    int enc = 0;
    if((*a) != NULL){
        while((*a) != NULL && (*a)->matricula == matricula){
            printf("Aluno %s\n", (*a)->nome);
            *a = (*a)->prox;
        }
    }
    buscamat((*a)->mat, *coddisc, &enc);

    if(enc == 1)
        rmvmatricula(&(*a)->mat, *coddisc);
} // IAGO ARRUME!

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

void exibir_hist_aluno(Alunos *aluno, Cursos *curso, int mat_aluno){
    if (aluno != NULL){
        if (aluno->matricula == mat_aluno){
            printf("Aluno: %s\n", aluno->nome);
            if(curso != NULL){
                if (curso->idcurso == aluno->codcurso){
                    printf("Curso: %s\n", curso->nomecurso);
                    printf("Disciplinas e notas:\n");
                    for (int i = 1; i <= curso->qntdperiodos; i++){
                        printf("Periodo: %d\n", i);
                        exibir_disc_periodo_main(curso, aluno->codcurso, i);
                        exibirNotasPeriodo(aluno->nota, i);
                    }
                }
                else if (aluno->codcurso < curso->idcurso)
                    exibir_hist_aluno(aluno, curso->esq, mat_aluno);
                else
                    exibir_hist_aluno(aluno, curso->dir, mat_aluno);
            }                
        } 
        else
            exibir_hist_aluno(aluno->prox, curso, mat_aluno);
    } 
}

/*---------------------------------------------------------------------------------------------------------------*/

/* extra) Função agregadas, associadas ou adicionais para complementar a coesão do software */

void gerarCodDisciplina(int cargah, int periodo, int *coddisc) {
    // Passo 1: obtendo o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int anoatual = tm.tm_year + 1900;

    // Passo 2: gerando 5 dígitos aleatórios
    srand(time(NULL));
    int num5 = rand() % 100000; // Gera um número entre 0 e 99999

    // Passo 3: gerando o código no formato AAAACCPNNNNN como número inteiro
    *coddisc = anoatual * 100000000 + cargah * 1000000 + periodo * 100000 + num5;
}

void gerarIdCurso(int qntperiodos, int *idcurso) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano = tm.tm_year + 1900;

    srand(time(NULL));
    int num4 = rand() % 10000;

    // Combina os componentes no formato PPPAAAANNNN como um único número inteiro.
    *idcurso = qntperiodos * 100000000 + (qntperiodos * 3) * 1000000 + (qntperiodos * 5) * 10000 + ano * 10000 + num4;
}

void gerarMatriculaAluno(int idcurso, int *matricula) {
    // Passo 1: obtendo o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano = tm.tm_year + 1900;

    // Passo 2: gerando números aleatórios
    srand(time(NULL));
    int num4 = rand() % 10000;  // Gera um número entre 0000 e 9999
    int num3 = rand() % 1000;   // Gera um número entre 000 e 999

    // Passo 3: combinando tudo em um número inteiro no formato AAAANNNNCCCCC
    *matricula = ano * 10000000 + num4 * 100000 + idcurso * 1000 + num3;
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

/*---------------------------------------------------------------------------------------------------------------*/