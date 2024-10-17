#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q1.h"

#define QTD_CURSOS 1000
#define ID_CURSOS 10000
#define QTD_ALUNOS 1000
#define QTD_DISCIPLINAS 10
#define QTD_MATRICULAS 10
#define REPEAT 100000

/*---------------------------------------------------------------------------------------------------------------*/

/*
Funções de povoamento das arvores de forma crescente, decrescente e aleatória.
*/

// CRESCENTE

void povoar_cursos_crescente(Cursos **raiz){ 
    for (int i = 1; i < QTD_CURSOS; i++){
        cadcurso(raiz, i, "Engenharia de Software", 8);
    }
}

void povoar_disciplinas_crescente(Cursos **raiz){
    if (*raiz != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
            d->cargah = 60;
            d->periodo = 3;
            d->cod_disciplina = i;
            caddisc(raiz, d, (*raiz)->idcurso);
        }
        povoar_disciplinas_crescente(&(*raiz)->esq);
        povoar_disciplinas_crescente(&(*raiz)->dir);
    }
}

void povoar_matriculas_crescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = 1; i < QTD_MATRICULAS; i++){
            cadmatricula(&aluno, i, aluno->matricula);
        }
        povoar_matriculas_crescente(aluno->prox);
    }
}

void povoar_notas_crescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = 8;
            cadnota(&aluno, aluno->matricula, i, n->semestre, n->notafinal);
        }
        povoar_notas_crescente(aluno->prox);
    }
}

void povoar_alunos_crescente(Alunos **aluno, Cursos *curso){
    int sucesso = 0;
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1; i < QTD_ALUNOS; i++){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// DESCRESCENTE

void povoar_cursos_decrescente(Cursos **raiz){
    for (int i = QTD_CURSOS; i > 1; i--){
        cadcurso(raiz, i, "Engenharia de Software", 8);
    }
}

void povoar_disciplinas_decrescente(Cursos **raiz){
    if (*raiz != NULL){
        for (int i = QTD_DISCIPLINAS; i > 1; i--){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
            d->cargah = 60;
            d->periodo = 3;
            d->cod_disciplina = i;
            caddisc(raiz, d, (*raiz)->idcurso);
        }
        povoar_disciplinas_decrescente(&(*raiz)->esq);
        povoar_disciplinas_decrescente(&(*raiz)->dir);
    }
}

void povoar_matriculas_decrescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = QTD_MATRICULAS; i > 1; i--){
            cadmatricula(&aluno, i, aluno->matricula);
        }
        povoar_matriculas_decrescente(aluno->prox);
    }
}

void povoar_notas_decrescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = QTD_DISCIPLINAS; i > 1; i--){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, i, n->semestre, n->notafinal);
        }
        povoar_notas_decrescente(aluno->prox);
    }
}

void povoar_alunos_descrescente(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = QTD_ALUNOS; i > 1; i--){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// ALEATÓRIO

void povoar_cursos_aleatorio(Cursos **raiz){
    int i = 0, sucesso = 0;
    while (i < QTD_CURSOS){
        if (cadcurso(raiz, rand() % QTD_CURSOS + 1, "Engenharia de Software", 8) == 1)
            i++;
    }
}

void povoar_disciplinas_aleatorio(Cursos **raiz){
    if (*raiz != NULL){
        int i = 0;
        while (i < QTD_DISCIPLINAS){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos");
            d->cod_disciplina = rand() % QTD_DISCIPLINAS + 1;
            d->cargah = 60;
            d->periodo = 3;
            if (caddisc(raiz, d, (*raiz)->idcurso) == 1)
                i++;
        }
        povoar_disciplinas_aleatorio(&(*raiz)->esq);
        povoar_disciplinas_aleatorio(&(*raiz)->dir);
    }
}

void povoar_alunos_aleatorio(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    int i = 0;
    for (i = 0; i < QTD_ALUNOS; i++){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS + 1);
    }
}

void povoar_matricula_aleatorio(Alunos *aluno){
    if (aluno != NULL){
        int i = 0;
        while (i < QTD_MATRICULAS){
            if (cadmatricula(&aluno, rand() % QTD_MATRICULAS + 1, aluno->matricula) == 1)
                i++;
        }
        povoar_matricula_aleatorio(aluno->prox);
    }
}

void povoar_notas_aleatorio(Alunos *aluno){
    if (aluno != NULL){
        int i = 0;
        while (i < QTD_DISCIPLINAS){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = rand() % QTD_DISCIPLINAS + 1;
            n->semestre = 3;
            n->notafinal = 8;
            if (cadnota(&aluno, aluno->matricula, n->coddisc, n->semestre, n->notafinal) == 1)
                i++;
        }
        povoar_notas_aleatorio(aluno->prox);
    }
}

void exibir_alunos(Alunos *alunos){
    if (alunos != NULL){
        printf("Matricula: %d\n", alunos->matricula);
        printf("Nome: %s\n", alunos->nome);
        printf("Codigo do Curso: %d\n", alunos->codcurso);
        printf("\n");
        exibir_alunos(alunos->prox);
    }
}

void exibir_disciplins(Disciplina *disc){
    if (disc != NULL){
        printf("Codigo: %d\n", disc->cod_disciplina);
        printf("Nome: %s\n", disc->nomedisc);
        printf("Carga horaria: %d\n", disc->cargah);
        printf("Periodo: %d\n", disc->periodo);
        printf("\n");
        exibir_disciplins(disc->esq);
        exibir_disciplins(disc->dir);
    }
}

