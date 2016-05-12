#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "lib.c"
// Trabalho de avaliação da disciplina de Estrutura de Dados I
// Grupo: Bruno Ribeiro e Gefferson Vivan

int main() {
    // variáveis inteiras para controle dos menus
    int menu, submenu, option, info, test;
    // ponteiro para utilização durante a execução do programa
    node *currentnode;
    // ponteiro que armazena a posição do primeiro conjunto (first) e ponteiro para utilização na execução do programa (current)
    nodeset *first, *current;

    first = initNodeSet();

    do {
        currentnode = initNode();
        current = initNodeSet();
        printf("Digite a opção desejada:\n1 - Adicionar Conjunto\n2 - Excluir Conjunto\n3 - Alterar Conjunto\n4 - Exibir Intersecção\n5 - Exibir União\n6 - Exibir Diferença\n7 - Visualizar Conjuntos\n0 - Sair\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                // adiciona um novo conjunto
                // se tiver sucesso na alocação, inicia o povoamento do novo conjunto
                // caso contrário, exibe um erro padrão
                current = insertNodeSet(first);

                if (current != NULL) {
                    // se for alocado normalmente, o ponteiro do último recebe o ponteiro recém adicionado
                    first = current;

                    // solicita o povoamento do conjunto
                    do {
                        printf("Digite um número a inserir no novo conjunto [para sair, digite uma letra]: ");
                        option = scanf("%d", &info);
                        getchar();

                        if (option) {
                            currentnode = insertNode(currentnode, info);
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
                        }
                    } while (option);
                } else {
                    alloc_error();
                }
            break;
            case 2:
                if (first == NULL) {
                    printf("Não há conjuntos disponíveis.\n");
                    break;
                }
                // excluir conjunto
                printf("Escolha o conjunto que deseja excluir:\n");
                printNodeSets(first);
                printf("Digite o índice do conjunto: ");
                test = scanf("%d", &option);

                if (test == 1) {
                    current = getNodeSet(first, option);
                } else {
                    current = initNodeSet();
                }

                if (current != NULL) {
                    printf("[%d] = ", option);
                    printNode(current->head);
                    printf("Você tem certeza que deseja excluir?: 1 - Sim, 0 - Não\n");
                    scanf("%d", &submenu);

                    if (submenu) {
                        first = deleteNodeSet(current);
                        printf("Conjunto excluído com sucesso!\n");
                    } else {
                        printf("Operação cancelada!\n");
                    }
                } else {
                    invalid_option();
                }
            break;
            case 3:
                if (first == NULL) {
                    printf("Não há conjuntos disponíveis.\n");
                    break;
                }
                // altera um conjunto existente no programa
                printf("Escolha o conjunto que deseja alterar:\n");
                printNodeSets(first);
                printf("Digite o índice do conjunto: ");
                test = scanf("%d", &option);

                if (test == 1) {
                    current = getNodeSet(first, option);
                } else {
                    current = initNodeSet();
                }

                if (current != NULL) {
                    printf("[%d] = ", option);
                    printNode(current->head);
                    printf("Digite a opção desejada: 1 - Inserir, 2 - Remover\n");
                    scanf("%d", &submenu);

                    // necessita de um submenu, pois a alteração pode ser de inserção ou remoção de um item do conjunto
                    switch (submenu) {
                        case 1:
                            if (current->head != NULL) {
                                printf("Digite o valor do elemento onde deseja inserir o novo\n(se houver mais de um será inserido após o primeiro encontrado):\n");
                                test = scanf("%d", &info);
                            } else {
                                test = 2;
                            }

                            if (test != 0) {
                                currentnode = getNodeByValue(current->head, info);

                                if (currentnode != NULL || test == 2) {
                                    printf("Digite o valor que deseja inserir:\n");
                                    test = scanf("%d", &info);

                                    if (test == 1) {
                                        currentnode = insertNode(currentnode, info);

                                        if (currentnode != NULL) {
                                            if (current->head == NULL)
                                                current->head = currentnode;
                                            printf("Valor inserido com sucesso!\n");
                                        } else {
                                            alloc_error();
                                        }
                                    } else {
                                        invalid_value();
                                    }
                                } else {
                                    invalid_value();
                                }
                            } else {
                                invalid_value();
                            }
                        break;
                        case 2:
                            printf("Digite o valor que deseja remover:\n");
                            test = scanf("%d", &info);

                            if (test == 1) {
                                current->head = deleteNodesWithValue(current->head, info);
                                printf("Valor excluído com sucesso!\n");
                            } else {
                                invalid_value();
                            }
                        break;
                        default:
                            invalid_option();
                    }
                } else {
                    invalid_option();
                }
            break;
            case 4:
                if (first == NULL) {
                    printf("Não há conjuntos disponíveis.\n");
                    break;
                }
                // intersecção
                currentnode = executeOp(first, 2);
                if (currentnode != NULL) {
                    printNode(currentnode);
                    deleteAllNodes(currentnode);
                } else {
                    printf("Não há intersecção!\n");
                }
            break;
            case 5:
                if (first == NULL) {
                    printf("Não há conjuntos disponíveis.\n");
                    break;
                }
                // união
                currentnode = executeOp(first, 1);
                if (currentnode != NULL) {
                    printNode(currentnode);
                    deleteAllNodes(currentnode);
                } else {
                    printf("Não há união!\n");
                }
            break;
            case 6:
                if (first == NULL) {
                    printf("Não há conjuntos disponíveis.\n");
                    break;
                }
                // diferença
                currentnode = getDif(first);
                if (currentnode != NULL) {
                    printNode(currentnode);
                    deleteAllNodes(currentnode);
                } else {
                    printf("Não há diferença!\n");
                }
            break;
            case 7:
                // imprime todos os conjuntos que existem no programa
                printNodeSets(first);
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
