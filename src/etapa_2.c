// Gabriel Gonçalves de Castro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool ajustar_matriz(char* nome_arquivo, int** matriz, unsigned tamanho);
int** alocar_matriz(unsigned n);
void desalocar_matriz(int** matriz, unsigned n);
void mostrar_matriz(int** matriz, unsigned tamanho);
unsigned verificar_labirinto(char* nome_arquivo);

int main(int argc, char const *argv[]){

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
    
    mostrar_matriz(matriz, tamanho_labirinto);

    desalocar_matriz(matriz, tamanho_labirinto);

    return 0;
}

bool ajustar_matriz(char* nome_arquivo, int** matriz, unsigned tamanho){

    FILE* file = fopen(nome_arquivo, "r");
    if(!file){
        return false;
    }

    char caractere_atual;
    int linha = 0, coluna = 0;
    unsigned total = tamanho * tamanho, lidos = 0;

    while(lidos < total && fscanf(file, "%c", &caractere_atual) == 1){
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

    return true;
}

int** alocar_matriz(unsigned tamanho){
    int** matriz = (int**) malloc(sizeof(int*) * tamanho);
    if(matriz == NULL) 
        return NULL;

    for(int i = 0; i < tamanho; ++i){
        matriz[i] = (int*) malloc(sizeof(int) * tamanho);
        if(matriz[i] == NULL){
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

void mostrar_matriz(int** matriz, unsigned tamanho){
    for(int i = 0; i < tamanho; ++i){
        for(int j = 0; j < tamanho; ++j)
            printf("\t%d  ", matriz[i][j]);
        printf("\n\n");
    }
}

unsigned verificar_labirinto(char* nome_arquivo){

    unsigned tamanho = 0;

    FILE* file = fopen(nome_arquivo, "r"); // G: Isso gerou uma repetição dessa parte especifica..
    if(file == NULL){
        return 0;
    }

    int quantidade_linhas = 0, quantidade_colunas = -1, tamanho_atual = 0;
    int linha_entrada = -1, coluna_entrada = -1;
    int linha_saida = -1, coluna_saida = -1;
    int contador_entrada = 0, contador_saida = 0;

    int i = 0, j = 0;
    char caractere_atual;
    while (fscanf(file, "%c", &caractere_atual) != EOF) {
        if (caractere_atual == '\n') {
            if (quantidade_colunas == -1)
                quantidade_colunas = tamanho_atual;
            else if (tamanho_atual != quantidade_colunas){
                fclose(file);
                return 0;
            }

            quantidade_linhas++;
            i++;
            j = 0;
            tamanho_atual = 0;
            continue;
        }

        if (caractere_atual != '#' && caractere_atual != '<' && caractere_atual != '>' && caractere_atual != '.' && caractere_atual != '\n'){
            fclose(file);
            return 0;
        }

        if (i >= 101 || j >= 101){
            fclose(file);
            return 0;
        }

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

    if (contador_entrada != 1 || contador_saida != 1){
        fclose(file);
        return 0;
    }

    if (tamanho_atual > 0) {
        if (quantidade_colunas == -1)
            quantidade_colunas = tamanho_atual;
        else if (tamanho_atual != quantidade_colunas){
            fclose(file);
            return 0;
        }
        quantidade_linhas++;
    }

    if (quantidade_linhas != quantidade_colunas){
        fclose(file);
        return 0;
    }

    tamanho = quantidade_linhas;

    if (tamanho < 7 || tamanho > 100){
        fclose(file);
        return 0;
    }

    if ((linha_entrada == 0     && linha_saida == 0) ||              
        (linha_entrada == tamanho - 1 && linha_saida == tamanho - 1) ||  
        (coluna_entrada == 0    && coluna_saida == 0) ||         
        (coluna_entrada == tamanho - 1 && coluna_saida == tamanho - 1)) {

        fclose(file);
        return 0;
    }

    bool entrada_na_borda = (linha_entrada == 0 || linha_entrada == tamanho - 1 ||
                             coluna_entrada == 0 || coluna_entrada == tamanho - 1);

    bool saida_na_borda = (linha_saida == 0 || linha_saida == tamanho - 1 ||
                           coluna_saida == 0 || coluna_saida == tamanho - 1);

    bool entrada_na_quina = ((linha_entrada == 0 && coluna_entrada == 0) ||
                            (linha_entrada == 0 && coluna_entrada == tamanho - 1) ||
                            (linha_entrada == tamanho - 1 && coluna_entrada == 0) ||
                            (linha_entrada == tamanho - 1 && coluna_entrada == tamanho - 1));

    bool saida_na_quina = ((linha_saida == 0 && coluna_saida == 0) ||
                           (linha_saida == 0 && coluna_saida == tamanho - 1) ||
                           (linha_saida == tamanho - 1 && coluna_saida == 0) ||
                           (linha_saida == tamanho - 1 && coluna_saida == tamanho - 1));

    if (!entrada_na_borda || !saida_na_borda || entrada_na_quina || saida_na_quina) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return tamanho;
}