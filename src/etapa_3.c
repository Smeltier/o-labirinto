// Gabriel Gonçalves de Castro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "includes/resolvedor_de_labirinto.h"

// G: Organizei todas as funções no arquivo resolvedor_de_labirinto, localizado na pasta includes, junto das outras estrututas.

int main(int argc, char const *argv[]){

    // Etapa 2.

    bool verificacao;

    printf("\nDigite o nome do arquivo que deseja validar, traduzir e resolver: ");

    char nome_arquivo[101];
    scanf(" %[^\n]", nome_arquivo);    

    unsigned tamanho_labirinto;
    tamanho_labirinto = verificar_labirinto(nome_arquivo);
    
    if(tamanho_labirinto == 0){
        fprintf(stderr, "Arquivo invalido.\n");
        exit(EXIT_FAILURE);
    }

    int** matriz = alocar_matriz(tamanho_labirinto);
    if(matriz == NULL){
        fprintf(stderr, "Falha ao alocar memoria para a matriz.\n");
        exit(EXIT_FAILURE);
    }

    verificacao = ajustar_matriz(nome_arquivo, matriz, tamanho_labirinto);

    if(!verificacao){
        fprintf(stderr, "Falha ao abrir o arquivo.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    // Etapa 3.

    verificacao = mostrar_labirinto_como_caracteres("F2a.txt", matriz, tamanho_labirinto); // F2b.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F3a.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    printf("\n\n");
    
    verificacao = mostrar_labirinto_como_numeros("F2b.txt", matriz, tamanho_labirinto); // F2b.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F3b.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    Par *entrada = encontrar_entrada(matriz, tamanho_labirinto), 
        *saida = encontrar_saida(matriz, tamanho_labirinto);

    if(!entrada || !saida){
        fprintf(stderr, "Falha ao alocar memoria para o par de coordenadas.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }


    anotar_labirinto(matriz, tamanho_labirinto, entrada, saida);


    printf("\n\n");
    
    verificacao = mostrar_labirinto_como_numeros("F2c.txt", matriz, tamanho_labirinto); // F2c.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F3b.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    par_liberar(entrada);
    par_liberar(saida);
    desalocar_matriz(matriz, tamanho_labirinto);
    
    return 0;
}