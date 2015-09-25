/*Utilize o arquivo main para fazer testes com as fun��es das
bibliotecas. */

#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <graphics.h>

/*Bibliotecas do projeto TowerDefense
("../" � utilizado aqui porque os arquivos est�o na pasta 
anterior a pasta dos testes header)
*/
#include "..\..\header\td_functions.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\grade.h"
#include "..\..\header\soldado.h"

#define MAXCHARA 1

using namespace std;


int main(){
	
	// Indica o loop do jogo
	bool gameLoop = true;
	
	// Pagina��o
	int pg = 1;
	
	// Cria um array de soldados
	Soldado chara[MAXCHARA];
	
	// Inicialize a janela gr�fica
	initwindow(TELA_W,TELA_H);

	// Soldado que o jogador vai controlar	
	chara[0].Init("Chara");

	
	// Loop do jogo
	while(gameLoop == true){
		
		// Troca a p�gina
		if(pg == 1){
			pg = 2;
		} else{
			pg = 1;
		}
		
		// Deixa a p�gina em modo desenho
		setactivepage(pg);
		
		// Limpa a tela
		cleardevice();
		
		// Se o usu�rio apertar uma das teclas de movimento...
		if( (GetKeyState(VK_LEFT) & 0x80) ||
		  (GetKeyState(VK_RIGHT) & 0x80)  ||
		  (GetKeyState(VK_UP) & 0x80)     ||
		   (GetKeyState(VK_DOWN) & 0x80)
			){
				// Indica o movimento
				chara[0].idle = false;
			}
		
		
		// Verifica a troca de sprites de dire��o
		if( GetKeyState(VK_LEFT) & 0x80){
			
			// Troca a dire��o (se for necess�rio)
			if (chara[0].direcao != ESQUERDA)
				chara[0].TrocaDir(ESQUERDA);
		}
			
		else if(GetKeyState(VK_RIGHT) & 0x80){
			
			// Troca a dire��o (se for necess�rio)
			if (chara[0].direcao != DIREITA)
				chara[0].TrocaDir(DIREITA);
		}
			
		else if(GetKeyState(VK_UP) & 0x80){
			
			// Troca a dire��o (se for necess�rio)
			if (chara[0].direcao != COSTA)
				chara[0].TrocaDir(COSTA);
		}
			
		else if(GetKeyState(VK_DOWN) & 0x80){
			
			// Troca a dire��o (se for necess�rio)
			if (chara[0].direcao != FRENTE)
				chara[0].TrocaDir(FRENTE);
		}
		
		else{
			
			// Indica que o soldado est� parado
			chara[0].idle = true;
		}
	
			

		
		// Verifica se o personagem n�o est� parado
		if(chara[0].idle != true){
			
			
			// O soldado vai fazer um movimento e, por isso, 
			//troca a imagem
			chara[0].TrocaImg();// TESTE
					
			// Movimenta o personagem
			chara[0].Move();
		}
		
		// Mostra o sprite
		chara[0].Show();
		
		// Deixa a p�gina em modo de visualiza��o
		setvisualpage(pg);	
			
		// Delay
		delay(FPS);		
			
	}

		closegraph();
		return 0;	
}

	



