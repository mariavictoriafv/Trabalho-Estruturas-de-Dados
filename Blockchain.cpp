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

//Construtor de copia
Blockchain::Blockchain(const Blockchain &_blockchain){
    createBlockchain();
    *this=_blockchain;
}

//Operador de atribuicao
Blockchain & Blockchain::operator=(const Blockchain &_blockchain){
    //Se as listas forem iguais, apenas retornamos a lista
    if(this==&_blockchain) return *this;

    //Limpamos a lista que vai receber as informacoes
    destroyBlockchain();
    createBlockchain();

    //Se a blockchain a ser copiada for vazia
    //Apenas retornamos 
    if(_blockchain.firstBlock==nullptr){
        firstBlock=nullptr;
        lastBlock=nullptr;
    }
    else{
        //Precisamos copiar os blocos da blockchain recebida
        //Para a blockchain atual
        Block *aux=_blockchain.firstBlock;
        //Esse ponteiro vai guardar o final da lista
        //Vamos autalizando esse final ate copiar todos os blocos
        Block *ptr_last;
        while(aux){
            //Caso seja o primeiro bloco da lista
            //Atualizamos o listaFirst
            //Como a classe block possui operador =, podemos fazer a atribuicao
            if(this->firstBlock==nullptr){
                firstBlock=aux;
                lastBlock=aux;
            }
            else{
                //Adicionamos o novo bloco na lista e 
                //Atualizamos os ponteiros
                *(ptr_last->nextBlock)=*(aux);
                ptr_last->nextBlock=aux;
                *(ptr_last->nextBlock->prevBlock)=*(ptr_last);
                ptr_last->nextBlock->prevBlock=ptr_last;
                ptr_last=aux;
            } 

            aux=aux->nextBlock;
        }
        //Atualizamos o fim da lista
        *lastBlock=*ptr_last;
    }

    return *this;
}

void Blockchain::createBlockchain(){
    this->firstBlock=NULL;
    this->lastBlock=NULL;
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
void Blockchain::createNewBlock(const int numTransactions, const int maxTransactios, const int minerCode, newTransactions *infos){
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

void Blockchain::changeTransaction(const int pos_B, const int pos_T, const int new_De, const int new_Para, const int new_Valor, const int new_Taxa){
    //Se a blockchain estiver vazio, nao alteramos nada
    if(firstBlock==nullptr) return;
    
    //Auxiliar para percorrer os blocos
    Block *aux=firstBlock;

    //Procuramos o bloco onde esta a transacao
    while(aux->pos!=pos_B) aux=aux->nextBlock;

    //Se o bloco estiver vazio, nao alteramos nada
    if(aux->listaFirst==nullptr) return;

    //Agora devemos encontrar a transacao que precisa ser mudada
    Transaction *copy=aux->listaFirst;

    for(int c=1; c<pos_T; c++) copy=copy->nextT;

    //Alteramos as informacoes
    copy->de=new_De;
    copy->para=new_Para;
    copy->valor=new_Valor;
    copy->taxa=new_Taxa;

    //Mineramos o bloco
    aux->mineBlock(false);
}

//Funcao que retorna um Vector com os saldos dos usuarios ate o bloco B
std::vector<int> Blockchain::getBalances(const int b){

    //Caso especial: lista vazia
    if(firstBlock==nullptr){
        //Criamos um vector bazio e o retornamos
        std::vector<int> empty;
        return empty;
    }

    //Bloco auxiliar para percorrer a lista de blocos
    Block *aux=firstBlock;

    int valueBlock=256; //Esse interio guardara o valor do proximo bloco a ser minerado
    int maiorCriador=0;

    //Primeiramente, temos que saber ate qual usuario precisamos imprimir o saldo
    //Comparamos com o criador do bloco e com os que aparecem nas transacoes
    while(aux && aux->pos<=b){
       //Transacao auxiliar para percorrer as transacoes dos blocos
       Transaction *copy=aux->listaFirst;


        if(aux->criador>maiorCriador) maiorCriador=aux->criador;

        while(copy){
            if(copy->de>maiorCriador) maiorCriador=copy->de;
            if(copy->para>maiorCriador) maiorCriador=copy->para;

            copy=copy->nextT;
        }

        aux=aux->nextBlock;
    }

    //Vector para armazenar os saldos dos usuarios
    //Inicialmente todos tem saldo 0
    std::vector<int> values(maiorCriador+1, 0);

    //Reinicialisando as variaveis auxiliares para percorrer as listas
    aux=firstBlock;
 
    //Agora precisamos percorrer novamente as listas
    //Mas vamos calcular os saldos de cada usuario no processo
    while(aux && aux->pos<=b){
        //Transacao auxiliar para percorrer as transacoes dos blocos
        Transaction *copy=aux->listaFirst;


        //Atribuimos a recompensa ao criador do bloco
        values[aux->criador]+=valueBlock;
        //Atualizamos o valor para o proximo bloco
        valueBlock/=2;

        while(copy){
            //Agora vamos atribuir os valores de cada usario a cada transacao
           values[copy->para]+=copy->valor; 
           values[aux->criador]+=copy->taxa;
           values[copy->de]-=(copy->taxa+copy->valor);

            copy=copy->nextT;
        }

        aux=aux->nextBlock;
    }

    //Retornamos esses valores para serem impressos na main
    return values;
}

Blockchain::TransactionIterator Blockchain::transactionBegin() const{
    //Se a Blockchain estiver vazia
    //Retornamos um iterador com informaçoes nulas
    if(firstBlock==nullptr){
        TransactionIterator it(NULL, NULL);
        return it;
    }

    Block *aux=firstBlock;
    while(aux){
        //Vemos se algum bloco possui transacao
        if(aux->listaFirst!=nullptr){
        //Retornamos a transacao encontrada
            TransactionIterator it(aux, aux->listaFirst);
            return it;
        }
        
        aux=aux->nextBlock;
    }

    //Caso nao haja nenhuma transacao na Blockchain, retornamos 
    //Um iterador que aponta para nulo
    TransactionIterator it(NULL, NULL);
    return it;
}

Blockchain::TransactionIterator Blockchain::transactionEnd() const{
    //Retornando um iterador com informacoes nulas 
    TransactionIterator it(NULL, NULL);
    return it;
}





