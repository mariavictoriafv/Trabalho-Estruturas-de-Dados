#include "Blockchain.h"

//Construtor sem argumentos
Blockchain::Blockchain(){
    this->firstBlock=NULL;
    this->lastBlock=NULL;
}

//Destrutor
Blockchain::~Blockchain(){
    destroyBlockchain();
}

void Blockchain::destroyBlockchain(){
    Block *aux1=firstBlock;
    //Destruimos todos os blocos da lista 
    while(aux1!=nullptr){
        Block *aux2=aux1->nextBlock;
        delete aux1;
        aux1=aux2;
    }
}

//Funcao para criar um novo bloco e inserir as suas transacoes
void Blockchain::createNewBlock(int numTransactions, int maxTransactios, int minerCode, newTransactions *infos){
    if(numTransactions!=0 && maxTransactios!=0){
        //ordenando o vetor por meio de um merge sort recursivo, porque e um algoritmo estavel
       mergeSort(infos,numTransactions);
    }
    
    //Criamos um novo bloco, para receber as transacoes
    //Caso especial: primeiro bloco da lista
    int _pos, _prevHash;
    if(firstBlock==nullptr){
        _pos=1;
        _prevHash=0;
        firstBlock=new Block( _pos, _prevHash, minerCode);
        lastBlock=firstBlock;
    }
    else{
        _pos=lastBlock->pos+1;
        _prevHash=lastBlock->getHash();
        lastBlock->nextBlock=new Block( _pos, _prevHash, minerCode);
        lastBlock->nextBlock->prevBlock=lastBlock;
        //Ataualizamos o fim da lista de blocos
        lastBlock=lastBlock->nextBlock;
    }   
    
    //Inserimos as transacoes ate atingirmos o limite
    // if(numTransactions!=0 && maxTransactios!=0){
        for(int k=0; k<numTransactions && k<maxTransactios; k++){
            lastBlock->addTransaction(infos[k].de, infos[k].para, infos[k].valor, infos[k].taxa);
        }
    // }

    //Mineramos o bloco, sem imprimir nenhuma informacao
    lastBlock->mineBlock(false);
    
}

void Blockchain::mergeSort(newTransactions *v, int p, int r,newTransactions *aux){
    if (p < r-1) {
        int meio = (p+r) / 2;
        mergeSort(v, p, meio,aux);
        mergeSort(v, meio, r,aux);
        merge(v, p, meio, r, aux); 
    }
}


void Blockchain::mergeSort(newTransactions *v, int n){
    newTransactions *aux = new newTransactions[n];
    mergeSort(v, 0, n,aux);
    delete[] aux;
}

//Funcao de merge para o Merge sort
void Blockchain::merge(newTransactions *v, int p, int q, int r,newTransactions *aux){
    int tam = r-p;
    int i = p; //cursor 1
    int j = q; //cursor 2
    int k = 0; //cursor para aux
    while(i < q && j < r) {
        if (v[i].taxa >= v[j].taxa)
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    }
    while(i < q)
        aux[k++] = v[i++];
    while(j < r)
        aux[k++] = v[j++];
    for(k = 0; k < tam; k++)
        v[p+k] = aux[k];    
}

void Blockchain::printBlockchain(){
    //Imprimindo a Blockchain como mostrado nos arquivos de exemplo

    std::cout<<"=====================\n";

    //Se a lista estiver vazia, nao imprimos nenhum valor
    if(firstBlock==nullptr){
        std::cout<<"\n";
        std::cout<<"=====================\n";
        return;
    } 

    //Se a lista nao estiver vazia, temos que percorrer os blocos imprimindo as transacoes
    Block *aux=firstBlock;
    while(aux){
            std::cout<<"---------------------\n";
            std::cout<<"Pos: "<<aux->pos<<"\n";
            std::cout<<"Prev hash: "<<aux->prevHash<<"\n";
            std::cout<<"Criador: "<<aux->criador<<"\n";
            std::cout<<"Transacoes:\n";

            //Se no bloco ha transacoes, vamos imprimi-las
            if(aux->listaFirst!=nullptr){
                Transaction *copy=aux->listaFirst;

                while(copy){
                    std::cout<<copy->de<<" -> "<<copy->para<<" (valor: "<<copy->valor<<" , taxa: "<<copy->taxa<<")\n";
                    copy=copy->nextT;
                }
            }

            std::cout<<"Proof of work: "<<aux->proofWork<<"\n";
            std::cout<<"Hash: "<<aux->getHash()<<"\n";
            std::cout<<"---------------------\n";

            aux=aux->nextBlock;
            //Se a lista ainda tiver um bloco, imprimimos uma separacao
            if(aux){
                std::cout<<"          ^\n";
                std::cout<<"          |\n";
                std::cout<<"          v\n";
            }
        }


    std::cout<<"\n=====================\n"; 
}