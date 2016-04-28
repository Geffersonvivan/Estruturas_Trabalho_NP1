#include <stdlib.h>
#include <stdio.h>

// INICIO BIBLIOTECA MERGESORT

// Biblioteca auxiliar para ordenação de listas (mergesort)
// Baseada no código disponível em http://ideone.com/LQqKlc de Bhavik Gujarati

// Função que quebra uma lista em duas partes
// Necessária para realizar a ordenação
node * splitNode(node *head) {
    // Node "fast" vai pular de dois em dois percorrendo a lista
    // apenas para marcar onde a lista tem que ser quebrada
    // Node "slow" vai de um em um, ele serve de retorno como
    // ponto de divisão da lista
    node *fast = head, *slow = head;

    // Percorre a lista até que "fast" tenha próximo e próximo do próximo
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Ponteiro "temp" recebe o próximo de "slow"
    // então anulamos o "next" de "slow" a fim de quebrar a lista ao meio
    node *temp = slow->next;
    slow->next = initNode();

    // Retornamos "temp" que é ponteiro de início da "segunda lista"
    return temp;
}


// Função para juntar novamente a lista
node * mergeNode(node *first, node *second) {
    // Verifica se a primeira ou a segunda existem
    // Caso apenas uma exista, a função termina aqui
    if (!first)
        return second;
    if (!second)
        return first;

    // Verifica qual node tem o menor valor
    // Caso o primeiro tenha o menor valor, ela será
    // colocada por primeiro
    if (first->info < second->info) {
        // Isso é feito recursivamente
        first->next = mergeNode(first->next, second);
        first->next->prev = first;
        first->prev = initNode();
        return first;
    // se não é colocada depois
    } else {
        // Isso é feito recursivamente
        second->next = mergeNode(first, second->next);
        second->next->prev = second;
        second->prev = initNode();
        return second;
    }
}


// Função que chama as demais para organizar uma lista
// Isso se chama "Algoritmo de merge sort"
node * mergeSort(node *head) {
    if (!head || !head->next)
        return head;

    // Quebra a lista ao meio, gerando uma segunda "head"
    node *second = splitNode(head);

    // Organiza o primeiro elemento e o primeiro da "segunda metade"
    // Utilizando a mergeSort de forma recusiva
    head = mergeSort(head);
    second = mergeSort(second);

    // Junta e organiza os elementos e retorna a nova "head"
    return mergeNode(head,second);
}

// FIM BIBLIOTECA MERGESORT

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


// retira itens com determinado valor de um conjunto
node * getNodeByValue(node *first, int value) {
    node *temp, *test = first;
    do {
        temp = test;
        test = test->next;

        if (temp->info == value && test != NULL && test->info != value) {
            return temp;
        }
    } while (test != NULL);

    return NULL;
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


// retira itens com determinado valor de um conjunto
node * deleteNodesWithValue(node *first, int value) {
    node *temp, *test = first;
    do {
        temp = test;
        test = test->next;

        if (temp->info == value) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            // para que retorne sempre a cabeça, mesmo que ela seja excluída haverá outra
            if (temp == first)
                first = temp->next;
            free(temp);
        }
    } while (test != NULL);

    return first;
};


