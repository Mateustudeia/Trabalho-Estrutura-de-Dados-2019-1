/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Node.cpp - Arquivo com assinaturas dos métodos do nó da arvore.
*/

#include "Node.h"
#include "AVL.h"

Node::Node(Temperatura temperatura) {
    temp = temperatura;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
    altura = 1;
}

Node::~Node()
{
    DesalocarFilhosRecursivo();
}

void Node::DesalocarFilhosRecursivo() 
{
    if(esq != nullptr){
        delete esq;
    }
    if(dir != nullptr){
        delete dir;
    }
}

Node* Node::ArrumarBalanceamento()
{
    AtualizarAltura();
    //checa o balanceamento do noh
    int fator_balanceamento = FatorBalanceamento();
    //1. Desbalanceamento Esquerda Esquerda
    if(fator_balanceamento > 1 && esq->FatorBalanceamento() >= 0){
        return RodarDireita();
    }
    //2. Desbalanceamento Esquerda Direita
    if(fator_balanceamento > 1 && esq->FatorBalanceamento() < 0){
        esq = esq->RodarEsquerda();
        return RodarDireita();
    }
    //3. Desbalanceamento Direita Direita
    if(fator_balanceamento < -1 && dir->FatorBalanceamento() <= 0){
        return RodarEsquerda();
    }
    //4. Desbalanceamento Direita Esquerda
    if(fator_balanceamento < -1 && dir->FatorBalanceamento() > 0){
        dir = dir->RodarDireita();
        return RodarEsquerda();
    }
    return this;
}

void Node::AtualizarAltura()
{
    int mEsq = 0;
    int mDir = 0;
    if (esq != nullptr) 
    {
        mEsq = esq->altura;
    }
    if (dir != nullptr) 
    {
        mDir = dir->altura;
    }
    if (esq > dir) 
    {
        altura = mEsq + 1;
    }
    else 
    {
        altura = mDir + 1;
    }
}

int Node::FatorBalanceamento()
{
    int altArvEsq = 0;
    int altArvDir = 0;
    if(esq != nullptr){
        altArvEsq = esq->altura;
    }
    if(dir != nullptr){
        altArvDir = dir->altura;
    }
    int fator_balanceamento = altArvEsq - altArvDir;
    return fator_balanceamento;
}

Node* Node::InserirRecursivo(Node* ptNode)
{
    if(ptNode->temp < temp){
        if(esq == nullptr){
            esq = ptNode;
            ptNode->pai = this;
        }else{
            esq = esq->InserirRecursivo(ptNode);
        }
    }else{
        if(dir == nullptr){
            dir = ptNode;
            ptNode->pai = this;
        }else{
            dir = dir->InserirRecursivo(ptNode);
        }
    }
    return ArrumarBalanceamento();
}

Node* Node::RodarEsquerda()
{
    Node* aux = this->dir;
    dir =  aux->esq;
    if(aux->esq != nullptr){
        aux->esq->pai = this;
    }
    aux->pai = this->pai;
    aux->esq = this;
    this->pai = aux;
    AtualizarAltura();
    aux->AtualizarAltura();
    return aux;
}

Node* Node::RodarDireita()
{
    Node* aux = esq;
    esq = aux->dir;
    if(aux->dir != nullptr){
        aux->dir->pai = this;
    }
    aux->dir = this;
    this->pai = aux;
    AtualizarAltura();
    aux->AtualizarAltura();
    return aux;
}

Node* Node::RemoverTemp(Node* _umNode, Temperatura _chave)
{
    //inicialmente caminhamos na árvore para encontrar
    
    //se chegamos a um node nulo, então valor não está na árvore
    if(_umNode == nullptr)
    {
        Serial.println ("Temperatura nao existe");
        return _umNode;
    }
    
    //valor é menor que o node atual, então par a sub arvore esquerda
    if(_chave < _umNode->temp)
    {
        _umNode->esq = RemoverTemp(_umNode->esq, _chave);
    }

    else if(_chave > _umNode->temp)
    {
        _umNode->dir = RemoverTemp(_umNode->dir, _chave);
    }
    
    //valor é igual ao armazenado no node atual, que deve ser apagado
    else
    {
        Node* aux;
        Node* sucessor = new Node();
        avl minhaArvore;
        
        //node não tem filhos à esquerda
        if(_umNode->esq == nullptr)
        {
            aux = _umNode->dir;
            minhaArvore.Transplantar(_umNode, _umNode->dir);
        }
        //node não tem filho à direita
        else if(_umNode->dir == nullptr)
        {
            aux = _umNode->esq;
            minhaArvore.Transplantar(_umNode, _umNode->esq);
        }
        
        //node tem dois filhos...substituímos pelo sucessor
        else
        {
            sucessor->temp = minhaArvore.Minimo();
            aux = sucessor;
            
            if(sucessor->pai != _umNode)
            {
                minhaArvore.Transplantar(sucessor, sucessor->dir);
                //atualiza altura do sucessor->pai até _umNode->dir
                Node* aux = sucessor->pai;
                while(aux != _umNode->dir)
                {
                    AtualizarAltura();
                    aux = aux->pai;
                }
                sucessor->dir = _umNode->dir->ArrumarBalanceamento();
                sucessor->dir->pai = sucessor;
            }
            minhaArvore.Transplantar(_umNode, sucessor);
            sucessor->esq = _umNode->esq;
            sucessor->esq->pai = sucessor;
        }
        //ponteiros ajustados, apagamos o node
        _umNode->esq = nullptr;
        _umNode->dir = nullptr;
        delete _umNode;
        
        //assumimos a nova raiz para fazermos ajustes
        _umNode = aux;
    }
    
    //caso nova raiz seja nula, devolva-a
    if(_umNode == nullptr)
    {
        return _umNode;
    }
    
    //verifica e arruma o balancemaneto em _umNode
    return _umNode->ArrumarBalanceamento();
}
