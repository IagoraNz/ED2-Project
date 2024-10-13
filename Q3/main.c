#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q3.h"

// Cadastrando cursos
int main() {
    AVLCurso *raiz = NULL;
    Cursos *curso;
    curso = (Cursos*)malloc(sizeof(Cursos));

    curso->idcurso = 1;
    strcpy(curso->nomecurso, "Engenharia de Software");
    curso->qntdperiodos = 8;
    curso->disc = NULL;
    int sucesso = cadcurso(&raiz, curso);

    if(sucesso == 1)
        printf("Curso cadastrado com sucesso!\n");
    else
        printf("Curso ja cadastrado!\n");

    exibircurso(raiz);

    // Cadastrar disciplinas
    AVLDisc *disc = NULL;
    Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));

    d->cod_disciplina = 1;
    strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
    d->cargah = 60;
    d->periodo = 1;

    sucesso = caddisc(&raiz, d, 1);
    if(sucesso == 1)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Disciplina ja cadastrada!\n");

    system("PAUSE");

    return 0;
}