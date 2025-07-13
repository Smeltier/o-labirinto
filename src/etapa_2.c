// Gabriel Gonçalves de Castro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool verificar_labirinto(FILE* file, unsigned* tamanho);
void ajustar_matriz(FILE* labirinto, int** matriz, unsigned tamanho);
int** alocar_matriz(unsigned n);
void desalocar_matriz(int** matriz, unsigned n);
void mostrar_matriz(int** matriz, unsigned tamanho);

int main(int argc, char const *argv[]){

    FILE* file = fopen("lab.txt", "r");
    if(!file){
        fprintf(stderr, "Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    int tamanho_labirinto;
    bool verificacao = verificar_labirinto(file, &tamanho_labirinto);
    
    if(!verificacao){
        fprintf(stderr, "Labirinto invalido.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int** matriz = alocar_matriz(tamanho_labirinto);
    if(!matriz){
        fprintf(stderr, "Falha ao alocar memoria para a matriz.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    rewind(file);

    ajustar_matriz(file, matriz, tamanho_labirinto);
    mostrar_matriz(matriz, tamanho_labirinto);

    desalocar_matriz(matriz, tamanho_labirinto);
    fclose(file);

    return 0;
}

bool verificar_labirinto(FILE* file, unsigned* tamanho){
    int quantidade_linhas = 0,
        quantidade_colunas = -1;
        
    int linha_entrada = -1, 
        coluna_entrada = -1;
    
    int linha_saida = -1, 
        coluna_saida = -1;
    
    int contador_entrada = 0, 
        contador_saida = 0;
        
    char caractere_atual,
         tamanho_atual = 0;
    int i = 0, j = 0;
    while (fscanf(file, "%c", &caractere_atual) != EOF) {
        if (caractere_atual == '\n') {
            if (quantidade_colunas == -1)
                quantidade_colunas = tamanho_atual;
            else if (tamanho_atual != quantidade_colunas)
                return false;

            quantidade_linhas++;
            i++;
            j = 0;
            tamanho_atual = 0;
            continue;
        }

        if (caractere_atual != '#' && caractere_atual != '<' && caractere_atual != '>' && caractere_atual != '.' && caractere_atual != '\n')
            return false;

        if (i >= 101 || j >= 101)
            return false;

        if (caractere_atual == '<') {
            linha_entrada = i;
            coluna_entrada = j;
            contador_entrada++;
        }
        if (caractere_atual == '>') {
            linha_saida = i;
            coluna_saida = j;
            contador_saida++;
        }

        j++;
        tamanho_atual++;
    }

    if (contador_entrada != 1 || contador_saida != 1)
        return false;

    if (tamanho_atual > 0) {
        if (quantidade_colunas == -1)
            quantidade_colunas = tamanho_atual;
        else if (tamanho_atual != quantidade_colunas)
            return false;
        quantidade_linhas++;
    }

    if (quantidade_linhas != quantidade_colunas)
        return false;

    *tamanho = quantidade_linhas;

    if ((linha_entrada == 0     && linha_saida == 0) ||              
        (linha_entrada == *tamanho - 1 && linha_saida == *tamanho - 1) ||  
        (coluna_entrada == 0    && coluna_saida == 0) ||         
        (coluna_entrada == *tamanho - 1 && coluna_saida == *tamanho - 1))
        return false;

    return true;
}

void mostrar_matriz(int** matriz, unsigned tamanho){
    for(int i = 0; i < tamanho; ++i){
        for(int j = 0; j < tamanho; ++j)
            printf("\t%d  ", matriz[i][j]);
        printf("\n\n");
    }
}

void ajustar_matriz(FILE* labirinto, int** matriz, unsigned tamanho){
    char caractere_atual;
    int linha = 0, coluna = 0;
    unsigned total = tamanho * tamanho, lidos = 0;

    while(lidos < total && fscanf(labirinto, "%c", &caractere_atual) == 1){
        switch(caractere_atual){
            case '#': matriz[linha][coluna] = -1; ++coluna; ++lidos; break;
            case '<': matriz[linha][coluna] = -2; ++coluna; ++lidos; break;
            case '>': matriz[linha][coluna] = -3; ++coluna; ++lidos; break;
            case '\n': break;
            default: matriz[linha][coluna] = 0; ++coluna; ++lidos; break;
        }

        if(coluna == tamanho){
            coluna = 0;
            ++linha;
        }
    } 
}

int** alocar_matriz(unsigned tamanho){
    int** matriz = (int**) malloc(sizeof(int*) * tamanho);
    if(!matriz) 
        return NULL;

    for(int i = 0; i < tamanho; ++i){
        matriz[i] = (int*) malloc(sizeof(int) * tamanho);
        if(!matriz[i]){
            for (int j = 0; j < i; ++j)
                free(matriz[j]);
            free(matriz);
            return NULL;
        }
    }
    return matriz;
}

void desalocar_matriz(int** matriz, unsigned n){
    for (int i = 0; i < n; ++i)
        free(matriz[i]);
    free(matriz);
}