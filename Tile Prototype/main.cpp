/**
	Prot�tipo visual de um n�vel de jogo com tiles
*/

#include <iostream>
#include <graphics.h>
#include "bgieasy.h" // biblioteca customiz�vel com fun��es para facilitar o uso da bgi
#include "tests.h" // biblioteca customiz�vel com fun��es de teste
#include "Sprite.h"
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
	
	// Recebe o tamanho necess�rio para criar uma imagem
	int imgSize;
	
	int const TILE_SIZE = 50; // normal tile size
	
	// N�mero de tiles por eixo X e Y
	int const FILL_WIDTH = 26; // (WIDTH_KELVINPC~ / WTILE_SIZE = 26)
	int const FILL_HEIGHT = 20; // (HEIGHT_KELVINPC~ / WTILE_SIZE = 20)
	
	int midX = getmaxx() / 2;
	int midY = getmaxy() / 2;
	
	
	// TILES
	void *woodTile; 
	void *greenTank;
	
	// Pointer that stores a reference from a Sprite struct (tank)
	Sprite *tank = new Sprite("greenShip1.jpg",TILE_SIZE,TILE_SIZE, midX, midY);
	//Sprite *woodTile = new Sprite("wood.jpg",TILE_SIZE,TILE_SIZE);	
	
	
	// Recebe a imagem do ch�o de madeira
	readimagefile("wood.jpg",0,0,TILE_SIZE,TILE_SIZE); 
	imgSize = imagesize(0,0,TILE_SIZE,TILE_SIZE);
	woodTile = malloc(imgSize);
	getimage(0,0,TILE_SIZE,TILE_SIZE,woodTile); // Os dois 0s referem-se ao local onde a imagem ser� colocada 

	//GetImage("wood.jpg",WTILE_SIZE,WTILE_SIZE, woodTile ); (N�o est� funcionando)*/

	// Limpa a tela
	cleardevice();
	
	// Preencha a tela com tiles
	for(int i = 0; i < TILE_SIZE * FILL_WIDTH ;i += TILE_SIZE){
		for(int j = 0; j < TILE_SIZE * FILL_HEIGHT; j += TILE_SIZE){
			putimage(i,j,woodTile,0);
		}
	}
	
	
			
	// Game Loop
	do{
		
		tank->Show();	

		
		// Limpa o buffer e recebe a tecla pressionada pelo jogador
		GetKey(&key);
		
	
		
	// Enquanto o jogador n�o apertar ESC, o jogo continua	
	}while( key != ESC);
	
	// Limpa a mem�ria
	delete tank;
	
	// Fecha o modo gr�fico e o programa
	closegraph();
	return 0;
}

	




	

	

