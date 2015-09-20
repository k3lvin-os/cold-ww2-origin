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


//Funções
void GUI();

// Menu de escolha do pincel
void Pincel(CampoJogo *meuCampo);

// Procedimento de carregar um arquivo de coordenadas
void Carrega(CampoJogo *meuCampo, Grade *minhaGrd);

// Opcção de sair do programa
void Sair(int &opcao, bool &editLoop);

// Menu principal no console
void MainMenu(int &opcao);

// Menu de edição no console
void Edita(CampoJogo *meuCampo, Grade *minhaGrd);

// Mostra campo e grade na tela
void CampoGrad(CampoJogo *meuCampo, Grade *minhaGrd);


int main(){
	
	// Recebe nome do arquivo 
	char nomeArq[8];
	
	// Contadores 
	int i, j;
	
	// Confirma se tudo ocorreu corretamente
	bool sucesso;
	
	// Recebe a entrada de dados por meio do teclado
	int tecla = 0;
	
	// Opcao do jogador no console
	int opcao = -1;
		
	// Declaração de variáveis
	Grade *minhaGrd;
 	CampoJogo *meuCampo;
	
	// Define se o programa continua em execução ou nõa
	bool editLoop = true;
	
	// Inicialize a janela do editor (maior em altura do que a janela do jogo)
	initwindow(EDIT_W,EDIT_H);
	
	// Inicialização de estruturas
	meuCampo = new CampoJogo();
	minhaGrd = new Grade();

	// Mostra o campo e a grade na tela
	CampoGrad(meuCampo,minhaGrd);
	
	// Faz interface com o usuário
	GUI();

	// Loop do programa
	while(editLoop == true){
			
			// Menu principal no console
			MainMenu(opcao);
			
			switch(opcao){
				case 1:
					
					// Carrega um arquivo de coordenadas
					Carrega(meuCampo, minhaGrd);
					break;
				
				case 2:
					Edita(meuCampo, minhaGrd);
					break;
				case 3:					
					// Procedimento de sáida do programa
					Sair(opcao,editLoop);
					break;
				default:	
					std::cout <<"\n Digite apenas nº de opções válidas (1-3)\n";
					break;
					
				}
	}
	
	closegraph();
	return 0;
}

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

// Menu principal no console
void MainMenu(int &opcao){
	std::cout << "EDITOR DE CAMPO DE JOGO\nSelecione uma das opções disponíveis\n";
	std::cout << "1 - Carregar campo de jogo\n2 - Editar campo de jogo\n3 - Sair\n";
	std::cin >> opcao;
}

// Opcção de sair do programa
void Sair(int &opcao, bool &editLoop){

	
	do{
		std::cout << "\nDeseja realmente sair do programa?";
		std::cout << "\n1- Sim \n2- Nao\n";
		std::cin >> opcao;
		if (opcao == 1)
			editLoop = false; // Faz o programa sair do laço e encerrar
	
	} while(opcao != 1 && opcao != 2);
	
}


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

void Pincel(CampoJogo *meuCampo){
	
	// Contador
	int i;
	
	// Lista os pinceis disponíveis
	std::cout << "\nSelecione um dos pinceis disponíveis:\n\n";
	for(i = 0; i < meuCampo->QTD_TILE; i++){
		std::cout << i + 1 << " - " << meuCampo->tipoTile[i].nome << "\n";
	}

}