void exibir_DisciplinasMain(Cursos *curso){
    if (curso != NULL){
        printf("IDCurso: %d\n", curso->idcurso);
        exibir_disciplins(curso->disc);
        exibir_DisciplinasMain(curso->esq);
        exibir_DisciplinasMain(curso->dir);
    }
}

void exibir_matriculas(Matricula *matriculas){
    if (matriculas != NULL){
        printf("CodigoDisc: %d\n", matriculas->coddisc);
        exibir_matriculas(matriculas->esq);
        exibir_matriculas(matriculas->dir);
    }
}

void exibir_matriculasMain(Alunos *alunos){
    if (alunos != NULL){
        printf("MatriculaAluno: %d\n", alunos->matricula);
        exibir_matriculas(alunos->mat);
        exibir_matriculasMain(alunos->prox);
    }
}

void exibir_nots(Notas *notas){
    if (notas != NULL){
        printf("CodigoDisc: %d\n", notas->coddisc);
        printf("Nota: %.2f\n", notas->notafinal);
        printf("Semestre: %d\n", notas->semestre);
        printf("\n");
        exibir_nots(notas->esq);
        exibir_nots(notas->dir);
    }
}

void exibir_notasMain(Alunos *alunos){
    if (alunos != NULL){
        printf("Matricula: %d\n", alunos->matricula);
        exibir_nots(alunos->nota);
        exibir_notasMain(alunos->prox);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

void povoamento_crescente(Cursos **raiz, Alunos **alunos){
    povoar_cursos_crescente(raiz);
    povoar_disciplinas_crescente(raiz);
    povoar_alunos_crescente(alunos, *raiz);
    povoar_matriculas_crescente(*alunos);
    povoar_notas_crescente(*alunos);
}

void povoamento_decrescente(Cursos **raiz, Alunos **alunos){
    povoar_cursos_decrescente(raiz);
    povoar_disciplinas_decrescente(raiz);
    povoar_alunos_descrescente(alunos, *raiz);
    povoar_matriculas_decrescente(*alunos);
    povoar_notas_decrescente(*alunos);
}

void povoamento_aleatorio(Cursos **raiz, Alunos **alunos){
    povoar_cursos_aleatorio(raiz);
    povoar_disciplinas_aleatorio(raiz);
    povoar_alunos_aleatorio(alunos, *raiz);
    povoar_matricula_aleatorio(*alunos);
    povoar_notas_aleatorio(*alunos);
}

void menu_povoamento(){
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    printf("3 - Aleatorio\n");
    printf("Escolha a forma de povoamento das arvores:\n");
}

/*---------------------------------------------------------------------------------------------------------------*/

// METRIFICANDO O TEMPO

double metrificar_tempo_por_busca_nota(Alunos *alunos, Cursos *raiz) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int i;

    int aluno_rand = 543;
    int disc_rand = 4;


    // Executa a busca várias vezes para obter uma média mais precisa
    for (i = 0; i < REPEAT; i++) {
        Alunos *aux = alunos;
        Cursos *aux2 = raiz;
        inicio = clock();
        notadiscporaluno(aux, aux2, aluno_rand, disc_rand);  // Função de busca
        fim = clock();

        // Soma o tempo de cada execução
        tempo_total += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    // Retorna o tempo médio por busca
    return tempo_total / REPEAT;
}

double metrificar_tempo_por_insercao(Cursos **curso, int opc){
    clock_t inicio, fim;
    double tempo = 0.0;
    int i;
    for(i = 0; i < REPEAT; i++){
        inicio = clock();
        cadcurso(curso, rand() % ID_CURSOS + 1, "Curso", 8);
        fim = clock();

        tempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    liberar_cursos(curso);
    if (opc == 1)
        povoar_cursos_crescente(curso);
    else if (opc == 2)
        povoar_cursos_decrescente(curso);
    else
        povoar_cursos_aleatorio(curso);
    return tempo / REPEAT;
}
/*---------------------------------------------------------------------------------------------------------------*/

int main (){
    srand(time(NULL));
    Cursos *raiz;
    Alunos *alunos;
    alunos = NULL;
    raiz = NULL;

    int op, i;
    double tempo;

    menu_povoamento();
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        povoamento_crescente(&raiz, &alunos);
        break;
    case 2:
        povoamento_decrescente(&raiz, &alunos);
        break;
    case 3:
        povoamento_aleatorio(&raiz, &alunos);
        break;
    default:
        break;
    }

    // Metrificando o tempo de busca da nota de uma disciplina de um determinado aluno.
    for(i = 0; i < 10; i++){
        tempo = metrificar_tempo_por_busca_nota(alunos, raiz);
        printf("Tempo de busca da nota de uma disciplina de um determinado aluno: %.2f\n", tempo * 1000000); // Microsegundos
    }

    // Metrificando o tempo de inserção de um curso
    for(i = 0; i < 10; i++){
        tempo = metrificar_tempo_por_insercao(&raiz, op);
        printf("Tempo de insercao do curso: %.2f\n", tempo*1000000); // Microsegundos
    }

    system("PAUSE");
    liberar_alunos(alunos);
    liberar_cursos(&raiz);
    return 0;
}