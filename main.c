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
    int opc, opc1, sucesso, idcurso, qtdperiodos, cpf;
    int matricula, coddisc;
    int matcomp, idcursocomp, coddisccomp, periodocomp;
    char buffer[50], nomecurso[50], nomedisc[50];

    Alunos *aluno;
    Cursos *curso;
    Disciplina *disc;
    Notas *nota;
    Matricula *mat;
    curso = NULL;
    disc = NULL;
    nota = NULL;
    mat = NULL;

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
            while(1){
                system("cls");
                menugeral();
                printf("Digite a opcao desejada: ");
                scanf("%d", &opc1);

                switch (opc1)
                {
                case 1:
                    printf("\n\nCADASTRO DE ALUNO\n");
                    printf("\nDigite o nome do aluno: ");
                    scanf("%s", buffer);
                    printf("\nDigite o CPF do aluno: ");
                    scanf("%d", &cpf);
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    gerarMatriculaAluno(idcursocomp, &matricula);
                    cadaluno(&aluno, matricula, buffer, idcursocomp);
                    printf("\nMatricula gerada: %d\n", matricula);
                    printf("Aluno cadastrado com sucesso!\n");
                    break;
                case 2:
                    printf("\nCADASTRO DE CURSO\n");
                    printf("\nDigite o nome do curso: ");
                    scanf("%s", nomecurso);
                    printf("\nDigite a quantidade de periodos: ");
                    scanf("%d", &qtdperiodos);
                    gerarIdCurso(qtdperiodos, &idcurso);
                    sucesso = cadcurso(&curso, idcurso, nomecurso, qtdperiodos);
                    if(sucesso){
                        printf("\nCodigo do curso gerado: %d\n", idcurso);
                        printf("Curso cadastrado com sucesso!\n");
                    }
                    else{
                        printf("Erro ao cadastrar curso!\n");
                    }
                    break;
                case 3:
                    disc = (Disciplina*)malloc(sizeof(Disciplina));
                    printf("\nCADASTRO DE DISCIPLINA\n");
                    printf("\nDigite o nome da disciplina: ");
                    scanf("%s", disc->nomedisc);
                    printf("\nDigite a carga horaria da disciplina: ");
                    scanf("%d", &disc->cargah);
                    printf("\nDigite o periodo da disciplina: ");
                    scanf("%d", &disc->periodo);
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    gerarCodDisciplina(disc->cargah, disc->periodo, &coddisc);
                    disc->cod_disciplina = coddisc;
                    sucesso = caddisc(&curso, disc, idcurso);
                    if(sucesso){
                        printf("\nCodigo da disciplina gerado: %d\n", coddisc);
                        printf("\nDisciplina cadastrada com sucesso!\n");
                    }
                    else
                        printf("Erro ao cadastrar disciplina!\n");
                    break;
                case 4:
                    printf("\nCADASTRO DE MATRICULA\n");
                    printf("\nDigite o codigo da disciplina: ");
                    scanf("%d", &coddisccomp);
                    printf("\nDigite o matricula do aluno: ");
                    scanf("%d", &matcomp);
                    cadmatricula(&aluno, coddisccomp, matcomp);
                    printf("Matricula cadastrada com sucesso!\n");
                    break;
                case 5:
                    printf("\nCADASTRO DE NOTA\n");
                    printf("\nDigite o codigo da disciplina: ");
                    scanf("%d", &coddisccomp);
                    printf("\nDigite o matricula do aluno: ");
                    scanf("%d", &matcomp);
                    printf("\nDigite o semestre: ");
                    scanf("%d", &aluno->nota->semestre);
                    printf("\nDigite a nota final: ");
                    scanf("%d", &aluno->nota->notafinal);
                    int sucesso = cadnota(&aluno, matcomp, coddisccomp, aluno->nota->semestre, aluno->nota->notafinal);
                    if(sucesso == 1)
                        printf("Nota cadastrada com sucesso!\n");
                    break;
                case 6:
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    alunosporcurso(&aluno, &curso, idcursocomp);
                    break;
                case 7:
                    exibir_cursos(curso);
                    break;
                case 8:
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    exibir_disc_curso_main(curso, idcursocomp);
                    break;
                case 9:
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    printf("\nDigite o periodo da disciplina: ");
                    scanf("%d", &periodocomp);
                    exibir_disc_periodo_main(curso, idcursocomp, periodocomp);
                    break;
                case 10:
                    printf("\nDigite o codigo do aluno: ");
                    scanf("%d", &matcomp);
                    exibir_disc_aluno_main(aluno, curso, matcomp);
                    break;
                case 11:
                    printf("\nDigite o codigo do aluno: ");
                    scanf("%d", &matcomp);
                    printf("\nDigite o periodo: ");
                    scanf("%d", &periodocomp);
                    notasdiscperiodoaluno(aluno, periodocomp, matcomp);
                    break;
                case 12:
                    printf("\nDigite o codigo do aluno: ");
                    scanf("%d", &matcomp);
                    printf("\nDigite o codigo da disciplina: ");
                    scanf("%d", &coddisccomp);
                    notadiscporaluno(aluno, matcomp, coddisccomp);
                    break;
                case 13:
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcursocomp);
                    printf("\nDigite o codigo da disciplina: ");
                    scanf("%d", &coddisccomp);
                    int remove = rmvdisc_curso(&curso, aluno, idcursocomp, coddisccomp);
                    printf("Disciplina removida com sucesso!\n");
                    break;
                case 14:
                    printf("\nDigite o codigo do aluno: ");
                    scanf("%d", &matcomp);
                    printf("\nDigite o codigo da disciplina: ");
                    scanf("%d", &coddisccomp);
                    rmvmatdealuno(&aluno, mat, matcomp, &coddisccomp);
                    printf("Disciplina removida com sucesso!\n");
                    break;
                case 15:
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
                }
                system("PAUSE");
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