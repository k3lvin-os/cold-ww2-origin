//=================================================
/*Inclua os arquivos da seguinte forma:*/

#include <iostream>
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <graphics.h>

/*Bibliotecas do projeto TowerDefense*/
#include "..\..\header\td_functions.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
#include "..\..\header\grade.h"

// Última atualização: 18 de set. 2015

//===============================================

int main(){
	
	// Declaração de variáveis
	Grade *minhaGrd;
	//CampoJogo *meuCampo;
 	CampoJogo *meuCampo;
	int x, y;
		
	// Inicialize a janela do editor (maior em altura do que a janela do jogo)
	initwindow(EDIT_W,EDIT_H);
	
	// Inicialização de estruturas
	meuCampo = new CampoJogo();
	minhaGrd = new Grade();
	
	
	
	
	// GUI
	setcolor(WHITE);
	x =getmaxx() / 2 - 60;
	y = getmaxy() - 30;
	moveto( x,y);
	outtext("Use o console para gerenciar a janela gráfica");
	

	
	// Mostra o campo de jogo
	meuCampo->Mostrar();
	
	// Coloca a grade
	minhaGrd->Colocar();
	
	// Verifique o pressionamento de teclas
	while(!kbhit());
	
	closegraph();
	
	return 0;
}
