#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "mergesort.h"
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
