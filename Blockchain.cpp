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
       orderTransactions(infos, numTransactions);
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
        for(int k=0; k<numTransactions && k<maxTransactios; k++){
            lastBlock->addTransaction(infos[k].de, infos[k].para, infos[k].valor, infos[k].taxa);
        }

    //Mineramos o bloco, sem imprimir nenhuma informacao
    lastBlock->mineBlock(false);
}

void Blockchain::mergeSortTransactions(newTransactions *values, int beg, int end, newTransactions *aux){
    
    if(beg==end) return; //so ordenamos o vetor se ele tiver mais de uma transacao    
    else if(beg<end-1){ //vamos ordenador o vetor enquanto o inicio for menor que o fim
        int middle = (beg+end) / 2; //definimos o valor do meio do vetor
        mergeSortTransactions(values, beg, middle, aux); //ordenamos a primeira metade do vetor
        mergeSortTransactions(values, middle, end, aux); //ordenamos a segunda metade do vetor
        mergeTransactions(values, beg, middle, end, aux); //unimos as partes ordenadas
    }
}


void Blockchain::orderTransactions(newTransactions *values, int num_){
    //Como essa implementacao do merge nao e in-place, criaamos um auxiliar 
    newTransactions *aux = new newTransactions[num_];
    //Chamamos a funcao de merge sort
    mergeSortTransactions(values, 0, num_, aux);
    //Depois de ordenar e colocar as informacoes no vetor original,
    //Deletamos o vetor que foi alocado
    delete[] aux;
}

//Funcao de merge para o Merge sort
void Blockchain::mergeTransactions(newTransactions *values, int beg, int half, int end, newTransactions *aux){
   //para percorrer as posicoes, usaremos iteradores do tipo int, pois é um vetor
    int i=beg; 
    int j=half; 
    int k=0; 

    //agora precisamos saber o tamanho do vetor 
    int tam = end-beg;

     //Vamos preencher o vetor auxiliar com as informacoes do vetor original
    //Ou seja, enquanto o final for maior que o inicio e o meio for maior que o inicio
    //Usamos apenas o intervalo indicado por i e j
    while(i<half && j<end) {
        //Colocamos a transacao de maior taxa antes, ou o que foi inserida primeiro
        if(values[i].taxa>=values[j].taxa){
            aux[k] = values[i];
            k++;
            i++;
        }
        else{
            aux[k] = values[j];
            k++;
            j++;
        }           
    }

    //Agora copiamos o resto do vetor original para o vetor auxiliar
    //Consideramos cada metade
    while(i<half){
        aux[k] = values[i];
        k++;
        i++;
    }       
    while(j<end){
        aux[k] = values[j];
        k++;
        j++;
    }
        
     //Copiamos o vetor auxiliar para o vetor original
    for(k=0; k<tam; k++) values[beg+k]=aux[k];    
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