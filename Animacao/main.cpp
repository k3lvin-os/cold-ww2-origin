/*Utilize o arquivo main para fazer testes com as funções das
bibliotecas. */

#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <graphics.h>

/*Bibliotecas do projeto TowerDefense
("../" é utilizado aqui porque os arquivos estão na pasta 
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
	
	// Paginação
	int pg = 1;
	
	// Cria um array de soldados
	Soldado chara[MAXCHARA];
	
	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H);

	// Soldado que o jogador vai controlar	
	chara[0].Init("Chara");

	
	// Loop do jogo
	while(gameLoop == true){
		
		// Troca a página
		if(pg == 1){
			pg = 2;
		} else{
			pg = 1;
		}
		
		// Deixa a página em modo desenho
		setactivepage(pg);
		
		// Limpa a tela
		cleardevice();
		
		// Se o usuário apertar uma das teclas de movimento...
		if( (GetKeyState(VK_LEFT) & 0x80) ||
		  (GetKeyState(VK_RIGHT) & 0x80)  ||
		  (GetKeyState(VK_UP) & 0x80)     ||
		   (GetKeyState(VK_DOWN) & 0x80)
			){
				// Indica o movimento
				chara[0].idle = false;
			}
		
		
		// Verifica a troca de sprites de direção
		if( GetKeyState(VK_LEFT) & 0x80){
			
			// Troca a direção (se for necessário)
			if (chara[0].direcao != ESQUERDA)
				chara[0].TrocaDir(ESQUERDA);
		}
			
		else if(GetKeyState(VK_RIGHT) & 0x80){
			
			// Troca a direção (se for necessário)
			if (chara[0].direcao != DIREITA)
				chara[0].TrocaDir(DIREITA);
		}
			
		else if(GetKeyState(VK_UP) & 0x80){
			
			// Troca a direção (se for necessário)
			if (chara[0].direcao != COSTA)
				chara[0].TrocaDir(COSTA);
		}
			
		else if(GetKeyState(VK_DOWN) & 0x80){
			
			// Troca a direção (se for necessário)
			if (chara[0].direcao != FRENTE)
				chara[0].TrocaDir(FRENTE);
		}
		
		else{
			
			// Indica que o soldado está parado
			chara[0].idle = true;
		}
	
			

		
		// Verifica se o personagem não está parado
		if(chara[0].idle != true){
			
			
			// O soldado vai fazer um movimento e, por isso, 
			//troca a imagem
			chara[0].TrocaImg();// TESTE
					
			// Movimenta o personagem
			chara[0].Move();
		}
		
		// Mostra o sprite
		chara[0].Show();
		
		// Deixa a página em modo de visualização
		setvisualpage(pg);	
			
		// Delay
		delay(FPS);		
			
	}

		closegraph();
		return 0;	
}

	



