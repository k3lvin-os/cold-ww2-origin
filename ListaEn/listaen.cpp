 #include <iostream>
 #include <stdlib.h>
 #include "listaen.h"
 using namespace std;
 

 
 
 /*O endere�o de uma lista encadeada � o endere�o
  da primeira c�lula*/
  
  /* Esta fun��o recebe um inteiro x e uma lista 
  encadeada ini de inteiros, com celula-cabe�a. A
  fun��oi devolve o endere�o de uma celula que cont�m
  x ou devolve NULL se t�o ceulula n�o existe.*/
Celula* Busca(int x, Celula *ini){
	
	Celula *p;
	p = ini->prox;
	while(p != NULL && p->conteudo != x)
		p = p->prox;
	return p;
}

/*Esta fun��o insere uma nova celula em uma lista
encadeada. A nova celula tem conteudo x e � inserida entre a 
celula apontada por p e a seguinte. Sup�e-se que p!= NULL*/
void Insere(int x, Celula *p){
	Celula *nova;
	nova = (Celula *) malloc(sizeof(Celula));
	nova->conteudo = x;
	nova->prox = p->prox;
	p->prox = nova;
	
}

/*Esta fun��o recebe o endere�o p 
de uma celula de uma lista encadeada
e remove da lista a celula p->prox. A
fun��o sup�e que p!= NULL e p->prox != NULL */
 void Remove(Celula *p){
 	Celula *celMorta;
 	celMorta = p->prox;
 	p->prox = celMorta->prox;
 	free(celMorta);
 }
 
 
// Retorna o ponteiro para c�lula inserida
Celula* InsereR(int x, Celula *cel){
	
	Celula *nova;
	nova = (Celula *) malloc(sizeof(Celula));
	nova->conteudo = x;
	nova->prox = cel->prox;
	cel->prox = nova;
	return nova; 
}

 // Imprime o conte�do de uma lista encadeada
 // com cabe�a. O endere�o da primeira c�lula � ini
 void Imprime(Celula *ini){
 	
	 // Ponteiro que vai passar por
	 // todas c�lulas
	 Celula *p;
	 
	 // Come�a o la�o a partir da posi��o ap�s a cabe�a
	 // e vai at� quando o retornar nulo 
	 for(p = ini->prox; p != NULL; p = p->prox)
	 	
	 	// Imprime o conte�do
		 cout << p->conteudo << "\n";
 }

 
