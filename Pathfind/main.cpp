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

using namespace std;


int main(){
	
	// Inicialize a janela gráfica
	initwindow(TELA_W,TELA_H);
	CampoJogo meuCampo;
	meuCampo.Init("mapa01.txt");
	meuCampo.Mostrar();
	while(!kbhit());
	closegraph();
	return 0;	
}
