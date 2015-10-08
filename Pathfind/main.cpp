#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <graphics.h>

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\grade.h"
#include "..\..\header\soldado.h"
#include "..\..\header\pagina.h"
#include "..\..\header\inimigo.h"
#include "..\..\header\jogador.h"

using namespace std;


int main(){
	

	
	// GUI 
	const int GUISoldX = 1000;
	const int GUISoldY = TELA_H - (TILE_H * 3);
	
	// Declaração de variáveis
	Jogador meuJog;
	Jogador outroJog;
	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	Soldado meuSold;
	time_t marcador = NULL;
	time_t agora = NULL;
	double diferenca;
	
	// Atribui times aos jogadores
	meuJog.Init("Aliados Socialistas");
	outroJog.Init("Aliados Capitalistas");

	
	// Cabeça da lista encadeada de tropas
	Soldado *soldado0 = NULL;
	
	// Ponteiro para trabalhar com a lista de tropas
	Soldado *pSold = NULL;
	
	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H);
	
	// Inicializa a estrutura página
	minhaPg.Init();
	
	// Inicializa o marcador
	time(&marcador);
	
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
	soldado0 = (Soldado *) malloc(sizeof(Soldado));
	soldado0->prox = NULL;
		
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
					
					time(&agora); // Recebe hora atual
					
					// Se se o tempo de delay passou
					if(difftime(agora,marcador) >= S_DELAY){
						
						cout << "Você  atingiu o delay necessário\n";
						
						//Insere uma nova tropa na lista encadeada
						pSold = soldado0->Insere(soldado0,"Chara");
						
						// Atribui a hora atual ao marcador
						time(&marcador);
					} else{
						diferenca = difftime(agora,marcador);
						cout << "Diferenca = " << diferenca << endl;
					}
					

				}				
		}
		
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
		
		// Envia os soldados
		soldado0->Enviar(soldado0, meuCampo);
		
		// Mostra soldado (Interface gráfica)
		meuSold.Show();
		
		//Deixa a página visual
		minhaPg.Visual();
						
		// Delay de FPS
		delay(FPS);
		
	}
	// Libera a memória
	soldado0->LimpaNo(soldado0);
	meuCampo.LimpaMem();
	
	
	closegraph();
	return 0;	
}
