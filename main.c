#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "./src/Q1.h"

int main(){
    int opc, sucesso;
    char buffer[50];

    while(1){
        system("cls");
        printf("MENU DO SISTEMA\n");
        printf("1. Alunos\n");
        printf("2. Cursos\n");
        printf("3. Disciplinas\n");
        printf("4. Notas\n");
        printf("5. Matriculas\n");
        printf("0. Sair\n");
        printf("Digite a opcao desejada: ");
        fgets(buffer, sizeof(buffer), stdin);
        sucesso = sscanf(buffer, "%d", &opc);

        if(sucesso == 1){
            switch (opc)
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
            case 0:
                break;
            default:
                printf("Entrada invalida. Por favor, digite um opcao existente!\n");
                system("PAUSE");
                break;
            }
        }
        else{
            printf("Entrada invalida. Por favor, digite um numero inteiro!\n");
            system("PAUSE");
        }
    }

    return 0;
}