#ifndef LISTADE_H_INCLUDED
#define LISTADE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(x,y)     (((x)<(y))?(x):(y))
///el puntero del main siempre apunta al ultimo
typedef struct s_nodo
{
    void *info;
    unsigned tamInfo;
    struct s_nodo *sig,*ant;
}t_nodo;

typedef t_nodo *t_lista;
///primitivas basicas
void crearLista(t_lista *pl);
int listaVacia(const t_lista *pl);
int listaLlena(const t_lista *pl,unsigned tamInfo);
void vaciarLista(t_lista *pl);
int insertarAlPrincipio(t_lista *pl,const void *d,unsigned tam);
int sacarPrimero(t_lista *pl,void *d,unsigned tam);
int verPrimero(const t_lista *pl,void *d,unsigned tam);
int insertarAlFinal(t_lista *pl,const void *d,unsigned tam);
int sacarUltimo(t_lista *pl,void *d,unsigned tam);
int verUltimo(t_lista *pl,void *d,unsigned tam);

///primitivas Masomenos

int insertarEnLO(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*),
                       void(*accion)(const void* d1,void *d2),int dup);
int insertarEnLD(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*),
                 void(*accion)(const void *d1,void *d2),int dup);
void ordenarLista(t_lista *pl,int(*cmp)(const void*,const void*));
void mostrarDeIzqADer(const t_lista *pl,void(*mostrar)(const void *d));
void mostrarDeDerAIzq(const t_lista *pl,void(*mostrar)(const void *d));
int eliminarPriOcuPorClave(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*));
int eliminarTodOcuPorClave(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void *,const void*));
int eliminarPorCondicion(t_lista *pl,int(*condicion)(const void *));
void eliminarDupYactualizarNododsLO(t_lista *pl,int(*cmp)(const void*,const void*),
                                    void(*accion)(const void *,void*));
#endif // LISTADE_H_INCLUDED
