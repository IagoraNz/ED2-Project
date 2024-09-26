#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "./src/Q1.h"

int main(){
    int opc, sucesso, idcurso, qtdperiodos;
    char buffer[50], nomecurso[50];

    Cursos *c;
    Matricula *m;
    c = NULL;
    m = NULL;

    printf("Cadastrandos os cursos\n");

    cadcurso(&c, 4, "Engenharia de Software", 8);
    cadcurso(&c, 2, "Ciencia da Computacao", 8);
    cadcurso(&c, 7, "Sistemas de Informacao", 8);
    cadcurso(&c, 10, "Engenharia Eletrica", 8);
    cadcurso(&c, 5, "Engenharia Mecanica", 8);
    cadcurso(&c, 3, "Engenharia Civil", 8);
    cadcurso(&c, 1, "Engenharia de Producao", 8);
    cadcurso(&c, 11, "Engenharia Quimica", 8);

    printf("Exibindo os cursos\n");

    exibircurso(c);

    printf("Cadastrando disciplinas\n");

    Disciplina *d;
    d = (Disciplina*)malloc(sizeof(Disciplina));
    strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
    d->cargah = 60;
    d->periodo = 1;
    d->cod_disciplina = 1001;
    int suc = caddisc(&c, d, 4);
    if (suc)
        printf("Disciplina cadastrada com sucesso!\n");
    else
        printf("Erro ao cadastrar disciplina!\n");

    printf("Exibindo as disciplinas\n");

    exibir_disc_curso_main(c, 4);

    getchar();

    return 0;
}