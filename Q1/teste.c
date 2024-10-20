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

    exibir_cursos(c);

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

    exibirDiscCurso(c, 4);

    printf("\nCadastrando alunos\n");

    Alunos *a;
    Alunos *aux;
    aux = NULL;
    a = NULL;

    cadaluno(&a, c, 2021000301, "Joao", 4);
    cadaluno(&a, c, 2021000002, "Maria", 2);
    cadaluno(&a, c, 2021000013, "Jose", 2);
    cadaluno(&a, c, 2021000444, "Ana", 2);
    cadaluno(&a, c, 2021000005, "Pedro", 4);
    cadaluno(&a, c, 2021100006, "Paulo", 4);
    cadaluno(&a, c, 2021000777, "Lucas", 4);
    cadaluno(&a, c, 2021000088, "Fabio", 10);

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

    exibirDiscAluno(a, c, 2021000301);

    printf("Exibindo as disciplinas dos alunos\n");
    exibirDiscAluno(a, c, 2021000301);

    printf("Cadastrando notas\n");
    int teste = 0;

    printf("\n");

    teste = cadnota(&a, 2021000301, 1001, 1,  8.5);
    printf("%d\n", teste);    

    teste = cadnota(&a, 2021000444, 1010, 3,  7.5);
    printf("%d\n", teste);

    printf("Exibindo as notas\n");

    exibir_hist_aluno(a, c, 2021000301);
    
    printf("\n\n");

    printf("Mostrar todos os alunos de um determinado curso\n");

    alunosporcurso(a, 10);

    printf("\n\n");

    printf("Mostrar todos os cursos do Campus\n");

    exibir_cursos(c);

    printf("\n\n");

    printf("Mostrar todas as disciplinas de um determinado curso\n");

    exibirDiscCurso(c, 4);

    printf("\n\n");

    printf("ix) Mostrar todas as disciplinas de um determinado periodo de um curso\n");

    exibirDiscPeriodo(c, 4, 1);

    printf("\n\n");

    printf("x) Mostrar todas as disciplinas que um determinado aluno esta matriculado\n");

    exibirDiscAluno(a, c, 2021000301);

    printf("\n\n");

    printf("xi) Mostrar todas as notas de disciplinas de um determinado periodo de um determinado aluno.\n");

    notasdiscperiodoaluno(a, 1, 2021000301);

    printf("\n\n");

    printf("xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o periodo e a carga horaria da disciplina.\n");

    notadiscporaluno(a, c, 2021000301, 1001);

    printf("\n\n");

    printf("xiii) Remover uma disciplina de um determinado curso desde que nao tenha nenhum aluno matriculado na mesma\n");

    rmvDiscCurso(&c, a, 4, 1001);
    printf("Disciplina removida com sucesso!\n");

    // Exibindo as disciplinas do curso 4 após a remoção da disciplina 1001

    exibirDiscCurso(c, 4);

    printf("\n\n");

    printf("xiv) Permita remover uma disciplina da arvore de matricula de um determinado aluno.\n");
    int remove;
    remove = rmvmatdealuno(&a, 2021000301, 1010);
    if (remove == 1)
        printf("Disciplina removida com sucesso!\n");
    else
        printf("Erro ao remover disciplina!\n");

    // Exibindo as disciplinas do aluno 2021000301 após a remoção da disciplina 1001

    exibirDiscAluno(a, c, 2021000301);

    printf("\n\n");

    printf("xv) Mostrar o historico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva nota organizadas pelo periodo que a disciplina esta cadastrada no curso.\n");

    exibir_hist_aluno(a, c, 2021000301);
    
    // Liberando a memória alocada
    liberar_cursos(&c);
    liberar_alunos(&a);
    liberar_matriculas(&m);

    system("PAUSE");

    getchar();

    return 0;
}