// Menu de edição no console
void Edita(CampoJogo *meuCampo, Grade *minhaGrd){
	
	// Para trabalhar com coordenadas...
	int x, y;
	
	// Contadores
	int i, j;
	
	// Indica que o usuário está pressionando o botão esquerdo do mouse
	bool pressing = false;
	
	// Tile aonde se deu um click com o mouse
	int tMouseX0;
	int tMouseY0;
	
	// Tile aonde se soltou o click
	int tMouseXF;
	int tMouseYF;
	
	// Recebe o tipo de alteração entre indices
	int alteraI, alteraJ;
	
	
	// Paginação
	int pg = 1;
	
	// Indica se está no modo desenho ou não
	bool desenho = false;
	
	// Indice do tile que o mouse está sendo em cima
	int tMouseX = 0, tMouseY = 0;
	
	// Pincel de tile
	int pincel = 0;
	
	// Armazena a escolha feita 
 	int opcao = -1;
	
	while(opcao != 3){
		// Pergunte e verifique a escolha feita
		std::cout << "Selecione uma das opcoes disponiveis:\n\n";
		std::cout << "1-Escolher pincel de desenho\n2-Desenhar n3-Sair do menu Edicao\n";
		std::cin >> opcao;
		switch(opcao){
			case 1: 
				Pincel(meuCampo);
				break;
			case 2:
				desenho = true;
				std::cout << "MODO DESENHO\n";
				
				// Enquanto estiver no modo desenho
				while(desenho == true){
					
					
					/*
								Comandos que NÃO geram mudanças gráficas diretas
					*/
					
					// Calcula o tile aonde está o mouse 
					tMouseX = mousex() / TILE_W;
					tMouseY = mousey() / TILE_H;
					
					// Calcula aonde colocar o tile com base no indice dele
					x = tMouseX * TILE_W;
					y = tMouseY * TILE_H;					
					
					// Verifica se o usuário deu um click com o botão esquerdo
					if (ismouseclick(WM_LBUTTONDOWN )){
						
						// Processsa o click
						clearmouseclick(WM_LBUTTONDOWN);
						
						//Calcula o tile aonde foi dado o click
						tMouseX0 = tMouseX;
						tMouseY0 = tMouseY;
						
						// Confirma o pressionamento
						pressing = true;
						
						// Teste
						std::cout << "\npressing =" << pressing << "\n";
					}
					
					// Verifica se o usuário soltou o botão esquerdo
					if(ismouseclick(WM_LBUTTONUP )){
						
						// Processsa o soltar do botão
						clearmouseclick(WM_LBUTTONUP);
						
						// Retira o pressionamento
						pressing = false;
						
						// Teste
						std::cout << "\npressing =" << pressing << "\n";
						
						// Calcula o indice do tile no fim do click
						tMouseXF = tMouseX;
						tMouseYF = tMouseY;
						
						// A posição inicial dos contadores deve começar a partir
						// do primeiro tile de área de click
						
						// Verifica os tipos de alterações
						if(tMouseX0 < tMouseXF)
							alteraJ = 1;
						else
							alteraJ = -1;
							
						if(tMouseY0 < tMouseYF)
							alteraI = 1;
						else
							alteraI = -1;
							
						// Percorra toda área de click e altere os valores da matriz  posTiles
						for( i = tMouseY0; i != (tMouseYF + alteraI); i+= alteraI){
							
							for(j = tMouseX0; j!= (tMouseXF + alteraJ); j+= alteraJ){
								
								// Troque o tipo de tile
								meuCampo->posTile[j][i] = pincel;
								
								//TESTE
								std::cout << "Trocando posTile[" << j << "][" << i << "]\n";
							}
						}
					}
					
					// Troca a página e deixa ela em modo desenho
					if(pg == 1){
						pg = 2;
					} else{
						pg = 1;
					}
					setactivepage(pg);
					
					/*
								Comandos que GERAM mudanças gráficas diretas
					*/
					
					// Limpa a tela
					cleardevice();
					
					// Mostra a tela em sua estrutura definida
					CampoGrad(meuCampo, minhaGrd);
					
					// Mostra GUI
					GUI();
					
					// Verifica o pressionamento e age conforme isso
					if(!pressing){
						
						// Mostra um tile temporário na posição atual
						putimage(x,y,meuCampo->tipoTile[pincel].image,0);
						
						/*TESTE*/
						std::cout<< "\nTile temporário\n";
							
					} else{
						
						// Comece a partir do primeiro tile da área de click do mouse

						
						// Verifica os tipos de alterações
						if(tMouseX0 < tMouseX)
							alteraJ = 1;
						else
							alteraJ = -1;
							
						if(tMouseY0 < tMouseY)
							alteraI = 1;
						else
							alteraI = -1;
						
						// Enquanto não percorrer toda a área de seleção
						for(i = tMouseY0; i != (tMouseY + alteraI); i += alteraI){
							
							/// Calcula a coordenada y do tile
							y = i * TILE_H;
							
							for(j = tMouseX0 ; j!= (tMouseX + alteraJ) ; j+= alteraJ){
								
								// Calcula a coordenada x do tile
								x = j * TILE_W;

								// Coloca os tiles na tela
								putimage(x,y,meuCampo->tipoTile[pincel].image,0);
								
								/*TESTE*/
								std::cout<< "\nColocando tile| pos[ " << j << "][" <<i <<"]\n"; 							
									
							}
						}						
					}
					// Deixa a página visual
					setvisualpage(pg);

					// Atualize os gráficos com uma boa taxa de FPS
					delay(FPS);
				} 
				break;
			default:
				std::cout << "\nDigite apenas opcoes validas (1-3)\n";
				break; 
				
		
		}
	}

}

// Mostra o campo e a grade na tela
void CampoGrad(CampoJogo *meuCampo, Grade *minhaGrd){
	
	// Mostra o campo de jogo
	meuCampo->Mostrar();
		
	// Coloca a grade
	minhaGrd->Colocar();
	
}



