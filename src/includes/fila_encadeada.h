#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

#include <stdbool.h>
#include "par.h"

typedef struct fila_encadeada fila_encadeada;

/*
* Descrição: Esvazia a fila.
* Entrada:   Ponteiro para a fila.
* Saída:     Nenhuma.
*/
void fe_esvaziar(fila_encadeada** fila);

/*
* Descrição: Retorna o item que está na frente da fila.
* Entrada:   Ponteiro para a fila.
* Saída:     O item que está na frente ou INT_MIN caso esteja vazia.
*/
Par* fe_frente(fila_encadeada* fila);

/*
* Descrição: Inicializa uma nova fila encadeada vazia.
* Entrada:   Nenhuma.
* Saída:     Ponteiro para a nova fila.
*/
fila_encadeada* fe_inicializar(void);

/*
* Descrição: Insere um efemento no fim da fila.
* Entrada:   Ponteiro para a fila e o efemento a inserir.
* Saída:     true se a inserção for bem sucedida, false caso contrário.
*/
bool fe_inserir(fila_encadeada* fila, int primeiro, int segundo);

/*
* Descrição: Libera toda a memória ocupada pela fila e seus componentes.
* Entrada:   Endereço do ponteiro para a fila.
* Saída:     Nenhuma.
*/
void fe_liberar(fila_encadeada** fila);

/*
* Descrição: Remove o efemento da frente da fila.
* Entrada:   Ponteiro para a fila.
* Saída:     true se a remoção for bem sucedida, false caso contrário.
*/
bool fe_remover(fila_encadeada* fila);

/*
* Descrição: Retorna a quantidade de efementos na fila.
* Entrada:   Ponteiro para a fila.
* Saída:     Número de efementos presentes na fila.
*/
int fe_tamanho(fila_encadeada* fila);

/*
* Descrição: Verifica se a fila está vazia.
* Entrada:   Ponteiro para a fila.
* Saída:     true se estiver vazia, false caso contrário.
*/
bool fe_vazia(fila_encadeada* fila);

#endif // FILA_ENCADEADA_H