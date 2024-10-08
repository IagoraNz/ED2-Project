#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./src/Q1.h"

#define QTD_CURSOS 1000
#define QTD_ALUNOS 1000
#define QTD_DISCIPLINAS 10
#define QTD_MATRICULAS 10

// Povoamento das Arvores de Forma Crescente, ou seja tendendo a direita.

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

// Povoamento das Arvores de forma decrecente, ou seja tendendo a esquerda.

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

// Povoamento das Arvores de forma aleatória.

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

// Povoamento dos Alunos

void povoar_alunos(Alunos **aluno, Cursos *curso){
    char *nomes[5] = {"Joao", "Maria", "Jose", "Ana", "Pedro"};
    for (int i = 1, j = QTD_CURSOS; i < QTD_ALUNOS; i++, j--){
        cadaluno(aluno, i, nomes[rand() % 5], j);
    }
}

int main (){
    srand(time(NULL));
    Cursos *raiz;
    Alunos *alunos;
    alunos = NULL;
    raiz = NULL;

    povoar_cursos_aleatorio(&raiz);
    povoar_disciplinas_aleatorio(&raiz);

    exibir_cursos(raiz);
    exibir_disc_curso_main(raiz, 400);
    // exibiralunos(alunos);
    // exibir_disc_curso_main(raiz, 1);
    liberar_alunos(alunos);
    liberar_cursos(raiz);
    return 0;
}