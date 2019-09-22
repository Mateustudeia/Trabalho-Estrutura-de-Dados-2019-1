/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Lista.h - Arquivo com assinaturas dos métodos da lista.
*/

#ifndef LISTA_H
#define LISTA_H

#include "NohLista.h"
#include  <SdFat.h>

class Lista {
    public:
        Lista();
        ~Lista();
        // Insere um dado no fim da lista.
        void insereTemperatura(Temperatura dado);
        void imprimirLista();
        void salvarEmArquivo(SdFile* arqEntrada, bool& controlaInsercao);
    protected:
        NohLista* mPtPrimeiro;
        bool Vazia();
        unsigned tamanho;
};
#endif
