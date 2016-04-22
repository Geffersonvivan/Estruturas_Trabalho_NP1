#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "mergesort.h"


// inicializa um conjunto
node * initNode() {
    return NULL;
};


// insere um item em um conjunto
node * insertNode(node *current, int info) {
    node *new_node;
    new_node = (node *) malloc(1*sizeof(node));
    if (new_node != NULL) {
        new_node->info = info;
        new_node->next = new_node->prev = initNode();
        if (current != NULL) {
            new_node->prev = current;
            new_node->next = current->next;
            current->next = new_node;
        }
    }

    return new_node;
};


// retira um item de um conjunto
int deleteNode(node *current) {
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
    return 1;
};


// imprime um conjunto
void printNode(node *head) {
    node *test;
    test = head;
    do {
        printf("%d | ", test->info);
        test = test->next;
    } while (test != NULL);
    printf("\n");
};


// inicializa um set de conjuntos
nodeset * initNodeSet() {
    return NULL;
};


// insere e retorna um novo conjunto
nodeset * insertNodeSet(nodeset *current) {
    nodeset *new_nodeset;
    new_nodeset = (nodeset *) malloc(1*sizeof(nodeset));
    if (new_nodeset != NULL) {
        new_nodeset->head = initNode();
        new_nodeset->next = new_nodeset->prev = initNodeSet();
        if (current != NULL) {
            new_nodeset->prev = current;
            new_nodeset->next = current->next;
            current->next = new_nodeset;
        }
    }

    return new_nodeset;
};


// exclui um conjunto e todos os seus nodes
int deleteNodeSet(nodeset *current) {
    node *test, *temp;
    test = current->head;

    // libera todos os nodes da memória
    do {
        temp = test;
        test = test->next;
        free(temp);
    } while (test != NULL);

    // reestrutura a lista de conjuntos
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    // libera da memória o conjunto atual
    free(current);
    return 1;
};


// imprime todos os conjuntos existentes
// utilizado para mostrar ao usuário para que ele escolha qual alterar ou excluir
// os conjuntos são identificados por um índice de zero a N para as operações
void printNodeSets(nodeset *first) {
    int i;
    nodeset *test;
    if (first != NULL) {
        test = first;

        for (i = 0; test != NULL; test = test->next, i++) {
            printf("[%d] = ", i);
            printNode(test->head);
        }
    } else {
        no_nodesets();
    }
};


// retorna um conjunto pelo índice informado
nodeset * getNodeSet(nodeset *first, int index) {
    int i;
    nodeset *temp;

    // ponteiro inicial não pode ser NULL e o índice tem que ser maior ou igual a zero
    if ((first == NULL) || (temp < 0))
        return NULL;

    for (i = 0; i <= index; i++) {
        if (i == 0) {
            temp = first;
        } else {
            if (temp->next != NULL) {
                temp = temp->next;
            }
        }
    }

    // se i for diferente do index solicitado, é porque o conjunto retornado não é o correto
    if (i-1 != index)
        return NULL;

    return temp;
}


