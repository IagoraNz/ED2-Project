#include <stdio.h>
#include "./src/Q3.h"
#include <string.h>
#include <stdlib.h>

int main () {
    AVLCurso *curso;
    // Alunos *alunos;
    AVLDisc *disc;
    disc = NULL;
    curso = NULL;
    // alunos = NULL;

    Cursos *c = (Cursos*) malloc(sizeof(Cursos));

    c->idcurso = 1;
    c->qntdperiodos = 8;
    strcpy(c->nomecurso, "Engenharia de Computação");
    c->disc = NULL;

    Disciplina *d = (Disciplina*) malloc(sizeof(Disciplina));
    d->cod_disciplina = 1;
    d->cargah = 60;
    d->periodo = 1;
    strcpy(d->nomedisc, "Cálculo I");

    // Exibir disciplinas de um determinado curso
    cadcurso(&curso, c);
    caddisc(&curso, d, 1);
    exibir_disc_curso_main(curso, 1);

    system("PAUSE");

    return 0;
}