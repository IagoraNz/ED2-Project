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
    int sucesso = cadcurso(&raiz, curso);

    if(sucesso == 1)
        printf("Curso cadastrado com sucesso!\n");
    else
        printf("Curso ja cadastrado!\n");

    curso = (Cursos*)malloc(sizeof(Cursos));

    curso->idcurso = 2;
    strcpy(curso->nomecurso, "Ciencia da Computacao");
    curso->qntdperiodos = 8;
    sucesso = cadcurso(&raiz, curso);

    if(sucesso == 1)
        printf("Curso cadastrado com sucesso!\n");
    else
        printf("Curso ja cadastrado!\n");

    curso = (Cursos*)malloc(sizeof(Cursos));

    curso->idcurso = 3;
    strcpy(curso->nomecurso, "Sistemas de Informacao");
    curso->qntdperiodos = 8;
    sucesso = cadcurso(&raiz, curso);

    if(sucesso == 1)
        printf("Curso cadastrado com sucesso!\n");
    else
        printf("Curso ja cadastrado!\n");

    curso = (Cursos*)malloc(sizeof(Cursos));

    curso->idcurso = 4;
    strcpy(curso->nomecurso, "Engenharia de Computacao");
    curso->qntdperiodos = 8;
    sucesso = cadcurso(&raiz, curso);

    if(sucesso == 1)
        printf("Curso cadastrado com sucesso!\n");
    else
        printf("Curso ja cadastrado!\n");

    exibircurso(raiz);

    system("PAUSE");

    return 0;
}