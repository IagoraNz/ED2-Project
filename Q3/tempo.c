#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q3.h"

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

void povoar_cursos_crescente(AVLCurso **raiz){ 
    for (int i = 1; i < QTD_CURSOS; i++){
        Cursos *c = (Cursos*)malloc(sizeof(Cursos));
        c->idcurso = i;
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        cadcurso(raiz, c);
    }
}

void povoar_disciplinas_crescente(AVLCurso **raiz){
    if (*raiz != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            d->cod_disciplina = i;
            d->cargah = 60;
            d->periodo = i;
            strcpy(d->nomedisc, "Calculo");
            caddisc(raiz, d, (*raiz)->info->idcurso);
        }
        povoar_disciplinas_crescente(&(*raiz)->esq);
        povoar_disciplinas_crescente(&(*raiz)->dir);
    }
}

void povoar_matriculas_crescente(Alunos *aluno, AVLCurso *curso){
    if (aluno != NULL){
        for (int i = 1; i < QTD_MATRICULAS; i++){
            cadmatricula(&aluno, curso, i, aluno->matricula);
        }
        povoar_matriculas_crescente(aluno->prox, curso);
    }
}

void povoar_notas_crescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = 1; i < QTD_DISCIPLINAS; i++){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, n);
        }
        povoar_notas_crescente(aluno->prox);
    }
}

void povoar_alunos_crescente(Alunos **aluno, AVLCurso *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1; i < QTD_ALUNOS; i++){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

void povoamento_crescente(AVLCurso **raiz, Alunos **alunos){
    povoar_cursos_crescente(raiz);
    povoar_disciplinas_crescente(raiz);
    povoar_alunos_crescente(alunos, *raiz);
    povoar_matriculas_crescente(*alunos, *raiz);
    povoar_notas_crescente(*alunos);
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Funções de povoamento das arvores de forma Decrescente.
*/

void povoar_cursos_decrescente(AVLCurso **raiz){
    for (int i = QTD_CURSOS; i > 0; i--){
        Cursos *c = (Cursos*)malloc(sizeof(Cursos));
        c->idcurso = i;
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        cadcurso(raiz, c);
    }
}

void povoar_disciplinas_decrescente(AVLCurso **raiz){
    if (*raiz != NULL){
        for (int i = QTD_DISCIPLINAS; i > 0; i--){
            Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
            d->cod_disciplina = i;
            d->cargah = 60;
            d->periodo = i;
            strcpy(d->nomedisc, "Calculo");
            caddisc(raiz, d, (*raiz)->info->idcurso);
        }
        povoar_disciplinas_decrescente(&(*raiz)->esq);
        povoar_disciplinas_decrescente(&(*raiz)->dir);
    }
}

void povoar_matriculas_decrescente(Alunos *aluno, AVLCurso *curso){
    if (aluno != NULL){
        for (int i = QTD_MATRICULAS; i > 0; i--){
            cadmatricula(&aluno, curso, i, aluno->matricula);
        }
        povoar_matriculas_decrescente(aluno->prox, curso);
    }
}

void povoar_notas_decrescente(Alunos *aluno){
    if (aluno != NULL){
        for (int i = QTD_DISCIPLINAS; i > 0; i--){
            Notas *n = (Notas*)malloc(sizeof(Notas));
            n->coddisc = i;
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            cadnota(&aluno, aluno->matricula, n);
        }
        povoar_notas_decrescente(aluno->prox);
    }
}

void povoar_alunos_decrescente(Alunos **aluno, AVLCurso *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = QTD_ALUNOS; i > 0; i--){
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS);
    }
}

