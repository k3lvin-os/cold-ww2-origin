#include <graphics.h>
#include <iostream>
#include "..\..\header\td_functions.h"
#include "..\..\header\sprite.h"
using namespace std;

Sprite *cursor;
void MouseMove(int x, int y){
	cursor->GoTo(x,y);
}

int main(){
	
	// Start a graphic window
	initwindow(600,800);
		
	//Receive the mid screen X coordinate
	int midX = getmaxx() / 2;
	int midY = getmaxy() / 2;
	
	// tiles fixed size
	int const TILE_SIZE = 32; 
	
	// Constant velocity of the game
	int const SPEED = 5;
	
	// Create a sprite of MarioKart
	Sprite *marioKart = new Sprite("Sprites/mario_kart.gif",TILE_SIZE,TILE_SIZE,midX,0);
	
	// Create a sprite of a mouse cursor
	cursor = new Sprite("Sprites/cursor.gif",TILE_SIZE,TILE_SIZE,midX,midY);
	
	//End of sprite store. So, clean the screen
	cleardevice();
	
	// Send a message to user
	outtext("Press Play to Begin");
	
	// Wait user input
	int tecla = 0;
	GetKey(&tecla);
	
	// Mario Kart will start in begin of screen Y axis and go to end Y axis
	for (int y = 0; y < getmaxy(); y+= SPEED){
		
		// Clean screen
		cleardevice();
		
		// Show Mario Kart
		marioKart->Show();
		
		// Show cursor
		cursor->Show();

		// Check mouse move
		registermousehandler(WM_MOUSEMOVE,MouseMove);
		
		// Move Mario Kart
		marioKart->Move(0,SPEED);
		
		// Put's a dealy in the reason of player sight
		delay(30);
	}
	
	
	return 0;
}
