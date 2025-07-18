#ifndef RESOLVEDOR_DE_LABIRINTO_H
#define RESOLVEDOR_DE_LABIRINTO_H

#include <stdbool.h>
#include "fila_encadeada.h"
#include "par.h"

bool ajustar_matriz(char* nome_arquivo, int** matriz, unsigned tamanho);
void anotar_labirinto(int** matriz, unsigned tamanho, Par* entrada, Par* saida);
int** alocar_matriz(unsigned n);
void desalocar_matriz(int** matriz, unsigned n);
Par* encontrar_entrada(int** matriz, unsigned tamanho);
Par* encontrar_saida(int** matriz, unsigned tamanho);
bool mostrar_labirinto_como_caracteres(char* nome_arquivo, int** matriz, unsigned tamanho);
bool mostrar_labirinto_como_numeros(char* nome_arquivo, int** matriz, unsigned tamanho);
unsigned verificar_labirinto(char* nome_arquivo);

#endif // RESOLVEDOR_DE_LABIRINTO_H