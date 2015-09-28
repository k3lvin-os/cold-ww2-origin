/*Constantes*/ 
#define FPS 30 // quadros por segundo


/*Inclusão de bibliotecas*/
#include "graphics.h" // para usar a BGI
#include <stdlib.h>     // para usar o rand
#include <time.h>     // para usar o time 
#include <iostream>   // Diversas funções
#include <tgmath.h>   // para usar o sqrt

// Indica a utilização do namespace std
using namespace std;

typedef struct TEstrelas{
	int x, y, cor;
	/*define o tipo TEstrelas que é a estrutura de dados a ser usada*/
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


TNave Nave; // Variável do tipo nave

int main(){	
	
	// Contador
	int i;
	
	// Variável utilizada para troca de página ativa e de visualização
	int pg = 1;
	
	// Loop do jogo
	bool gameLoop = true;
	
	// Variáveis para o cálculo de cor
	int red, green, blue;
	
	// Fornece uma seed para o gerador de números aleatórios
	srand(time(NULL));
	
	// Inicializa janela gráfica
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
	
	
	// Posição inicial da nave
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
	//(não foi solicitado um comando para sair do loop, logo
	// manteve-se sem essa mecânica)
	while(gameLoop == true){
		
		// Troca a página, a fim de atualizar o desenho
		if(pg == 1){
			pg = 2;
		} else{
			pg = 1;
		}
		
		// Deixe a página em questão no modo desenho
		setactivepage(pg);
		
		//=========================================================
		// Atualização da página
		//========================================================
		
		// Limpe a tela
		cleardevice();
		
		// Faça o seguinte procedimento com todas estrelas 
		for(i = 0; i < 2000; i++){
			
			// Coloque-as no céu
			putpixel(Estrelas[i].x, Estrelas[i].y, Estrelas[i].cor);
		}

		// Configura a cor de desenho da nave
		setfillstyle(1, Nave.corInter);
		setcolor(Nave.corExter);
		
		// Texto bônus
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
			// Gere coordenadas aleatórias para uma vertice
			Nave.vertices[0] = rand() % 700 + 50;
			Nave.vertices[1] = rand() % 500 + 50;
			
			// Calcula a posição das outras vertices em 
			// relação a primeira coordenada
			Nave.vertices[2] = Nave.vertices[0] + 50;
			Nave.vertices[3] = Nave.vertices[1];
			Nave.vertices[4] = Nave.vertices[0] + 25;
			Nave.vertices[5] = Nave.vertices[1] - 50;
			
		}
		
		// Desenha a nave
		fillpoly(3,Nave.vertices);
		
		// Deixe a página que foi alterada em modo de visualização
		setvisualpage(pg);
		
		// Dê o delay para uma padronização do FPS
		delay(FPS);
	}
	
	// Fecha janela gráfica
	closegraph();
	
	// Encerra a execução do programa
	return 0;
}
