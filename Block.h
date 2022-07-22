#ifndef Block_H
#define Block_H

#include <string>
#include <iostream>
#include "Transaction.h"
#include "SHA256.h"

class Block{
    friend class Blockchain;
    friend class iterator;

public:
    //construtor de Block sem proofWork
    Block(const int posX, const int prevHashX, const int criadorX);
    //construtor de Block com proofWork
    Block(const int posX, const int prevHashX, const int criadorX, const int proofWorkX);
    //construtor de copia
    Block(const Block &_block);
    //destutor
    ~Block();

    Block &operator=(const Block &); //operador de atribuicao
    void createNewBlock(); //funcao para criar um novo bloco
    void destroyBlock(); //funcao que destroi um bloco

    void addTransaction(const int a, const int b,const int valor,const int taxa);
    void mineBlock(bool print); //funcao para minerar o bloco
    int getHash(); //funcao para retornar o Hash do bloco
    bool isMineBlock(); //funcao para verificar se um bloco foi minerado
    void showValues(); //funcao que vao imprimir os valores usados no calculo do hash
    void showBinary(); //funcao para mostrar na tela o hash em representacao binaria
    void showResult(); //funcao para imprimir o proofWork, o hash, e o hash binario

private:

    int pos;
    int prevHash;
    int criador; 
    int proofWork;
    Transaction *listaFirst; //apontador para a primeira transacao do bloco
    Transaction *listaLast; //apontador para a ultima transacao do bloco
    Block *nextBlock; //apontador para o bloco seguinte
    Block *prevBlock; //apontador para o bloco anterior
    int transactionSize(); //retorna quantas transacoes ha no bloco

};


#endif