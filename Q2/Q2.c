#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q1.h"

#define QTD_CURSOS 1000
#define QTD_DISCIPLINAS 10
#define QTD_ALUNOS 1000

void povoar_cursos(Cursos **raiz){
    char *nomes[5] = {"Engenharia de Software", "Ciencia da Computacao", "Engenharia Eletrica", "Engenharia Mecanica", "Engenharia Civil"};
    int qntperiodos[5] = {8, 8, 10, 10, 10};
    for (int i = 1; i < QTD_CURSOS; i++){
        cadcurso(raiz, i, nomes[rand() % 5], qntperiodos[rand() % 5]);
    }
}

void povoar_disciplinas(Cursos **raiz){
    if (*raiz != NULL){
        char *nomes[6] = {"Algoritmos e Estruturas de Dados", "Calculo I", "Calculo II", "Calculo III", "Calculo IV", "Fisica I"};
        int carga_horaria[6] = {60, 90, 90, 90, 90, 60};
        for (int i = QTD_DISCIPLINAS; i > 0; i--){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, nomes[rand() % 6]);
            d->cargah = carga_horaria[rand() % 6];
            d->periodo = 3;
            d->cod_disciplina = i;
            caddisc(raiz, d, rand() % QTD_CURSOS);
        }
        povoar_disciplinas(&(*raiz)->esq);
        povoar_disciplinas(&(*raiz)->dir);
    }
}

void povoar_alunos(Alunos **raiz, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1; i < QTD_ALUNOS; i++){
        cadaluno(raiz, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

void povoar_matriculas(Alunos *raiz){
    for (int i = 1; i < QTD_ALUNOS; i++){
        for (int j = 1; j < QTD_DISCIPLINAS; j++){
            cadmatricula(&raiz, j, i);
        }
    }
}

void povoar_notas(Alunos *raiz){
    for (int i = 1; i < QTD_ALUNOS; i++){
        for (int j = 1; j < QTD_DISCIPLINAS; j++){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = j;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&raiz, i, j, n->semestre, n->notafinal);
        }
    }
}

int main (){
    srand(time(NULL));
    Cursos *raiz = NULL;
    povoar_cursos(&raiz);
    povoar_disciplinas(&raiz);
    exibircurso(raiz);
    system("pause");
    for (int i = 0; i < QTD_CURSOS; i++){
        exibir_disc_curso_main(raiz, i);
    }
    system("pause");
    Alunos *raiz_alunos = NULL;
    povoar_alunos(&raiz_alunos, raiz);
    exibiralunos(raiz_alunos);
    system("pause");
    povoar_matriculas(raiz_alunos);
    exibirmat(raiz_alunos->mat);
    system("pause");
    povoar_notas(raiz_alunos);
    for (int i = 1; i < QTD_ALUNOS; i++){
        exibir_hist_aluno(raiz_alunos, raiz, i);
    }
    system("pause");
    return 0;
}