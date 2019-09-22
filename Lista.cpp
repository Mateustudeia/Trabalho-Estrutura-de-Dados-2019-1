/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Lista.cpp - Arquivo com metodos da lista.
*/

#include "Lista.h"

Lista::Lista() : mPtPrimeiro(nullptr) 
{
    tamanho = 0;
}

Lista::~Lista() 
{
    NohLista* iter = mPtPrimeiro;
    NohLista* proximo = nullptr;
    while (iter != nullptr) {
        proximo = iter->mPtProximo;
        delete iter;
        iter = proximo;
    }
}

void Lista::insereTemperatura(Temperatura dado) {
// insere um dado no final da lista
    NohLista* ptNovo = new NohLista(dado);
    
    if (Vazia()) {
        mPtPrimeiro = ptNovo;
    } else {
        NohLista* ptNoh = mPtPrimeiro;
        while(ptNoh->mPtProximo != nullptr) {
            ptNoh = ptNoh->mPtProximo;
        }
        ptNoh->mPtProximo = ptNovo;
    }
    ++tamanho;
}

bool Lista::Vazia() 
{
    return (mPtPrimeiro == nullptr);
}

void Lista::salvarEmArquivo(SdFile* arqEntrada, bool& controlaInsercao)
{
  if (controlaInsercao == false)
    {
      arqEntrada->open("arqTrabalho.dat",O_WRONLY|O_CREAT|O_TRUNC);
      controlaInsercao = true;
    } 
    else 
    {
      arqEntrada->open("arqTrabalho.dat",O_WRONLY|O_APPEND);
      
    }
    //if(arqEntrada.open("arqTrabalho.dat",O_WRONLY|O_CREAT|O_APPEND))
    //{
    NohLista* atual = mPtPrimeiro;
    Temperatura temperatura;
    while(atual != nullptr)
    {
      temperatura = atual->mDado;
      Serial.print("Salvando temp: ");
      Serial.print(atual->mDado);
      Serial.println("ºC");
      arqEntrada->write((void *) &temperatura, sizeof(Temperatura));
      atual = atual->mPtProximo;
    }
    arqEntrada->close();
  //}
}
void Lista::imprimirLista()
{
  if (mPtPrimeiro != nullptr)
  {
    NohLista* atual = mPtPrimeiro;
    Temperatura temperatura;
    Serial.println("As temperaturas salvas na lista são: ");
    while(atual != nullptr)
    {
      temperatura = atual->mDado;
      Serial.print("[ ");
      Serial.print(atual->mDado);
      Serial.print("ºC");
      Serial.print("]");
      atual = atual->mPtProximo;
      Serial.print("->");
    }
    Serial.println(" ");
  }
  else 
  {
    Serial.print("Lista Vazia!");
  }
}
