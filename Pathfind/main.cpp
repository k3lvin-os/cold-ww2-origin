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
	bool posCego = false; // Indica se o soldado chegou ao ponto n�o v�s�vel
	bool visivel = false; // Indica se o soldado chegou ao ponto visivel (hora da pathfind)
	bool dest = false; // Indica se o soldado chegou ao destino
	
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
	
	// Teste
	meuCampo.Console();
	
	// Inicializa o soldado
	meuSold.Init("Chara");
	
	// Mostra soldado
	meuSold.Show();	
	
	// Deixa a p�gina visual
	minhaPg.Visual();
	

	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova p�gina para modifca��es nos gr�ficos
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo
		meuCampo.Mostrar();
		
		// Se o soldado n�o estiver no "ponto cego"
		if(posCego == false){
			
			// Movimenta-se at� o ponto cego
			posCego = meuSold.MovUntil(meuSold.X + (TILE_W * 21) , meuSold.Y - (TILE_H * 3));
		} 
		// Se o soldado estiver no "ponto cego"
		else{
			
			// Se o soldado n�o estiver no ponto vis�vel
			if(visivel == false){
					
					// Vai at� a �rea vis�vel
					visivel = meuSold.MovUntil(meuSold.x, 64);
			} 
			// Se  o soldado chegou a �rea vis�vel
			else{
				
				// Se o soldado n�o chegou ao destino
				if(dest == false){
					
					// Vai ao destino pathfind
					dest = meuSold.MoveDest(meuCampo,35,2);
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
