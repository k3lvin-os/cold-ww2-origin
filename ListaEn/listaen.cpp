 #include <iostream>
 #include <stdlib.h>
 #include "listaen.h"
 using namespace std;
 

 
 
 /*O endereço de uma lista encadeada é o endereço
  da primeira célula*/
  
  /* Esta função recebe um inteiro x e uma lista 
  encadeada ini de inteiros, com celula-cabeça. A
  funçãoi devolve o endereço de uma celula que contém
  x ou devolve NULL se tão ceulula não existe.*/
Celula* Busca(int x, Celula *ini){
	
	Celula *p;
	p = ini->prox;
	while(p != NULL && p->conteudo != x)
		p = p->prox;
	return p;
}

/*Esta função insere uma nova celula em uma lista
encadeada. A nova celula tem conteudo x e é inserida entre a 
celula apontada por p e a seguinte. Supõe-se que p!= NULL*/
void Insere(int x, Celula *p){
	Celula *nova;
	nova = (Celula *) malloc(sizeof(Celula));
	nova->conteudo = x;
	nova->prox = p->prox;
	p->prox = nova;
	
}

/*Esta função recebe o endereço p 
de uma celula de uma lista encadeada
e remove da lista a celula p->prox. A
função supõe que p!= NULL e p->prox != NULL */
 void Remove(Celula *p){
 	Celula *celMorta;
 	celMorta = p->prox;
 	p->prox = celMorta->prox;
 	free(celMorta);
 }
 
 
// Retorna o ponteiro para célula inserida
Celula* InsereR(int x, Celula *cel){
	
	Celula *nova;
	nova = (Celula *) malloc(sizeof(Celula));
	nova->conteudo = x;
	nova->prox = cel->prox;
	cel->prox = nova;
	return nova; 
}

 // Imprime o conteúdo de uma lista encadeada
 // com cabeça. O endereço da primeira célula é ini
 void Imprime(Celula *ini){
 	
	 // Ponteiro que vai passar por
	 // todas células
	 Celula *p;
	 
	 // Começa o laço a partir da posição após a cabeça
	 // e vai até quando o retornar nulo 
	 for(p = ini->prox; p != NULL; p = p->prox)
	 	
	 	// Imprime o conteúdo
		 cout << p->conteudo << "\n";
 }

 
