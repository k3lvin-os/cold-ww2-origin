#include <graphics.h>
#include <iostream>
#include "..\..\header\td_functions.h" // Funções
#include "..\..\header\sprite.h"      // Estrutura que trabalha com Sprites
#include "..\..\header\td_defines.h" // Definção de constantes
using namespace std;


// Este é o cenário principal do jogo
struct CampoJogo{
	int tiles[TILE_QTDX][TILE_QTDY];
	
};

struct Tiles{
	Sprite *tipoTile[QTD_TIPO];
	
	// Construtor padrão
	Tiles();
};

Tiles::Tiles(){
	*tipoTile = new Sprite[QTD_TIPO];
	tipoTile[0].GetImage("")
}


int main(){
	initwindow(TELA_W,TELA_H);
	while(!kbhit());
	return 0;
}


