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
    //funcao para ordenar as transacoes com base na taxa
    void mergesortTransactions(newTransactions *vetor, int beg, int end);
    //funcao para fazer o merge
    void mergeTransactions(newTransactions *vetor, int beg, int middle, int end);

    Block *firstBlock; //apontador para o primeiro bloco
    Block *lastBlock; //apontador para o ultimo block


};

#endif