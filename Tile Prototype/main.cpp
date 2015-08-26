/**
	Prot�tipo visual de um n�vel de jogo com tiles
*/

#include <iostream>
#include <graphics.h>
#include "bgieasy.h" // biblioteca customiz�vel com fun��es para facilitar o uso da bgi
#include "tests.h" // biblioteca customiz�vel com fun��es de teste
using namespace std;


#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC    	27


int main(){
	
	int const WIDTH_KELVINPC = 1280;
	int const HEIGHT_KELVINPC = 960;
	
	// Inicia uma janela gr�fica
	initwindow(WIDTH_KELVINPC, HEIGHT_KELVINPC, "Tile Prototype");
	
	// Declara��o de vari�veis
	int key = 0;
	
	int const WTILE_SIZE = 50; // wood tile
	
	// N�mero de tiles por eixo X e Y
	int const FILL_WIDTH = 26; // (WIDTH_KELVINPC~ / WTILE_SIZE = 26)
	int const FILL_HEIGHT = 20; // (HEIGHT_KELVINPC~ / WTILE_SIZE = 20)
	
	// Recebe a imagem do ch�o de madeira
	void *woodTile;
	
	
	
	// Recebe a imagem do ch�o de madeira
	readimagefile("wood.jpg",0,0,WTILE_SIZE,WTILE_SIZE); 
	int size = imagesize(0,0,WTILE_SIZE,WTILE_SIZE);
	woodTile = malloc(size);
	getimage(0,0,WTILE_SIZE,WTILE_SIZE,woodTile); // Os dois 0s referem-se ao local onde a imagem ser� colocada 

	//GetImage("wood.jpg",WTILE_SIZE,WTILE_SIZE, woodTile ); (N�o est� funcionando)*/

	// Limpa a tela
	cleardevice();
	
	// Preencha a tela com tiles
	for(int i = 0; i < WTILE_SIZE * FILL_WIDTH ;i += WTILE_SIZE){
		for(int j = 0; j < WTILE_SIZE * FILL_HEIGHT; j += WTILE_SIZE){
			putimage(i,j,woodTile,0);
		}
	}
			
	// Game Loop
	do{
		
		// Limpa o buffer e recebe a tecla pressionada pelo jogador
		GetKey(&key);	
	
		
	// Enquanto o jogador n�o apertar ESC, o jogo continua	
	}while( key != ESC);
	
	// Fecha o modo gr�fico e o programa
	closegraph();
	return 0;
}
	

	

