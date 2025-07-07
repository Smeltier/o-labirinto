// Gabriel Gonçalves de Castro

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum Direcao { ESQUERDA, CIMA, BAIXO, DIREITA };

char** alocar_matriz(unsigned n);
void ajustar_bordas(unsigned n, char** labirinto);
void ajustar_esquema_de_paredes(int* entrada, int* saida);
void ajustar_paredes(unsigned n, unsigned p, char** labirinto);
void ajustar_posicao(unsigned n, int* posicao_entrada, int* posicao_saida);
void desalocar_matriz(char** matriz, unsigned n);
int escolher_parede();
float gerar_probabilidade();
void inicializar_labirinto(unsigned n, char** labirinto);
void posicionar_entrada_saida(unsigned n, char** labirinto);
void salvar_labirinto_em_arquivo(FILE* file, unsigned n, char** labirinto);


int main(int argc, char const *argv[]){
    srand(time(NULL));

    FILE* file = fopen("lab.txt", "w");
    if(!file){
        fprintf(stderr, "Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    unsigned n, p;

    printf("Digite o tamanho do labirinto (7 <= n <= 100) e a densidade de paredes (10 <= p <= 80):\n");
    do{
        scanf("%u %u", &n, &p);

        if(n < 7 || n > 100 || p < 10 || p > 80)
            printf("Entrada invalida. Digite novamente tamanho do labirinto (7 <= n <= 100) e a densidade de paredes (10 <= p <= 80):\n");

    } while (n < 7 || n > 100 || p < 10 || p > 80);
    

    char** labirinto = alocar_matriz(n);
    if(!labirinto){
        fprintf(stderr, "Falha ao alocar memoria para a matriz.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    inicializar_labirinto(n, labirinto);
    ajustar_bordas(n, labirinto);
    ajustar_paredes(n, p, labirinto);
    posicionar_entrada_saida(n, labirinto);
    salvar_labirinto_em_arquivo(file, n, labirinto);

    desalocar_matriz(labirinto, n);
    fclose(file);

    exit(EXIT_SUCCESS);
}

char** alocar_matriz(unsigned n){
    char** matriz = (char**) malloc(sizeof(char*) * n);
    if(!matriz)
        return NULL;

    for(int i = 0; i < n; ++i){
        matriz[i] = (char*) malloc(sizeof(char) * n);

        if(!matriz[i]){
            for (int j = 0; j < i; ++j)
                free(matriz[j]);

            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void ajustar_bordas(unsigned n, char** labirinto){
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(i == 0 || i == n -1 || j == 0 || j == n - 1)
                labirinto[i][j] = '#';    
}

void ajustar_esquema_de_paredes(int* entrada, int* saida){
    *entrada = escolher_parede();
    do{ 
        *saida = escolher_parede();
    } while (*entrada == *saida);
}

void ajustar_paredes(unsigned n, unsigned p, char** labirinto){
    float densidade = (float) p / 100;

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(labirinto[i][j] == '.' && gerar_probabilidade() < densidade)
                labirinto[i][j] = '#';
}

void ajustar_posicao(unsigned n, int* posicao_entrada, int* posicao_saida){
    do{
        *posicao_entrada = 1 + rand() % (n - 2);
        *posicao_saida   = 1 + rand() % (n - 2);
    } while(*posicao_entrada == *posicao_saida);
}

void desalocar_matriz(char** matriz, unsigned n){
    for (int i = 0; i < n; ++i)
        free(matriz[i]);
    free(matriz);
}

int escolher_parede(){
    return rand() % 4;
}

float gerar_probabilidade(){
    return (float)rand() / RAND_MAX;
}

void inicializar_labirinto(unsigned n, char** labirinto){
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            labirinto[i][j] = '.';    
}

void posicionar_entrada_saida(unsigned n, char** labirinto){
    int entrada, saida;
    ajustar_esquema_de_paredes(&entrada, &saida);

    int posicao_entrada, posicao_saida;
    ajustar_posicao(n, &posicao_entrada, &posicao_saida);

    switch (entrada){
        case ESQUERDA: labirinto[posicao_entrada][0] = '<'; break;
        case CIMA: labirinto[0][posicao_entrada] = '<'; break;
        case BAIXO: labirinto[n - 1][posicao_entrada] = '<'; break;
        case DIREITA: labirinto[posicao_entrada][n - 1] = '<'; break;
    }

    switch (saida){
        case ESQUERDA: labirinto[posicao_saida][0] = '>'; break;
        case CIMA: labirinto[0][posicao_saida] = '>'; break;
        case BAIXO: labirinto[n - 1][posicao_saida] = '>'; break;
        case DIREITA: labirinto[posicao_saida][n - 1] = '>'; break;
    }
}

void salvar_labirinto_em_arquivo(FILE* file, unsigned n, char** labirinto){
    for (int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
            fprintf(file, "%c", labirinto[i][j]);
        fprintf(file, "\n");
    }
}