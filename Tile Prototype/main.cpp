/**
	Protótipo visual de um nível de jogo com tiles
*/

#include <iostream>
#include <graphics.h>
#include "bgieasy.h" // biblioteca customizável com funções para facilitar o uso da bgi
#include "tests.h" // biblioteca customizável com funções de teste
using namespace std;


#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC    	27


int main(){
	
	int const WIDTH_KELVINPC = 1280;
	int const HEIGHT_KELVINPC = 960;
	
	// Inicia uma janela gráfica
	initwindow(WIDTH_KELVINPC, HEIGHT_KELVINPC, "Tile Prototype");
	
	// Declaração de variáveis
	int key = 0;
	
	int const WTILE_SIZE = 50; // wood tile
	
	// Número de tiles por eixo X e Y
	int const FILL_WIDTH = 26; // (WIDTH_KELVINPC~ / WTILE_SIZE = 26)
	int const FILL_HEIGHT = 20; // (HEIGHT_KELVINPC~ / WTILE_SIZE = 20)
	
	// Recebe a imagem do chão de madeira
	void *woodTile;
	
	
	
	// Recebe a imagem do chão de madeira
	readimagefile("wood.jpg",0,0,WTILE_SIZE,WTILE_SIZE); 
	int size = imagesize(0,0,WTILE_SIZE,WTILE_SIZE);
	woodTile = malloc(size);
	getimage(0,0,WTILE_SIZE,WTILE_SIZE,woodTile); // Os dois 0s referem-se ao local onde a imagem será colocada 

	//GetImage("wood.jpg",WTILE_SIZE,WTILE_SIZE, woodTile ); (Não está funcionando)*/

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
	
		
	// Enquanto o jogador não apertar ESC, o jogo continua	
	}while( key != ESC);
	
	// Fecha o modo gráfico e o programa
	closegraph();
	return 0;
}
	

	

