#include "Block.h"

//construtor de Block sem proofWork
Block:: Block(const int posX, const int prevHashX, const int criadorX){
    pos=posX;
    prevHash=prevHashX;
    criador=criadorX;
    nextBlock=nullptr;
    prevBlock=nullptr;
    listaFirst=nullptr;
    listaLast=nullptr;
}

//construtor de Block com proofWork
Block::Block(const int posX, const int prevHashX, const int criadorX, const int proofWorkX){
    pos=posX;
    prevHash=prevHashX;
    criador=criadorX;
    proofWork=proofWorkX;
    nextBlock=nullptr;
    prevBlock=nullptr;
    listaFirst=nullptr;
    listaLast=nullptr;
}

//construtor de copia
Block::Block(const Block &_block){
    createNewBlock();
    *this=_block;
}

//destrutor
Block::~Block(){
    destroyBlock();
}

//operador de atribuicao
Block & Block::operator=(const Block &_block) {
    //se os blocos forem iguais, apenas retornamos o bloco
    if(this==&_block) return *this;

    //limpamos o bloco
    destroyBlock();
    createNewBlock();

    if(_block.listaFirst==nullptr){ //se o bloco estiver vazio
        this->listaFirst=nullptr;
        this->listaLast=nullptr;
    }
    else{ //se nao, copiamos as informacoes e as transacoes
        pos=_block.pos;
        prevHash=_block.prevHash;
        criador=_block.criador;
        proofWork=_block.proofWork;
        
        Transaction *aux=_block.listaFirst;
        while(aux!=nullptr){
            addTransaction(aux->de, aux->para, aux->valor, aux->taxa);
            aux=aux->nextT;
        }
        
    }

    return *this;
}

//funcao que cria um novo bloco
void Block::createNewBlock(){
    nextBlock=nullptr;
    prevBlock=nullptr;
    listaFirst=nullptr;
    listaLast=nullptr;
}

//funcao que destroi um bloco
void Block::destroyBlock(){
    //esse while percorre os nodos, deletando cada transacao
    while(listaFirst){
        Transaction *aux;
        aux=listaFirst;
        listaFirst=listaFirst->nextT;
        delete aux;
    }
}

void Block::addTransaction(const int a=0, const int b=0,const int valor=0,const int taxa=0){
    //os valores nao podem ser negativos
    if(a>=0 && b>=0 && valor>=0 && taxa>=0){
        //caso a transacao a ser adicionada seja a primeira da lista
        if(listaFirst==nullptr){
            //alocamos uma nova transacao, que por enquanto sera o inicio e o fim da lista
            listaFirst=new Transaction(a, b, valor, taxa);
            listaLast=listaFirst;
        }
        //caso nao seja
        else{
            //vamos criar uma nova transacao no fim da lista e atualizar o fim da lista
            listaLast->push_back_T(a, b, valor, taxa);
            listaLast=listaLast->nextT;
        }
    }

}

int Block::getHash(){
    SHA256 hash;
    Transaction *aux;
    int c=2; //contador de elementos do vetor

    //vetor que armazenara os numeros para o calculo do hash
    //aloca o vetor de acordo com o numero de transacoes
    int *v= new int[4+(4*transactionSize())];

    //armazenando no vetor as variaveis do bloco que serao usadas para calcular o hash
    v[0]=pos;
    v[1]=prevHash;
    v[2]=criador;

    //auxiliar que vai percorrer a lista pegando os dados das transacoes
    aux=listaFirst;

    //iteracao para percorrer a lista e colocar as informacoes no vetor
    while (aux!=nullptr){
        //a cada transacao, mais 4 informacoes serao adicionadas
        c+=4;
        v[c-3]=aux->de;
        v[c-2]=aux->para;
        v[c-1]=aux->valor;
        v[c]=aux->taxa;
        //passamos para a proxima transacao
        aux=aux->nextT;
       
    }

    //por fim, colocados o proofWork no vetor
    c++;
    v[c]=proofWork;
    //fazemos esse c++ porque em um vetor que vai de 0 ate n, temos n+1 posicoes
    c++;
  
    int resultado = hash.calcula(v, c);

    delete []v;

    return resultado;
}

