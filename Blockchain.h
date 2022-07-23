#ifndef Blockchain_
#define Blockchain_

#include <iostream>
#include <vector>
#include "Block.h"

struct newTransactions{
      int de;
      int para;
      int valor;
      int taxa;
};

//Declarando o iterador para que ele seja reconhecido pela Blockchain
class iterator;

class Blockchain{
    friend class iterator;

public:
    typedef iterator TransactionIterator;

    //Construtor sem argumentos
    Blockchain();

    //Destrutor
    ~Blockchain();

    //Construtor de copia
    Blockchain(const Blockchain &_blockchain);

    //Operador de atrbuicao
    Blockchain &operator=(const Blockchain &);

    //Funcoes auxiliares
    void destroyBlockchain();
    void createBlockchain();

    //Funcao que cria um novo bloco
    void createNewBlock(const int numTransactions, const int maxTransactios, const int minerCode, newTransactions *infos);
    
    //Funcao para imprimir a Blockchain toda
    void printBlockchain();
    
    //Funcao para alterar uma transacao
    void changeTransaction(const int pos_B, const int pos_T, const int new_De, const int new_Para, const int new_Valor, const int new_Taxa);
    
    //Funcao para calcular e retornar um vector com os saldos ate o bloco B
    std::vector<int> getBalances(const int b);

    //Funcao para adicionar um bloco no fim da lista
    void push_backB(const Block &_block);
    
    //Funcao para retornar a primeira transacao da lista
    TransactionIterator transactionBegin() const;
    
    //Funcao para retornar a ultima transacao da lista
    TransactionIterator transactionEnd() const;

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

//Definindo e implementando o iterador da Blockchain
class iterator{ 
    friend class Blockchain;

public:
    //Constutor
    iterator(Block *_thisBlock, Transaction *_thisTransaction){
        nowBlock=_thisBlock;
        nowTransc=_thisTransaction;
    }

    //Pos incremento
    iterator operator++(int){
        //Testamos se o iterador ja nao aponta para nulo
        if(!nowTransc) return *this;

        //Se houver uma proxima transacao no mesmo bloco
        //Alteramos a transacao e retornamos o iterador 
        if(nowTransc->nextT!=nullptr){
            iterator aux=*this;
            nowTransc=nowTransc->nextT;
            return aux;
        }
        
        iterator it=*this; //Guardamos esse iterador para retorna-lo

        nowBlock=nowBlock->nextBlock;

        //Procuramos a proxima transacao na Blockchain
        while(nowBlock){
            if(nowBlock->listaFirst){
                nowTransc=nowBlock->listaFirst;
                return it;
            }
            nowBlock=nowBlock->nextBlock;
        }


        //Caso nao haja nenhuma proxima transacao na Blockchain,
        //retornamos as informacoes antigas, armazenadas em it
        //Atualizamos a transacao apontada pelo iterador para nulo
        nowTransc=nullptr;

        return it;
    }

    //Comparador !=
    bool operator!=(const iterator &T) const{
        return (nowTransc!=T.nowTransc);
    }

    //Comparador ==
    bool operator==(const iterator &T) const{
        return (nowTransc==T.nowTransc);
    }

    //Operador de derreferencia
    Transaction &operator*(){
        return *nowTransc;
    }

    //Versao constante para o operador de derreferencia
    const Transaction &operator*() const{
        return *nowTransc;
    }
    
private:
    Block *nowBlock;
    Transaction *nowTransc;
};

#endif