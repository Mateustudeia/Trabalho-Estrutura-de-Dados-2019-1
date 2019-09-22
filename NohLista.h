/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * NohLista.h - Arquivo com metodos do nó da lista.
*/

#ifndef NOHLISTA_H
#define NOHLISTA_H

#include "Node.h"

class NohLista {
    friend class Lista;
    protected:
        NohLista(Temperatura d) : mDado(d), mPtProximo(nullptr){};
        Temperatura mDado;
        NohLista* mPtProximo;
};
#endif
