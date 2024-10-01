#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "./src/Q1.h"

int main(){

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
    printf("\n\nCursos cadastrados com sucesso!\n");

    printf("\nExibindo os cursos\n");

    exibircurso(c);

    printf("\nCadastrando disciplinas\n");

    Disciplina *d;
    d = (Disciplina*)malloc(sizeof(Disciplina));
    strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
    d->cargah = 60;
    d->periodo = 1;
    d->cod_disciplina = 1001;
    int suc = caddisc(&c, d, 4);
    if (suc)
        printf("\nDisciplina cadastrada com sucesso!\n");
    else
        printf("\nErro ao cadastrar disciplina!\n");

    d = (Disciplina*)malloc(sizeof(Disciplina));
    strcpy(d->nomedisc, "Calculo I");
    d->cargah = 60;
    d->periodo = 2;
    d->cod_disciplina = 991;
    suc = caddisc(&c, d, 4);
    if (suc)
        printf("\nDisciplina cadastrada com sucesso!\n");
    else
        printf("\nErro ao cadastrar disciplina!\n");

    d = (Disciplina*)malloc(sizeof(Disciplina));
    strcpy(d->nomedisc, "Calculo II");
    d->cargah = 60;
    d->periodo = 3;
    d->cod_disciplina = 1010;
    suc = caddisc(&c, d, 4);
    if (suc)
        printf("\nDisciplina cadastrada com sucesso!\n");
    else
        printf("\nErro ao cadastrar disciplina!\n");

    printf("Exibindo as disciplinas\n");

    exibir_disc_curso_main(c, 4);

    printf("\nCadastrando alunos\n");

    Alunos *a;
    Alunos *aux;
    aux = NULL;
    a = NULL;

    cadaluno(&a, 2021000301, "Joao", 4);
    cadaluno(&a, 2021000002, "Maria", 4);
    cadaluno(&a, 2021000013, "Jose", 4);
    cadaluno(&a, 2021000444, "Ana", 4);
    cadaluno(&a, 2021000005, "Pedro", 4);
    cadaluno(&a, 2021100006, "Paulo", 4);
    cadaluno(&a, 2021000777, "Lucas", 4);
    cadaluno(&a, 2021000088, "Fabio", 4);

    printf("Exibindo os alunos\n");

    exibiralunos(a);

    printf("\nMatriculando alunos\n");

    cadmatricula(&a, 1001, 2021000301);
    cadmatricula(&a, 1001, 2021000002);
    cadmatricula(&a, 1001, 2021000013);
    cadmatricula(&a, 991, 2021000444);
    cadmatricula(&a, 1010, 2021000301);
    cadmatricula(&a, 1001, 2021100006);
    printf("\nAlunos matriculados com sucesso!\n");

    printf("Exibindo Matriculas\n");
    printf("Nome: %s\n", a->nome);
    exibirmat(a->mat);

    printf("Exibindo os alunos\n");

    exibiralunos(a);

    printf("\nExibindo as disciplinas dos alunos\n");

    exibir_disc_aluno_main(a, c, 2021000301);

    printf("Exibindo as disciplinas dos alunos\n");
    exibir_disc_aluno_main(a, c, 2021000301);

    printf("Cadastrando notas\n");
    int teste = 0;

    printf("\n");

    teste = cadnota(&a, 2021000301, 1001, 1,  8.5);
    printf("%d\n", teste);    

    teste = cadnota(&a, 2021000444, 1010, 3,  7.5);
    printf("%d\n", teste);

    printf("Exibindo as notas\n");

    exibir_hist_aluno(a, c, 2021000301);
    
    system("PAUSE");

    getchar();

    return 0;
}