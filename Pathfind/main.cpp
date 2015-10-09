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

// Variáveis Globais
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

	
	Soldado *soldado0 = NULL;	// Cabeça da lista encadeada de tropas
	Soldado *pSold = NULL;	// Ponteiro para trabalhar com lista de tropas

	
	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H);
	
	
	minhaPg.Init();	// Inicializa a estrutura página
	minhaPg.Troca();	// Troca a página atual


	// Trabalha com a página nos "bastidores"
	minhaPg.Ativa();
	
	// Inicialização do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa01.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();

	// Inicializa a cabeça da lista encadeada de soldados
	soldado0 = (Soldado *) malloc(sizeof(Soldado));
	soldado0->prox = NULL;
		
	// Deixa a página visual
	minhaPg.Visual();
	
	// O cronômetro do jogo é iniciado
	time(&countdown);
	
	// O marcador de envio de soldado é iniciado
	envioSold.Init();	
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		meuCampo.Mostrar();		// Mostra campo de jogo
		minhaGUI.Mostra("default"); // Mostra gui padrão
		

		
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
		
		//Deixa a página visual
		minhaPg.Visual();
						
		// Delay de FPS
		delay(FPS);
		
	}
	// Libera a memória
	soldado0->LimpaNo(soldado0);
	meuCampo.LimpaMem();
	meuJog.inimigo0->LimpaNo(meuJog.inimigo0);
	outroJog.inimigo0->LimpaNo(outroJog.inimigo0);
	
	
	closegraph();
	return 0;	
}
