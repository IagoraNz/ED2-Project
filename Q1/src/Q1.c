/*---------------------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

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

/* 
    summary
        Função responsável por converter o nome do aluno para maiúsculo
    param
        nome: nome do aluno
*/
void converternome(char *nome){
    int i = 0;
    while (nome[i] != '\0') {
        nome[i] = toupper(nome[i]); // Converte para maiúscula com a função toupper
        i++; // Incrementa o índice para o próximo caractere
    }
}

/* 
    summary
        Função responsável por criar um novo aluno
    param
        mat: matrícula do aluno
        nome: mome do aluno
        codcurso: código do curso do aluno
    return
        Retorna o novo aluno
*/
Alunos* criaraluno(int mat, char *nome, int codcurso){
    // Aloca memória para o novo aluno
    Alunos *novo = (Alunos*) malloc(sizeof(Alunos));
    // Atribui os valores para o novo aluno
    novo->matricula = mat;
    char *aux_nome = strdup(nome);  
    converternome(aux_nome);       
    strcpy(novo->nome, aux_nome);
    novo->codcurso = codcurso;
    // Inicializa os ponteiros
    novo->nota = NULL;
    novo->mat = NULL;
    novo->prox = NULL;
    return novo;
}

/* 
    summary
        Função responsável por validar o curso
    param
        cursos: árvore de cursos
        codcurso: código do curso
        enc: ponteiro para a variável de controle
*/
void validacurso(Cursos *cursos, int codcurso, int *enc){
    if(cursos != NULL){
        // Se o curso existe, enc = 1
        if(cursos->idcurso == codcurso)
            *enc = 1;
        // Se o curso não existe, recorre na árvore
        validacurso(cursos->esq, codcurso, enc);
        validacurso(cursos->dir, codcurso, enc);
    }
}

/* 
    summary
        Função responsável por cadastrar o aluno
    param
        aluno: lista de alunos
        curso: árvore de cursos
        mat: matrícula do aluno
        nome: nome do aluno
        codcurso: código do curso do aluno
    return
        Retorna 1 se o aluno foi cadastrado, 0 caso contrário
*/
int cadaluno(Alunos **aluno, Cursos *curso, int mat, char *nome, int codcurso){
    int sucesso = 0, enc = 0;
    
    // Se a lista estiver vazia ou o ponto de inserção for alcançado
    if(*aluno == NULL){
        validacurso(curso, codcurso, &enc);
        if(enc == 1){ // Se o curso existe, insere o aluno
            *aluno = criaraluno(mat, nome, codcurso);
            sucesso = 1;
        }
    }
    else{
        // Verifica se a matrícula já existe, se sim, não insere
        if((*aluno)->matricula == mat)
            sucesso = 0; 
        // Verifica se o novo aluno deve ser inserido antes do aluno atual (ordenado por nome)
        else if(strcmp(nome, (*aluno)->nome) < 0){
            validacurso(curso, codcurso, &enc); // Verifica se o curso existe
            if(enc == 1){ // Se o curso existe, insere o aluno
                Alunos *novo = criaraluno(mat, nome, codcurso);  
                novo->prox = *aluno; 
                *aluno = novo;
                sucesso = 1;
            }
        }
        else // Recorre na lista caso contrário
            sucesso = cadaluno(&(*aluno)->prox, curso, mat, nome, codcurso);
    }
    
    return sucesso; 
}

/*---------------------------------------------------------------------------------------------------------------*/

/* ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
as disciplinas para permitir o cadastro do curso. */

/* 
    summary
        Função responsável por cadastrar o curso
    param
        curso: árvore de cursos
        idcurso: código do curso
        nomecurso: nome do curso como constante
        qntperiodos: quantidade de períodos do curso
*/
int cadcurso(Cursos **curso, int idcurso, const char *nomecurso, int qntperiodos){
    int sucesso = 0;
    // Se a árvore estiver vazia, insere o curso
    if(*curso == NULL){
        // Aloca memória para o novo curso
        Cursos *novo = (Cursos*)malloc(sizeof(Cursos));
        // Atribui os valores para o novo curso
        novo->idcurso = idcurso;
        strcpy(novo->nomecurso, nomecurso);
        novo->qntdperiodos = qntperiodos;
        // Inicializa os ponteiros
        novo->disc = NULL;
        novo->dir = NULL;
        novo->esq = NULL;
        *curso = novo;
        sucesso = 1;
    }
    else{ // Se a árvore não estiver vazia, recorre na árvore
        if(idcurso == (*curso)->idcurso) // Se o curso já existe, não insere
            sucesso = 0;
        else if(idcurso < (*curso)->idcurso) // Se o id do curso é menor, vai para a esquerda
            sucesso = cadcurso(&((*curso)->esq), idcurso, nomecurso, qntperiodos);
        else // Se o id do curso é maior, vai para a direita
            sucesso = cadcurso(&((*curso)->dir), idcurso, nomecurso, qntperiodos);
    }
    return sucesso;
}



