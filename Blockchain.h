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
    //Funcao para alterar uma transacao
    void changeTransaction(int pos_B, int pos_T, int new_De, int new_Para, int new_Valor, int new_Taxa);
    //Funcao para calcular e imprimir o saldo
    void printTotal(int b);
    //Funcoes auxiliares
    void destroyBlockchain();

    private:
    //Funcao que vai chamar o metodo de ordenacao
    void orderTransactions(newTransactions *values, int num_);
    //Funcao para ordenar as transacoes com base na taxa
    void mergeSortTransactions(newTransactions *values, int beg, int end, newTransactions *aux) ;
    //Funcao para juntar as partes ordenadas
    void mergeTransactions(newTransactions *values, int beg, int half, int end, newTransactions *aux);

    Block *firstBlock; //apontador para o primeiro bloco
    Block *lastBlock; //apontador para o ultimo block


};

#endif