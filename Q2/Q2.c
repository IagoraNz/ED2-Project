#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q1.h"

/*---------------------------------------------------------------------------------------------------------------*/

/* Criação de constantes definidas */

#define QTD_D_CURSOS 2000
#define QTD_CURSOS 1000
#define ID_CURSOS 10000
#define QTD_ALUNOS 1000
#define QTD_DISCIPLINAS 10
#define QTD_MATRICULAS 10
#define REPEAT 100000

/*---------------------------------------------------------------------------------------------------------------*/

/* Funções de povoamento das arvores de forma crescente, decrescente e aleatória. */

/*--------------------- CRESCENTE --------------------*/

/*
    summary
        Função que povoará a árvore de cursos de forma crescente.
    param
        raiz: árvore de cursos
*/
void povoar_cursos_crescente(Cursos **raiz){ 
    for(int i = 1; i < QTD_CURSOS; i++)
        cadcurso(raiz, i, "Engenharia de Software", 8);
}

/*
    summary
        Função que povoará a árvore de disciplinas de forma crescente.
    param
        raiz: árvore de cursos
*/
void povoar_disciplinas_crescente(Cursos **raiz){
    if(*raiz != NULL){
        // Povoando a árvore de disciplinas até a quantidade de disciplinas definida
        for(int i = 1; i < QTD_DISCIPLINAS; i++){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados"); // Nome arbitrário, apenas para preencher
            // Bem como os outros campos
            d->cargah = 60;
            d->periodo = 3;
            d->cod_disciplina = i;
            caddisc(raiz, d, (*raiz)->idcurso);
        }
        // Recorre na árvore de cursos
        povoar_disciplinas_crescente(&(*raiz)->esq);
        povoar_disciplinas_crescente(&(*raiz)->dir);
    }
}

/*
    summary
        Função que povoará a árvore de matrículas de forma crescente.
    param
        aluno: árvore de alunos
*/
void povoar_matriculas_crescente(Alunos *aluno){
    if(aluno != NULL){
        // Povoando a árvore de matrículas até a quantidade de matrículas definida
        for(int i = 1; i < QTD_MATRICULAS; i++)
            cadmatricula(&aluno, i, aluno->matricula);
        povoar_matriculas_crescente(aluno->prox);
    }
}

/*
    summary
        Função que povoará a árvore de notas de forma crescente.
    param
        aluno: árvore de alunos
*/
void povoar_notas_crescente(Alunos *aluno){
    if (aluno != NULL){
        // Povoando a árvore de notas até a quantidade de disciplinas definida
        for(int i = 1; i < QTD_DISCIPLINAS; i++){
            // Alocando espaço para a nota
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = 8;
            cadnota(&aluno, aluno->matricula, i, n->semestre, n->notafinal);
        }
        povoar_notas_crescente(aluno->prox);
    }
}

/*
    summary
        Função que povoará a árvore de alunos de forma crescente.
    param
        aluno: árvore de alunos
        curso: árvore de cursos
*/
void povoar_alunos_crescente(Alunos **aluno, Cursos *curso){
    int sucesso = 0;
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"}; // Nomes arbitrários
    // Povoando a árvore de alunos até a quantidade de alunos definida
    for(int i = 1; i < QTD_ALUNOS; i++)
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
}

/*---------------------------------------------------------------------------------------------------------------*/

/*--------------------DESCRESCENTE --------------------*/

/*
    summary
        Função que povoará a árvore de cursos de forma decrescente.
    param
        raiz: árvore de cursos
*/
void povoar_cursos_decrescente(Cursos **raiz){
    // Povoando a árvore de cursos até a quantidade de cursos definida
    for(int i = QTD_D_CURSOS; i > 1000; i--)
        cadcurso(raiz, i, "Engenharia de Software", 8); // Nome arbitrário
}

/*
    summary
        Função que povoará a árvore de disciplinas de forma decrescente.
    param
        raiz: árvore de cursos
*/
void povoar_disciplinas_decrescente(Cursos **raiz){
    if(*raiz != NULL){
        // Povoando a árvore de disciplinas até a quantidade de disciplinas definida
        for(int i = QTD_DISCIPLINAS; i > 1; i--){
            // Alocando espaço para a disciplina
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Algoritmos e Estruturas de Dados");
            d->cargah = 60;
            d->periodo = 3;
            d->cod_disciplina = i;
            caddisc(raiz, d, (*raiz)->idcurso);
        }
        // Recorre na árvore de cursos
        povoar_disciplinas_decrescente(&(*raiz)->esq);
        povoar_disciplinas_decrescente(&(*raiz)->dir);
    }
}

