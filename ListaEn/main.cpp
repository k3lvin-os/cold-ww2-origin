#include <iostream>
#include <stdlib.h>
#include "listaen.h"
using namespace std;

int main(){
	
	int qtdElem, temp;
	
	// Contadores
	int i;
	Celula *cel;
	
	// Cabeça da horda
	Celula *HordaIni;
	HordaIni =(Celula *) malloc(sizeof(Celula));
	HordaIni->prox = NULL;
	
	// Recebe a qtd. de elementos
	do{
		cout << "Digite a qtd. de elementos: ";
		cin >> qtdElem;
		
		if(qtdElem<=0)
			cout << "Digite apenas valores postivos";
		
	}while(qtdElem <= 0);
	
	// Recebe os valores dos elementos e atribui à lista
	for(i = 0, cel = HordaIni; i < qtdElem; i++){
		cout << "Digite um valor para a posição " << i << "da lista encadeada: \n";
		cin >> temp;
		cel = InsereR(temp,cel);
	}
	Remove(HordaIni);
	
	// Imprime todos valores
	Imprime(HordaIni);	
	return 0;
}