// retira todos os itens de um conjunto
int deleteAllNodes(node *first) {
    node *temp, *test = first;
    do {
        temp = test;
        test = test->next;
        free(temp);
    } while (test != NULL);
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
// inserção em pilha
nodeset * insertNodeSet(nodeset *current) {
    nodeset *new_nodeset;
    new_nodeset = (nodeset *) malloc(1*sizeof(nodeset));
    if (new_nodeset != NULL) {
        new_nodeset->head = initNode();
        new_nodeset->next = new_nodeset->prev = initNodeSet();
        if (current != NULL) {
            new_nodeset->next = current;
            new_nodeset->prev = current->prev;
            current->prev = new_nodeset;
        }
    }

    return new_nodeset;
};


// exclui um conjunto e todos os seus nodes
nodeset * deleteNodeSet(nodeset *current) {
    nodeset *test;
    node *first = current->head;

    // libera todos os nodes da memória
    deleteAllNodes(first);

    // reestrutura a lista de conjuntos
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    // percorre até o primeiro elemento para retorná-lo
    test = current;

    while (test->prev != NULL) {
        test = test->prev;
    }

    if (test == current)
        test = initNodeSet();

    // libera da memória o conjunto atual
    free(current);

    // retorna o novo início
    return test;
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
    if ((first == NULL) || (temp < 0) || (index < 0))
        return NULL;

    if (index == 0)
        return first;

    for (i = 1; i <= index; i++) {
        if (temp != NULL && temp->next != NULL) {
            temp = temp->next;
        }
    }

    // se i for diferente do index solicitado, é porque o conjunto retornado não é o correto
    if (i-1 != index)
        return NULL;

    return temp;
}


// função que executa as operações entre todos os conjuntos e retorna um conjunto resultado
// op: 1 - União 2 - Intersecção 3 - Diferença
node * executeOp(nodeset *head, int op) {
    // ponteiro de retorno e pornteiros para uso dentro da função
    node *result, *temp;
    nodeset *first, *next;

    result = temp = initNode();
    first = next = initNodeSet();

    // inicializamos o ponteiro da lista atual e da próxima e
    // organizamos ambas com mergeSort
    first = head;
    next = head->next;

    // realiza a união dos primeiros dois conjuntos

    // organiza o primeiro conjunto com mergeSort
    first->head = mergeSort(first->head);

    // se houver um segundo conjunto (próximo), realiza a união entre ambos
    // joga a união em result e atualiza o next para início do laço while abaixo
    if (next != NULL) {
        next->head = mergeSort(next->head);
        switch (op) {
            // união
            case 1:
                result = getUnion(first->head, next->head);
            break;
            // intersec
            case 2:
                result = getInt(first->head, next->head);
            break;
            // dif
            case 3:
                result = getDif(first->head, next->head);
            break;
            // se a op informada não for nenhuma das 3
            default:
                return result;
        }
        next = next->next;
    } else {
        // caso haja apenas um conjunto, o resultado será ele mesmo organizado e retirados os duplicados
        switch (op) {
            // união
            case 1:
                result = getUnion(first->head, NULL);
            break;
            // intersec
            case 2:
                result = getInt(first->head, NULL);
            break;
            // dif
            case 3:
                result = getDif(first->head, NULL);
            break;
            // se a op informada não for nenhuma das 3
            default:
                return result;
        }
    }

    // enquanto houver mais elementos, organiza o next com mergeSort, une-o com o resultado anterior
    // joga a união em temp, exclui o resultado anterior da memória, atualiza result com o resultado atual
    // e atualiza next para o próximo conjunto
    while (next) {
        next->head = mergeSort(next->head);
        switch (op) {
            // união
            case 1:
                temp = getUnion(result, next->head);
            break;
            // intersec
            case 2:
                temp = getInt(result, next->head);
            break;
            // dif
            case 3:
                temp = getDif(result, next->head);
            break;
            // se a op informada não for nenhuma das 3
            default:
                return result;
        }
        deleteAllNodes(result);
        result = temp;
        next = next->next;
    }

    return result;
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

    // caso haja itens em ambas as listas dadas como entrada
    // percorre as duas listas até o fim da menor delas
	while (node1 && node2) {
        // se os valores de node1 e node2 forem iguais
		if (node1->info == node2->info) {
            // se for o primeiro item, adiciona-se e define-se a cabeça da lista resultado
			if (prev1 == NULL) {
                lastNode = insertNode(lastNode, node1->info);
				if (head3 == NULL)
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
            if (node1->info < node2->info) {
                if (prev1 == NULL) {
                    lastNode = insertNode(lastNode, node1->info);
                    if (head3 == NULL)
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
                    if (head3 == NULL)
                        head3 = lastNode;
                } else {
                    if (prev2->info != node2->info)
                        lastNode = insertNode(lastNode, node2->info);
                }
                // como prev2 é menor que prev1, avançamos apenas prev2
                prev2 = node2;
                node2 = node2->next;
            }
		}
	}

    // caso uma das listas de entrada tenha acabado de ser percorrida
    // então o resultado receberá o restante da outra lista, mas sem itens repetidos
	if (node1 == NULL) {
        // caso node1 seja NULL vamos percorrer node2
		while (node2) {
            // se prev2 for NULL significa que estamos no primeiro elemento de node2
            // então basta adicionar o elemento
			if (prev2 == NULL) {
				lastNode = insertNode(lastNode, node2->info);
				// CASO UMA DAS LISTAS SEJA NULL NÃO HAVERÁ CABEÇA DO RESULTADO DEFINIDA
				if (head3 == NULL)
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
                    if (head3 == NULL)
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


// função que retorna a diferença de duas listas duplamente encadeadas
// recebe duas cabeças de listas e retorna uma nova lista
// basicamente subtrai a intersecção da união
node * getDif(node *head1, node *head2) {
	node *union_list, *intersection_list, *diff_list, *test;

    // gera união e intersecção
	union_list = getUnion(head1, head2);
	intersection_list = getInt(head1, head2);

    // o resultado recebe a união e uma variável de testes é instanciada para percorrer
    // a lista de intersecção
    diff_list = union_list;
    test = intersection_list;

    // cada item da lista de intersecção é retirado da lista resultado
    while (test != NULL) {
        diff_list = deleteNodesWithValue(diff_list, test->info);
        test = test->next;
	}

    // limpamos da memória a lista de intersecção, pois não é mais necessária
    deleteAllNodes(intersection_list);

	return diff_list;
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


void invalid_value() {
    printf("Valor inválido!\n");
}
