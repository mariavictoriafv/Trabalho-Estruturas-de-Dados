#ifndef Blockchain_
#define Blockchain_

#include <iostream>
#include "Block.h"

struct newTransactions{
      int de;
      int para;
      int valor;
      int taxa;
};


class Blockchain{
    public:
    //Construtor sem argumentos
    Blockchain();
    //Destrutor
    ~Blockchain();
    //Funcao que cria um novo bloco
    void createNewBlock(int numTransactions, int maxTransactios, int minerCode, newTransactions *infos);
    //Funcao para imprimir a Blockchain toda
    void printBlockchain();
    //Funcao para calcular e imprimir o saldo
    void printTotal(int b);
    //Funcoes auxiliares
    void destroyBlockchain();

    private:
    //Funcao que vai chamar o metodo de ordenacao
    void mergeSort(newTransactions v[], int n);
    //Funcao para ordenar as transacoes com base na taxa
    void mergeSort(newTransactions v[], int p, int r,newTransactions aux[]) ;
    //Funcao para juntar as partes ordenadas
    void merge(newTransactions v[], int p, int q, int r,newTransactions aux[]);

    Block *firstBlock; //apontador para o primeiro bloco
    Block *lastBlock; //apontador para o ultimo block


};

#endif