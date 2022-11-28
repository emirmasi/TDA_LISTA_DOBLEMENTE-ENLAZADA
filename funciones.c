#include "listaDE.h"

///primitivas basicas
void crearLista(t_lista *pl)
{
    *pl = NULL;
}
int listaVacia(const t_lista *pl)
{
    return *pl == NULL;
}
int listaLlena(const t_lista *pl,unsigned tamInfo)
{
    t_nodo *aux = (t_nodo*)malloc(sizeof(t_nodo));
    aux->info = malloc(tamInfo);

    free(aux->info);
    free(aux);

    return aux == NULL || aux->info == NULL;
}
void vaciarLista(t_lista *pl)
{
    t_nodo *elim,*act = *pl;

    if(act)///si no es nulo
    {
        while(act->ant)///nos posicionamos en el primer nodo
            act = act->ant;
        while(act)
        {
            elim = act;
            act = elim->sig;
            free(elim->info);
            free(elim);
        }
    }
}
int insertarAlPrincipio(t_lista *pl,const void *d,unsigned tam)
{
    t_nodo *act = *pl;
    t_nodo *nue;
    if(act)///preguntamos si act no es nulo
        while(act->ant)///mientras act->ant no sea nulo
            act = act->ant;///vamos recorriendo hacia atras
    nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,tam);
    nue->tamInfo = tam;
    nue->ant = NULL;
    nue->sig = act;
    if(act)///si actual no es nulo, o sea que no es el primer nodo
        act->ant = nue;///asigna el anterior del actual va a ser el nuevo nodo;
    *pl = nue;
    return 1;
}
int sacarPrimero(t_lista *pl,void *d,unsigned tam)
{
    t_nodo *elim;
    t_nodo *act = *pl;
    if(act)
    {
        while(act->ant)
            act = act->ant;
    }
    else
        return 0;

    elim = act;
    act = elim->sig;
    memcpy(d,elim->info,MINIMO(tam,elim->tamInfo));
    free(elim->info);
    free(elim);

    return 1;
}
int verPrimero(const t_lista *pl,void *d,unsigned tam)
{
    t_nodo *act = *pl;
    if(act)
    {
        while(act->ant)
            act = act->ant;
    }
    else
        return 0;
    memcpy(d,act->info,MINIMO(tam,act->tamInfo));
    return 1;
}
int insertarAlFinal(t_lista *pl,const void *d,unsigned tam)
{
    t_nodo *act = *pl;
    t_nodo *nue;

    if(act)
        while(act->sig)
            act = act->sig;
    nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,tam);
    nue->tamInfo = tam;
    nue->sig = NULL;
    nue->ant = act;
    if(act)
        act->sig = nue;
    *pl = nue;
    return 1;
}
int sacarUltimo(t_lista *pl,void *d,unsigned tam)
{
    t_nodo *elim,*act = *pl;

    if(act)
    {
        while(act->sig)
            act = act->sig;
    }
    else
        return 0;
    elim = act;
    act = elim->ant;
    memcpy(d,elim->info,MINIMO(tam,elim->tamInfo));
    free(elim->info);
    free(elim);
    return 1;
}
int verUltimo(t_lista *pl,void *d,unsigned tam)
{
    t_nodo *act = *pl;

    if(act)
    {
        while(act->sig)
            act = act->sig;
    }
    else
        return 0;

    memcpy(d,act->info,MINIMO(tam,act->tamInfo));
    return 1;
}

///primitivas Masomenos

