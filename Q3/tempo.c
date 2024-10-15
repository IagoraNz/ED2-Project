#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q3.h"

#define QTD_CURSOS 1000
#define ID_CURSOS 10000
#define QTD_ALUNOS 1000
#define QTD_DISCIPLINAS 10
#define QTD_MATRICULAS 10
#define REPEAT 10000

/*---------------------------------------------------------------------------------------------------------------*/

/*
Funções de povoamento das arvores de forma crescente, decrescente e aleatória.
*/

// CRESCENTE

void povoar_cursos_crescente(AVLCurso **raiz){ 
    for (int i = 1; i < QTD_CURSOS; i++){
        Cursos *c = (Cursos*)malloc(sizeof(Cursos));
        c->idcurso = i;
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        cadcurso(raiz, c);
    }
}

void povoar_disciplinas_crescente(AVLCurso **raiz){
    if (*raiz != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            d->cod_disciplina = i;
            d->cargah = 60;
            d->periodo = i;
            strcpy(d->nomedisc, "Calculo");
            caddisc(raiz, d, (*raiz)->info->idcurso);
        }
        povoar_disciplinas_crescente(&(*raiz)->esq);
        povoar_disciplinas_crescente(&(*raiz)->dir);
    }
}

void povoar_matriculas_crescente(Alunos *aluno, AVLCurso *curso){
    int sucesso;
    if (aluno != NULL){
        for (int i = 1; i < QTD_MATRICULAS; i++){
            cadmatricula(&aluno, curso, i, aluno->matricula);
        }
        povoar_matriculas_crescente(aluno->prox, curso);
    }
}

void povoar_notas_crescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, n);
        }
        povoar_notas_crescente(aluno->prox);
    }
}

void povoar_alunos_crescente(Alunos **aluno, AVLCurso *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1; i < QTD_ALUNOS; i++){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

void povoamento_crescente(AVLCurso **raiz, Alunos **alunos){
    povoar_cursos_crescente(raiz);
    povoar_disciplinas_crescente(raiz);
    povoar_alunos_crescente(alunos, *raiz);
    povoar_matriculas_crescente(*alunos, *raiz);
    povoar_notas_crescente(*alunos);
}

/*---------------------------------------------------------------------------------------------------------------*/

void menu_povoamento(){
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    printf("3 - Aleatorio\n");
    printf("Escolha a forma de povoamento das arvores:\n");
}

/*---------------------------------------------------------------------------------------------------------------*/


void notadiscporaluno_Teste(Alunos *aluno, AVLCurso *curso, int matricula, int coddisc){
    if (aluno != NULL){
        if (aluno->matricula == matricula){
            AVLCurso *c = buscar_curso(curso, aluno->codcurso);
            if (c != NULL){
                AVLDisc *d = c->info->disc;
                while (d != NULL){
                    if (d->info->cod_disciplina == coddisc){
                        AVLNotas *nota = aluno->nota;
                        while (nota != NULL){
                            if (nota->info->coddisc == coddisc){
                                int sucesso = 1;
                            }
                            if (coddisc < nota->info->coddisc)
                                nota = nota->esq;
                            else
                                nota = nota->dir;
                        }
                    }
                    if (coddisc < d->info->cod_disciplina)
                        d = d->esq;
                    else
                        d = d->dir;
                }
            }
        }
        else
            notadiscporaluno_Teste(aluno->prox, curso, matricula, coddisc);
    }
}

// METRIFICANDO O TEMPO

double metrificar_tempo_por_busca_nota(Alunos *alunos, AVLCurso *raiz) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int i;

    int aluno_rand = 876;  // Escolhe aluno aleatório
    int disc_rand = 5;  // Escolhe disciplina aleatória

    // Executa a busca várias vezes para obter uma média mais precisa
    for (i = 0; i < REPEAT; i++) {
        inicio = clock();
        notadiscporaluno_Teste(alunos, raiz, aluno_rand, disc_rand);  // Função de busca
        fim = clock();

        // Soma o tempo de cada execução
        tempo_total += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    // Retorna o tempo médio por busca
    return tempo_total / REPEAT;
}

double metrificar_tempo_por_insercao(AVLCurso **curso){
    clock_t inicio, fim;
    double tempo = 0.0;
    int i;
    
    for(i = 0; i < REPEAT; i++){
        Cursos *c = (Cursos*)malloc(sizeof(Cursos));
        c->idcurso = rand() % ID_CURSOS;
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        inicio = clock();
        cadcurso(curso, c);
        fim = clock();

        tempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    liberarAVLCurso(curso);
    povoar_cursos_crescente(curso);
    return tempo / REPEAT;
}

/*---------------------------------------------------------------------------------------------------------------*/

int main (){
    srand(time(NULL));
    AVLCurso *raiz;
    Alunos *alunos;
    alunos = NULL;
    raiz = NULL;

    povoamento_crescente(&raiz, &alunos);

    double tempo_medio;
    for (int i = 0; i < 10; i++) {
        tempo_medio = metrificar_tempo_por_busca_nota(alunos, raiz);
        printf("Tempo medio de busca: %.10f\n", tempo_medio);
    }   

    for (int i = 0; i < 10; i++) {
        tempo_medio = metrificar_tempo_por_insercao(&raiz);
        printf("Tempo medio de insercao: %.10f\n", tempo_medio);
    }

    liberarAVLCurso(&raiz);
    liberarAlunos(&alunos);
    
    return 0;
}