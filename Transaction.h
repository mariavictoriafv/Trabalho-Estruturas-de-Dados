#ifndef Transaction_H
#define Transaction_H

#include <string>
#include <iostream>

class Transaction{

public:
    void imprime() const{
        std::cout<<de<<" -> "<<para<<" (valor: "<<valor<<" , taxa: "<<taxa<<")\n";
    }

private:
    friend class Block;
    friend class Blockchain;
    friend class iterator;

    Transaction(const int deX, const int paraX, const int valorX, const int taxaX);

    //funcao para colocar uma nova transacao na lista
    void push_back_T(const int deX, const int paraX, const int valorX, const int taxaX); 
    //funcao para imprimir as transacoes da Blockchain

    int de;
    int para;
    int valor;
    int taxa;
    Transaction *nextT; //ponteiro para a próxima transacao

};


#endif