#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <graphics.h>

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\soldado.h"
#include "..\..\header\pagina.h"
#include "..\..\header\tdelay.h"
#include "..\..\header\jogador.h"
#include "..\..\header\gametime.h"

using namespace std;

int main(){
	
	// Declaração de variáveis
	Jogador meuJog;
	Jogador outroJog;
	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	time_t agora = NULL;
	GameTime countdown;
	int teste = 2;
		
	// Atribui times aos jogadores
	meuJog.Init(LADO1);
	outroJog.Init(LADO2);

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
	
	// Deixa a página visual
	minhaPg.Visual();
	
	// O cronômetro do jogo é iniciado
	countdown.Init();
	
	//Loop do jogo
	while(gameLoop == true){
		
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		meuCampo.Mostrar();		// Mostra campo de jogo
		meuJog.MostraGUI(); // Mostra gui do jogador
		
		// Verifica o input do usuário com a GUI
		meuJog.InputGUI();
		
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
		
		// Rotina de envio de soldados 
		meuJog.soldado0->Envia(meuJog.soldado0, meuCampo);
		
		
		//Deixa a página visual
		minhaPg.Visual();
		
		// Verifica o tempo de jogo
		countdown.Verifica();
						
		// Delay de FPS
		delay(FPS);
		
	}
	// Libera a memória
	meuCampo.LimpaMem();
	meuJog.soldado0->LimpaNo(meuJog.soldado0);
	outroJog.soldado0->LimpaNo(outroJog.soldado0);
	
	
	closegraph();
	return 0;	
}
