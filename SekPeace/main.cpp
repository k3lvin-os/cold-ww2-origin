#include <iostream>
#include <stdlib.h> // Para gerar números aleatórios
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <math.h> // Para usar a função potenciação e raiz quadrada
#include <windows.h> // Para trabalhar com funções de som do Windows
#include <graphics.h>

// Funções que NÃO utilizam as estruturas dos arquivos header
void Carrega(void *arrayImg, void *arrayMask, char *rPath);
void GetImage(void** pImg, char path[], int width, int height);
void* GetImage(char path[], int width, int height);

// Bibliotecas criados pela equipe de desenvolvimento
#include "..\..\header\radiobutton.h"
#include "..\..\header\enumeracoes.h"
#include "..\..\header\td_defines.h"
#include "..\..\header\sprite.h"
#include "..\..\header\campojogo.h"
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
using namespace std;



/*Funções que utilizam as funções dos arquivos header*/
void EnviaSold(Jogador *meuJog, Jogador *outroJog, CampoJogo meuCampo);
void Avisa(TDelay gameTime, Lider Hitler);
void MostraLideres(Lider *meuLider, Lider *outroLider);
void Aviso(int posX, int posY, char * msg, int color, Lider hitler);
void DefesaTorre(Jogador *meuJog, Jogador *outroJog, Jogador *eixoIA);
bool SemTorrePerto(Torre *torre0, int tileCimaX,int tileCimaY);


// Variáveis globais
//======================================================
Jogador meuJog,  outroJog, eixoIA;
CampoJogo meuCampo;
OndaEixo ondaEixo;
char onda;			// Ceritifique-se que essas variáveis
Pagina minhaPg;		// são inicializadas no começo de todas
bool gameLoop;		// funções em que são utilzadas
TDelay gameTime;
Grade minhaGrd;
EscolhaEmMenu escolhaMenu;
Botao botaoUmJog, botaoDoisJog, botaoCredit, botaoJogar, botaoVoltar;
char *ladoMeuJog,*ladoOutroJog;
int gameSpeed;
//==========================================================

// Funções que usam variáveis globais
void SinglePlayer();
EscolhaEmMenu MenuUmJogador();
EscolhaEmMenu Menu();
EscolhaEmMenu MenuUmJog();
void BackgroundMenu();



int main(){
	
	// Inicialize os botões que serão usados nos menus
	botaoUmJog.Init(BOTAO1_X,BOTAO1_Y,4,4);
	botaoDoisJog.Init(BOTAO2_X,BOTAO2_Y,5,4);
	botaoCredit.Init(BOTAO3_X,BOTAO3_Y,4,4);
	botaoJogar.Init(BOTAO_JOGAR_X,BOTAO_JOGAR_Y,3,1);
	botaoVoltar.Init(BOTAO_VOLTAR_X,BOTAO_VOLTAR_Y,3,1);

	gameSpeed = NULL;

	// Fornece uma seed para o gerador de números pseudoaleatórios
	srand(time(NULL));
	
	minhaPg.Init();	// Inicializa a estrutura página
	
	// Inicializa a janela gráfica
	initwindow(TELA_W,TELA_H, "Seek Of Peace: Cold WW2");
	
	escolhaMenu = MENU;
	
	// Loop do jogo
	while(escolhaMenu != SAIR ){
		
		switch(escolhaMenu){
			case MENU:
				escolhaMenu = Menu();
				break;
			case UM_JOGADOR:
				escolhaMenu = MENU;
				SinglePlayer();
				break;
			case MENU_UM_JOG:
				escolhaMenu = MenuUmJog();
		}	
	}	
	closegraph();
	return 0;	
}


/*Funções*/

