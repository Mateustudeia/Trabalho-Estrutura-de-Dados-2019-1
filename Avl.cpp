/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Avl.cpp - Arquivo com metodos da arvore.
*/
#include "AVL.h"

avl::avl() 
{
    raiz = NULL;
}

avl::~avl() 
{
    delete raiz;
}

Node* avl::busca(Temperatura dado) 
{
    Node* atual = raiz;

    while (atual != NULL) 
    {
        if (atual->temp == dado) 
        {
            return atual;
        }
        else if (atual->temp > dado) 
        {
            atual = atual->esq;
        }
        else 
        {
            atual = atual->dir;
        }
    }
    return atual;
}

void avl::insereTemperatura(Temperatura dado) 
{
    Node* novo = new Node(dado);
    if (raiz == NULL)
    {
        raiz = novo;
    }
    else 
    {
        raiz = raiz->InserirRecursivo(novo);
    }
}


Temperatura avl::Minimo()
{
  if (raiz == NULL){
    return 0;

  }
  else
  {
    Node* NodeMin = MinimoAux(raiz);
    return NodeMin->temp;
  }
}

Node* avl::MinimoAux(Node* raizSub)
{
  while (raizSub->esq != NULL)
  {
    raizSub = raizSub->esq;
  }
  return raizSub;
}

Temperatura avl::Maximo()
{
  if (raiz == NULL)
  {
    return 0;
  }
  else
  {
    Node* NodeMax = MaximoAux(raiz);
    return NodeMax->temp;
  }
}

Node* avl::MaximoAux(Node* raizSub)
{
  while (raizSub->dir != NULL)
  {
    raizSub = raizSub->dir;
  }
  return raizSub;
}

void avl::Transplantar(Node* antigo, Node* novo)
{
  if (raiz == antigo)
  {
    raiz = novo;
  }
  else if(antigo == antigo->pai->esq)
  {
    antigo->pai->esq = novo;
  }
  else
  {
    antigo->pai->dir = novo;
  }
  if (novo != NULL)
  {
    novo->pai = antigo->pai;
  }
}

void avl::Remover(Temperatura dado)
{
    raiz = raiz->RemoverTemp(raiz, dado);
    //cout << raiz << endl;
}

void avl::PercorreEmOrdem()
{
  PercorreEmOrdemAux(raiz);
}

void avl::PercorreEmOrdemAux(Node* atual)
{
    if (atual != NULL)
    {
        PercorreEmOrdemAux(atual->esq);
        PercorreEmOrdemAux(atual->dir);
    }
}

void avl::PercorreParaImprimir()
{
  PercorreParaImprimirAux(raiz);
}

void avl::PercorreParaImprimirAux(Node* atual)
{
    if (atual != NULL)
    {
        PercorreParaImprimirAux(atual->esq);
        PercorreParaImprimirAux(atual->dir);
    }
}

void avl::PercorrerPraSalvar(SdFile* arqEntrada)
{
  PercorrerPraSalvarAux(arqEntrada, raiz);
}

void avl::PercorrerPraSalvarAux(SdFile* arqEntrada ,Node* atual)
{
    if(atual != NULL)
    {
        PercorrerPraSalvarAux(arqEntrada,atual->esq);
        insertData(arqEntrada, atual->temp);
        PercorrerPraSalvarAux(arqEntrada,atual->dir);
    }
}

void avl::insertData(SdFile* arqEntrada, Temperatura temperatura)
{
    arqEntrada->write((void*) &temperatura, sizeof(Temperatura));
}
