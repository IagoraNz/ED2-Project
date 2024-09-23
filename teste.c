#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
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

    printf("Cadastrando matriculas\n");

    cadmatricula(&m, 4);
    cadmatricula(&m, 2);
    cadmatricula(&m, 7);
    cadmatricula(&m, 10);
    cadmatricula(&m, 5);
    cadmatricula(&m, 3);
    cadmatricula(&m, 1);
    cadmatricula(&m, 11);

    printf("Exibindo as matriculas\n");

    exibirmat(m);

    printf("Removendo matricula\n");

    rmvmatricula(&m, 7);

    printf("Exibindo as matriculas\n");

    exibirmat(m);

    getchar();

    return 0;
}