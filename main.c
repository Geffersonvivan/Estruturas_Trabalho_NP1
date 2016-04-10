#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int main () {
    // variáveis inteiras para controle dos menus
    int menu, submenu, option, info, test;
    // ponteiro para utilização durante a execução do programa
    node *currentnode;
    // ponteiro que armazena a posição do primeiro conjunto (first), do último (last), e ponteiro para utilização na execução do programa (current)
    nodeset *first, *last, *current;

    first = last = init_nodeset();

    do {
        currentnode = init();
        current = init_nodeset();
        printf("Digite a opção desejada:\n1 - Adicionar Conjunto\n2 - Excluir Conjunto\n3 - Alterar Conjunto\n4 - Exibir Intersecção\n5 - Exibir União\n6 - Exibir Diferença\n7 - Visualizar Conjuntos\n0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                // adiciona um novo conjunto
                // se tiver sucesso na alocação, inicia o povoamento do novo conjunto
                // caso contrário, exibe um erro padrão
                current = push_nodeset(last);

                if (current != NULL) {
                    // se for alocado normalmente, o ponteiro do último recebe o ponteiro recém adicionado
                    last = current;
                    // na primeira alocação, o ponteiro primeiro (first) e último (last) apontarão para o mesmo lugar
                    if (first == NULL)
                        first = last;

                    // solicita o povoamento do conjunto
                    do {
                        printf("Digite um número a inserir no novo conjunto: ");
                        scanf("%d", &info);
                        currentnode = push(currentnode, info);

                        // caso tenha sucesso na alocação, verifica se o ponteiro do conjunto possui a cabeça do conjunto
                        // se não tiver, receberá o node recém adicionado
                        // caso a alocação não tenha sucesso, exibe um erro padrão
                        if (currentnode != NULL) {
                            if (current->head == NULL)
                                current->head = currentnode;
                        } else {
                            alloc_error();
                            break;
                        }

                        // vai aceitar outros valores além de 1 como "Sim", mas não prejudica o funcionamento do sistema
                        printf("Deseja inserir outro número? 1 - Sim, 0 - Não\n");
                        scanf("%d", &option);
                    } while (option);
                } else {
                    alloc_error();
                }
            break;
            case 2:
                // excluir conjunto
            break;
            case 3:
                // altera um conjunto existente no programa
                printf("Escolha o conjunto que deseja alterar:\n");
                print_nodesets(first);
                printf("Digite o índice do conjunto: ");
                test = scanf("%d", &option);

                if (test == 1) {
                    current = get_nodeset(first, option);
                } else {
                    current = init_nodeset();
                }

                if (current != NULL) {
                    printf("[%d] = ", option);
                    print(current->head);
                    printf("Digite a opção desejada:\n1 - Inserir\n2 - Remover\n");
                    scanf("%d", &submenu);
                    // necessita de um submenu, pois a alteração pode ser de inserção ou remoção de um item do conjunto
                    switch (submenu) {
                        case 1:
                        break;
                        case 2:
                        break;
                        default:
                            invalid_option();
                    }
                } else {
                    invalid_option();
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
            case 7:
                // case de testes, imprime todos os conjuntos que existem no programa
                print_nodesets(first);
            break;
            case 0:
                printf("Encerrando...");
            break;
            default:
                invalid_option();
        }

    } while (menu);

    return 0;
}
