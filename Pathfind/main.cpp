#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <graphics.h>

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\tdelay.h"
#include "..\..\header\soldado.h"
#include "..\..\header\pagina.h"
#include "..\..\header\jogador.h"
#include "..\..\header\gametime.h"


/*Protótipo de funções*/
void EnviaSold(Jogador *meuJog, Jogador *outroJog, CampoJogo meuCampo);
void OndaSold(char onda, char* dest, Jogador *eixoIA , CampoJogo meuCampo);


using namespace std;

int main(){
	
	// Declaração de variáveis
	Jogador meuJog,  outroJog, eixoIA;
	char onda;
	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	time_t agora = NULL;
	TDelay gameTime;
	int teste = 2;
		
	// Atribui times aos jogadores
	meuJog.Init(LADO2);
	outroJog.Init(LADO1);
	eixoIA.Init(LADO3);

	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H, "Seek Of Peace: Cold WW2");
	
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
	
	// Começa a contar o tempo de jogo
	gameTime.Init();
	
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
		EnviaSold(&meuJog,&outroJog,meuCampo);
		
		// Rotina de envio de soldados do Eixo (IA)
		EnviaSold(&eixoIA,&outroJog,meuCampo);
				
		//Deixa a página visual
		minhaPg.Visual();
		
		// Verifica se hora de enviar uma onda da IA
		onda = gameTime.SoldOnda();	
		OndaSold(onda,outroJog.lado,&eixoIA,meuCampo);

					
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


/*Funções*/

// Rotina de envio de soldados para outro jogador 
void EnviaSold(Jogador *meuJog, Jogador *outroJog, CampoJogo meuCampo){

	Soldado *novoIni;
	Soldado *pSold, *anterior;
	Soldado *soldado0;
	TDelay *tempoEspera;
	
	soldado0 = meuJog->soldado0;
	tempoEspera = &(outroJog->esperaIni);
	
	for(pSold = soldado0->prox; pSold != NULL; pSold = pSold->prox){
	
		if(pSold->vida > 0 && pSold->dest != true){
			
			pSold->Show();
			
			pSold->IA(meuCampo, tempoEspera);
			
		} 
		
		else{
			
			anterior = pSold->Anterior(soldado0);
			
			if(pSold->dest == true)
				pSold->Chegou(anterior);
			else
				pSold->Morre(anterior);		
		}
	}
}

//=========================================================================

// Rotina de envio de onda de soldados do Eixo
void OndaSold(char onda, char* dest, Jogador *eixoIA , CampoJogo meuCampo){
	
	int soldX,  soldY, qtdIni, i;
	Soldado *pSold;
	Soldado *soldado0;
	
	soldado0 = eixoIA->soldado0;

	
	if(onda != SEM_ONDA){
		
		if(dest == LADO2){
			soldX = EUACEGOX;
			soldY = EUACEGOY;
		} 
		else if(dest == LADO1){
			soldX = URSSCEGOX;
			soldY = URSSCEGOY;
		}
		
		switch(onda){
			
			case '0':
				outtextxy(590,10,"COMEÇAR");
				delay(2000);
				break;
			case '1':
				
				
				outtextxy(480,30,"Faltam 4 m para o ataque final do EIXO");
				delay(2000);
				
				qtdIni = 10;
				for(i = 0; i < qtdIni; i++){
					pSold = soldado0->Insere(soldado0,"Nazi");
					pSold->GoTo(soldX,soldY);
					pSold->direcao = BAIXO;
					pSold->posCego = true;
				}
				
				break;
		}
		
	}

}


