#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "./src/Q1.h"

int main(){
    int opc, sucesso, idcurso, qtdperiodos, coddisc, semestre;
    int notafinal;
    char buffer[50], nomecurso[50];

    Cursos *c;
    Matricula *m;
    Notas *n;
    m = NULL;
    n = NULL;
    c = NULL;

    while(1){
        system("cls");
        printf("MENU DO SISTEMA\n");
        printf("1. Cadastrar alunos\n");
        printf("2. Cadastrar curso\n");
        printf("3. Cadastrar disciplina\n");
        printf("4. Cadastrar matricula\n");
        printf("5. Cadastrar nota\n");
        printf("6. Mostrar todos os alunos de um determinado curso\n");
        printf("7. Mostrar todos os cursos do campus\n");
        printf("8. Mostrar todas as disciplinas de um determinado curso\n");
        printf("9. Mostrar todas as disciplinas de um determinado periodo de um curso\n");
        printf("10. Mostrar todas as disciplinas que um determinado aluno esta matriculado\n");
        printf("11. Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno\n");
        printf("12. Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horaria da disciplina\n");
        printf("13. Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na mesma\n");
        printf("14. Permita remover uma disciplina da arvore de matrícula de um determinado aluno\n");
        printf("15. Mostrar o historico de um determinado aluno\n");
        printf("16. Exibir cursos\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            break;
        case 2:
            system("cls");
            printf("CADASTRAR CURSO\n");
            printf("Digite o ID do curso: ");
            scanf("%d", &idcurso);
            printf("Digite o nome do curso: ");
            scanf("%s", nomecurso);
            printf("Digite a quantidade de periodos: ");
            scanf("%d", &qtdperiodos);
            cadcurso(&c, idcurso, nomecurso, qtdperiodos);
            system("PAUSE");
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            // Lembrar de implementar aqui a buscamat e tirar da função
            system("cls");
            printf("CADASTRAR NOTA\n");
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &coddisc);
            printf("Digite o semestre: ");
            scanf("%d", &semestre);
            printf("Cadastre a nota final: ");
            scanf("%f", &notafinal);
            cadnota(&m, &n, coddisc, semestre, notafinal);
            break;
        case 16:
            system("cls");
            exibircurso(c);
            system("PAUSE");
            break;
        case 0:
            break;
        default:
            break;
        }
    }

    return 0;
}