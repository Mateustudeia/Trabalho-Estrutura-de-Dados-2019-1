/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * Node.h - Arquivo com metodos do nó da arvore.
*/

#ifndef NODE_H
#define NODE_H

using namespace std;

typedef float Temperatura; //temperaturas lendo em tipo float

class Node {
friend class avl;
private:
    Temperatura temp;
    Node* esq;
    Node* dir;
    Node* pai;
    int altura;
public:
    Node(Temperatura temperatura = 0);
    ~Node();
    Node* InserirRecursivo(Node* ptNode);
    int fatorBalanceamento();
    Node* ArrumarBalanceamento();
    void AtualizarAltura();
    int FatorBalanceamento();
    void DesalocarFilhosRecursivo();
    Node* RodarEsquerda();
    Node* RodarDireita();
};
#endif