/*
    summary
        Função que povoará a árvore de matrículas de forma decrescente.
    param
        aluno: árvore de alunos
*/
void povoar_matriculas_decrescente(Alunos *aluno){
    // Povoando a árvore de matrículas até a quantidade de matrículas definida
    if(aluno != NULL){
        for(int i = QTD_MATRICULAS; i > 1; i--)
            cadmatricula(&aluno, i, aluno->matricula); // Matrícula do aluno
        povoar_matriculas_decrescente(aluno->prox);
    }
}

/*
    summary
        Função que povoará a árvore de notas de forma decrescente.
    param
        aluno: árvore de alunos
*/
void povoar_notas_decrescente(Alunos *aluno){
    if(aluno != NULL){
        // Povoando a árvore de notas até a quantidade de disciplinas definida
        for(int i = QTD_DISCIPLINAS; i > 1; i--){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, i, n->semestre, n->notafinal);
        }
        povoar_notas_decrescente(aluno->prox);
    }
}

/*
    summary
        Função que povoará a árvore de alunos de forma decrescente.
    param
        aluno: árvore de alunos
        curso: árvore de cursos
*/
void povoar_alunos_descrescente(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"}; // Nomes arbitrários
    for(int i = QTD_ALUNOS; i > 1; i--) // Povoando a árvore de alunos até a quantidade de alunos definida
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_D_CURSOS + 1000);
}

/*---------------------------------------------------------------------------------------------------------------*/

/*--------------------- ALEATÓRIO --------------------*/

/*
    summary
        Função que povoará a árvore de cursos de forma aleatória.
    param
        raiz: árvore de cursos
*/
void povoar_cursos_aleatorio(Cursos **raiz){
    int i = 0, sucesso = 0;
    while (i < QTD_CURSOS){
        if (cadcurso(raiz, rand() % QTD_CURSOS + 1, "Engenharia de Software", 8) == 1)
            i++;
    }
}

/*
    summary
        Função que povoará a árvore de disciplinas de forma aleatória.
    param
        raiz: árvore de cursos
*/
void povoar_disciplinas_aleatorio(Cursos **raiz){
    if(*raiz != NULL){
        int i = 0;
        while(i < QTD_DISCIPLINAS){ // Povoando a árvore de disciplinas até a quantidade de disciplinas definida
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            // Nome e dados arbitrários
            strcpy(d->nomedisc, "Algoritmos");
            d->cod_disciplina = rand() % QTD_DISCIPLINAS + 1;
            d->cargah = 60;
            d->periodo = 3;
            if (caddisc(raiz, d, (*raiz)->idcurso) == 1)
                i++;
        }
        // Recorre na árvore de cursos
        povoar_disciplinas_aleatorio(&(*raiz)->esq);
        povoar_disciplinas_aleatorio(&(*raiz)->dir);
    }
}

/*
    summary
        Função que povoará a árvore de matrículas de forma aleatória.
    param
        aluno: árvore de alunos
*/
void povoar_alunos_aleatorio(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"}; // Nomes arbitrários
    int i = 0;
    for (i = 0; i < QTD_ALUNOS; i++) // Povoando a árvore de alunos até a quantidade de alunos definida
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS + 1); 
}

/*
    summary
        Função que povoará a árvore de matrículas de forma aleatória.
    param
        aluno: árvore de alunos
*/
void povoar_matricula_aleatorio(Alunos *aluno){
    if(aluno != NULL){
        int i = 0;
        while(i < QTD_MATRICULAS){ // Povoando a árvore de matrículas até a quantidade de matrículas definida
            if(cadmatricula(&aluno, rand() % QTD_MATRICULAS + 1, aluno->matricula) == 1)
                i++;
        }
        // Recorre na árvore de alunos
        povoar_matricula_aleatorio(aluno->prox);
    }
}

