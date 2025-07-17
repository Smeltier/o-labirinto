#include "fila_encadeada.h"
#include "par.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct componente {
    Par* conteudo;
    struct componente* proximo;
} componente;

struct fila_encadeada {
    componente* primeiro;
    int quantidade;
};

static componente* criar_componente(int primeiro, int segundo){
    componente* novo_componente = (componente*) calloc(1, sizeof(componente));
    if (novo_componente) {
        novo_componente->conteudo = par_inicializar(primeiro, segundo);
        if (!novo_componente->conteudo) {
            free(novo_componente);
            return NULL;
        }
    }
    return novo_componente;
}

fila_encadeada* fe_inicializar(void){
    return (fila_encadeada*) calloc(1, sizeof(fila_encadeada));
}

bool fe_inserir(fila_encadeada* fila, int primeiro, int segundo){
    if (!fila) return false;

    componente* novo_componente = criar_componente(primeiro, segundo);
    if (!novo_componente) return false;

    if (fe_vazia(fila)) {
        fila->primeiro = novo_componente;
    } else {
        componente* atual = fila->primeiro;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo_componente;
    }

    fila->quantidade++;
    return true;
}

bool fe_remover(fila_encadeada* fila){
    if (!fila || fe_vazia(fila))
        return false;

    componente* temp = fila->primeiro;
    fila->primeiro = temp->proximo;

    par_liberar(temp->conteudo);
    free(temp);

    fila->quantidade--;
    return true;
}

Par* fe_frente(fila_encadeada* fila){
    if (!fila || fe_vazia(fila))
        return NULL;
    return fila->primeiro->conteudo;
}

void fe_esvaziar(fila_encadeada** fila){
    if (!fila || !(*fila)) return;

    componente* atual = (*fila)->primeiro;
    while (atual) {
        componente* proximo = atual->proximo;
        par_liberar(atual->conteudo);
        free(atual);
        atual = proximo;
    }

    (*fila)->primeiro = NULL;
    (*fila)->quantidade = 0;
}

void fe_liberar(fila_encadeada** fila){
    if (!fila || !(*fila)) return;
    fe_esvaziar(fila);
    free(*fila);
    *fila = NULL;
}

int fe_tamanho(fila_encadeada* fila){
    if (!fila) return 0;
    return fila->quantidade;
}

bool fe_vazia(fila_encadeada* fila){
    if (!fila) return true;
    return fila->quantidade == 0;
}