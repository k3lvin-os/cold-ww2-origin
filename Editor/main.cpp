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

// �ltima atualiza��o: 18 de set. 2015

//===============================================

#include "editor.h" // Arquivo auxiliar ao editor de n�veis

int main(){
	
	// Recebe nome do arquivo 
	char nomeArq[8];
	
	// Confirma se tudo ocorreu corretamente
	bool sucesso;
	
	// Recebe a entrada de dados por meio do teclado
	int tecla = 0;
	
	// Opcao do jogador no console
	int opcao = -1;
		
	// Declara��o de vari�veis
	Grade *minhaGrd;
 	CampoJogo *meuCampo;
	
	// Define se o programa continua em execu��o ou n�a
	bool editLoop = true;
	
	// Inicialize a janela do editor (maior em altura do que a janela do jogo)
	initwindow(EDIT_W,EDIT_H);
	
	// Inicializa��o de estruturas
	meuCampo = new CampoJogo();
	minhaGrd = new Grade();

	// Mostra o campo de jogo
	meuCampo->Mostrar();
		
	// Coloca a grade
	minhaGrd->Colocar();
	
	// Faz interface com o usu�rio
	GUI();

	// Loop do programa
	while(editLoop == true){
		
			std::cout << "EDITOR DE CAMPO DE JOGO\nSelecione uma das op��es dispon�veis\n";
			std::cout << "1 - Carregar campo de jogo\n2 - Editar campo de jogo\n3 - Sair\n";
			std::cin >> opcao;
			
			switch(opcao){
				case 1:
					
					// Requere o nome do arquivo com as coord. do campo de jogo e carrega-o
					std::cout << "Digite o nome do arquivo com as coord. do campo de jogo\n";
					std::cin >> nomeArq;
					sucesso = meuCampo->PosLoad(nomeArq);
					
					// Verifica se o processo ocorreu corretamente
					if(!sucesso){
						std::cout << "\nFalha na leitura do arquivo\"" << nomeArq << "\".\n"; 
					} else{
						
						// Se tudo ocorreu corretamente, atualize o campo de jogo
						std::cout << "Arquivo carregado com sucesso!";
						meuCampo->Mostrar();
						minhaGrd->Colocar();
					}
					break;
				case 3:
					do{
						std::cout << "\nDeseja realmente sair do programa?";
						std::cout << "\n1- Sim \n2- Nao\n";
						std::cin >> opcao;
						if (opcao == 1)
							editLoop = false; // Faz o programa sair do la�o e encerrar
					
					} while(opcao != 1 && opcao != 2);
					break;
				default:	
					std::cout <<"\n Digite apenas n� de op��es v�lidas (1-3)\n";
					break;
					
				}

		
		delay(FPS);
	}
	
	closegraph();
	return 0;
}