/*
    summary
        Função que povoará a árvore de notas de forma aleatória.
    param
        aluno: árvore de alunos
*/
void povoar_notas_aleatorio(Alunos *aluno){
    if(aluno != NULL){
        int i = 0;
        while(i < QTD_DISCIPLINAS){ // Povoando a árvore de notas até a quantidade de disciplinas definida
            Notas *n = (Notas*)malloc(sizeof(Notas));
            // Dados arbitrários
            n->coddisc = rand() % QTD_DISCIPLINAS + 1;
            n->semestre = 3;
            n->notafinal = 8;
            if(cadnota(&aluno, aluno->matricula, n->coddisc, n->semestre, n->notafinal) == 1)
                i++;
        }
        povoar_notas_aleatorio(aluno->prox);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/*--------------------- CHAMADAS --------------------*/

/*
    summary
        Função que chama as funções de povoamento das árvores de forma crescente
    param
        raiz: árvore de cursos
        alunos: árvore de alunos
*/
void povoamento_crescente(Cursos **raiz, Alunos **alunos){
    povoar_cursos_crescente(raiz);
    povoar_disciplinas_crescente(raiz);
    povoar_alunos_crescente(alunos, *raiz);
    povoar_matriculas_crescente(*alunos);
    povoar_notas_crescente(*alunos);
}

/*
    summary
        Função que chama as funções de povoamento das árvores de forma decrescente
    param
        raiz: árvore de cursos
        alunos: árvore de alunos
*/
void povoamento_decrescente(Cursos **raiz, Alunos **alunos){
    povoar_cursos_decrescente(raiz);
    povoar_disciplinas_decrescente(raiz);
    povoar_alunos_descrescente(alunos, *raiz);
    povoar_matriculas_decrescente(*alunos);
    povoar_notas_decrescente(*alunos);
}

/*
    summary
        Função que chama as funções de povoamento das árvores de forma aleatória
    param
        raiz: árvore de cursos
        alunos: árvore de alunos
*/
void povoamento_aleatorio(Cursos **raiz, Alunos **alunos){
    povoar_cursos_aleatorio(raiz);
    povoar_disciplinas_aleatorio(raiz);
    povoar_alunos_aleatorio(alunos, *raiz);
    povoar_matricula_aleatorio(*alunos);
    povoar_notas_aleatorio(*alunos);
}

/*
    summary
        Função que exibe o menu de povoamento das árvores
*/
void menu_povoamento(){
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    printf("3 - Aleatorio\n");
    printf("Escolha a forma de povoamento das arvores:\n");
}

/*---------------------------------------------------------------------------------------------------------------*/

/*--------------------- METRIFICANDO O TEMPO --------------------*/

/*
    summary
        Função que metrifica o tempo de busca da nota de uma disciplina de um determinado aluno
    param
        alunos: árvore de alunos
        raiz: árvore de cursos
    return
        Retorna o tempo médio por busca
*/
double metrificar_tempo_por_busca_nota(Alunos *alunos, Cursos *raiz){
    // Variáveis para medir o tempo
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int i;

    // Aluno e disciplina aleatórios
    int aluno_rand = 543;
    int disc_rand = 4;

    // Executa a busca várias vezes para obter uma média mais precisa
    for(i = 0; i < REPEAT; i++){
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

/*
    summary
        Função que metrifica o tempo de inserção de um curso
    param
        curso: árvore de cursos
        opc: opção de povoamento
    return
        Retorna o tempo médio por inserção
*/
double metrificar_tempo_por_insercao(Cursos **curso, int opc){
    // Variáveis para medir o tempo
    clock_t inicio, fim;
    double tempo = 0.0;
    int i, idcurso;
    
    // Executa a inserção várias vezes para obter uma média mais precisa
    for(i = 0; i < REPEAT; i++){
        if (opc == 2)
            idcurso = rand() % QTD_CURSOS + 1;
        else
            idcurso = rand() % ID_CURSOS + 1;
        inicio = clock();
        cadcurso(curso, idcurso, "Curso", 8);
        fim = clock();

        tempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    // Libera a árvore de cursos
    liberar_cursos(curso);
    // Povoamento da árvore de cursos entre crescente, decrescente e aleatório a cada execução
    if (opc == 1)
        povoar_cursos_crescente(curso);
    else if (opc == 2)
        povoar_cursos_decrescente(curso);
    else
        povoar_cursos_aleatorio(curso);
    return tempo / REPEAT;
}

/*---------------------------------------------------------------------------------------------------------------*/

/*--------------------- MAIN --------------------*/

int main(){
    // Inicializando as variáveis
    srand(time(NULL));
    Cursos *raiz;
    Alunos *alunos;
    alunos = NULL;
    raiz = NULL;

    int op, i;
    double tempo;

    // Menu de povoamento das árvores
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
    printf("BUSCA\n\n");
    for(i = 0; i < 30; i++){
        tempo = metrificar_tempo_por_busca_nota(alunos, raiz);
        printf("%.2f\n", tempo * 1000000); // Microsegundos
    }

    // Metrificando o tempo de inserção de um curso
    printf("INSERCAO\n\n");
    for(i = 0; i < 30; i++){
        tempo = metrificar_tempo_por_insercao(&raiz, op);
        printf("%.2f\n", tempo * 1000000); // Microsegundos
    }

    getchar();
    // Liberando a memória alocada
    liberar_alunos(&alunos);
    liberar_cursos(&raiz);
    return 0;
}