// Rotina de envio de soldados para outro jogador 
void EnviaSold(Jogador *meuJog, Jogador *outroJog, CampoJogo meuCampo){

	Soldado *novoIni;
	Soldado *pSold, *anterior;
	Soldado *soldado0;
	TDelay *tempoEspera;
	BarraVida meuHP;
	
	soldado0 = meuJog->soldado0;
	tempoEspera = &(outroJog->esperaIni);
	
	for(pSold = soldado0->prox; pSold != NULL; pSold = pSold->prox){
	
		if(pSold->vida > 0 && pSold->chegou != true){
			
			pSold->Show();
			pSold->IA(meuCampo, tempoEspera);
			meuHP.Show(pSold->x,pSold->y,pSold->vida,"soldado");
			
		} 
		
		else{
			
			anterior = pSold->Anterior(soldado0);
			
			if(pSold->chegou == true){
				
				pSold->Remove(anterior);
				outroJog->vida -= DANO_CHEGOU;
				outroJog->lider.Furia();
			}
			else{
				pSold->Remove(anterior);
				outroJog->dinheiro += BONUS_SOLD;
				
			}
			
			pSold = anterior;		
		}
	}
}

//=========================================================================



// Mostra uma mensagem conforme o tempo de jogo
void Avisa(TDelay gameTime, Lider Hitler){
	int gTimeInt;
	gTimeInt = gameTime.GameTime();
	
	setcolor(YELLOW);
	if(gTimeInt >= BEGIN && gTimeInt <= BEGIN + 2)
		Aviso(550,10,"INICIO DA BATALHA",YELLOW,Hitler);
		
	else if (gTimeInt >= ONDA1 && gTimeInt <= ONDA1 + 2)
		Aviso(480,30,"Cuidado! Aí vem o primeiro soldado do Eixo", YELLOW,Hitler);
				
	else if(gTimeInt >= ONDA2 && gTimeInt <= ONDA2 + 2)
		Aviso(480,30,"Faltam 3 m para o ataque final do EIXO",YELLOW,Hitler);
	
	else if(gTimeInt >= ONDA5 && gTimeInt <= ONDA5 + 2)
		Aviso(480,30,"Faltam 2 m para o ataque final do EIXO",YELLOW,Hitler);

	else if(gTimeInt >= ONDA8 && gTimeInt <= ONDA8 + 2)
		Aviso(480,30,"Falta 1 m para o ataque final do EIXO",YELLOW,Hitler);

	else if(gTimeInt >= ONDA10 && gTimeInt <= ONDA10 + 2)
		Aviso(480,30,"É hora do ataque final do EIXO...",YELLOW,Hitler);

	else if(gTimeInt >= END && gTimeInt <= END + 2)
		Aviso(590,10,"Fim de Jogo.", YELLOW, Hitler);
}

/*Busca uma imagem com as informações passadas por parâmetro*/
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


