
#include "listaDE.h"
void mostrarVec(const void *vec);
int cmpEntero(const void *d1,const void *d2);
int main()
{
    int vec[10] = {2,4,6,7,8,2,3,1,0,9};
    int vec2[] = {1,2,4,5};
    int i,elim = 2,insertar = 0;
    t_lista lista;
    crearLista(&lista);
//    for(i = 0;i<10;i++)
//        insertarAlPrincipio(&lista,vec+i,sizeof(int));
//    printf("\n de der a izq\n");
//    mostrarDeDerAIzq(&lista,mostrarVec);
//    printf("\n de izq a der\n");
//    mostrarDeIzqADer(&lista,mostrarVec);
//
//    printf("\n luego de eliminar el num 2\n");
//    eliminarPriOcuPorClave(&lista,&elim,sizeof(int),cmpEntero);
//    mostrarDeIzqADer(&lista,mostrarVec);
    for(i = 0;i<4;i++)
        insertarAlFinal(&lista,vec2+i,sizeof(int));
    mostrarDeIzqADer(&lista,mostrarVec);

    insertarEnLO(&lista,&insertar,sizeof(int),cmpEntero,NULL,0);
    printf("\ndespues de insertar el 3\n");
    mostrarDeIzqADer(&lista,mostrarVec);
    return 0;
}
void mostrarVec(const void *dato)
{
        printf("[%d]\t",*(int*)dato);
}
int cmpEntero(const void *d1,const void *d2)
{
    return *(int*)d1 - *(int*)d2;
}
