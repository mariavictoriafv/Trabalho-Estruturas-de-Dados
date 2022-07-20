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
        mergesortTransactions(infos, 0, numTransactions);
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
    if(numTransactions!=0 && maxTransactios!=0){
        for(int k=0; k<numTransactions && k<maxTransactios; k++){
            lastBlock->addTransaction(infos[k].de, infos[k].para, infos[k].valor, infos[k].taxa);
        }
    }

    //Mineramos o bloco, sem imprimir nenhuma informacao
    lastBlock->mineBlock(false);
    
}

//Merge sort para ordenar as transacoes
void Blockchain::mergesortTransactions(newTransactions *vetor, int beg, int end){

    if(beg==end) return; //so ordenamos o vetor se ele tiver mais de uma transacao
    else if(beg<end-1){ //vamos ordenador o vetor enquanto o inicio for menor que o fim
        int middle=(beg+end)/2; //definimos o valor do meio do vetor
        mergesortTransactions(vetor, beg, middle); //ordenamos a primeira metade do vetor
        mergesortTransactions(vetor, middle, end); //ordenamos a segunda metade do vetor
        mergeTransactions(vetor, beg, middle, end); //unimos as partes ordenadas
    }
}

//Funcao de merge para o Merge sort
void Blockchain::mergeTransactions(newTransactions *vetor, int beg, int middle, int end){
    //para percorrer as posicoes, usaremos iteradores do tipo int, pois é um vetor
    int it1=beg;
    int it2=middle;
    int it3=0;

    //agora precisamos saber o tamanho do vetor 
    int size=end-beg;
    
    //criando um vetor auxiliar para receber as informacoes ordenadas, pois o merge sort nao e in-place
    newTransactions newVetor[size];

    //Vamos preencher o vetor auxiliar com as informacoes do vetor original
    //Ou seja, enquanto o final e maior que o inicio e o meio e maior que o inicio
    //Usamos apenas o intervalo indicado por it1 e it2
    while(it1<middle && it2<end){
        //Colocamos a transacao de maior taxa antes, ou o que foi inserida primeiro
        std::cout<<it1<<"-"<<it2<<"\n";
        if(vetor[it1].taxa>=vetor[it2].taxa){
            //std::cout<<vetor[it1].taxa<<"-"<<vetor[it2]<<"\n";
            newVetor[it3]=vetor[it1];
            it3++;
            it1++;
        }
        else{
            newVetor[it3]=vetor[it2];
            it3++;
            it2++;
        }
    }

    //Agora copiamos o resto do vetor original para o vetor auxiliar
    //Consideramos cada metade
    while(it1<middle){
        newVetor[it3]=newVetor[it1];
        it3++;
        it1++;
    } 
    while(it2<end){
        newVetor[it3]=newVetor[it2];
        it3++;
        it2++;
    }

    //Copiamos o vetor auxiliar para o vetor original
    for(int i=0; i<size; i++) {
        vetor[i+beg]=newVetor[i];
        //std::cout<<i+beg<<"-"<<vetor[i+beg].taxa<<"-"<<newVetor[i].taxa<<"\n";
    }
    //std::cout<<"-------------------\n";

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