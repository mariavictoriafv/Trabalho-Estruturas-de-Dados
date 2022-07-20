#ifndef Transaction_H
#define Transaction_H

#include <string>
#include <iostream>

class Transaction{

private:
    friend class Block;
    friend class Blockchain;

    Transaction(const int deX, const int paraX, const int valorX, const int taxaX);

    //funcao para colocar uma nova transacao na lista
    void push_back_T(const int deX, const int paraX, const int valorX, const int taxaX); 

    int de;
    int para;
    int valor;
    int taxa;
    Transaction *nextT; //ponteiro para a próxima transacao

};


#endif