void povoamento_decrescente(AVLCurso **raiz, Alunos **alunos){
    povoar_cursos_decrescente(raiz);
    povoar_disciplinas_decrescente(raiz);
    povoar_alunos_decrescente(alunos, *raiz);
    povoar_matriculas_decrescente(*alunos, *raiz);
    povoar_notas_decrescente(*alunos);
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Funções de povoamento das arvores de forma Aleatória.
*/

void povoar_cursos_aleatorio(AVLCurso **raiz) {
    int i = 0;
    while (i < QTD_CURSOS) {
        Cursos *c = (Cursos *)malloc(sizeof(Cursos));
        c->idcurso = rand() % QTD_CURSOS + 1; // Definindo IDs únicos sequenciais
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        if (cadcurso(raiz, c) == 1) {
            i++;
        }
    }
}

void povoar_disciplinas_aleatorio(AVLCurso **raiz) {
    if (*raiz != NULL) {
        int i = 0; // Começando em 0
        while (i < QTD_DISCIPLINAS) {
            Disciplina *d = (Disciplina *)malloc(sizeof(Disciplina));
            strcpy(d->nomedisc, "Calculo");
            d->cod_disciplina = rand() % QTD_DISCIPLINAS + 1; // Definindo códigos únicos sequenciais
            d->cargah = 60;
            d->periodo = 3;

            int sucesso = caddisc(raiz, d, (*raiz)->info->idcurso);
            if (sucesso == 1) {
                i++;
            }
        }
        povoar_disciplinas_aleatorio(&(*raiz)->esq);
        povoar_disciplinas_aleatorio(&(*raiz)->dir);
    }
}

void povoar_matriculas_aleatorio(Alunos *aluno, AVLCurso *curso) {
    if (aluno != NULL) {
        int i = 0; // Começando em 0
        while (i < QTD_MATRICULAS) {
            if (cadmatricula(&aluno, curso, rand() % QTD_MATRICULAS + 1, aluno->matricula) == 1) {
                i++;
            }
        }
        povoar_matriculas_aleatorio(aluno->prox, curso);
    }
}

void povoar_notas_aleatorio(Alunos *aluno) {
    if (aluno != NULL) {
        int i = 0; // Começando em 0
        while (i < QTD_DISCIPLINAS) {
            Notas *n = (Notas *)malloc(sizeof(Notas));
            n->coddisc = rand() % QTD_DISCIPLINAS + 1; // Código de disciplina mantido
            n->semestre = 3;
            n->notafinal = (rand() % 10) + 1;
            if (cadnota(&aluno, aluno->matricula, n) == 1) {
                i++;
            }
        }
        povoar_notas_aleatorio(aluno->prox);
    }
}

void povoar_alunos_aleatorio(Alunos **aluno, AVLCurso *curso) {
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 0; i < QTD_ALUNOS; i++) {
        cadaluno(aluno, curso, i, nomes[rand() % 5], rand() % QTD_CURSOS + 1);
    }
}

void povoamento_aleatorio(AVLCurso **raiz, Alunos **alunos){
    povoar_cursos_aleatorio(raiz);
    povoar_disciplinas_aleatorio(raiz);
    povoar_alunos_aleatorio(alunos, *raiz);
    povoar_matriculas_aleatorio(*alunos, *raiz);
    povoar_notas_aleatorio(*alunos);
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Função de menu para escolha de povoamento.
*/

void menu_povoamento(){
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    printf("3 - Aleatorio\n");
    printf("Escolha a forma de povoamento das arvores:\n");
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Função de busca de notas para metrificar.
*/


void notadiscporaluno_Teste(Alunos *aluno, AVLCurso *curso, int matricula, int coddisc){
    int encontrou = 0;
    if(aluno != NULL){
        if(aluno->matricula == matricula){
            AVLCurso *c = buscar_curso(curso, aluno->codcurso);
            AVLDisc *d = buscar_disciplina(c->info->disc, coddisc);
            AVLNotas *n = buscar_nota(aluno->nota, coddisc);
            if(d != NULL && n != NULL){
                encontrou = 1;
            }
        }
        else
            notadiscporaluno_Teste(aluno->prox, curso, matricula, coddisc);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Função de metrificação de tempo para busca de notas.
*/

double metrificar_tempo_por_busca_nota(Alunos *alunos, AVLCurso *raiz) {
    clock_t inicio, fim;
    double tempo_total = 0.0;
    int i;

    int aluno_rand = 543;  // Escolhe aluno aleatório
    int disc_rand = 4;  // Escolhe disciplina aleatória

    // Executa a busca várias vezes para obter uma média mais precisa
    for (i = 0; i < REPEAT; i++) {
        inicio = clock();
        notadiscporaluno_Teste(alunos, raiz, aluno_rand, disc_rand);  // Função de busca
        fim = clock();

        // Soma o tempo de cada execução
        tempo_total += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }

    // Retorna o tempo médio por busca
    return tempo_total / REPEAT;
}

/*---------------------------------------------------------------------------------------------------------------*/

/*
Função de metrificação de tempo para inserção.
*/

double metrificar_tempo_por_insercao(AVLCurso **curso, int opc){
    clock_t inicio, fim;
    double tempo = 0.0;
    int i;
    
    for(i = 0; i < REPEAT; i++){
        Cursos *c = (Cursos*)malloc(sizeof(Cursos));
        c->idcurso = rand() % ID_CURSOS;
        c->qntdperiodos = 8;
        strcpy(c->nomecurso, "Engenharia de Computação");
        c->disc = NULL;
        inicio = clock();
        cadcurso(curso, c);
        fim = clock();

        tempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    }
    liberarAVLCurso(curso);
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
    AVLCurso *raiz;
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

    liberarAVLCurso(&raiz);
    liberarAlunos(&alunos);

    getchar();
    
    return 0;
}