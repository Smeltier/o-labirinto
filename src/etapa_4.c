// Gabriel Gonçalves de Castro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "includes/resolvedor_de_labirinto.h"

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

    printf("\nLabirinto original: \n\n");

    verificacao = mostrar_labirinto_como_caracteres("F2a.txt", matriz, tamanho_labirinto); // F2b.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F2a.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    printf("\n\n");
    
    printf("Labirinto original versao numerica: \n\n");

    verificacao = mostrar_labirinto_como_numeros("F2b.txt", matriz, tamanho_labirinto); // F2b.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F2b.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        exit(EXIT_FAILURE);
    }

    Par *entrada = encontrar_entrada(matriz, tamanho_labirinto), 
        *saida = encontrar_saida(matriz, tamanho_labirinto);

    if(!entrada || !saida){
        fprintf(stderr, "Falha ao alocar memoria para o par de coordenadas.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        par_liberar(entrada);
        par_liberar(saida);
        exit(EXIT_FAILURE);
    }

    anotar_labirinto(matriz, tamanho_labirinto, entrada, saida);

    printf("\n\n");

    printf("Caminhos presentes no labirinto: \n\n");
    
    verificacao = mostrar_labirinto_como_numeros("F2c.txt", matriz, tamanho_labirinto); // F2c.txt
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F2c.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        par_liberar(entrada);
        par_liberar(saida);
        exit(EXIT_FAILURE);
    }

    // Etapa 4.

    pilha_encadeada* caminho = pe_inicializar();
    if(!caminho){
        fprintf(stderr, "Falha ao alocar memória para a pilha.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        par_liberar(entrada);
        par_liberar(saida);
        exit(EXIT_FAILURE);
    }

    printf("\n\n");

    verificacao = extrair_caminho(matriz, tamanho_labirinto, entrada, saida, caminho);
    if(!verificacao){
        fprintf(stderr, "Labirinto impossivel de ser resolvido.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        par_liberar(entrada);
        par_liberar(saida);
        pe_liberar(&caminho);
        exit(EXIT_FAILURE);
    }

    marcar_caminho(matriz, tamanho_labirinto, caminho);

    printf("Caminho final (siga o -4): \n\n");

    verificacao = mostrar_labirinto_como_numeros("F3b.txt", matriz, tamanho_labirinto);
    if(!verificacao){
        fprintf(stderr, "Falha ao criar o arquivo F3b.txt.\n");
        desalocar_matriz(matriz, tamanho_labirinto);
        par_liberar(entrada);
        par_liberar(saida);
        pe_liberar(&caminho);
        exit(EXIT_FAILURE);
    }

    printf("Labirinto resolvido! Digite 'S' caso queira visualizar uma animacao da resolucao ou 'N' caso contrario: ");

    char escolha;
    scanf(" %c", &escolha);

    if(escolha == 'S'){
        verificacao = mostrar_animacao(matriz, tamanho_labirinto, caminho);
        if(!verificacao){
            fprintf(stderr, "Falha ao exibir o labirinto animado.\n");
            desalocar_matriz(matriz, tamanho_labirinto);
            par_liberar(entrada);
            par_liberar(saida);
            pe_liberar(&caminho);
            exit(EXIT_FAILURE);
        }
    }

    printf("\n");

    par_liberar(entrada);
    par_liberar(saida);
    pe_liberar(&caminho);
    desalocar_matriz(matriz, tamanho_labirinto);
    
    return 0;
}