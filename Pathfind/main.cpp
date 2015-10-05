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
		
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo
		meuCampo.Mostrar();
		
		// Utiliza a IA do soldado
		meuSold.IA(meuCampo);
		
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
