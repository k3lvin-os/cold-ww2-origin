#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <graphics.h>

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\td_functions.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\grade.h"
#include "..\..\header\soldado.h"
#include "..\..\header\pagina.h"

using namespace std;


int main(){
	
	// Declara��o de vari�veis
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	Soldado meuSold; 
	int x, y; // Op��o do jogador para movimenta��o
	bool visivel = false; // Indica se o soldado chegou ao ponto visivel (hora da pathfind)
	
	// Inicialize a janela gr�fica
	initwindow(TELA_W,TELA_H);
	
	// Inicializa a estrutura p�gina
	minhaPg.Init();
	
	// Troca a p�gina atual
	minhaPg.Troca();

	// Trabalha com a p�gina nos "bastidores"
	minhaPg.Ativa();
	
	// Inicializa��o do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa01.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();
	
	// Inicializa o soldado
	meuSold.Init("Chara");
	
	// Mostra soldado
	meuSold.Show();	
	
	// Deixa a p�gina visual
	minhaPg.Visual();
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova p�gina para modifica��es nos gr�ficos
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo
		meuCampo.Mostrar();
		
		// Se o soldado n�o estiver no "ponto cego"
		if(meuSold.posCego == false){
			
			// Se o soldado n�o souber para onde ir
			if(meuSold.movNUntil == false){
				
				// Calcula as coordendas do ponto cego
				x = meuSold.X + (TILE_W * 21);
				y = meuSold.Y - (TILE_H * 3);
				
				// Define o ponto cego como destino
				meuSold.MovUntil(x,y);
			}
			
			// Movimenta-se at� o ponto cego
			meuSold.posCego = meuSold.MovUntil();
		} 
		// Se o soldado estiver no "ponto cego"
		else{
			
			// Se o soldado n�o estiver no ponto vis�vel
			if(visivel == false){
					
					// Se o soldado n�o souber para onde ir
					if(meuSold.movNUntil == false){
						
						// Define a coordenada do ponto vis�vel
						meuSold.MovUntil(meuSold.x, 64);
					} 
					
					// Movimente o soldado at� o destino
					visivel = meuSold.MovUntil();
			} 
			
			// Se o soldado chegou a �rea vis�vel
			else{
				
				// Se o soldado n�o chegou ao destino
				if(meuSold.dest  == false){
					
					// Se o soldado n�o souber para onde ir
					if(meuSold.movNUntil == false){
						
						// Usa a Pathfind
						meuSold.dest = 
						meuSold.MoveDest(meuCampo,DEST1_X,DEST1_Y);
					} 
					
					// Movimenta-se at� o ponto definido
					meuSold.MovUntil();
				}
				
			}		
		}
		// Mostra soldado
		meuSold.Show();
		
		//Deixa a p�gina visual
		minhaPg.Visual();
				
		// Delay de FPS
		delay(FPS);
		
	}
	closegraph();
	return 0;	
}
