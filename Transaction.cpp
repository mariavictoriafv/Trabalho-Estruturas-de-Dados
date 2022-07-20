#include "Transaction.h"


//construtor para a classe transacao
Transaction::Transaction(const int deX, const int paraX, const int valorX, const int taxaX){
    de=deX;
    para=paraX;
    valor=valorX;
    taxa=taxaX;
    nextT=nullptr;
}

//funcao para colocar uma nova transacao na lista
void Transaction::push_back_T(const int deX, const int paraX, const int valorX, const int taxaX){
    //colocamos o apontador da transacao para apontar para uma proxima, que sera criada;
    nextT= new Transaction(deX, paraX, valorX, taxaX);
}