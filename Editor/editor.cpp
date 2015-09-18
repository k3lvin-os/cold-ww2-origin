#include "editor.h"

/*Bibliotecas do projeto TowerDefense*/
#include "..\..\header\td_functions.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\grade.h"



// Interface com o usuário (texto)
void GUI(){
	
	int x, y;
		
	// GUI
	setcolor(WHITE);
	x =getmaxx() / 2 - 60;
	y = getmaxy() - 30;
	moveto( x,y);
	outtext("Use o console para gerenciar a janela gráfica");
}

// Procedimento de carregar um arquivo de coordenadas
void Carrega(CampoJogo *meuCampo, Grade *minhaGrd){
	bool sucesso;
	char nomeArq[8];
	
	// Requere o nome do arquivo com as coord. do campo de jogo e carrega-o
	std::cout << "Digite o nome do arquivo com as coord. do campo de jogo\n";
	std::cin >> nomeArq;
	sucesso = meuCampo->PosLoad(nomeArq);
	
	// Verifica se o processo ocorreu corretamente
	if(!sucesso){
		std::cout << "\nFalha na leitura do arquivo\"" << nomeArq << "\".\n"; 
	} 
	else{
		
		// Se tudo ocorreu corretamente, atualize o campo de jogo
		std::cout << "Arquivo carregado com sucesso!";
		meuCampo->Mostrar();
		minhaGrd->Colocar();
	}
	
}
