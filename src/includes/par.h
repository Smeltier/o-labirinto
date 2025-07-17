#ifndef PAR_H
#define PAR_H

typedef struct Par Par;
typedef int Item;

Par* par_inicializar(int primeiro, int segundo);
Item par_primeiro(Par* par);
Item par_segundo(Par* par);
void par_liberar(Par* par);

#endif // PAR_H