#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int main () {
    int menu, submenu;

    do {
        printf("Digite a opção desejada:\n1 - Adicionar Conjunto\n2 - Excluir Conjunto\n3 - Alterar Conjunto\n4 - Exibir Intersecção\n5 - Exibir União\n6 - Exibir Diferença\n0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                // adicionar conjunto
            break;
            case 2:
                // excluir conjunto
            break;
            case 3:
                // alterar conjunto
                printf("Digite a opção desejada:\n1 - Inserir\n2 - Remover\n");
                scanf("%d", &submenu);
                switch (submenu) {
                    case 1:
                    break;
                    case 2:
                    break;
                    default:
                        printf("Opção inválida!\n");
                }
            break;
            case 4:
                // intersecção
            break;
            case 5:
                // união
            break;
            case 6:
                // diferença
            break;
            case 0:
                printf("Encerrando...");
            break;
            default:
                printf("Opção inválida!\n");
        }

    } while (menu != 0);

    return 0;
}
