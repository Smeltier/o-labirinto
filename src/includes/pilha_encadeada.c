#include "pilha_encadeada.h"
#include <stdlib.h>
#include <limits.h>

struct componente {
    Par* conteudo;
    struct componente* proximo;
};
typedef struct componente componente;

struct pilha_encadeada {
    struct componente* primeiro;
    int quantidade;
};

static componente* criar_componente(int primeiro, int segundo){
    componente* novo_componente = (componente*) calloc(1, sizeof(componente));
    if(novo_componente)
        novo_componente->conteudo = par_inicializar(primeiro, segundo);
    return novo_componente;
}

void pe_esvaziar(pilha_encadeada** pilha){
    if(!pilha || !(*pilha))
        return;

    componente* componente_auxiliar = (*pilha)->primeiro;
    while(componente_auxiliar){
        componente* componente_temporario = componente_auxiliar->proximo;
        par_liberar(componente_auxiliar->conteudo);
        free(componente_auxiliar);
        componente_auxiliar = componente_temporario;
    }

    (*pilha)->primeiro = NULL;
    (*pilha)->quantidade = 0;
}

pilha_encadeada* pe_inicializar(void){
    return (pilha_encadeada*) calloc(1, sizeof(pilha_encadeada));   
}

bool pe_inserir(pilha_encadeada* pilha, int primeiro, int segundo){
    if(!pilha)
        return false;

    componente* novo_componente = criar_componente(primeiro, segundo);
    if(!novo_componente)
        return false;

    novo_componente->proximo = pilha->primeiro;
    pilha->primeiro = novo_componente;
    pilha->quantidade++;

    return true;
}

void pe_liberar(pilha_encadeada** pilha){
    if(!pilha || !(*pilha))
        return;
    pe_esvaziar(pilha);
    free(*pilha);
    *pilha = NULL;
}

bool pe_remover(pilha_encadeada* pilha){
    if(!pilha || pe_vazia(pilha))
        return false;
    
    componente* componente_temporario = pilha->primeiro;

    pilha->primeiro = componente_temporario->proximo;
    pilha->quantidade--;

    par_liberar(componente_temporario->conteudo);
    free(componente_temporario);

    return true;
}

int pe_tamanho(pilha_encadeada* pilha){
    if(!pilha)
        return 0;
    return pilha->quantidade;
}

Par* pe_topo(pilha_encadeada* pilha){
    if(!pilha || pe_vazia(pilha))
        return NULL;
    return pilha->primeiro->conteudo;
}

bool pe_vazia(pilha_encadeada* pilha){
    if(!pilha)
        return true;
    return pilha->quantidade == 0;
}