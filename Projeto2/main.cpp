/*Constantes*/ 
#define FPS 30 // quadros por segundo


/*Inclus�o de bibliotecas*/
#include "graphics.h" // para usar a BGI
#include <stdlib.h>     // para usar o rand
#include <time.h>     // para usar o time 
#include <iostream>
#include <tgmath.h>

// Indica a utiliza��o do namespace
using namespace std;

typedef struct TEstrelas{
	int x, y, cor;
	/*define o tipo TEstrelas que � a estrutura de dados a ser usada*/
};
TEstrelas Estrelas[2000]; /*Vetor de 2000 elementos do tipo TEstrelas*/

// Estrutura de dado Nave
typedef struct TNave{
	
	// Medida de lado da nave (padr�o)
	static const int LADO = 50;
	
	// Cores internas e externas da nave
	int corInter, corExter;
	
	// Coordenada da nave (baricentro da nave)
	int x, y; 
	
	// Veritices da nave
	int vertices[6];
	
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
	
	// Configura��o inicial da nave do jogador
	Nave.x = getmaxx() / 2;
	Nave.y = getmaxy() / 2;
	
	// Condi��o de incio do loop 
	Nave.corInter = 0;
	Nave.corExter = 0;
	
	// Enquanto a cor interna e a cor externa forem iguais
	while(Nave.corExter != Nave.corInter){
		
		// Gera uma cor interna
		red = rand() % 256;
		green = rand() % 256;
		blue = rand() % 256;
		Nave.corExter = COLOR(red,green,blue);
		
		// Gera uma cor externa
		red = rand() % 256;
		green = rand() % 256;
		blue = rand() % 256;
		Nave.corInter = COLOR(red,green,blue);
		
	}
	
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
		
		// Calcule a posi��o dos pontos da nave
		Nave.vertices[0] = Nave.x;
		Nave.vertices[1] = Nave.y + Nave.LADO;
		Nave.vertices[2] = Nave.x + sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[3] = Nave.y - sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[4] = Nave.x - sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[5] = Nave.y - sqrt(2 * (Nave.LADO ^2));
		
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
