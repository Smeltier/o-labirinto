#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "resolvedor_de_labirinto.h"

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

    fclose(file);

    return true;
}

void anotar_labirinto(int** matriz, unsigned tamanho, Par* entrada, Par* saida){

    fila_encadeada* fila = fe_inicializar();

    int x_entrada = par_primeiro(entrada),
        y_entrada = par_segundo(entrada),
        x_saida = par_primeiro(saida),
        y_saida = par_segundo(saida);

    if(matriz[x_entrada][y_entrada] != 0){
        fe_liberar(&fila);
        return;
    }

    matriz[x_entrada][y_entrada] = 1;
        
    fe_inserir(fila, x_entrada, y_entrada);

    int dx[] = {-1, 1, 0, 0},
        dy[] = {0, 0, -1, 1};

    while(!fe_vazia(fila)){
        Par* atual = fe_frente(fila);

        int i = par_primeiro(atual),
            j = par_segundo(atual);
        fe_remover(fila);

        for(int d = 0; d < 4; ++d){
            int x = i + dx[d],
                y = j + dy[d];

            if(x >= 0 && x < tamanho && y >= 0 && y < tamanho){
                if(matriz[x][y] != -1){
                    if(matriz[x][y] == 0 || matriz[x][y] > matriz[i][j] + 1){
                        matriz[x][y] = matriz[i][j] + 1;

                        if(x != x_saida || y != y_saida)
                            fe_inserir(fila, x, y);
                    }
                }
            }
        }
    }

    fe_liberar(&fila);
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

Par* encontrar_entrada(int** matriz, unsigned tamanho){
    int x_entrada,
        y_entrada;
    for(int i = 0; i < tamanho; ++i)
        for(int j = 0; j < tamanho; ++j)
            if(matriz[i][j] == -2){
                x_entrada = i;
                y_entrada = j;
            }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for(int d = 0; d < 4; ++d){
        int x = x_entrada + dx[d];
        int y = y_entrada + dy[d];

        if(x >= 0 && x < tamanho && y >= 0 && y < tamanho && matriz[x][y] == 0){
            x_entrada = x;
            y_entrada = y;
            break;
        }
    }
    
    return par_inicializar(x_entrada, y_entrada);
}

Par* encontrar_saida(int** matriz, unsigned tamanho){
    int x_saida,
        y_saida;
    for(int i = 0; i < tamanho; ++i)
        for(int j = 0; j < tamanho; ++j)
            if(matriz[i][j] == -3){
                x_saida = i;
                y_saida = j;
            }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for(int d = 0; d < 4; ++d){
        int x = x_saida + dx[d];
        int y = y_saida + dy[d];

        if(x >= 0 && x < tamanho && y >= 0 && y < tamanho && matriz[x][y] == 0){
            x_saida = x;
            y_saida = y;
            break;
        }
    }

    return par_inicializar(x_saida, y_saida);
}

bool mostrar_labirinto_como_caracteres(char* nome_arquivo, int** matriz, unsigned tamanho){
    FILE* file = fopen(nome_arquivo, "w");
    if(!file) return false;

    for(int i = 0; i < tamanho; ++i){
        for(int j = 0; j < tamanho; ++j){
            switch(matriz[i][j]){
                case 0: 
                    printf("%3c ", ' '); 
                    fprintf(file, "%3c ", ' '); 
                    break;
                case -1: 
                    printf("%3c ", '#'); 
                    fprintf(file, "%3c ", '#'); 
                    break;
                case -2: 
                    printf("%3c ", '<'); 
                    fprintf(file, "%3c ", '<'); 
                    break;
                case -3: 
                    printf("%3c ", '>'); 
                    fprintf(file, "%3c ", '>'); 
                    break;
            }
        }
        printf("\n\n");
        fprintf(file, "\n\n");
    }

    fclose(file);
    return true;
}

bool mostrar_labirinto_como_numeros(char* nome_arquivo, int** matriz, unsigned tamanho){
    FILE* file = fopen(nome_arquivo, "w");
    if(!file) return false;

    for(int i = 0; i < tamanho; ++i){
        for(int j = 0; j < tamanho; ++j){
            printf("%3d ", matriz[i][j]);
            fprintf(file, "%3d ", matriz[i][j]);
        }
        printf("\n\n");
        fprintf(file, "\n\n");
    }

    return true;
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