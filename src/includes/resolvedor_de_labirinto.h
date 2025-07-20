#ifndef RESOLVEDOR_DE_LABIRINTO_H
#define RESOLVEDOR_DE_LABIRINTO_H

#include <stdbool.h>
#include "fila_encadeada.h"
#include "pilha_encadeada.h"
#include "par.h"
#include "cores.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR_COMMAND "cls"
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
    #define CLEAR_COMMAND "clear"
#endif

#define BLOCO "███" 
#define VAZIO "   "
#define INICIO_GREEN GREEN BLOCO RESET
#define FIM_RED      RED BLOCO RESET
#define CAMINHO_YELL YELLOW " X " RESET
#define PAREDE_GRAY  GRAY BLOCO RESET

bool ajustar_matriz(char* nome_arquivo, int** matriz, unsigned tamanho);

void anotar_labirinto(int** matriz, unsigned tamanho, Par* entrada, Par* saida);

int** alocar_matriz(unsigned n);

void desalocar_matriz(int** matriz, unsigned n);

Par* encontrar_entrada(int** matriz, unsigned tamanho);

Par* encontrar_saida(int** matriz, unsigned tamanho);

bool extrair_caminho(int** matriz, unsigned tamanho, Par* entrada, Par* saida, pilha_encadeada* caminho);

void marcar_caminho(int** matriz, unsigned tamanho, pilha_encadeada* caminho);

bool mostrar_animacao(int** matriz, unsigned tamanho, pilha_encadeada* pilha);

void mostrar_labirinto_estilizado(int** matriz, unsigned tamanho);

bool mostrar_labirinto_como_caracteres(char* nome_arquivo, int** matriz, unsigned tamanho);

bool mostrar_labirinto_como_numeros(char* nome_arquivo, int** matriz, unsigned tamanho);

unsigned tamanho_caminho(int** matriz, unsigned tamanho);

unsigned verificar_labirinto(char* nome_arquivo);

#endif // RESOLVEDOR_DE_LABIRINTO_H