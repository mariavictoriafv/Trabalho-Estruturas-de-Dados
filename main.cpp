#include <iostream>
#include <string>
#include "SHA256.h"
#include "Block.h"
#include "Blockchain.h"
using namespace std;

//sua main devera ter esse include e usar a funcao imprimeTransacoes
//para imprimir...
//o arquivo imprimeTransacoes.h nao precisa ser enviado (o submitty ja tem uma copia dele, para garantir
//que ninguem vai modificar a funcao de impressao)
//O include abaixo pode ser mantido comentado quando voce for enviar a primeira parte do trabalho 
//e tambem enquanto voce nao termina a implementacao dos iteradores (caso contrario seu programa nao compilara)
//#include "imprimeTransacoes.h"

int main() {
	std::string operation, type;

//Lendo as variaveis da entrada. Algumas so serao lidas em determinadas operacoes
	std::cin>>operation;

//Operacos da parte 2
	if(operation=="operacoes"){
		//Criando a Blockchain
		Blockchain MyBlockchain;

		//Enquanto tiverem operacoes para serem lidas
		while(std::cin>>type){

			if(type=="criarBloco"){
				//Lendo as informacoes para criar o bloco
				int num, numMax, minerCode;
				std::cin>>num>>numMax>>minerCode;
				//Criamos o vetor de transacoes
				newTransactions *list = new newTransactions[num];
				
				//So vamos ler as transacoes se existirem transacoes
					//Lendo as informacoes das transacoes
					for(int i=0; i<num; i++){
						cin>>list[i].de;
						cin>>list[i].para;
						cin>>list[i].valor;
						cin>>list[i].taxa;
					}

				//Criamos o bloco e o colocamos na Blockchain
				MyBlockchain.createNewBlock(num, numMax, minerCode, list);
				delete[] list;
			}
			else if(type=="imprimeBlockchain"){
				MyBlockchain.printBlockchain();
			} 	
			else if(type=="imprimeSaldo"){
				int b;
				std::cin>>b;
				//Vector para receber o vector dos saldos
				std::vector<int> balances;

				balances=MyBlockchain.getBalances(b);

				std::cout<<"=====================\n";

				//Agora imprimimos os saldos de cada usuario, caso possivel
				if(!balances.empty()){
					std::cout<<"Saldo apos bloco "<<b<<"\n";

					for(int i=0; i<balances.size(); i++)
						std::cout<<i<<" : "<<balances[i]<<"\n";
				}

				std::cout<<"=====================\n";
			}
			else if(type=="alteraTransacao"){
				int posB, posT, newD, newPara, newValor, newTaxa;
				std::cin>>posB>>posT>>newD>>newPara>>newValor>>newTaxa;
				MyBlockchain.changeTransaction(posB, posT, newD, newPara, newValor, newTaxa);
			}
		}
	} 

//Operacos da parte 1
	else{
		if(operation=="minerarBloco") std::cin>>type;

		int pos_, prevHash_, criador_, proofWork_, n=0;
		
		std::cin>>pos_>>prevHash_>>criador_;
		if(operation=="validarBloco") std::cin>>proofWork_;
		std::cin>>n;

	//Criando o bloco com as informacoes lidas
		Block MyBlock(pos_, prevHash_, criador_, proofWork_);

	//Prenchendo o bloco com as transacoes que vao sendo lidas da entrada padrap
		for(int i=0; i<n; i++){
			int a, b, c, d;
			std::cin>>a>>b>>c>>d;
			MyBlock.addTransaction(a,b,c,d);
		}

	//Aqui chamamos a operacao que foi pedida, e escrevemos a saida na formatacao pedida
		if(operation=="validarBloco"){
			
			std::cout<<MyBlock.getHash()<<"\n";
			MyBlock.showBinary();//imprimir numero em binario
			std::cout<<"\n";	
			//testando se o bloco foi minerado
			if(MyBlock.isMineBlock())
				std::cout<<"OK\n";
			else
				std::cout<<"Nao minerado\n";
		}
		else if(operation=="minerarBloco"){

			//caso a opcao seja isso, mineramos o bloco e imprimos as informacoes apenas uma vez
			if(type=="quiet"){
				MyBlock.mineBlock(false);
				MyBlock.showResult();	
			}
			//aqui imprimimos tudo ate achar o proofWork valido
			else if(type=="verbose"){ 
				MyBlock.mineBlock(true);
				MyBlock.showResult();
			}	
		}
	}



	return 0;
}

