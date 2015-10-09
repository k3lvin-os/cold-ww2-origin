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
#include "..\..\header\gui.h"
#include "..\..\header\mousetd.h"
#include "..\..\header\t_envio.h"

using namespace std;

// Vari�veis Globais
Jogador meuJog;
Jogador outroJog;
T_Envio envioSold;
MouseTd meuMouse;
GUI minhaGUI;

int main(){
	

	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	time_t marcador = NULL;
	time_t agora = NULL;
	double diferenca;
	time_t countdown;
		
	// Atribui times aos jogadores
	meuJog.Init("Aliados Socialistas");
	outroJog.Init("Aliados Capitalistas");

	
	Soldado *soldado0 = NULL;	// Cabe�a da lista encadeada de tropas
	Soldado *pSold = NULL;	// Ponteiro para trabalhar com lista de tropas

	
	// Inicialize a janela gr�fica
	initwindow(TELA_W,TELA_H);
	
	
	minhaPg.Init();	// Inicializa a estrutura p�gina
	minhaPg.Troca();	// Troca a p�gina atual


	// Trabalha com a p�gina nos "bastidores"
	minhaPg.Ativa();
	
	// Inicializa��o do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa01.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();

	// Inicializa a cabe�a da lista encadeada de soldados
	soldado0 = (Soldado *) malloc(sizeof(Soldado));
	soldado0->prox = NULL;
		
	// Deixa a p�gina visual
	minhaPg.Visual();
	
	// O cron�metro do jogo � iniciado
	time(&countdown);
	
	// O marcador de envio de soldado � iniciado
	envioSold.Init();	
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova p�gina para modifica��es
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		meuCampo.Mostrar();		// Mostra campo de jogo
		minhaGUI.Mostra("default"); // Mostra gui padr�o
		

		
		// Verifica o click do mouse
		if(GetKeyState(VK_LBUTTON) & 0x80){
			mouseX = mousex();
			mouseY = mousey();
			
			// Verifica o tipo de entrada de dados com o mouse
			// e lida com ela
			meuMouse.Check(mouseX,mouseY);			
		}
		
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
		
		// Envia os soldados
		soldado0->Enviar(soldado0, meuCampo);
		
		//Deixa a p�gina visual
		minhaPg.Visual();
						
		// Delay de FPS
		delay(FPS);
		
	}
	// Libera a mem�ria
	soldado0->LimpaNo(soldado0);
	meuCampo.LimpaMem();
	meuJog.inimigo0->LimpaNo(meuJog.inimigo0);
	outroJog.inimigo0->LimpaNo(outroJog.inimigo0);
	
	
	closegraph();
	return 0;	
}
