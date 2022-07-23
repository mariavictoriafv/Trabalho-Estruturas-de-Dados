Eu li as regras
Maria Victória Fernandes Vaz - matrícula: ES105470
Fontes de consulta: materiais disponibilizados na disciplina de IFN213 e respostas no fórum da disciplina
-A implementação do Merge sort que eu usei é baseada na implementação vista em sala de aula
-A implementação do iterador também é baseada na implementação de listas duplamente encadeadas
aprendida em sala de aula

-Respostas das perguntas da parte 2

1)Quantas Capicoins existirão no mundo?

Se a recompensa por minerar o primeiro bloco é 256 Capicoins e o valor cai pela metada a cada
bloco, temos que a recompensa por minerar o bloco n é dada por 256/(2^n). Então o total de
Capicoins é o somatório dessa sequência até 256/(2^n) ser o menor inteiro possível:
256+128+64+32+16+8+4+2+1=511.

2)Dadas duas blockchains válidas (onde cada bloco contém o hash correto do bloco anterior),
é possível ver se as duas são iguais de forma muito eficiente: basta comparar o hash do último
bloco das duas. Por que isso “garante” a igualdade?

Uma das informações utilizadas para calcular o Hash é o PrevHash, ou seja, o Hash do bloco 
anterior. Isso significa que se alguma informação de um bloco for alterada, isso mudará o
PrevHash do próximo bloco e todos os Hashs daí em diante. Dessa forma, como o Hash do
último bloco depende das informações de todos os outros blocos, para que o Hash do último
bloco seja igual a outro de uma outra Blockchain, todas as outras informações teriam de ser iguais
também, ou seja, as Blockchains teriam que ser iguais, salvo raras excessões;