// função que retorna a união entre duas listas duplamente encadeadas
// recebe duas cabeças de listas e retorna a cabeça de uma terceira lista que é a união das duas entradas
node * getUnion(node *head1, node *head2) {
    // node1 e node2 recebem as cabeças para serem tratadas na função
	node *node1 = head1;
	node *node2 = head2;
	// head3 será a cabeça da nova lista gerada
	// lastNode será o último node adicionado, para que o próximo seja colocado depois dele
	// prev1 e prev2 receberão os nodes visitados anteriormente
	// a fim de que não haja itens repetidos no resultado
	node *head3, *lastNode, *prev1, *prev2;

	head3 = lastNode = prev1 = prev2 = initNode();

    // caso uma das listas de entrada for vazia
    // então o resultado receberá a outra lista, mas sem itens repetidos
    // a lista resultado será NULL somente se ambas estiverem vazias
	if (node1 == NULL) {
        // caso node1 seja NULL vamos percorerr node2
		while (node2) {
            // se prev2 for NULL significa que estamos no primeiro elemento de node2
            // então basta adicionar o primeiro elemento e definir a cabeça da nova lista
			if (prev2 == NULL) {
				lastNode = insertNode(lastNode, node2->info);
				head3 = lastNode;
			} else {
                // a partir do segundo elemento, verificamos se ele é diferente do que
                // foi visitado anteriormente para ele não seja repetido
				if (prev2->info != node2->info)
                    lastNode = insertNode(lastNode, node2->info);
			}
			// atualizamos o anterior como o que acabamos de visitar e o próximo a ser visitado
			prev2 = node2;
			node2 = node2->next;
		}
	} else {
        // igual o caso anterior, só que usando node1
        if (node2 == NULL) {
            while (node1) {
                if (prev1 == NULL) {
                    lastNode = insertNode(lastNode, node1->info);
                    head3 = lastNode;
                } else {
                    if (prev1->info != node1->info)
                        lastNode = insertNode(lastNode, node1->info);
                }
                prev1 = node1;
                node1 = node1->next;
            }
        }
	}

    // caso haja itens em ambas as listas dadas como entrada
    // percorre as duas listas até o fim da menor delas
	while (node1 && node2) {
        // se os valores de node1 e node2 forem iguais
		if (node1->info == node2->info) {
            // se for o primeiro item, adiciona-se e define-se a cabeça da lista resultado
			if (prev1 == NULL) {
                lastNode = insertNode(lastNode, node1->info);
				head3 = lastNode;
            // se não, adiciona apenas se for diferente do node visitado anteriormente
			} else {
				if(prev1->info != node1->info)
                    lastNode = insertNode(lastNode, node1->info);
			}
			// atualiza itens visitados anteriormente e próximos
			prev1 = node1;
			prev2 = node2;
			node1 = node1->next;
			node2 = node2->next;
		} else {
            // quando forem diferentes, o procedimento é o mesmo, a única diferença é que
            // como as listas estão organizadas com mergeSort, avançamos somente a lista mais "atrasada", ou seja, que tem o menor valor
            if(node1->info < node2->info) {
                if (prev1 == NULL) {
                    lastNode = insertNode(lastNode, node1->info);
                    head3 = lastNode;
                } else {
                    if (prev1->info != node1->info)
                        lastNode = insertNode(lastNode, node1->info);
                }
                // como prev1 é menor que prev2, avançamos apenas prev1
                prev1 = node1;
                node1 = node1->next;
            } else {
                if (prev2 == NULL) {
                    lastNode = insertNode(lastNode, node2->info);
                    head3 = lastNode;
                } else {
                    if (prev2->info != node2->info)
                        lastNode = insertNode(lastNode, node1->info);
                }
                // como prev2 é menor que prev1, avançamos apenas prev2
                prev2 = node2;
                node2 = node2->next;
            }
		}
	}

	return head3;
}


// função que retorna a intersecção de duas listas duplamente encadeadas
// recebe duas cabeças de listas e retorna uma nova lista
node * getInt(node *head1, node *head2) {
    // node1 e node2 recebem as cabeças para serem tratadas na função
	node *node1 = head1;
	node *node2 = head2;
	// head3 será a cabeça da nova lista gerada
	// lastNode será o último node adicionado, para colocar um depois do outro
	node *head3, *lastNode;

	head3 = lastNode = initNode();

    // caso uma das cabeças seja NULL não há como realizar intersecção
	if(head1 == NULL || head2 == NULL)
		return NULL;

    // percorremos as listas até o fim da menor delas
	while(node1 && node2) {
        // se os dados forem iguais, adicionamos à intersecção
		if(node1->info == node2->info) {
            lastNode = insertNode(lastNode, node1->info);
            // se a lista resultado estiver vazia, ela recebe o primeiro node adicionado
            if (head3 == NULL)
                head3 = lastNode;
			node1 = node1->next;
			node2 = node2->next;

		} else {
            // como as listas estão organizadas com mergeSort
            // quando os valores forem diferentes, avançamos a lista mais "atrasada", ou seja, que tem o menor valor
            if(node1->info < node2->info)
                node1 = node1->next;
            else
                node2 = node2->next;
        }
	}

	return head3;
}


void alloc_error() {
    printf("Erro de alocação de memória!\n");
}


void invalid_option() {
    printf("Opção inválida!\n");
}


void no_nodesets() {
    printf("Não existem conjuntos ainda.\n");
}