/*---------------------------------------------------------------------------------------------------------------*/

/* iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90. */

/* 
    summary
        Função responsável por validar a carga horária
    param
        validar: ponteiro para a variável de controle
        cargahoraria: carga horária da disciplina
*/
void validarCargahoraria(int *validar, int cargahoraria){
    *validar = 0;
    // Se a carga horária for múltiplo de 15 e estiver entre 30 e 90, a carga horária é válida
    if (cargahoraria % 15 == 0 && (cargahoraria >= 30 && cargahoraria <= 90)) 
        *validar = 1;
}

/* 
    summary
        Função responsável por validar o período
    param
        curso: árvore de cursos
        validar: ponteiro para a variável de controle
        periodo: período da disciplina
*/
void validarPeriodo(Cursos *curso, int *validar, int periodo){
    *validar = 0;
    // Se o período estiver entre 1 e a quantidade máxima de períodos do curso, o período é válido
    if (periodo >= 1 && periodo <= curso->qntdperiodos)
        *validar = 1;
}

/* 
    summary
        Função responsável por inserir a disciplina na árvore de disciplinas
    param
        disc: árvore de disciplinas
        No: disciplina a ser inserida
        insere: ponteiro para a variável de controle
*/
void inseredisc(Disciplina **disc, Disciplina *No, int *insere){
    // Se a árvore de disciplinas estiver vazia, insere a disciplina
    if(*disc == NULL){
        *disc = No;
        No->esq = NULL;
        No->dir = NULL;
        *insere = 1; // Insere com sucesso
    }
    // Se a árvore de disciplinas não estiver vazia, recorre na árvore
    else if (No->cod_disciplina == (*disc)->cod_disciplina)
        *insere = 0; // Disciplina já existe
    else if (No->cod_disciplina < (*disc)->cod_disciplina)
        inseredisc(&((*disc)->esq), No, insere); // Recorre na subárvore esquerda
    else
        inseredisc(&((*disc)->dir), No, insere); // Recorre na subárvore direita
}

