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
#define REPEAT 10000

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
            caddisc(raiz, d, 1);
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
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, i, n->semestre, n->notafinal);
        }
        povoar_notas_crescente(aluno->prox);
    }
}

void povoar_alunos_crescente(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1; i < QTD_ALUNOS; i++){
        cadaluno(aluno, i, nomes[rand() % 5], rand() % QTD_CURSOS);
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
            caddisc(raiz, d, 1);
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
        cadaluno(aluno, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// ALEATÓRIO

void povoar_cursos_aleatorio(Cursos **raiz){
    int i = 1, sucesso = 0;
    while (i < QTD_CURSOS){
        if (cadcurso(raiz, rand() % QTD_CURSOS, "Engenharia de Software", 8) == 1)
            i++;
    }
}

void povoar_disciplinas_aleatorio(Cursos **raiz){
    if (*raiz != NULL){
        int i = 1, sucesso = 0;
        while (i < QTD_DISCIPLINAS){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
            d->cargah = 60;
            d->periodo = 3;
            d->cod_disciplina = rand() % QTD_DISCIPLINAS;
            if (caddisc(raiz, d, (*raiz)->idcurso) == 1)
                i++;
        }
        povoar_disciplinas_aleatorio(&(*raiz)->esq);
        povoar_disciplinas_aleatorio(&(*raiz)->dir);
    }
}

void povoar_matriculas_aleatorio(Alunos *aluno){
    if (aluno != NULL){
        int i = 1, sucesso = 0;
        while (i < QTD_MATRICULAS){
            if (cadmatricula(&aluno, rand() % QTD_MATRICULAS, aluno->matricula) == 1)
                i++;
        }
        povoar_matriculas_aleatorio(aluno->prox);
    }
}

void povoar_notas_aleatorio(Alunos *aluno){
    if (aluno != NULL){
        int i = 1, sucesso = 0;
        while (i < QTD_DISCIPLINAS){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = rand() % QTD_DISCIPLINAS;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            if (cadnota(&aluno, aluno->matricula, n->coddisc, n->semestre, n->notafinal) == 1)
                i++;
        }
        povoar_notas_aleatorio(aluno->prox);
    }
}

void povoar_alunos_aleatorio(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    int i = 1, sucesso = 0;
    while (i < QTD_ALUNOS){
        if (cadaluno(aluno, rand() % QTD_ALUNOS, nomes[rand() % 5], rand() % QTD_CURSOS) == 1)
            i++;
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
    povoar_matriculas_aleatorio(*alunos);
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

    int aluno_rand = 876;  // Escolhe aluno aleatório
    int disc_rand = 5;  // Escolhe disciplina aleatória

    // Executa a busca várias vezes para obter uma média mais precisa
    for (i = 0; i < REPEAT; i++) {
        inicio = clock();
        notadiscporaluno(alunos, raiz, aluno_rand, disc_rand);  // Função de busca
        fim = clock();

        // Soma o tempo de cada execução
        tempo_total += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    // Retorna o tempo médio por busca
    return tempo_total / REPEAT;
}

double metrificar_tempo_por_insercao(Cursos **curso){
    clock_t inicio, fim;
    double tempo = 0.0;
    int i;
    
    for(i = 0; i < REPEAT; i++){
        inicio = clock();
        cadcurso(curso, rand() % ID_CURSOS, "Curso", (rand() % 9) + 8);
        fim = clock();

        tempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    liberar_cursos(curso);
    povoar_cursos_crescente(curso);
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
        printf("Tempo de busca da nota: %.10f\n", tempo);
    }

    // Metrificando o tempo de inserção de um curso
    for(i = 0; i < 10; i++){
        tempo = metrificar_tempo_por_insercao(&raiz);
        printf("Tempo de insercao do curso: %.10f\n", tempo);
    }

    system("PAUSE");
    liberar_alunos(alunos);
    liberar_cursos(&raiz);
    return 0;
}