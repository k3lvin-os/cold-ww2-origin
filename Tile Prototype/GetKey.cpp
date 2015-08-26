#include <graphics.h>
#include <iostream>

// Limpa o buffer e recebe a tecla pressionada pelo jogador
void GetKey(int *key){
		
		// Limpa o buffer para usar getch
		fflush(stdin);
		
		// Receba o input do jogador
		*key = getch();
}