int insertarEnLO(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*),
                 void(*accion)(const void* d1,void *d2),int dup)
{
    t_nodo *act = *pl;
    t_nodo *nue;
    t_nodo *ant,*sig;
    int res;
    if(act)
    {


        while(act->sig && (res = cmp(d,act->info))>0)
            act = act->sig;
        while(act->ant && (res = cmp(d,act->info))<0)
            act = act->ant;

        if(res == 0 && !dup && accion)
        {
            accion(d,act->info);
            return 1;
        }
        if(res<0)
        {
            ant = act->ant;
            sig = act;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }

    }
    else
    {
        ant = NULL;
        sig = NULL;
    }

    nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,tam);
    nue->tamInfo = tam;
    ///tengo que meterlo entre en ant y sig
    nue->ant = ant;
    nue->sig = sig;

    if(sig)///hago los doble enlaze
        sig->ant = nue;
    if(ant)
        ant->sig = nue;

    *pl = nue;
    return 1;
}
int insertarEnLD(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*),
                 void(*accion)(const void *d1,void *d2),int dup)
{


    return 1;
}
void ordenarLista(t_lista *pl,int(*cmp)(const void*,const void*))
{
    t_nodo *act = *pl,
            *inf = NULL,
             *sup = NULL;
    int marca = 1;

    if(!act)
        return ;

    while(act->ant)
        act = act->ant;

    while(marca)
    {
        marca = 0;
        while(act->sig != sup)
        {
            if(cmp(act->info,act->sig->info) > 0)
            {
                marca = 1;
                void *info = act->info;
                unsigned tam = act->tamInfo;

                act->info = act->sig->info;
                act->tamInfo = act->sig->tamInfo;
                act->sig->info = info;
                act->sig->tamInfo = tam;
            }
            act = act->sig;
        }
        act = sup;

        while(act->ant != inf)
        {
            if(cmp(act->info,act->ant->info)<0)
            {
                marca = 1;
                void *info = act->info;
                unsigned tam = act->tamInfo;

                act->info = act->ant->info;
                act->tamInfo = act->ant->tamInfo;
                act->ant->info = info;
                act->ant->tamInfo = tam;
            }
            act = act->ant;
        }
        inf = act;
    }

}
void mostrarDeIzqADer(const t_lista *pl,void(*mostrar)(const void *d))
{
    t_nodo *act = *pl;
    if(act)
    {
        while(act->ant)///me paro al principio de la lista
            act = act->ant;
        while(act)
        {
            mostrar(act->info);
            act = act->sig;
        }
    }

}
void mostrarDeDerAIzq(const t_lista *pl,void(*mostrar)(const void *d))
{
    t_nodo *act = *pl;

    if(act)
    {
        while(act->sig)
            act = act->sig;

        while(act)
        {
            mostrar(act->info);
            act = act->ant;
        }
    }
}
int eliminarPriOcuPorClave(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void*,const void*))
{
    t_nodo *act = *pl;
    int res;
    if(act)
    {


        while(act->sig && (res = cmp(d,act->info)) > 0)
            act = act->sig;
        while(act->ant && (res = cmp(d,act->info)) < 0)
            act = act->ant;

        if(res == 0 )
        {
            ///tengo que preguntar
            t_nodo *ant = act->ant;
            t_nodo *sig = act->sig;

            if(ant)///si no es el primero
                ant->sig = sig;///ant->sig = sig;
            if(sig)///si no es el ultimo
            {
                sig->ant = ant;///sig->ant = ant;
                *pl = sig;
            }
            else
                *pl = ant;
            memcpy(d,act->info,MINIMO(tam,act->tamInfo));
            free(act->info);
            free(act);
        }
    }
    else
        return 0;

    return 1;
}
int eliminarTodOcuPorClave(t_lista *pl,const void *d,unsigned tam,int(*cmp)(const void *,const void*))
{
    t_nodo *act = *pl;
    t_nodo *ant,*sig;
    int res,cont = 0 ;

    if(!*pl)
        return 0;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        if(!cmp(d,act->info))
        {
            memcpy(d,act->info,MINIMO(tam,act->tamInfo));
            cont++;

            ant = act->ant;
            sig = act->sig;

            if(ant)
                ant->sig = sig;
            if(sig)
            {
                sig->ant = ant;
                *pl = sig;
            }
            else
                *pl = ant;

            free(act->info);
            free(act);
            act = sig;
        }
        else
            act = act->sig;
    }
    return cont;
}
int eliminarPorCondicion(t_lista *pl,int(*condicion)(const void *))
{
    t_nodo *act = *pl,
            *ant,*sig;
    int cant = 0;
    if(!*pl)
        return 0;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        if(condicion(act->info))
        {
            cant++;
            ant = act->ant;
            sig = act->sig;

            if(ant)
                ant->sig = sig;
            if(sig)
            {
                sig->ant = ant;
                *pl = sig;
            }else
                *pl = ant;
            free(act->info);
            free(act);
            act = sig;

        }
    }
    return cant;
}
void eliminarDupYactualizarNododsLO(t_lista *pl,int(*cmp)(const void*,const void*),
                                    void(*accion)(const void *,void*))
{
    t_nodo *act = *pl,
            *sig,*elim;


    if(!*pl)
        return;

    while(act->ant)
        act = act->ant;

    while(act && act->sig->info)
    {
        if(cmp(act->info,act->sig->info)==0)///voy a eliminar el siguiente
        {
            accion(act->sig->info,act->info);///aca hago lo que quiera acumular en act

            elim = act->sig;
            sig = elim->sig;
            act->sig = sig;

            if(sig)
                sig->ant = act;
            *pl = act;

            free(elim->info);
            free(elim);

        }
        else
            act = act->sig;
    }
}
