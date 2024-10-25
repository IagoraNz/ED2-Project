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
    printf("\xBA 16. Sair                                 \xBA\n");
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

int cod_curso(Alunos *aluno, int matricula){
    int codcurso;
    if(aluno != NULL){
        if(aluno->matricula == matricula)
            codcurso = aluno->codcurso;
        else
            codcurso = cod_curso(aluno->prox, matricula);
    }
    return codcurso;
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

    while(opc != 16){
        menugeral();
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                printf("\nCADASTRO DE ALUNOS\n");
                printf("\nDigite o nome: ");
                scanf("%s", buffer);
                exibir_cursos(curso);
                printf("\n\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                gerarMatriculaAluno(idcurso, &matricula);
                sucesso = cadaluno(&aluno, curso, matricula, buffer, idcurso);
                if(sucesso == 1)
                    printf("Aluno cadastrado com sucesso!\n");
                break;
            case 2:
                printf("\nCADASTRO DE CURSO\n");
                printf("\nDigite o nome do curso: ");
                scanf("%s", nomecurso);
                printf("\nDigite a quantidade de periodos: ");
                scanf("%d", &qtdperiodos);
                gerarIdCurso(qtdperiodos, &idcurso);
                Cursos *cursoatual = (Cursos*)malloc(sizeof(Cursos));
                cursoatual->idcurso = idcurso;
                strcpy(cursoatual->nomecurso, nomecurso);
                cursoatual->qntdperiodos = qtdperiodos;
                cursoatual->disc = NULL;
                sucesso = cadcurso(&curso, cursoatual);
                if(sucesso == 1)
                    printf("Curso cadastrado com sucesso!\n");
                break;
            case 3:
                printf("\nCADASTRO DE DISCIPLINA\n");
                printf("\nDigite o nome da disciplina: ");
                scanf("%s", buffer);
                printf("\nDigite a carga horaria: ");
                scanf("%d", &intbuffer);
                printf("\nDigite o periodo: ");
                scanf("%d", &opc1);
                gerarCodDisciplina(intbuffer, opc1, &coddisc);
                printf("\nDeseja visualizar os cursos disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &ib2);
                if(ib2 == 1)
                    exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                Disciplina *discatual = (Disciplina*)malloc(sizeof(Disciplina));
                discatual->cod_disciplina = coddisc;
                strcpy(discatual->nomedisc, buffer);
                discatual->cargah = intbuffer;
                discatual->periodo = opc1;
                sucesso = caddisc(&curso, discatual, idcurso);
                if(sucesso == 1)
                    printf("Disciplina cadastrada com sucesso!\n");
                break;
            case 4:
                printf("\nCADASTRO DE MATRICULA\n");
                printf("\nDesaja visualizar as disciplinas do curso disponiveis? (1 - Sim, 0 - Nao): ");
                scanf("%d", &opc1);
                if(opc1 == 1){
                    exibir_cursos(curso);
                    printf("\nDigite o codigo do curso: ");
                    scanf("%d", &idcurso);
                    exibirDiscCurso(curso, idcurso);
                }
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
                exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcurso);
                alunosporcurso(aluno, idcurso);
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibirDiscAluno(aluno, curso, matcomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisc);
                printf("\nDigite o semestre: ");
                scanf("%d", &intbuffer);
                printf("\nDigite a nota final: ");
                scanf("%f", &notafinal);
                Notas *notaatual = (Notas*)malloc(sizeof(Notas));
                notaatual->coddisc = coddisc;
                notaatual->semestre = intbuffer;
                notaatual->notafinal = notafinal;
                sucesso = cadnota(&aluno, matcomp, notaatual);
                if(sucesso == 1)
                    printf("Nota cadastrada com sucesso!\n");
                break;
            case 6:
                exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                alunosporcurso(aluno, idcursocomp);
                break;
            case 7:
                exibir_cursos(curso);
                break;
            case 8:
                exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                exibirDiscCurso(curso, idcursocomp);
                break;
            case 9:
                exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                printf("\nDigite o periodo da disciplina: ");
                scanf("%d", &periodocomp);
                exibirDiscPeriodo(curso, idcursocomp, periodocomp);
                break;
            case 10:
                exibir_alunos(aluno);
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibirDiscAluno(aluno, curso, matcomp);
                break;
            case 11:
                exibir_alunos(aluno);
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                printf("\nDigite o periodo: ");
                scanf("%d", &periodocomp);
                notasdiscperiodoaluno(aluno, periodocomp, matcomp);
                break;
            case 12:
                exibir_alunos(aluno);
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibirDiscCurso(curso, cod_curso(aluno, matcomp));
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisccomp);
                notadiscporaluno(aluno, curso, matcomp, coddisccomp);
                break;
            case 13:
                exibir_cursos(curso);
                printf("\nDigite o codigo do curso: ");
                scanf("%d", &idcursocomp);
                exibirDiscCurso(curso, idcursocomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisccomp);
                int remove = rmvDiscCurso(&curso, aluno, idcursocomp, coddisccomp);
                if (remove == 1)
                    printf("Disciplina removida com sucesso!\n");
                break;
            case 14:
                exibir_alunos(aluno);
                printf("\nDigite o codigo do aluno: ");
                scanf("%d", &matcomp);
                exibirDiscAluno(aluno, curso, matcomp);
                printf("\nDigite o codigo da disciplina: ");
                scanf("%d", &coddisccomp);
                rmvmatdealuno(&aluno, matcomp, coddisccomp);
                break;
            case 15:
                exibir_alunos(aluno);
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