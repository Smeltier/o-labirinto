#ifndef PILHA_ENCADEADA_H
#define PILHA_ENCADEADA_H

#include <stdbool.h>
#include "par.h"

typedef struct pilha_encadeada pilha_encadeada;

/*
 * Descrição:  Esvazia a pilha.
 * Entrada:    Endereço do ponteiro da pilha.
 * Saída:      Nenhuma.
 */
void pe_esvaziar(pilha_encadeada** pilha);

/*
 * Descrição:  Inicializa a pilha.
 * Entrada:    Nenhuma.
 * Saída:      Ponteiro para a nova pilha inicializada.
 */
pilha_encadeada* pe_inicializar(void);

/*
 * Descrição:  Insere um item no topo da pilha.
 * Entrada:    Uma pilha e o item.
 * Saída:      true se o item foi inserido corretamente; caso contrário, false.
 */
bool pe_inserir(pilha_encadeada* pilha, int primeiro, int segundo);

/*
 * Descrição:  Libera a memória alocada para a pilha.
 * Entrada:    Endereço do ponteiro da pilha.
 * Saída:      Nenhuma.
 */
void pe_liberar(pilha_encadeada** pilha);

/*
 * Descrição:  Remove o item do topo da pilha.
 * Entrada:    Uma pilha.
 * Saída:      true se o item foi removido corretamente; caso contrário, false.
 */
bool pe_remover(pilha_encadeada* pilha);

/*
 * Descrição:  Retorna o tamanho atual da pilha.
 * Entrada:    Uma pilha.
 * Saída:      Quantidade de itens atualmente na pilha.
 */
int pe_tamanho(pilha_encadeada* pilha);

/*
 * Descrição:  Retorna o item no topo da pilha.
 * Entrada:    Uma pilha.
 * Saída:      Item no topo da pilha; Se estiver vazia ou não alocada retorna INT_MIN.
 */
Par* pe_topo(pilha_encadeada* pilha);

/*
 * Descrição:  Verifica se a pilha está vazia.
 * Entrada:    Uma pilha.
 * Saída:      true se a pilha estiver vazia; caso contrário, false.
 */
bool pe_vazia(pilha_encadeada* pilha);

#endif // PILHA_ENCADEADA_H