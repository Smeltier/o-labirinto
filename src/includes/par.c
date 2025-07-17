#include <stdlib.h>
#include <limits.h>
#include "par.h"

struct Par {
    Item primeiro, 
         segundo;
};

Par* par_inicializar(int primeiro, int segundo){
    Par* novo_par = (Par*) malloc(sizeof(Par));
    if(novo_par){
        novo_par->primeiro = primeiro;
        novo_par->segundo = segundo;
    }
    return novo_par;
}

Item par_primeiro(Par* par){
    if(!par) return INT_MIN;
    return par->primeiro;
}

Item par_segundo(Par* par){
    if(!par) return INT_MIN;
    return par->segundo;
}

void par_liberar(Par* par){
    if(!par) return;
    free(par);
}