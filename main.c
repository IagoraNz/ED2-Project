#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "./src/Q1.h"

void menugeral(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA            M E N U   G E R A L           \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar alunos                      \xBA\n");
    printf("\xBA 2. Cadastrar curso                       \xBA\n");
    printf("\xBA 3. Cadastrar disciplina                  \xBA\n");
    printf("\xBA 4. Cadastrar matricula                   \xBA\n");
    printf("\xBA 5. Cadastrar nota                        \xBA\n");
    printf("\xBA 6. Mostrar todos os alunos de um         \xBA\n");
    printf("\xBA    determinado curso                     \xBA\n");
    printf("\xBA 7. Mostrar todos os cursos do campus     \xBA\n");
    printf("\xBA 8. Mostrar todas as disciplinas de um    \xBA\n");
    printf("\xBA    determinado curso                     \xBA\n");
    printf("\xBA 9. Mostrar todas as disciplinas de um    \xBA\n");
    printf("\xBA    determinado periodo de um curso       \xBA\n");
    printf("\xBA 10. Mostrar todas as disciplinas que um  \xBA\n");
    printf("\xBA     determinado aluno esta matriculado   \xBA\n");
    printf("\xBA 11. Mostrar todas as notas de disciplinas\xBA\n");
    printf("\xBA     de um determinado periodo de um      \xBA\n");
    printf("\xBA     determinado aluno                    \xBA\n");
    printf("\xBA 12. Mostrar a nota de uma disciplina de  \xBA\n");
    printf("\xBA     um determinado aluno, mostrando o    \xBA\n");
    printf("\xBA     periodo e a carga horaria da         \xBA\n");
    printf("\xBA     disciplina                           \xBA\n");
    printf("\xBA 13. Remover uma disciplina de um         \xBA\n");
    printf("\xBA     determinado curso desde que nao      \xBA\n");
    printf("\xBA     tenha nenhum aluno matriculado na    \xBA\n");
    printf("\xBA     mesma                                \xBA\n");
    printf("\xBA 14. Permita remover uma disciplina da    \xBA\n");
    printf("\xBA     arvore de matricula de um            \xBA\n");
    printf("\xBA     determinado aluno                    \xBA\n");
    printf("\xBA 15. Mostrar o historico de um            \xBA\n");
    printf("\xBA     determinado aluno                    \xBA\n");
    printf("\xBA 16. Voltar                               \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBC\n");
}

