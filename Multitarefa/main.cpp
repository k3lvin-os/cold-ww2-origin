#include <graphics.h>
#include <iostream>
#include "..\..\header\td_functions.h"
#include "..\..\header\sprite.h"
using namespace std;

int main(){
	
	// Start a graphic window
	initwindow(600,800);
		
	//Receive the mid screen X coordinate
	int midX = getmaxx() / 2;
	
	// tiles fixed size
	int const TILE_SIZE = 32; 
	
	// Constant velocity of the game
	int const SPEED = 1;
	
	// Create a sprite of MarioKart
	Sprite *marioKart = new Sprite("\mario_kart.gif",TILE_SIZE,TILE_SIZE,midX,0);
	
	//End of sprite store. So, clean the screen
	cleardevice();
	
	// Send a message to user
	outtext("Press Play to Begin");
	
	// Wait user input
	int tecla = 0;
	GetKey(&tecla);
	
	// O Mario Kart sairá de uma posição até o final da tela
	for (int y = 0; y < getmaxy(); y+= SPEED){
		
		// Limpa a tela
		cleardevice();
		
		// Mostra o MarioKart
		marioKart->Show();
		
		// Movimenta o Mario Kart
		marioKart->Move(0,SPEED);
		
		// Coloque um delay a fim de permitir a visualização
		delay(1);
	}
	
	// Limpa a memória
	delete marioKart;
	return 0;
}
