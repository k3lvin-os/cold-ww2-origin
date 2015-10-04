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
	
	// Declaração de variáveis
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	Soldado meuSold; 
	int x, y; // Opção do jogador para movimentação
	bool visivel = false; // Indica se o soldado chegou ao ponto visivel (hora da pathfind)
	
	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H);
	
	// Inicializa a estrutura página
	minhaPg.Init();
	
	// Troca a página atual
	minhaPg.Troca();

	// Trabalha com a página nos "bastidores"
	minhaPg.Ativa();
	
	// Inicialização do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa01.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();
	
	// Inicializa o soldado
	meuSold.Init("Chara");
	
	// Mostra soldado
	meuSold.Show();	
	
	// Deixa a página visual
	minhaPg.Visual();
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova página para modificações nos gráficos
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo
		meuCampo.Mostrar();
		
		// Se o soldado não estiver no "ponto cego"
		if(meuSold.posCego == false){
			
			// Se o soldado não souber para onde ir
			if(meuSold.movNUntil == false){
				
				// Calcula as coordendas do ponto cego
				x = meuSold.X + (TILE_W * 21);
				y = meuSold.Y - (TILE_H * 3);
				
				// Define o ponto cego como destino
				meuSold.MovUntil(x,y);
			}
			
			// Movimenta-se até o ponto cego
			meuSold.posCego = meuSold.MovUntil();
		} 
		// Se o soldado estiver no "ponto cego"
		else{
			
			// Se o soldado não estiver no ponto visível
			if(visivel == false){
					
					// Se o soldado não souber para onde ir
					if(meuSold.movNUntil == false){
						
						// Define a coordenada do ponto visível
						meuSold.MovUntil(meuSold.x, 64);
					} 
					
					// Movimente o soldado até o destino
					visivel = meuSold.MovUntil();
			} 
			
			// Se o soldado chegou a área visível
			else{
				
				// Se o soldado não chegou ao destino
				if(meuSold.dest  == false){
					
					// Se o soldado não souber para onde ir
					if(meuSold.movNUntil == false){
						
						// Usa a Pathfind
						meuSold.dest = 
						meuSold.MoveDest(meuCampo,DEST1_X,DEST1_Y);
					} 
					
					// Movimenta-se até o ponto definido
					meuSold.MovUntil();
				}
				
			}		
		}
		// Mostra soldado
		meuSold.Show();
		
		//Deixa a página visual
		minhaPg.Visual();
				
		// Delay de FPS
		delay(FPS);
		
	}
	closegraph();
	return 0;	
}
