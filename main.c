#include <stdio.h>
#include "sistema.h"

int main() {
    int op;

    do {
        menu();
        printf("Escolha: ");

        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch(op) {
            case 1:
                cadastrarPessoa();
                break;
            case 2:
                estatisticas();
                break;
            case 3:
                alertas();
                break;
        }

    } while (op != 4);

    return 0;
}