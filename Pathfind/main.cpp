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
#include "..\..\header\tropa.h"

using namespace std;


int main(){
	
	const int GUISoldX = 1000;
	const int GUISoldY = TELA_H - (TILE_H * 3);
	
	// Declaração de variáveis
	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	Soldado meuSold;
	
	// Cabeça da lista encadeada de tropas
	Tropa *tropa0;
	
	// Ponteiro para trabalhar com a lista de tropas
	Tropa *pTropa;
	
	 
	
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
	
	// Inicializa o "soldado" (GUI) 
	meuSold.Init("Chara");
	meuSold.GoTo(GUISoldX,GUISoldY);

	// Inicializa a cabeça da lista encadeada de soldados
	tropa0 = (Tropa *) malloc(sizeof(Tropa));
	tropa0->prox = NULL;
		
	// Deixa a página visual
	minhaPg.Visual();
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo
		meuCampo.Mostrar();
		
		// Verifica o click do mouse
		if(GetKeyState(VK_LBUTTON) & 0x80){
			mouseX = mousex();
			mouseY = mousey();
			if(mouseX >= GUISoldX && mouseX <= GUISoldX + TILE_W
				&& mouseY >= GUISoldY && mouseY <= GUISoldY + TILE_H ){
					
					// Hora de enviar uma tropa
					pTropa = tropa0->Insere("Chara");
					pTropa->Enviar();
				}				
		}
		
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
		
		// Mostra soldado (Interface gráfica)
		meuSold.Show();
		
		//Deixa a página visual
		minhaPg.Visual();
						
		// Delay de FPS
		delay(FPS);
		
	}
	closegraph();
	return 0;	
}
