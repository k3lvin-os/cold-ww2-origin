/*Constantes*/ 
#define FPS 30 // quadros por segundo


/*Inclus�o de bibliotecas*/
#include "graphics.h" // para usar a BGI
#include <stdlib.h>     // para usar o rand
#include <time.h>     // para usar o time 
#include <iostream>   // Diversas fun��es
#include <tgmath.h>   // para usar o sqrt

// Indica a utiliza��o do namespace std
using namespace std;

typedef struct TEstrelas{
	int x, y, cor;
	/*define o tipo TEstrelas que � a estrutura de dados a ser usada*/
};
TEstrelas Estrelas[2000]; /*Vetor de 2000 elementos do tipo TEstrelas*/

// Estrutura de dado Nave
typedef struct TNave{
	
	// Cores interna e externa da nave
	int corInter, corExter;
	
	// Veritices da nave
	int vertices[6];
	
	// Deslocamento da nave
	int passo;
	
};


TNave Nave; // Vari�vel do tipo nave

int main(){	
	
	// Contador
	int i;
	
	// Vari�vel utilizada para troca de p�gina ativa e de visualiza��o
	int pg = 1;
	
	// Loop do jogo
	bool gameLoop = true;
	
	// Vari�veis para o c�lculo de cor
	int red, green, blue;
	
	// Fornece uma seed para o gerador de n�meros aleat�rios
	srand(time(NULL));
	
	// Inicializa janela gr�fica
	initwindow(800,600);
	
	// Gera os pixels
	for(i = 0; i < 2000; i++){
	
		// Varia de 1 a 799
		Estrelas[i].x = rand() % 800 + 1;
		
		// Varia de 1 a 599
		Estrelas[i].y = rand() % 600 + 1;
		
		// As cores variam de 0 a 255
		red = rand() % 256;
		green = rand() % 256;
		blue  = rand() % 256;
		
		// Calcula e armazena a cor resultante
		Estrelas[i].cor = COLOR(red,green,blue);
		
		// Teste
		//cout << "\nEstrela[ " << i << "] --> x = " << Estrelas[i].x << " | y = " << Estrelas[i].y << " | cor = " << Estrelas[i].cor;
	}
	
	
	// Posi��o inicial da nave
	Nave.vertices[0] = 400;
	Nave.vertices[1] = 300; 
	Nave.vertices[2] = 450; 
	Nave.vertices[3] = 300;
	Nave.vertices[4] = 425;
	Nave.vertices[5] = 250;
	
	// Cor interna e externa
	Nave.corExter = COLOR(255,255,255);
	Nave.corInter = COLOR(0,0,0);
	
	// Define a velocidade da nave
	Nave.passo = 5;
	
	// Enquanto estiver na jogatina ou loop do jogo
	//(n�o foi solicitado um comando para sair do loop, logo
	// manteve-se sem essa mec�nica)
	while(gameLoop == true){
		
		// Troca a p�gina, a fim de atualizar o desenho
		if(pg == 1){
			pg = 2;
		} else{
			pg = 1;
		}
		
		// Deixe a p�gina em quest�o no modo desenho
		setactivepage(pg);
		
		//=========================================================
		// Atualiza��o da p�gina
		//========================================================
		
		// Limpe a tela
		cleardevice();
		
		// Fa�a o seguinte procedimento com todas estrelas 
		for(i = 0; i < 2000; i++){
			
			// Coloque-as no c�u
			putpixel(Estrelas[i].x, Estrelas[i].y, Estrelas[i].cor);
		}

		// Configura a cor de desenho da nave
		setfillstyle(1, Nave.corInter);
		setcolor(Nave.corExter);
		
		// Texto b�nus
		outtextxy(getmaxx() / 2 - 50,getmaxy() - 100, "The Dark Side Of the Moon");
				
		
		// Se apertar a tecla para cima
		if(GetKeyState(VK_LEFT) & 0x80){
			for(i = 0; i < 6; i+= 2)
				Nave.vertices[i] -= Nave.passo;
			
		}
		
		
		// Se apertar  a tecla para cima
		if(GetKeyState(VK_UP)& 0x80 ){
			for(i = 1; i < 6; i+= 2)
				Nave.vertices[i] -= Nave.passo;
			
		}
		
		// Se apertar a tecla direita
		if(GetKeyState(VK_RIGHT)& 0x80){
			for(i = 0; i < 6; i+= 2)
				Nave.vertices[i] += Nave.passo;
			
		}
		
		// Se apertar a tecla para baixo
		if(GetKeyState(VK_DOWN)& 0x80){
			for(i = 1; i < 6; i+= 2)
				Nave.vertices[i] += Nave.passo;
		}
		
		// Se apertar a tecla HOME...
		if(GetKeyState(VK_HOME) & 0x80){
			// Gere coordenadas aleat�rias para uma vertice
			Nave.vertices[0] = rand() % 700 + 50;
			Nave.vertices[1] = rand() % 500 + 50;
			
			// Calcula a posi��o das outras vertices em 
			// rela��o a primeira coordenada
			Nave.vertices[2] = Nave.vertices[0] + 50;
			Nave.vertices[3] = Nave.vertices[1];
			Nave.vertices[4] = Nave.vertices[0] + 25;
			Nave.vertices[5] = Nave.vertices[1] - 50;
			
		}
		
		// Desenha a nave
		fillpoly(3,Nave.vertices);
		
		// Deixe a p�gina que foi alterada em modo de visualiza��o
		setvisualpage(pg);
		
		// D� o delay para uma padroniza��o do FPS
		delay(FPS);
	}
	
	// Fecha janela gr�fica
	closegraph();
	
	// Encerra a execu��o do programa
	return 0;
}
