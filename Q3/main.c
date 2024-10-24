#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q3.h"

/*
    summary
        Essa função é responsável por exibir o menu geral do programa.
    param
        void
*/
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

/*
    summary
        Função responsável por cadastrar um aluno.
    param
        Alunos **aluno, AVLCurso *curso, int matricula, char *nome, int codcurso
    return
        int - 1 se o aluno foi cadastrado com sucesso, 0 caso contrário
*/
int buscar_aluno(Alunos *aluno, int matricula){
    int enc = 0;
    if(aluno != NULL){
        if(aluno->matricula == matricula)
            enc = 1;
        else
            enc = buscar_aluno(aluno->prox, matricula);
    }
    return enc;
}

/*
    summary
        Função principal do programa.
    param
        void
*/
int main(){

    AVLCurso *curso;
    AVLDisc *disc;
    AVLMatricula *mat;  
    AVLNotas *nota;
    Alunos *aluno;
    curso = NULL;
    disc = NULL;
    mat = NULL;
    nota = NULL;
    aluno = NULL;

    int opc, opc1, sucesso, idcurso, qtdperiodos;
    int matricula, coddisc, intbuffer, ib2;
    float notafinal;
    int matcomp, idcursocomp, coddisccomp, periodocomp;
    char buffer[50], nomecurso[50];

    while(1){
        menugeral();
        scanf("%d", &opc);
        switch(opc){
            case 1:
                printf("\nCADASTRO DE ALUNOS\n");
                printf("\nDigite a matricula: ");
                scanf("%d", &matricula);
                printf("\nDigite o nome: ");
                scanf("%s", buffer);
                printf("\nDeseja visualizar os cursos disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &opc1);
                if(opc1 == 1)
                    exibir_cursos(curso);
                printf("\n\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                sucesso = cadaluno(&aluno, curso, matricula, buffer, idcurso);
                if(sucesso == 1)
                    printf("Aluno cadastrado com sucesso!\n");
                break;
            case 2:
                printf("\nCADASTRO DE CURSO\n");
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                printf("\nDigite o nome do curso: ");
                scanf("%s", nomecurso);
                printf("\nDigite a quantidade de periodos: ");
                scanf("%d", &qtdperiodos);
                AVLCurso *cursoatual = (AVLCurso*)malloc(sizeof(AVLCurso));
                cursoatual->info = (Cursos*)malloc(sizeof(Cursos));
                cursoatual->info->idcurso = idcurso;
                strcpy(cursoatual->info->nomecurso, nomecurso);
                cursoatual->info->qntdperiodos = qtdperiodos;
                cursoatual->info->disc = NULL;
                cursoatual->altura = 0;
                cursoatual->esq = NULL;
                cursoatual->dir = NULL;
                sucesso = cadcurso(&curso, cursoatual);
                if(sucesso == 1)
                    printf("Curso cadastrado com sucesso!\n");
                break;
            case 3:
                printf("\nCADASTRO DE DISCIPLINA\n");
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisc);
                printf("\nDigite o nome da disciplina: ");
                scanf("%s", buffer);
                printf("\nDigite a carga horaria: ");
                scanf("%d", &intbuffer);
                printf("\nDigite o periodo: ");
                scanf("%d", &opc1);
                printf("\nDeseja visualizar os cursos disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &ib2);
                if(ib2 == 1)
                    exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                AVLDisc *discatual = (AVLDisc*)malloc(sizeof(AVLDisc));
                discatual->info = (Disciplina*)malloc(sizeof(Disciplina));
                discatual->info->cod_disciplina = coddisc;
                strcpy(discatual->info->nomedisc, buffer);
                discatual->info->cargah = intbuffer;
                discatual->info->periodo = opc1;
                discatual->esq = NULL;
                discatual->dir = NULL;
                sucesso = caddisc(&curso, discatual, idcurso);
                if(sucesso == 1)
                    printf("Disciplina cadastrada com sucesso!\n");
                break;
            case 4:
                printf("\nCADASTRO DE MATRICULA\n");
                printf("\nDesaja visualizar as disciplinas do curso disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &opc1);
                if(opc1 == 1)
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcurso);
                    // Exibir as disciplinas do curso void exibir_disc_curso_main(AVLCurso *curso, int idcurso)
                    exibir_disc_curso_main(curso, idcurso);
                    
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisc);
                printf("\nDesaja visualizar os alunos disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &opc1);
                if(opc1 == 1)
                    alunosporcurso(aluno, idcurso);
                printf("\nDigite a matricula do aluno: ");
                scanf("%d", &matricula);
                sucesso = cadmatricula(&aluno, curso, coddisc, matricula);
                if(sucesso == 1)
                    printf("Matricula realizada com sucesso!\n");
                break;
            case 5:
                printf("\nCADASTRO DE NOTA\n");
                printf("\nDeseja visualizar as disciplinas do aluno disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &opc1);
                if(opc1 == 1)
                    // Exibir os alunos disponiveis void exibir_disc_aluno_main(Alunos *aluno, AVLCurso *cursos, int matricula)
                    exibir_cursos(curso);
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcurso);
                    alunosporcurso(aluno, idcurso);
                    printf("\nDigite o codigo do aluno: ");
                    scanf("%d", &matcomp);
                    exibir_hist_aluno(aluno, curso, matcomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisc);
                printf("\nDigite a matricula do aluno: ");
                scanf("%d", &matricula);
                printf("\nDigite o semestre: ");
                scanf("%d", &intbuffer);
                printf("\nDigite a nota final: ");
                scanf("%f", &notafinal);
                Alunos *alunoatual = buscar_aluno(aluno, matricula);
                Notas *notaatual = (Notas*)malloc(sizeof(Notas));
                notaatual->coddisc = coddisc;
                notaatual->semestre = intbuffer;
                notaatual->notafinal = notafinal;
                sucesso = cadnota(&nota, matricula, notaatual);
                if(sucesso == 1)
                    printf("Nota cadastrada com sucesso!\n");
                break;
            case 6:
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                exibircurso(buscar_curso(curso, idcursocomp));
                break;
            case 7:
                exibir_cursos(curso);
                break;
            case 8:
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                exibirDiscCurso(curso, idcursocomp);
                break;
            case 9:
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                printf("\nDigite o periodo da disciplina: ");
                scanf("%d", &periodocomp);
                exibirDiscPeriodo(curso, idcursocomp, periodocomp);
                break;
            case 10:
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibirDiscAluno(aluno, curso, matcomp);
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
                notadiscporaluno(aluno, curso, matcomp, coddisccomp);
                break;
            case 13:
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisccomp);
                int remove = rmvDiscCurso(&curso, aluno, idcursocomp, coddisccomp);
                if (remove == 1)
                    printf("Disciplina removida com sucesso!\n");
                break;
            case 14:
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisccomp);
                rmvmatdealuno(&aluno, matcomp, coddisccomp);
                break;
            case 15:
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibir_hist_aluno(aluno, curso, matcomp);
                break;
            case 16:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
            system("PAUSE");
            system("cls");
        }
    }

    // Liberando a memória alocada
    liberarAVLCurso(&curso);
    liberarAVLDisc(&disc);
    liberarAVLMatricula(&mat);
    liberarAVLNotas(&nota);
    liberarAlunos(&aluno);

    return 0;
}