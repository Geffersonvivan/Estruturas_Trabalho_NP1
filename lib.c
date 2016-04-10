#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

// inicializa um conjunto
node * init() {
    return NULL;
};

// inicializa um set de conjuntos
nodeset * init_nodeset() {
    return NULL;
};

// insere um item em um conjunto
node * push(node *current, int info) {
    node *new_node;
    new_node = (node *) malloc(1*sizeof(node));
    if (new_node != NULL) {
        new_node->info = info;
        new_node->next = new_node->prev = init();
        if (current != NULL) {
            new_node->prev = current;
            new_node->next = current->next;
            current->next = new_node;
        }
    }

    return new_node;
};

// retira um item de um conjunto
int pop(node *current) {
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
void print(node *head) {
    node *test;
    test = head;
    do {
        printf("%d | ", test->info);
        test = test->next;
    } while (test != NULL);
    printf("\n");
};

// insere e retorna um novo conjunto
nodeset * push_nodeset(nodeset *current) {
    nodeset *new_nodeset;
    new_nodeset = (nodeset *) malloc(1*sizeof(nodeset));
    if (new_nodeset != NULL) {
        new_nodeset->head = init();
        new_nodeset->next = new_nodeset->prev = init_nodeset();
        if (current != NULL) {
            new_nodeset->prev = current;
            new_nodeset->next = current->next;
            current->next = new_nodeset;
        }
    }

    return new_nodeset;
};

// exclui um conjunto e todos os seus nodes
int pop_nodeset(nodeset *current) {
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
void print_nodesets(nodeset *first) {
    int i;
    nodeset *test;
    if (first != NULL) {
        test = first;

        for (i = 0; test != NULL; test = test->next, i++) {
            printf("[%d] = ", i);
            print(test->head);
        }
    } else {
        no_nodesets();
    }
};

// retorna um conjunto pelo índice informado
nodeset * get_nodeset(nodeset *first, int index) {
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

void alloc_error() {
    printf("Erro de alocação de memória!\n");
}

void invalid_option() {
    printf("Opção inválida!\n");
}

void no_nodesets() {
    printf("Não existem conjuntos ainda.\n");
}
