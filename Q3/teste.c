#include <stdio.h>
#include "./src/Q3.h"
#include <string.h>
#include <stdlib.h>

int main () {
    AVLCurso *curso;
    Alunos *alunos;
    AVLDisc *disc;
    disc = NULL;
    curso = NULL;
    alunos = NULL;
    int sucesso;

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

    // cadastrando cursos
    c = (Cursos*) malloc(sizeof(Cursos));
    c->idcurso = 2;
    c->qntdperiodos = 8;
    strcpy(c->nomecurso, "Engenharia de Produção");
    c->disc = NULL;
    cadcurso(&curso, c);

    c = (Cursos*) malloc(sizeof(Cursos));
    c->idcurso = 3;
    c->qntdperiodos = 8;
    strcpy(c->nomecurso, "Engenharia Civil");
    c->disc = NULL;

    cadcurso(&curso, c);

    exibirAlturaCurso(curso);

    sucesso = caddisc(&curso, d, 1);
    if (sucesso)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Disciplina não cadastrada!\n");

    d = (Disciplina*) malloc(sizeof(Disciplina));
    d->cargah = 60;
    d->periodo = 1;
    strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados I");
    d->cod_disciplina = 2;

    sucesso = caddisc(&curso, d, 1);
    if (sucesso)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Disciplina não cadastrada!\n");

    d = (Disciplina*) malloc(sizeof(Disciplina));
    d->cargah = 60;
    d->periodo = 1;
    strcpy(d->nomedisc, "Física I");
    d->cod_disciplina = 3;

    sucesso = caddisc(&curso, d, 1);
    if (sucesso)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Disciplina não cadastrada!\n");

    d = (Disciplina*) malloc(sizeof(Disciplina));
    d->cargah = 60;
    d->periodo = 1;
    strcpy(d->nomedisc, "Química Geral");
    d->cod_disciplina = 4;

    sucesso = caddisc(&curso, d, 1);
    if (sucesso)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Disciplina não cadastrada!\n");

    exibirAlturaDisciplinaMain(curso, 1);
    system("PAUSE");

    cadaluno(&alunos, curso, 1, "João", 1);
    cadaluno(&alunos, curso, 2, "Maria", 1);
    cadaluno(&alunos, curso, 3, "José", 1);

    sucesso = rmvdisc_curso(&curso, alunos, 1, 1);
    if (sucesso == 1)
        printf("Disciplina removida com sucesso!\n");
    else
        printf("Disciplina não removida!\n");
    system("PAUSE");

    exibir_disc_curso_main(curso, 1);

    alunosporcurso(alunos, 1);
    
    sucesso = cadmatricula(&alunos, curso, 1, 1);
    if (sucesso)
        printf("Matricula realizada com sucesso!\n");
    else
        printf("Matricula não realizada!\n");
    sucesso = cadmatricula(&alunos, curso, 1, 2);
    if (sucesso)
        printf("Matricula realizada com sucesso!\n");
    else
        printf("Matricula não realizada!\n");
    sucesso = cadmatricula(&alunos, curso, 2, 1);
    if (sucesso)
        printf("Matricula realizada com sucesso!\n");
    else
        printf("Matricula não realizada!\n");

    sucesso = cadmatricula(&alunos, curso, 3, 1);
    if (sucesso)
        printf("Matricula realizada com sucesso!\n");
    else
        printf("Matricula não realizada!\n");

    exibirAlturaMatriculaMain(alunos, 1);
    printf("\n");

    exibir_disc_aluno_main(alunos, curso, 1);
    exibir_disc_aluno_main(alunos, curso, 2);

    system("PAUSE");

    Notas *n = (Notas*) malloc(sizeof(Notas));
    n->coddisc = 1;
    n->semestre = 1;
    n->notafinal = 8.5;

    sucesso = cadnota(&alunos, 1, n);
    if (sucesso)
        printf("Nota cadastrada com sucesso!\n");
    else
        printf("Nota não cadastrada!\n");

    n = (Notas*) malloc(sizeof(Notas));
    n->coddisc = 2;
    n->semestre = 1;
    n->notafinal = 9.0;

    sucesso = cadnota(&alunos, 1, n);
    if (sucesso)
        printf("Nota cadastrada com sucesso!\n");
    else
        printf("Nota não cadastrada!\n");

    n = (Notas*) malloc(sizeof(Notas));
    n->coddisc = 3;
    n->semestre = 1;
    n->notafinal = 7.5;

    sucesso = cadnota(&alunos, 1, n);
    if (sucesso)
        printf("Nota cadastrada com sucesso!\n");
    else
        printf("Nota não cadastrada!\n");
    
    system("PAUSE");

    notadiscporaluno(alunos, curso, 1, 1);

    system("PAUSE");

    notasdiscperiodoaluno(alunos, 1, 1);

    exibirAlturaNotasMain(alunos, 1);

    system("PAUSE");

    return 0;
}