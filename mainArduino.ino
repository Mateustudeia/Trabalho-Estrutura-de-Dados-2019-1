/** 
 * GCC 216 - Estruturas de Dados
 * Projeto Prático - Sistema de Controle de Temperatura com Sistema Distribuido
 * Copyright 2019 - Mateus Tudéia
 * mainArduino.ino - Arquivo gerencia as operações base do sistema.
*/

#include <Thermistor.h>
#include <LiquidCrystal.h>
#include <SdFat.h>
#include "Arduino.h"
#include "Lista.h"
#include "Avl.h"

SdFat sdCard;

/*========== Portas conectadas ==========*/
//SDCARD
const int chipSelect = 7; //4;
//SENSOR TEMPERATURA
Thermistor temp (1); // termistor conectado na porta A1 (cria o objeto)


/*========== Funcao setup ========== */
void setup() 
{
  //Inicializando o LCD e informando o tamanho de 16 colunas e 2 linhas
  //que é o tamanho do LCD usado neste projeto.
  arquivo.close();
  Serial.begin(9600);
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
}

/*========== Declarações ==========*/
// INSTÂNCIAS
SdFile arquivo;
Lista* lista = new Lista();
avl* arvore = new avl();

//DECLARAÇÕES DE VARIÁVEIS 
float temperatura = 0;
bool controleLista = false;
 
/*========== Funcao loop ==========*/
void loop()
{
  //CONTROLADOR DE LOOP
  controlaLoop++;

  // CONDIÇÃO QUE CONTROLA LEITURA DE TEMPERATURA
  if(controlaLoop <= 5 or (controlaLoop > 10 and controlaLoop <= 15))
  {	   
    // CONDIÃO PARA INSTÂNCIAR UM NOVA LISTA
    if (controlaLoop == 11) Lista* lista = new Lista();

    // CALCULANDO TEMPERATURA
    temperatura = temp.getTemp();

    // INSIRINDO TEMPERATURAS NA LISTA
    lista->insereTemperatura(temperatura); 
  
    // IMPRIMINDO NO SERIAL [COM] A TEMPERATURA LIDA
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");
    
    delay(3000);
  }

  // CONDIÇÃO QUE CONTROLA FUNÇÃO PARA SALVAR EM ARQUIVO
  if(controlaLoop == 6 or controlaLoop == 16)
  {  
    // IMPRIMINDO LISTA NO SERIAL
    lista->imprimirLista();
    Serial.println("Inserindo as temperaturas no Arquivo...");

    delay(5000);

    // PERCORRENDO A LISTA PARA SALVAR NO ARQUIVO
    lista->salvarEmArquivo(&arquivo, controleLista);
    
    // DELETANDO A LISTA ATUAL PARA ECONOMIZAR MEMORIA 
    delete lista;
  }

  // CONDIÇÃO QUE CONTROLA FUNÇÃO DE LEITURA DO ARQUIVO PARA A ARVORE
  if(controlaLoop == 27)
  {
    Serial.println("Inserindo as temperaturas do Arquivo na Arvore...");
    delay(2000);
    arquivo.open("arqTrabalho.dat",O_READ);
  
    // PERCORRENDO ARQUIVO DE [TEMPERATURA] A [TEMPERATURA] PARA INSERIR NA ARVORE
    Temperatura itemInserido; 
    while(arquivo.read(reinterpret_cast<void*>(&itemInserido), sizeof(Temperatura)) == sizeof(Temperatura))
    {
      arvore->insereTemperatura(itemInserido);
    } 
    // PERCORRE A ARVORE PARA ENCONTRAR O MENOR E MAIOR VALOR
    Serial.println("Foram encontrados os seguintes valores como Minimo e Maximo: ");
    Temperatura Minimo = arvore->Minimo(); 
    Temperatura Maximo = arvore->Maximo();

    // IMPRIMINDO A MENOR TEMPERATURA
    Serial.print("Menor Temperatura: ");
    Serial.print(Minimo);
    Serial.write("º"); //Simbolo de graus celsius
    Serial.println("C");
  
    // IMPRIMINDO A MAIOR TEMPERATURA
    Serial.print("Maior Temperatura: ");
    Serial.print(Maximo);
    Serial.write("º"); //Simbolo de graus celsius
    Serial.println("C");

    // FECHANDO ARQUIVO PARA RETORNAR O PONTEIRO DE ESCRITA PARA O INICIO
    arquivo.close();
    
    // ABRINDO ARQUIVO EM MODO DE ESCRITA E LIMPANDO DADOS
    arquivo.open("arqTrabalho.dat",O_WRONLY | O_TRUNC);

    // PERCORRENDO PARA SALVAR DO ARQUIVO NA ARVORE
    arvore->PercorrerPraSalvar(&arquivo);
    arquivo.close();
    
    // DELETANDO ARVORE PARA ECONOMIZAR MEMORIA
    delete arvore;
    
    Serial.println("Percorrendo o Arquivo para imprimir na tela os dados ordemados ...");
    delay(5000);

    // ABRINDO ARQUIVO PARA LEITURA
    arquivo.open("arqTrabalho.dat", O_READ);
    Temperatura itemLido;
    
    // CONTADOR PARA EXIBIR NUMERAÇÃO DAS TEMPERATURAS LIDAS
    int cont = 0;
    Serial.println("As temperaturas no arquivo são:");
    
    // PERCORRENDO ARQUIVO PARA PARA VISUALIZAR ORDENAÇÃO
    while(arquivo.read(reinterpret_cast<void*>(&itemLido), sizeof(Temperatura)) == sizeof(Temperatura))
    {
      // CONDIÇÃO PARA VISUALIZAR MELHOR OS VALORES IMPRESSOS 
      if(cont % 5 == 0) Serial.println();
      Serial.print(cont++);
      Serial.print(" - ");
      Serial.print("[");
      Serial.print(itemLido);
      Serial.print("ºC");
      Serial.print("] ");
    }
    Serial.println();

    // FINAL DE EXECUÇÃO
    Serial.println("Ficamos por aqui.");
    Serial.println("Obrigado!");
    delay(100000000000);
    }
}
