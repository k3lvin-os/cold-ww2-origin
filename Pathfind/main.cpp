

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
#include "..\..\header\t_envio.h"
#include "..\..\header\jogador.h"



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
	time_t countdown;
		
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
	time(&countdown);
	
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
		
		// Envia os soldados
		meuJog.soldado0->Enviar(meuJog.soldado0, meuCampo);
		
		//Deixa a página visual
		minhaPg.Visual();
						
		// Delay de FPS
		delay(FPS);
		
	}
	// Libera a memória
	meuJog.soldado0->LimpaNo(meuJog.soldado0);
	meuCampo.LimpaMem();
	meuJog.inimigo0->LimpaNo(meuJog.inimigo0);
	outroJog.inimigo0->LimpaNo(outroJog.inimigo0);
	outroJog.soldado0->LimpaNo(outroJog.soldado0);
	
	
	closegraph();
	return 0;	
}