bool Block::isMineBlock(){
  
    //calculamos o hash do numero
    int hash_int = getHash();

    //essa operação bitwise usa o número 1023 porque ele é formado exatamente por uma sequencia de 10 1's
    //assim, caso o hash tenha uma sequencia de 10 0's, a operacao dara false, e o bloca tera sido minerado
    //fazendo a funcao retornar true
    if( (hash_int & 1023)==0 ) return true;
    
    return false;
}

void Block::mineBlock(bool print){
    //iniciamos o proofWork para fazer os testes
    proofWork=0;

    if(!print){ //usado no modo quiet
        //incrementamos o valor de proofWork ate que ele gere um bloco valido
        while(!isMineBlock()) proofWork++;
    }
    else{ //usado no modo verbose
        //vamos minerar o bloco, porem imprimindo o prooWork e hash binario
			
        while(true){
            showValues(); //imprimir os numeros no hash
            std::cout<<"\n";	
            showBinary();
            std::cout<<"\n";
            std::cout<<"\n";

            if(isMineBlock()) break;
            proofWork++; //atualizamos o valor de proofWork
        }
    }
}

int Block::transactionSize() const{
    int c=0;
    Transaction *aux;
    aux=listaFirst;

    //contamos quantas transacoes existem no bloco
    while (aux!=nullptr){
        c++;
        aux=aux->nextT;
    }
    
    return c;
}

void Block::showValues() const{
    //mostrando as informacoes e transacoes na tela
    std::cout<<pos<<" ";
    std::cout<<prevHash<<" ";
    std::cout<<criador<<" ";

    Transaction *aux;
    aux=listaFirst;

    while(aux!=nullptr){
        std::cout<<aux->de<<" ";
        std::cout<<aux->para<<" ";
        std::cout<<aux->valor<<" ";
        std::cout<<aux->taxa<<" ";

        aux=aux->nextT;
    }    

    std::cout<<proofWork<<" ";

}

void Block::showBinary(){
    int hash=getHash(); //achamos o hash do bloco
    int _hash=hash;
    std::string binaryHash1="";

    if(hash>=0){ // caso o hash seja positivo
        while(hash!=0){
            if(hash%2==0) binaryHash1+="0"; //se o numero for par, entao adicionamos 0 em sua representacao binaria
            else binaryHash1+="1"; //caso contrario, devemos adicionar o 1

            hash/=2; //divimos o numero por 2
        }
    }
    else{ //caso o hash seja negativo
        //nesse caso, precisamos inverter a representacao binario do numero positivo
        while(hash!=0){
            if(hash%2==0) binaryHash1+="1"; //se o numero for par, entao adicionamos 0 em sua representacao binaria
            else binaryHash1+="0"; //caso contrario, devemos adicionar o 1

            hash/=2; //divimos o numero por 2
        }

        //alem disso, agora temos que somar 1 ao resultado
        for(int i=0; binaryHash1.length()>i; i++){
            if(binaryHash1[i]=='0'){
                 binaryHash1[i]='1';
                 break;
            }
            else binaryHash1[i]='0';
        }
        binaryHash1+="1"; //adicionamos 1 ao final

    }

    //agora precisamos inverter os bits do array
    std:: string binaryHash2="";
    for(int i=1; i<=binaryHash1.length(); i++)
        binaryHash2 += binaryHash1[binaryHash1.length()-i];
    

    // //completando para um numero com 32 bits
    for(int i=0; binaryHash2.length()<32; i++){
        std::string bit;
        if(_hash>=0) bit="0";
        else bit="1";
        bit+=binaryHash2;
        binaryHash2=bit;
    }
    
    //imprimindo o numero
    std::cout<<binaryHash2;
}

//funcao para imprimir o proofWork, o hash, e o hash binario
void Block::showResult(){
    std::cout<<proofWork<<"\n";
	std::cout<<getHash()<<"\n";
	showBinary();
	std::cout<<"\n";	

}