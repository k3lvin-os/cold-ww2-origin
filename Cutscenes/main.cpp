#include <iostream>
#include <stdlib.h> // Para gerar números aleatórios
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <math.h> // Para usar a função potenciação e raiz quadrada
#include <winsock2.h> // Para trabalhar com comunicação em rede
#include <stdio.h>	  // Para trabalhar com funlções da linguagem C
#include <windows.h> // Para trabalhar com funções de som do Windows
#include <graphics.h>

// Para usar a biblioteca Winsock (comunicação em rede)
#pragma comment (lib, "Ws2_32.lib")

void* GetImage(char path[], int width, int height);
void GetImage(void** pImg, char path[], int width, int height);

#include "linguagem.h"
Linguagem linguagem;

void RecebePacoteJogo();
void EnviaPacoteJogo();

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\radiobutton.h"
#include "..\..\header\enumeracoes.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\cenario.h"
#include "..\..\header\tdelay.h"
#include "..\..\header\soldado.h"
#include "..\..\header\pagina.h"
#include "..\..\header\lider.h"
#include "..\..\header\torre.h"
#include "..\..\header\jogador.h"
#include "..\..\header\ondaeixo.h"
#include "..\..\header\grade.h"
#include "..\..\header\botao.h"
#include "..\..\header\barra_vida.h"
#include "..\..\header\rede.h"
#include "cutscenes.h"
using namespace std;


int main(){
	
	char *lado;
	Cutscenes cutscenes;
	char opcao, nLado=0;
	Pagina minhaPg;
	Jogador meuJog;
	TipoGameplay tipoGameplay;
	
	tipoGameplay = SINGLEPLAYER;
	
	
	initwindow(TELA_W,TELA_H,"Seek Of Peace: Cold WW2");
	
	minhaPg.Init();
	minhaPg.Troca();
	minhaPg.Ativa();
	cutscenes.Carrega();
	cleardevice();
	minhaPg.Visual();
	
	// ================================== SELEÇÃO DE IDIOMA =====================
	int lingua;
	do{
		cout << "Escolha o idioma:\n 1 - Inglês\n 2 - Português\nidioma: ";
		cin >> lingua;
		
		if(lingua != 1 && lingua != 2){
			cout << "\nDigite um idioma válido\n";
		}
		
	} while(lingua != 1 && lingua != 2);
	
	if(lingua == 1)
		linguagem.Init(INGLES);
	else
		linguagem.Init(PORTUGUES);
	// ================================== SELEÇÃO DE IDIOMA =====================
	
	
	do{
		cout << endl << endl <<  "FINAIS DO JOGO" << endl << "Digite uma das opções a seguir:" << endl
		<< "1 - Final dos Nazistas" << endl << "2 - Final dos EUA" << endl << "3 - Final da URSS" <<
		endl << "4 - Final da Guerra Fria" << endl <<  "5 - Sair" << endl << "Opcao: ";
		
		outtextxy(TELA_W /2 - 64 ,TELA_H /2,"Use o console para selecionar uma cutscene");
		cin >> opcao;
	
		if(opcao == '1'){
			cutscenes.MostraFinal(FINAL_NAZI);
		}
		
		else if(opcao == '2'){
			cutscenes.MostraFinal(FINAL_EUA);
		}
		
		else if(opcao == '3'){
			cutscenes.MostraFinal(FINAL_URSS);
		}
		
		
		else if(opcao == '4'){
			cutscenes.MostraFinal(FINAL_GUERRAFRIA);	
		}
		
		else if(opcao != '5'){
			cout << "\nOpção inválida\n";
		}
		
		
	}while(opcao != '5');
	
	closegraph();
	return 0;
	
	return 0;
}

//*Busca uma imagem com as informações passadas por parâmetro*/
void GetImage(void** pImg, char path[], int width, int height){
	
	// Lê e coloca na tela uma imagem
	readimagefile(path,0,0,width,height); 
	
	/// Calcula o tamanho da imagem com base na posição
	int size = imagesize(0,0,width,height);
	
	// Aloca memória para a variável que vai recebe-la
	*pImg = malloc(size);
	
	// Recebe a imagem
	getimage(0,0,width,height,*pImg); 
}


/*Busca e retorna uma imagem com as informações passadas por parâmetro*/
void* GetImage(char path[], int width, int height){
		
	void *pImg;
	readimagefile(path,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	pImg = malloc(size);
	getimage(0,0,width,height,pImg); 
	return pImg;
}		


