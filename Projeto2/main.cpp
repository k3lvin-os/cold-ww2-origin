/*Constantes*/ 
#define FPS 30 // quadros por segundo


/*Inclusão de bibliotecas*/
#include "graphics.h" // para usar a BGI
#include <stdlib.h>     // para usar o rand
#include <time.h>     // para usar o time 
#include <iostream>
#include <tgmath.h>

// Indica a utilização do namespace
using namespace std;

typedef struct TEstrelas{
	int x, y, cor;
	/*define o tipo TEstrelas que é a estrutura de dados a ser usada*/
};
TEstrelas Estrelas[2000]; /*Vetor de 2000 elementos do tipo TEstrelas*/

// Estrutura de dado Nave
typedef struct TNave{
	
	// Medida de lado da nave (padrão)
	static const int LADO = 50;
	
	// Cores internas e externas da nave
	int corInter, corExter;
	
	// Coordenada da nave (baricentro da nave)
	int x, y; 
	
	// Veritices da nave
	int vertices[6];
	
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
	
	// Configuração inicial da nave do jogador
	Nave.x = getmaxx() / 2;
	Nave.y = getmaxy() / 2;
	
	// Condição de incio do loop 
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
		
		// Calcule a posição dos pontos da nave
		Nave.vertices[0] = Nave.x;
		Nave.vertices[1] = Nave.y + Nave.LADO;
		Nave.vertices[2] = Nave.x + sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[3] = Nave.y - sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[4] = Nave.x - sqrt(2 * (Nave.LADO ^2));
		Nave.vertices[5] = Nave.y - sqrt(2 * (Nave.LADO ^2));
		
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