/* 
    summary
        Função principal responsável por cadastrar a disciplina
    param
        curso: árvore de cursos
        No: disciplina a ser inserida
        idcurso: código do curso
    return
        Retorna 1 se a disciplina foi cadastrada, 0 caso contrário
*/
int caddisc(Cursos **curso, Disciplina *No, int idcurso) {
    int validar_h = 0, validar_p = 0, sucesso = 0;
    
    // Validação da carga horária
    validarCargahoraria(&validar_h, No->cargah);
    
    if(validar_h == 1){
        if(*curso != NULL){
            if((*curso)->idcurso == idcurso){
                // Validação do período
                validarPeriodo(*curso, &validar_p, No->periodo);
                
                if(validar_p == 1){
                    // Inserir disciplina
                    inseredisc(&((*curso)->disc), No, &sucesso);
                }
            }
            else{
                // Recorre na árvore de cursos para a direita ou esquerda
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

/* 
    summary
        Função responsável por inserir a matrícula na árvore de matrículas
    param
        mat: árvore de matrículas
        codigo: código da disciplina
        igual: ponteiro para a variável de controle
*/
void inserirMatricula(Matricula **mat, int codigo, int *igual){
    // Se a árvore de matrículas estiver vazia, insere a matrícula
    if(*mat == NULL){
        Matricula *novo = (Matricula*)malloc(sizeof(Matricula));
        novo->coddisc = codigo;
        novo->esq = NULL;
        novo->dir = NULL;
        *mat = novo;
        *igual = 1;
    } 
    // Se a árvore de matrículas não estiver vazia, recorre na árvore
    else if(codigo < (*mat)->coddisc)
        inserirMatricula(&(*mat)->esq, codigo, igual);
    else if(codigo > (*mat)->coddisc)
        inserirMatricula(&(*mat)->dir, codigo, igual);
    else
        *igual = 0;
}

/* 
    summary
        Função responsável por cadastrar a matrícula
    param
        aluno: lista de alunos
        codigo: código da disciplina
        mat: matrícula do aluno
    return
        Retorna 1 se a matrícula foi cadastrada, 0 caso contrário
*/
int cadmatricula(Alunos **aluno, int codigo, int mat){
    int igual = 0;
    if(*aluno != NULL){
        if((*aluno)->matricula == mat){
            inserirMatricula(&(*aluno)->mat, codigo, &igual);
        }
        else
            igual = cadmatricula(&(*aluno)->prox, codigo, mat);
    }
    return igual;
}

/* 
    summary
        Função responsável por buscar a matrícula
    param
        mat: árvore de matrículas
        codigo: código da disciplina
        enc: ponteiro para a variável de controle
*/
void buscamat(Matricula *mat, int codigo, int *enc){
    if(mat == NULL)
        *enc = 0;
    else{
        if(mat->coddisc == codigo)
            *enc = 1;
        else{
            if(codigo < mat->coddisc)
                buscamat(mat->esq, codigo, enc);
            else
                buscamat(mat->dir, codigo, enc);
        }
    }
}

/* 
    summary
        Função responsável por exibir as matrículas
    param
        mat: árvore de matrículas
*/
void exibirmat(Matricula *mat){
    if(mat != NULL){
        exibirmat(mat->esq);
        printf("%d\n", mat->coddisc);
        exibirmat(mat->dir);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
árvore de notas.*/

/* 
    summary
        Função responsável por buscar a disciplina
    param
        mat: árvore de matrículas
        cod: código da disciplina
        enc: ponteiro para a variável de controle
*/
void busca_disc(Matricula *mat, int cod, int *enc){ 
    if(mat != NULL){
        if(mat->coddisc == cod)
            *enc = 1;
        else if(cod < mat->coddisc)
            busca_disc(mat->esq, cod, enc);
        else
            busca_disc(mat->dir, cod, enc);
    }
}

/* 
    summary
        Função responsável por verificar se o nó de matrícula é uma folha
    param
        mat: matrícula
    return
        Retorna 1 se o nó é uma folha, 0 caso contrário
*/
int ehfolhamat(Matricula *mat){
    return (mat->esq == NULL && mat->dir == NULL);
}

/* 
    summary
        Função responsável por verificar se o nó de matrícula tem apenas um filho
    param
        mat: matrícula
    return
        Retorna o nó filho
*/
Matricula* soumfilhomat(Matricula *mat){
    Matricula *aux;
    aux = NULL;
    /*
        operation
            Verifica se o nó tem apenas um filho
        example
               15
              /  \
            10   NULL
            mat->esq = 10, que é diferente de NULL
            mat->dir = NULL, que é igual a NULL, então:
            aux = mat->esq = 10
    */
    if(mat->esq == NULL) 
        aux = mat->dir;
    else if (mat->dir == NULL)
        aux = mat->esq;

    return aux;
}

/* 
    summary
        Função responsável por encontrar o menor filho à esquerda
    param
        mat: matrícula
    return
        Retorna o menor filho à esquerda
*/
Matricula* menorfilhoesqmat(Matricula *mat){
    Matricula *aux;
    aux = NULL;
    /*
        operation
            Encontra o menor filho à esquerda
        example
              15
             /  \
            10   20
            /   /  \
            5  17  25
            mat = 15, que é diferente de NULL
            mat->esq = 10, que é diferente de NULL
            mat = 10
            mat->esq = 5, que é diferente de NULL
            mat = 5
            mat->esq = NULL, que é igual a NULL, então:
            return mat = 5
    */
    if(mat){
        aux = menorfilhoesqmat(mat->esq);
        if(!aux)
            aux = mat;
    }
    return aux;
}

/* 
    summary
        Função responsável por remover a matrícula
    param
        mat: matrícula
        cod: código da disciplina
        remove: ponteiro para a variável de controle
*/
void rmvmatricula(Matricula **mat, int cod, int *remove){
    /*
        operation
            Remover um nó da árvore de matrículas
        example
              15
             /  \
            10   20
            /   /  \
            5  17  25
            O nó a ser removido é o nó 15
            cod = 15, que é diferente de NULL
            mat->coddisc = 15, que é igual ao código a ser removido, então:
            Caso 1: O nó é uma folha (sem filhos) == FALSE
            Caso 2: O nó tem apenas um filho == FALSE
            Caso 3: O nó tem dois filhos == TRUE, então:
            menorfilho = 17
            Então, o nó 15 é substituído pelo menor filho da subárvore direita, que é o nó 17
    */
    if(*mat != NULL){
        // Se encontrou o nó a ser removido
        if((*mat)->coddisc == cod){
            Matricula *aux;
            
            // Caso 1: O nó é uma folha (sem filhos)
            if(ehfolhamat(*mat)){
                aux = *mat;
                free(aux);
                *mat = NULL;
                *remove = 1;
            } 
            // Caso 2: O nó tem apenas um filho
            else if ((aux = soumfilhomat(*mat)) != NULL) {
                Matricula *temp;
                temp = *mat;
                free(temp);
                *mat = aux;  // Substitui o nó pelo seu único filho
                *remove = 1;
            } 
            else {
                Matricula *menorfilho = menorfilhoesqmat((*mat)->dir);
                (*mat)->coddisc = menorfilho->coddisc;
                rmvmatricula(&(*mat)->dir, menorfilho->coddisc, remove);
            }
        } 
        // Se o código é menor, continua na subárvore esquerda
        else if(cod < (*mat)->coddisc)
            rmvmatricula(&(*mat)->esq, cod, remove);
        // Se o código é maior, continua na subárvore direita
        else
            rmvmatricula(&(*mat)->dir, cod, remove);
    }
}

/* 
    summary
        Função responsável por inserir a nota na árvore de notas
    param
        nota: árvore de notas
        cod: código da disciplina
        semestre: semestre da disciplina
        notafinal: nota final da disciplina
    return
        Retorna 1 se a nota foi cadastrada, 0 caso contrário
*/
int inserenota(Notas **nota, int cod, int semestre, float notafinal){
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
            sucesso = inserenota(&((*nota)->esq), cod, semestre, notafinal);
        else
            sucesso = inserenota(&((*nota)->dir), cod, semestre, notafinal);
    }
    return sucesso;
}

/* 
    summary
        Função principal responsável por cadastrar a nota
    param
        aluno: lista de alunos
        mat: matrícula do aluno
        cod: código da disciplina
        semestre: semestre da disciplina
        notafinal: nota final da disciplina
    return
        Retorna 1 se a nota foi cadastrada, 0 caso contrário
*/
int cadnota(Alunos **aluno, int mat, int cod, int semestre, float notafinal) {
    int enc = 0, remove = 0;
    if(*aluno != NULL){
        if((*aluno)->matricula == mat){
            int enc_disc = 0;
            busca_disc((*aluno)->mat, cod, &enc_disc); // Verifica se a disciplina está na árvore de matrículas
            if(enc_disc == 1){ // Se a disciplina está na árvore de matrículas, insere a nota
                if(inserenota(&(*aluno)->nota, cod, semestre, notafinal) == 1){
                    // Remove a disciplina da árvore de matrículas
                    rmvmatricula(&(*aluno)->mat, cod, &remove);
                    enc = 1;
                }
            }
        } 
        else
            enc = cadnota(&(*aluno)->prox, mat, cod, semestre, notafinal);
    }
    
    return enc;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vi) Mostrar todos os alunos de um determinado curso. */

/* 
    summary
        Função responsável por exibir os alunos de um determinado curso
    param
        aluno: lista encadeada de alunos
        codcurso: código do curso
*/
void alunosporcurso(Alunos *aluno, int codcurso){
    if(aluno != NULL){
        if(aluno->codcurso == codcurso){
            printf("Matricula: %d\n", aluno->matricula);
            printf("Nome: %s\n", aluno->nome);
            printf("\n");
        }
        alunosporcurso(aluno->prox, codcurso);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* vii) Mostrar todos os cursos do Campus. */ 

/* 
    summary
        Função responsável por exibir os cursos
    param
        curso: árvore de cursos
*/
void exibir_cursos(Cursos *curso) {
    if(curso != NULL){
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

/* 
    summary
        Função responsável por printar as disciplinas
    param
        disc: árvore de disciplinas
*/
void printarDiscCurso(Disciplina *disc){
    if(disc != NULL){
        printarDiscCurso(disc->esq);
        printf("Codigo: %d\n", disc->cod_disciplina);
        printf("Nome: %s\n", disc->nomedisc);
        printf("Carga horaria: %d\n", disc->cargah);
        printf("Periodo: %d\n", disc->periodo);
        printf("\n");
        printarDiscCurso(disc->dir);
    }
}

/* 
    summary
        Função principal responsável por exibir as disciplinas de um determinado curso
    param
        curso: árvore de cursos
        idcurso: código do curso
*/
void exibirDiscCurso(Cursos *curso, int idcurso){
    if(curso != NULL){
        if(curso->idcurso == idcurso){
            Disciplina *disc = curso->disc;
            printarDiscCurso(disc);
        }
        else if(idcurso < curso->idcurso)
            exibirDiscCurso(curso->esq, idcurso);
        else
            exibirDiscCurso(curso->dir, idcurso);
       
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// ix) Mostrar todas as disciplinas de um determinado período de um curso.

/* 
    summary
        Função responsável por printar as disciplinas de um determinado período
    param
        disc: árvore de disciplinas
        periodo: período da disciplina
*/
void printarDiscPeriodo(Disciplina *disc, int periodo) {
    if(disc != NULL){
        // Exibe as disciplinas em ordem
        printarDiscPeriodo(disc->esq, periodo);
        if(disc->periodo == periodo){
            printf("Codigo: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horaria: %d\n", disc->cargah);
            printf("Periodo: %d\n", disc->periodo);
            printf("\n");
        }
        printarDiscPeriodo(disc->dir, periodo);
    }
}

/* 
    summary
        Função principal responsável por exibir as disciplinas de um determinado período de um curso
    param
        curso: árvore de cursos
        idcurso: código do curso
        periodo: período da disciplina
*/
void exibirDiscPeriodo(Cursos *curso, int idcurso, int periodo){
    // Se a árvore de cursos não estiver vazia, recorre na árvore
    if(curso != NULL){
        if(curso->idcurso == idcurso)
            printarDiscPeriodo(curso->disc, periodo);
        else if(idcurso < curso->idcurso)
            exibirDiscPeriodo(curso->esq, idcurso, periodo);
        else
            exibirDiscPeriodo(curso->dir, idcurso, periodo);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* x) Mostrar todas as disciplinas que um determinado aluno está matriculado */

/* 
    summary
        Função responsável por printar as disciplinas
    param
        disc: árvore de disciplinas
        cod_disc: código da disciplina
*/
void printarDisc(Disciplina *disc, int cod_disc){
    if(disc != NULL){
        if(disc->cod_disciplina == cod_disc){
            printf("Codigo: %d\n", disc->cod_disciplina);
            printf("Nome: %s\n", disc->nomedisc);
            printf("Carga horaria: %d\n", disc->cargah);
            printf("Periodo: %d\n", disc->periodo);
            printf("\n");
        }
        else if(cod_disc < disc->cod_disciplina)
            printarDisc(disc->esq, cod_disc);
        else
            printarDisc(disc->dir, cod_disc);
    }
}

/* 
    summary
        Função responsável por exibir as disciplinas de um determinado aluno
    param
        curso: árvore de cursos
        cod_disc: código da disciplina
        idcurso: código do curso
*/
void exibirDisc(Cursos *curso, int cod_disc, int idcurso) {
    if(curso != NULL){
        if(curso->idcurso == idcurso){
            if(curso->disc != NULL)
                printarDisc(curso->disc, cod_disc);
        }
        else if(idcurso < curso->idcurso)
            exibirDisc(curso->esq, cod_disc, idcurso);
        else
            exibirDisc(curso->dir, cod_disc, idcurso);
    }
}

/* 
    summary
        Função responsável por exibir as disciplinas de um determinado aluno
    param
        mat: árvore de matrículas
        cursos: árvore de cursos
        codcurso: código do curso
*/
void discAluno(Matricula *mat, Cursos *cursos, int codcurso){
    if(mat != NULL){
        exibirDisc(cursos, mat->coddisc, codcurso);
        discAluno(mat->esq, cursos, codcurso);
        discAluno(mat->dir, cursos, codcurso);
    }
}

/* 
    summary
        Função principal responsável por exibir as disciplinas de um determinado aluno
    param
        aluno: lista de alunos
        cursos: árvore de cursos
        matricula: matrícula do aluno
*/
void exibirDiscAluno(Alunos *aluno, Cursos *cursos, int matricula){
    if(aluno != NULL){
        if (aluno->matricula == matricula)
            discAluno(aluno->mat, cursos, aluno->codcurso);
        else
            exibirDiscAluno(aluno->prox, cursos, matricula);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.*/

/* 
    summary
        Função responsável por exibir as notas de um determinado período
    param
        nota: árvore de notas
        periodo: período da disciplina
*/
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

/* 
    summary
        Função principal responsável por exibir as notas de um determinado período de um determinado aluno
    param
        a: lista de alunos
        periodo: período da disciplina
        mat: matrícula do aluno
*/
void notasdiscperiodoaluno(Alunos *aluno, int periodo, int mat){
    if(aluno != NULL){
        if(aluno->matricula == mat)
            exibirNotasPeriodo(aluno->nota, periodo);
        else
            notasdiscperiodoaluno(aluno->prox, periodo, mat);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
disciplina. */

/* 
    summary
        Função responsável por buscar o curso
    param
        curso: árvore de cursos
        idcurso: código do curso
    return
        Retorna o curso
*/
Cursos* buscar_curso(Cursos *curso, int idcurso){
    Cursos *aux;
    aux = NULL;
    if(curso != NULL){
        if (curso->idcurso == idcurso)
            aux = curso;
        else if (idcurso < curso->idcurso)
            aux = buscar_curso(curso->esq, idcurso);
        else
            aux = buscar_curso(curso->dir, idcurso);
    }
    return aux;
}

/* 
    summary
        Função responsável por buscar a disciplina
    param
        d: árvore de disciplinas
        coddisc: código da disciplina
    return
        Retorna a disciplina
*/
Disciplina* buscar_disciplina(Disciplina *disc, int coddisc){
    Disciplina *resultado = NULL;
    if(disc != NULL){
        if(disc->cod_disciplina == coddisc)
            resultado = disc;
        else if(coddisc < disc->cod_disciplina)
            resultado = buscar_disciplina(disc->esq, coddisc);
        else
            resultado = buscar_disciplina(disc->dir, coddisc);
    }
    return resultado;
}

/* 
    summary
        Função responsável por buscar a nota
    param
        nota: árvore de notas
        coddisc: código da disciplina
    return
        Retorna a nota
*/
Notas* buscar_nota(Notas *nota, int coddisc){
    Notas *resultado = NULL;
    if(nota != NULL){
        if (nota->coddisc == coddisc)
            resultado = nota;
        else if (coddisc < nota->coddisc)
            resultado = buscar_nota(nota->esq, coddisc); 
        else
            resultado = buscar_nota(nota->dir, coddisc);
    }
    return resultado;
}

/* 
    summary
        Função principal responsável por exibir a nota de uma disciplina de um determinado aluno
    param
        aluno: lista de alunos
        curso: árvore de cursos
        matricula: matrícula do aluno
        coddisc: código da disciplina
*/
void notadiscporaluno(Alunos *aluno, Cursos *curso, int matricula, int coddisc){
    // Inicializa as variáveis
    Cursos *c = NULL;
    Disciplina *d = NULL;
    Notas *nota = NULL;
    // Se a lista de alunos não estiver vazia
    if(aluno != NULL){
        if(aluno->matricula == matricula){
            // Se o aluno foi encontrado, busca o curso, a disciplina e a nota
            c = buscar_curso(curso, aluno->codcurso);
            if(c != NULL){
                d = buscar_disciplina(c->disc, coddisc);  // Usando a função recursiva de disciplina
                if(d != NULL){
                    nota = buscar_nota(aluno->nota, coddisc);  // Usando a função recursiva de nota
                    if(nota != NULL){
                        printf("Disciplina: %s\n", d->nomedisc);
                        printf("Nota: %.2f\n", nota->notafinal);
                        printf("Periodo: %d\n", d->periodo);
                        printf("Carga horaria: %d\n", d->cargah);
                    }
                }
            }
        } 
        else
            notadiscporaluno(aluno->prox, curso, matricula, coddisc);  // Recorre ao próximo aluno
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
mesma */

/* 
    summary
        Função responsável por verificar se o nó é uma folha
    param
        disc: disciplina
    return
        Retorna 1 se o nó é uma folha, 0 caso contrário
*/
int ehfolhadisc(Disciplina *disc){
    return (disc->esq == NULL && disc->dir == NULL);
}

/* 
    summary
        Função responsável por verificar se o nó tem apenas um filho
    param
        disc: disciplina
    return
        Retorna o nó filho
*/
Disciplina* soumfilhodisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc->dir == NULL)
        aux = disc->esq;
    else if (disc->esq == NULL)
        aux = disc->dir;
    return aux;
}

/* 
    summary
        Função responsável por encontrar o menor filho à esquerda
    param
        disc: disciplina
    return
        Retorna o menor filho à esquerda
*/
Disciplina* menorfilhoesqdisc(Disciplina *disc){
    Disciplina *aux;
    aux = NULL;
    if (disc != NULL)
        aux = menorfilhoesqdisc(disc->esq);
        if (!aux)
            aux = disc;
    return aux;
}

/* 
    summary
        Função responsável por remover a disciplina
    param
        disc: disciplina
        cod_disc: código da disciplina
        remove: ponteiro para a variável de controle
*/
void rmvdisc(Disciplina **disc, int cod_disc, int *remove){
    if((*disc != NULL)){    
        // Inicializa as variáveis
        Disciplina *aux;
        Disciplina *endfilho;
        Disciplina *endmenorfilho;
        // Se encontrou o nó a ser removido
        if((*disc)->cod_disciplina == cod_disc){
            // Caso 1: O nó é uma folha (sem filhos)
            if(ehfolhadisc(*disc)){
                aux = *disc;
                free(aux);
                *disc = NULL;
            } 
            // Caso 2: O nó tem apenas um filho
            else if((endfilho = soumfilhodisc(*disc)) != NULL){
                aux = *disc;
                free(aux); 
                *disc = endfilho;  
            } 
            // Caso 3: O nó tem dois filhos
            else{
                endmenorfilho = menorfilhoesqdisc((*disc)->dir);
                (*disc)->cod_disciplina = endmenorfilho->cod_disciplina;
                (*disc)->cargah = endmenorfilho->cargah;
                (*disc)->periodo = endmenorfilho->periodo;
                strcpy((*disc)->nomedisc, endmenorfilho->nomedisc);
                rmvdisc(&(*disc)->dir, endmenorfilho->cod_disciplina, remove);
            }
            *remove = 1;
        }
        // Se o código é menor, continua na subárvore esquerda
        else if (cod_disc < (*disc)->cod_disciplina)
            rmvdisc(&(*disc)->esq, cod_disc, remove);
        // Se o código é maior, continua na subárvore direita
        else 
            rmvdisc(&(*disc)->dir, cod_disc, remove);
    }
}

/* 
    summary
        Função responsável por validar a remoção da disciplina
    param
        alunos: lista de alunos
        cod_disc: código da disciplina
        validar_disc: ponteiro para a variável de controle
*/
void validarRemocao(Alunos *alunos, int cod_disc, int *validar_disc){
    int enc = 0;
    if(alunos != NULL){
        buscamat(alunos->mat, cod_disc, &enc);
        if(enc != 0)
            *validar_disc = 1;
        validarRemocao(alunos->prox, cod_disc, validar_disc);
    }
}

/* 
    summary
        Função principal responsável por remover uma disciplina de um determinado curso
    param
        cursos: árvore de cursos
        alunos: lista de alunos
        idcurso: código do curso
        cod_disc: código da disciplina
    return
        Retorna 1 se a disciplina foi removida, 0 caso contrário
*/
int rmvDiscCurso(Cursos **cursos, Alunos *alunos, int idcurso, int cod_disc){
    int remove = 0, validar_disc = 0;
    if((*cursos)){
        validarRemocao(alunos, cod_disc, &validar_disc);
        if(validar_disc != 0){
            if ((*cursos)->idcurso == idcurso)
                rmvdisc(&(*cursos)->disc, cod_disc, &remove);   
            else if (idcurso < (*cursos)->idcurso)
                remove = rmvDiscCurso(&(*cursos)->esq, alunos, idcurso, cod_disc);
            else
                remove = rmvDiscCurso(&(*cursos)->dir, alunos, idcurso, cod_disc);
        }
    }
    return remove;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. */

/* 
    summary
        Função principal responsável por remover uma disciplina da árvore de matrícula de um determinado aluno
    param
        a: lista de alunos
        m: matrícula
        matricula: matrícula do aluno
        coddisc: código da disciplina
    return
        Retorna 1 se a disciplina foi removida, 0 caso contrário
*/
int rmvmatdealuno(Alunos **aluno, Matricula *mat, int matricula, int coddisc){
    int remove = 0;
    if(*aluno != NULL){
        if((*aluno)->matricula == matricula)
            rmvmatricula(&(*aluno)->mat, coddisc, &remove);
        else
            remove = rmvmatdealuno(&(*aluno)->prox, mat, matricula, coddisc);
    }
    return remove;
}

/*---------------------------------------------------------------------------------------------------------------*/

/* xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
nota organizadas pelo período que a disciplina está cadastrada no curso. */

/* 
    summary
        Função responsável por exibir a disciplina
    param
        disc: árvore de disciplinas
        cod_disciplina: código da disciplina
*/
void exibir_disciplina(Disciplina *disc, int cod_disciplina){
    if(disc != NULL){
        if(disc->cod_disciplina == cod_disciplina) 
            printf("Disciplina: %s\n", disc->nomedisc);
        else if(cod_disciplina < disc->cod_disciplina)
            exibir_disciplina(disc->esq, cod_disciplina);
        else
            exibir_disciplina(disc->dir, cod_disciplina);
    }
}

/* 
    summary
        Função responsável por exibir as notas
    param
        nota: árvore de notas
        disc: árvore de disciplinas
        periodo: período da disciplina
*/
void exibir_notas(Notas *nota, Disciplina *disc, int periodo){
    if(nota != NULL){
        if(nota->semestre == periodo){
            exibir_disciplina(disc, nota->coddisc);
            printf("Nota: %.2f\n", nota->notafinal);
            printf("Semestre: %d\n\n", nota->semestre);
        }
        exibir_notas(nota->esq, disc, periodo);
        exibir_notas(nota->dir, disc, periodo);
    }
}

/* 
    summary
        Função responsável por exibir o nome do curso
    param
        c: árvore de cursos
        idcurso: código do curso
    return
        Retorna a quantidade de períodos do curso
*/
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

/* 
    summary
        Função principal responsável por exibir o histórico de um determinado aluno
    param
        a: lista de alunos
        c: árvore de cursos
        matricula: matrícula do aluno
*/
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

/* 
    summary
        Função responsável por buscar a matrícula
    param
        mat: árvore de matrículas
        cod: código da disciplina
        enc: ponteiro para a variável de controle
*/
void gerarCodDisciplina(int cargah, int periodo, int *coddisc) {
    // Passo 1: obtendo o ano atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int anoatual = tm.tm_year + 1900;

    int num5 = rand() % 100000; // Gera um número entre 0 e 99999

    // Passo 3: gerando o código no formato AAAACCPNNNNN como número inteiro
    *coddisc = anoatual * 100000000 + cargah * 1000000 + periodo * 100000 + num5;
}

/* 
    summary
        Função responsável por gerar o id do curso
    param
        qntperiodos: quantidade de períodos do curso
        idcurso: ponteiro para o id do curso
*/
void gerarIdCurso(int qntperiodos, int *idcurso) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano = tm.tm_year + 1900;

    int num4 = rand() % 10000;

    // Combina os componentes no formato PPPAAAANNNN como um único número inteiro.
    *idcurso = qntperiodos * 100000000 + (qntperiodos * 3) * 1000000 + (qntperiodos * 5) * 10000 + ano * 10000 + num4;
}

/* 
    summary
        Função responsável por gerar a matrícula do aluno
    param
        idcurso: código do curso
        matricula: ponteiro para a matrícula do aluno
*/
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

/* 
    summary
        Função responsável por exibir os alunos
    param
        aluno: lista de alunos
*/
void exibiralunos(Alunos *aluno){
    if(aluno != NULL){
        printf("Matricula: %d\n", aluno->matricula);
        printf("Nome: %s\n", aluno->nome);
        printf("Codigo do Curso: %d\n", aluno->codcurso);
        printf("\n");
        exibiralunos(aluno->prox);
    }
}

/* 
    summary
        Funções responsáveis por liberar a memória alocada
    param
        nota: árvore de notas
        mat: árvore de matrículas
        disc: árvore de disciplinas
        aluno: lista de alunos
        curso: árvore de cursos
*/
void liberar_notas(Notas **nota){
    if(*nota != NULL){
        liberar_notas(&(*nota)->esq);
        liberar_notas(&(*nota)->dir);
        free(*nota);
        *nota = NULL;
    }
}

void liberar_matriculas(Matricula **mat){
    if(*mat != NULL){
        liberar_matriculas(&(*mat)->esq);
        liberar_matriculas(&(*mat)->dir);
        free(*mat);
        *mat = NULL;
    }
}

void liberar_disciplinas(Disciplina **disc){
    if(*disc != NULL){
        liberar_disciplinas(&(*disc)->esq);
        liberar_disciplinas(&(*disc)->dir);
        free(*disc);
        *disc = NULL;
    }
}

void liberar_alunos(Alunos **a){
    if(*a != NULL){
        liberar_alunos(&(*a)->prox);
        liberar_notas(&(*a)->nota);
        liberar_matriculas(&(*a)->mat);
        free(*a);
        *a = NULL;
    }
}

void liberar_cursos(Cursos **c){
    if(*c != NULL){
        liberar_cursos(&(*c)->esq);
        liberar_cursos(&(*c)->dir);
        liberar_disciplinas(&(*c)->disc);
        free(*c);
        *c = NULL;
    }
}

/*---------------------------------------------------------------------------------------------------------------*/