/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Avl.h - Arquivo com assinaturas dos métodos da arvore.
*/
#ifndef AVL_H
#define AVL_H

#include "Node.h"
#include  <SdFat.h>

using namespace std;

class avl 
{
private:
    Node* raiz;
    void PercorreEmOrdemAux(Node* atual);
    void PercorreParaImprimirAux(Node* atual);
    Node* MinimoAux(Node* raizSub);
    Node* MaximoAux(Node* raizSub);
    Node* insereTemperaturaRecursiva(Node* umNode, Temperatura dado);
    bool verificaNode(Node* umNode); //verifica se os ponteiros de umNode estão ok
public:
    avl();
    ~avl();
    void insereTemperatura(Temperatura dado);
    Node* busca(Temperatura dado);
    Temperatura Minimo();
    Temperatura Maximo();
    void PercorreEmOrdem();
    void PercorrerPraSalvar(SdFile* arqEntrada);
    void PercorrerPraSalvarAux(SdFile* arqEntrada ,Node* atual);
    void insertData(SdFile* arqEntrada, Temperatura temperatura);
};
#endif