void menudisc(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA        M E N U   D I S C I P L I N A     \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar disciplina                  \xBA\n");
    printf("\xBA 2. Remover disciplina                    \xBA\n");
    printf("\xBA 3. Mostrar todas as disciplinas          \xBA\n");
    printf("\xBA 4. Mostrar todas as disciplinas de um    \xBA\n");
    printf("\xBA    determinado curso                     \xBA\n");
    printf("\xBA 5. Mostrar todas as disciplinas de um    \xBA\n");
    printf("\xBA    determinado periodo de um curso       \xBA\n");
    printf("\xBA 6. Mostrar todas as disciplinas que um   \xBA\n");
    printf("\xBA     determinado aluno esta matriculado   \xBA\n");
    printf("\xBA 7. Voltar                                \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
}

void menucurso(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA           M E N U   C U R S O            \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar curso                       \xBA\n");
    printf("\xBA 2. Remover curso                         \xBA\n");
    printf("\xBA 3. Mostrar todos os cursos do campus     \xBA\n");
    printf("\xBA 4. Voltar                                \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
}

void menunota(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA            M E N U   N O T A             \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar nota                        \xBA\n");
    printf("\xBA 2. Remover nota                          \xBA\n");
    printf("\xBA 3. Mostrar todas as notas de disciplinas \xBA\n");
    printf("\xBA 4. Mostrar todas as notas de disciplinas \xBA\n");
    printf("\xBA    de um determinado periodo de um      \xBA\n");
    printf("\xBA    determinado aluno                     \xBA\n");
    printf("\xBA 5. Mostrar a nota de uma disciplina de   \xBA\n");
    printf("\xBA    um determinado aluno, mostrando o     \xBA\n");
    printf("\xBA    periodo e a carga horaria da          \xBA\n");
    printf("\xBA    disciplina                            \xBA\n");
    printf("\xBA 6. Exibir notas                          \xBA\n");
    printf("\xBA 7. Voltar                                \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
}

void menumatricula(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA         M E N U   M A T R I C U L A       \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar matricula                   \xBA\n");
    printf("\xBA 2. Remover matricula                     \xBA\n");
    printf("\xBA 3. Mostrar todas as disciplinas que um   \xBA\n");
    printf("\xBA    determinado aluno esta matriculado    \xBA\n");
    printf("\xBA 4. Remover uma disciplina da arvore de   \xBA\n");
    printf("\xBA    matricula de um determinado aluno     \xBA\n");
    printf("\xBA 5. Mostrar o historico de um determinado \xBA\n");
    printf("\xBA    aluno                                 \xBA\n");
    printf("\xBA 6. Exibir matricula                      \xBA\n");
    printf("\xBA 7. Voltar                                \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
}

void menualuno(){
    int i;
    printf("\xC9");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
    printf("\xBB\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA           M E N U   A L U N O            \xBA\n");
    printf("\xBA                                          \xBA\n");
    printf("\xBA 1. Cadastrar aluno                       \xBA\n");
    printf("\xBA 2. Remover aluno                         \xBA\n");
    printf("\xBA 3. Mostrar todos os alunos de um         \xBA\n");
    printf("\xBA    determinado curso                     \xBA\n");
    printf("\xBA 4. Mostrar o historico de um determinado \xBA\n");
    printf("\xBA    aluno                                 \xBA\n");
    printf("\xBA 5. Exibir aluno                          \xBA\n");
    printf("\xBA 6. Voltar                                \xBA\n");
    printf("\xC8");
    for(i = 0; i < 42; i++){
        printf("\xCD");
    }
}

int main(){
    int opc, opc1, sucesso, idcurso, qtdperiodos;
    char buffer[50], nomecurso[50];

    Cursos *c;
    Matricula *m;
    c = NULL;
    m = NULL;

    while(1){
        system("cls");
        printf("\xC9");
        for(int i = 0; i < 41; i++){
            printf("\xCD");
        }
        printf("\xBB\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA       M E N U   P R I N C I P A L       \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 1. Menu geral                           \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 2. Menu de disciplina                   \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 3. Menu de cursos                       \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 4. Menu de notas                        \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 5. Menu de matricula                    \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA 6. Menu de alunos                       \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA Developers:                             \xBA\n");
        printf("\xBA      I. Iago Roberto Esmerio Almeida    \xBA\n");
        printf("\xBA      II. Francinaldo de Sousa Barbosa   \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA Professora:                             \xBA\n");
        printf("\xBA      Juliana Oliveira de Carvalho       \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA                    Aproveite o sistema! \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA                                         \xBA\n");
        printf("\xBA Pressione o numero para                 \xBA\n");
        printf("\xBA escolher o menu...                      \xBA\n");
        printf("\xC8");
        for (int i = 0; i < 41; i++) {
            printf("\xCD");
        }
        printf("\xBC\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            /*--------------------------------------------------------------------------------------------------------*/
            /* i. O menu geral contém as principais funções listadas no escopo e descrição do projeto */
            system("cls");
            menugeral();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);

            switch (opc1)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            default:
                break;
            }
            break;
            /*--------------------------------------------------------------------------------------------------------*/
            /* ii. Os demais menus a seguir contém as funções de cadastro, remoção e exibição de disciplinas e
            outras funções classificadas de acordo com a relação com a sua respectiva estrutura */
        case 2:
            system("cls");
            menudisc();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);

            switch (opc1)
            {
            case 1:
                printf("\nCADASTRO DE DISCIPLINA\n");
                printf("\nDigite o nome da disciplina: ");
                
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
            }
            break;
        case 3:
            system("cls");
            menucurso();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);

            switch (opc1)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
            }
            break;
        case 4:
            system("cls");
            menunota();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);

            switch (opc1)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
            }
            break;
        case 5:
            system("cls");
            menumatricula();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);
            switch (opc1)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
            }
            break;
        case 6:
            system("cls");
            menualuno();
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc1);
            switch (opc1)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}