/*Mostra os líders/ avatares dos jogadores*/
void MostraLideres(Lider *meuLider, Lider *outroLider){
	
	BarraVida meuHP;

		
	meuLider->VerificaFuria();
	outroLider->VerificaFuria();
	
	meuLider->VerificaImg();
	outroLider->VerificaImg();
	
	meuLider->Show();
	outroLider->Show();
	
	if(meuLider->nome == "Stalin"){
		meuHP.Show(STALIN_X, STALIN_Y,*meuLider->vida,"lider");
		meuHP.Show(ROOSEVELT_X,ROOSEVELT_Y,*outroLider->vida,"lider");
	} else{
		meuHP.Show(ROOSEVELT_X,ROOSEVELT_Y,*meuLider->vida,"lider");
		meuHP.Show(STALIN_X, STALIN_Y,*outroLider->vida,"lider");
	}
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


/*Texto e outros recursos gráficos mostrados pela função Avisa*/
void Aviso(int posX, int posY, char * msg, int color, Lider hitler){
	settextjustify(LEFT_TEXT,TOP_TEXT);
	hitler.Show();
	setcolor(color);	
	outtextxy(posX,posY,msg);
}

/*Procedimento de defesa da torre*/
void DefesaTorre(Jogador *meuJog, Jogador *outroJog, Jogador *eixoIA){
	Torre *torre0;
	Soldado *soldado0;
	Torre *pTorre;
	
	torre0 = meuJog->torre0;
	
	for(pTorre = torre0->prox; pTorre != NULL;pTorre = pTorre->prox){
		
		if(pTorre->alvo == NULL){		

			soldado0 = eixoIA->soldado0;
			
			if(pTorre->BuscaAlvo(soldado0) == false){
				
				soldado0 = outroJog->soldado0;
				
				if(pTorre->BuscaAlvo(soldado0) == false){
					pTorre->tipoAnimCanhao = 0;
					pTorre->AnimacaoPatrulha();				
				}
			}
		}
		
		if(pTorre->alvo != NULL){
			
			if(pTorre->CampoVisao(*pTorre->alvo) == true){
				
				pTorre->AnimacaoMira();
				
				if(pTorre->reload.PassouDelay(TORRE_RELOAD)){
					pTorre->tipoAnimCanhao = 2;
					pTorre->Atira();
					pTorre->reload.Atualiza();
				}
			} else		
				pTorre->alvo = NULL;
		}
		
		pTorre->MostraTorre();
	}
	
}

// Modo de um jogador
void SinglePlayer(){


	minhaPg.Troca();	// Troca a página atual

	// Trabalha com a página nos "bastidores"
	minhaPg.Ativa();
	
	cleardevice();
	
	// Atribui times aos jogadores
	meuJog.Init(ladoMeuJog,&gameSpeed);
	outroJog.Init(ladoOutroJog,&gameSpeed);
	eixoIA.Init(LADO3,&gameSpeed);
	
	// Inicializa gerenciador de ondas do eixo
	ondaEixo.Init(&eixoIA,&gameSpeed);
	
	// Inicialização do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa05.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();
	
	// Deixa a página visual
	minhaPg.Visual();
	
	// Começa a contar o tempo de jogo
	gameTime.Atualiza();
	
	// Música do gameplay 
	PlaySound("../../Assets/Music/gameplay.wav",NULL,SND_LOOP | SND_ASYNC);	
		
	// Define o loop de jogo
	gameLoop = true;
			
	//Loop do jogo
	while(gameLoop == true){
	
		
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo	
		meuCampo.Mostrar();	
		
		// Mostra gui do jogador
		meuJog.MostraGUI(); 
	
		// Verifica se é hora de enviar uma onda de soldados do Eixo
		onda = gameTime.SoldOnda();	
		
		// Verifica o tipo de envio de soldados do Eixo
		ondaEixo.Verifica(onda,meuJog.lado,meuCampo);

		// Avisa momentos importantes para o jogador
		Avisa(gameTime, eixoIA.lider);
			
		// Verifica o input do usuário com a GUI
		meuJog.InputGUI();
		
		// Coloca procedimento de colocar torre
		meuJog.ArrastaTorre(meuCampo);
				
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
		
		// Rotina de envio de soldados do jogador
		EnviaSold(&meuJog,&outroJog,meuCampo);
		
		// Rotina de envio de soldados do Eixo contra o jogador
		EnviaSold(&eixoIA,&meuJog,meuCampo);
			
		// Rotina de defesa da torre
		DefesaTorre(&meuJog,&outroJog,&eixoIA);
		
		// Mostra os lideres
		MostraLideres(&meuJog.lider,&outroJog.lider);
							
		//Deixa a página visual
		minhaPg.Visual();
	
		// Delay de FPS
		delay(FPS);	
	}
	// Libera a memória
	meuCampo.LimpaMem();
	meuJog.soldado0->LimpaNo(meuJog.soldado0);
	outroJog.soldado0->LimpaNo(outroJog.soldado0);
	eixoIA.soldado0->LimpaNo(eixoIA.soldado0);
	meuJog.torre0->LimpaNo(meuJog.torre0);
	outroJog.torre0->LimpaNo(outroJog.torre0);
	eixoIA.torre0->LimpaNo(eixoIA.torre0);
}

//=============================================================
// Menu de jogo
EscolhaEmMenu Menu(){

	
	EscolhaEmMenu escolha;
	int mouseX,mouseY;

	minhaPg.Troca();
	minhaPg.Ativa();
	
	BackgroundMenu();
	
	// Botoões do menu
	botaoUmJog.Show();
	botaoDoisJog.Show(); 
	botaoCredit.Show();
	
	outtextxy(BOTAO1_X + 48  ,BOTAO1_Y + (TILE_H * 2), "UM"); 
	outtextxy(BOTAO1_X + 8 ,BOTAO1_Y + (TILE_W * 2) + 16, "JOGADOR"); 
	outtextxy(BOTAO2_X + 56  ,BOTAO2_Y + (TILE_H * 2), "DOIS"); 
	outtextxy(BOTAO2_X  + 16,BOTAO2_Y + (TILE_W * 2) + 16, "JOGADORES");
	outtextxy(BOTAO3_X + 8  ,BOTAO3_Y + 72 , "CRÉDITOS"); 
			
	minhaPg.Visual(); 
	
	escolha = SEM_ESCOLHA;
	while(escolha == SEM_ESCOLHA){
		
		if( botaoUmJog.CheckClick() == true)  
			escolha = MENU_UM_JOG;
	}
	
	return escolha;
}


// Menu de um jogador
EscolhaEmMenu MenuUmJog(){
	
	int mouseX, mouseY;
	EscolhaEmMenu escolha;
	Radio radioSpeed, lider;
	
	radioSpeed.prox = NULL;
	lider.prox = NULL;
	
	radioSpeed.Insere(&radioSpeed,"4",false,TILE_W * 20 + 16, TILE_H * 10 + 16);
	radioSpeed.Insere(&radioSpeed,"8",true,TILE_W * 22 + 16, TILE_H * 10 + 16);	escolha = SEM_ESCOLHA;
	lider.Insere(&lider,"Stalin",true,TILE_W * 20 + 16, TILE_H * 12 + 16);
	lider.Insere(&lider,"Roosevelt",false,TILE_W * 23 + 16,TILE_H * 12 + 16);
	
	while(escolha == SEM_ESCOLHA){
	
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		BackgroundMenu();
				
		// Barra de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 24,TILE_H * 11 );
		bar(TILE_W * 20, TILE_H * 12, TILE_W * 28, TILE_H * 13);
		
		setcolor(LIGHTGREEN);

		// Botões radio da velocidade do jogo
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, "Velocidade do jogo");
		radioSpeed.MostraLista(&radioSpeed);
		
		// Botões de rádio de escolha de lideres
		outtextxy(TILE_W * 11, TILE_H * 12 + 16,"Lider:" );
		lider.MostraLista(&lider);
		
		
		// Botão "JOGAR"
		setcolor(LIGHTGRAY);
		setfillstyle(1,LIGHTGRAY);
		
		botaoJogar.Show();
		botaoVoltar.Show();
		
		
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		setcolor(LIGHTGREEN);
		outtextxy(BOTAO_JOGAR_X + 8,BOTAO_JOGAR_Y + 24,"JOGAR");
		outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,"VOLTAR");
		
		minhaPg.Visual();
		
		radioSpeed.VerificaClick(&radioSpeed);
		lider.VerificaClick(&lider);
		
		if(botaoJogar.CheckClick() == true){
			escolha = UM_JOGADOR;			
			
			if( lider.RadioChecked(&lider)->label == "Roosevelt"){
				ladoMeuJog = LADO1;
				ladoOutroJog = LADO2;
			} 
			else{
				ladoMeuJog = LADO2;
				ladoOutroJog = LADO1;
			}
			
			if(radioSpeed.RadioChecked(&radioSpeed)->label == "4")
				gameSpeed = 4;
			else
				gameSpeed = 8;
		}
		
		if(botaoVoltar.CheckClick() == true){
			escolha = MENU;
		}
			
	}
	radioSpeed.LimpaNo(&radioSpeed);
	return escolha;
}

// Desenha o visual básico do menu de jogo
void BackgroundMenu(){
	
	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	// Modifica texto para o tamanho do logo
	settextstyle(BOLD_FONT,HORIZ_DIR,7);
	
	// Carrega o menu de jogo (imagem de fundo)
	meuCampo.Init("menu.txt"); // **** Simplificar esta função
								//       , assim que possível
	meuCampo.Mostrar();		 
	 
	// Logo do jogo
	setcolor(GREEN);
	outtextxy(LOGO_X,LOGO_Y,"SEEK OF PEACE");
	setcolor(DARKGRAY);
	outtextxy(LOGO2_X,LOGO2_Y,"COLD WW2");
	setfillstyle(1,LIGHTGRAY);
	
	// Modifica texto para tamanho usual
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	setcolor(LIGHTGREEN);
	
}

