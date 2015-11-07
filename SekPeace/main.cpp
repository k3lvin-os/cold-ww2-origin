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
#include "..\..\header\rede.h"
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
Botao botaoUmJog, botaoDoisJog, botaoCredit, botaoJogar, botaoVoltar,
botaoCliente, botaoServidor, botaoConectar, botaoAbrirServ;
char *ladoMeuJog,*ladoOutroJog;
int gameSpeed;
Radio radioSpeed, radioLider, radioModoIP;
Rede minhaRede;

//==========================================================

// Funções que usam variáveis globais
void SinglePlayer();
EscolhaEmMenu MenuUmJogador();
EscolhaEmMenu Menu();
EscolhaEmMenu MenuUmJog();
EscolhaEmMenu MenuDoisJog();
void BackgroundMenu();
EscolhaEmMenu MenuCliente();
EscolhaEmMenu MenuServidor();



int main(){
	
	// Inicializa biblioteca de conexões em rede
	minhaRede.WinSockInit();
	
	// Inicialize os botões que serão usados nos menus
	botaoUmJog.Init(BOTAO1_X,BOTAO1_Y,4,4);
	botaoDoisJog.Init(BOTAO2_X,BOTAO2_Y,5,4);
	botaoCredit.Init(BOTAO3_X,BOTAO3_Y,4,4);
	botaoJogar.Init(BOTAO_JOGAR_X,BOTAO_JOGAR_Y,3,1);
	botaoVoltar.Init(BOTAO_VOLTAR_X,BOTAO_VOLTAR_Y,3,1);
	botaoCliente.Init(BOTAO_CLIENTE_X, BOTAO_CLIENTE_Y, 5,4);
	botaoServidor.Init(BOTAO_SERV_X,BOTAO_SERV_Y ,5,4);
	botaoConectar.Init(TILE_W * 17,TILE_H * 12 + 8, 5,1);
	botaoAbrirServ.Init(TILE_W * 11,TILE_H * 14,3,2);
	
	//Inicialize os radio buttons que serão usados nos menus
	radioSpeed.prox = NULL;
	radioLider.prox = NULL;
	radioModoIP.prox = NULL;
	radioSpeed.Insere(&radioSpeed,"4",false,TILE_W * 20 + 16, TILE_H * 10 + 16);
	radioSpeed.Insere(&radioSpeed,"8",true,TILE_W * 22 + 16, TILE_H * 10 + 16);	
	radioLider.Insere(&radioLider,"Stalin",true,TILE_W * 20 + 16, TILE_H * 12 + 16);
	radioLider.Insere(&radioLider,"Roosevelt",false,TILE_W * 23 + 16,TILE_H * 12 + 16);
	radioModoIP.Insere(&radioModoIP,"Automático", true,TILE_W * 20 + 16, TILE_H * 10 + 16);
	radioModoIP.Insere(&radioModoIP,"Manual", false,TILE_W * 20 + 16, TILE_H * 11 + 16);
	
	// A velocidade do jogo ainda não foi definida
	gameSpeed = NULL;
	
	// Carrega o IP padrão do servidor
	minhaRede.ipServer = LOCALHOST;
	minhaRede.portaServ = PORTA_PADRAO;
	
	// Fornece uma seed para o gerador de números pseudoaleatórios
	srand(time(NULL));
	
	// Inicializa a estrutura página
	minhaPg.Init();	
	
	// Inicializa a janela gráfica
	initwindow(TELA_W,TELA_H, "Seek Of Peace: Cold WW2");
	
	// Processo de carregamento dos tiles do jogo
	minhaPg.Troca();
	minhaPg.Ativa();
	meuCampo.Init();	
	cleardevice();
	minhaPg.Visual();
	// ======= Fim do processamento ============
	
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
				break;
			case MENU_DOIS_JOG:
				escolhaMenu = MenuDoisJog();
				break;
			case MENU_CLIENTE:
				escolhaMenu = MenuCliente();
				break;
			case MENU_SERVIDOR:
				escolhaMenu = MenuServidor();
				break;
		}	
	}
	
	WSACleanup();
	radioSpeed.LimpaNo(&radioSpeed);
	closegraph();
	return 0;	
}


// Menu de dois jogadores
EscolhaEmMenu MenuDoisJog(){
	
	EscolhaEmMenu escolha;

	minhaPg.Troca();
	minhaPg.Ativa();
	
	cleardevice();
	BackgroundMenu();
	
	botaoCliente.Show();
	botaoServidor.Show();	
	botaoVoltar.Show();
	outtextxy(botaoCliente.x + 32, botaoCliente.y + 72,"CLIENTE");
	outtextxy(botaoServidor.x + 24,botaoServidor.y + 72,"SERVIDOR");
	outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,"VOLTAR");

	minhaPg.Visual();
	
	escolha = SEM_ESCOLHA;
	while(escolha == SEM_ESCOLHA){
		
		if(botaoCliente.CheckClick() == true)
			escolha = MENU_CLIENTE;
			
		if(botaoServidor.CheckClick() == true)
			escolha = MENU_SERVIDOR;
			
		if(botaoVoltar.CheckClick() == true)
			escolha = MENU;
	}
		
	return escolha;
}



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
	Soldado *soldado0, *alvo;
	Torre *pTorre;
	
	torre0 = meuJog->torre0;
	
	for(pTorre = torre0->prox; pTorre != NULL;pTorre = pTorre->prox){
		
		alvo = NULL;
		pTorre->tipoAnimCanhao = 0;
		soldado0 = eixoIA->soldado0;
		
		alvo = pTorre->BuscaAlvo(soldado0);	
		
		if(alvo == NULL){
				
			soldado0 = outroJog->soldado0;
				
			if(pTorre->BuscaAlvo(soldado0) == NULL)
				pTorre->AnimacaoPatrulha();	
							
		}
			
		if(alvo != NULL){
			
			pTorre->AnimacaoMira(alvo);
			
			if(pTorre->reload.PassouDelay(TORRE_RELOAD)){
				pTorre->reload.Atualiza();
				pTorre->tipoAnimCanhao = 2;
				pTorre->Atira(alvo);
			}	
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
	meuCampo.PosLoad("mapa05.txt");
	
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
		
		// Executa procedimento de colocar torre
		meuJog.ArrastaTorre(meuCampo);
				
		// Limpa campo de carregamento de imagens
		meuCampo.LimpaD();
				
		// Rotina de defesa da torre
		DefesaTorre(&meuJog,&outroJog,&eixoIA);
		
		// Rotina de envio de soldados do jogador
		EnviaSold(&meuJog,&outroJog,meuCampo);
		
		// Rotina de envio de soldados do Eixo contra o jogador
		EnviaSold(&eixoIA,&meuJog,meuCampo);
		
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
			
		if(botaoDoisJog.CheckClick() == true)
			escolha = MENU_DOIS_JOG;
	}
	
	return escolha;
}


// Menu de um jogador
EscolhaEmMenu MenuUmJog(){
	
	EscolhaEmMenu escolha;
	escolha = SEM_ESCOLHA;
	
	while(escolha == SEM_ESCOLHA){
	
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		BackgroundMenu();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 24,TILE_H * 11 );
		bar(TILE_W * 20, TILE_H * 12, TILE_W * 28, TILE_H * 13);
	
		// Mostra os botões 
		botaoJogar.Show();
		botaoVoltar.Show();
				
		// Mostra botões radio
		radioSpeed.MostraLista(&radioSpeed);
		radioLider.MostraLista(&radioLider);
		
		// Mostra o texto dos botões 
		outtextxy(TILE_W * 11, TILE_H * 12 + 16,"Lider:" );
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, "Velocidade do jogo");
		outtextxy(BOTAO_JOGAR_X + 8,BOTAO_JOGAR_Y + 24,"JOGAR");
		outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,"VOLTAR");
		
		minhaPg.Visual();
		
		// Verifica clicks nos botões rádio
		radioSpeed.VerificaClick(&radioSpeed);
		radioLider.VerificaClick(&radioLider);
		
		
		// --------------- Processamento do botão Jogar===================
		if(botaoJogar.CheckClick() == true){
			escolha = UM_JOGADOR;			
				
			if( radioLider.RadioChecked(&radioLider)->label == "Roosevelt"){
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
		//========================== Fim do processamento==================	
	
		// Processamento do botão voltar
		if(botaoVoltar.CheckClick() == true){
			escolha = MENU;
		}
			
	}
	return escolha;
}

// Desenha o visual básico do menu de jogo
void BackgroundMenu(){
	
	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	// Modifica texto para o tamanho do logo
	settextstyle(BOLD_FONT,HORIZ_DIR,7);
	
	// Carrega o menu de jogo (imagem de fundo)
	meuCampo.PosLoad("menu.txt"); 
								
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


// Menu do cliente
EscolhaEmMenu MenuCliente(){
	
	EscolhaEmMenu escolha;
	escolha = SEM_ESCOLHA;
	char ipEPorta[25];
	char temp[7];
	
	minhaRede.ClientInit();
	while(escolha == SEM_ESCOLHA){
		
			
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		BackgroundMenu();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 27,TILE_H * 12 );
		
		botaoVoltar.Show();
		botaoJogar.Show();
		botaoConectar.Show();
		
		radioModoIP.MostraLista(&radioModoIP);
		
		strcpy(ipEPorta,minhaRede.ipServer);
		strcat(ipEPorta,":");
		itoa(minhaRede.portaServ,temp,10);
		strcat(ipEPorta,temp);
		
		
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, "IP / Porta do Servidor: ");
		outtextxy(TILE_W * 27 + 8, TILE_H * 10 + 24, ipEPorta);
		outtextxy(botaoJogar.x + 8,botaoJogar.y + 24,"JOGAR");
		outtextxy(botaoVoltar.x + 4,botaoVoltar.y + 24,"VOLTAR");
		outtextxy(botaoConectar.x + 16,botaoConectar.y + 24,"CONECTAR");
		
		//minhaGrd.Colocar();
		minhaPg.Visual();
		
		radioModoIP.VerificaClick(&radioModoIP);
		
		if(botaoConectar.CheckClick() == true){
			if(minhaRede.ConectaServer() == true){
				minhaRede.EnviaParaOServer("Oi");
			}
		}
		
		if(botaoVoltar.CheckClick() == true){
			escolha = MENU_DOIS_JOG;
			minhaRede.FechaConexaoClient();
			delay(150);
		}
			
		
	}
	
	return escolha;
}

EscolhaEmMenu MenuServidor(){
	
	// Inicializa as flags e o servidor
	minhaRede.FlagsInit();	
	minhaRede.ServerInit();
	
	EscolhaEmMenu escolha;
	escolha = SEM_ESCOLHA;
	
	while(escolha == SEM_ESCOLHA){
	
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		BackgroundMenu();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 24,TILE_H * 11 );
		bar(TILE_W * 20, TILE_H * 12, TILE_W * 28, TILE_H * 13);
		bar(TILE_W * 20, TILE_H * 14, TILE_W * 32, TILE_H * 17);
	
		// Mostra os botões 
		botaoJogar.Show();
		botaoVoltar.Show();
		botaoAbrirServ.Show();
				
		// Mostra botões radio
		radioSpeed.MostraLista(&radioSpeed);
		radioLider.MostraLista(&radioLider);
		
		// Mostra o texto dos botões 
		outtextxy(TILE_W * 11, TILE_H * 12 + 16,"Lider:" );
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, "Velocidade do jogo");
		outtextxy(BOTAO_JOGAR_X + 8,BOTAO_JOGAR_Y + 24,"JOGAR");
		outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,"VOLTAR");
		
		if(minhaRede.servidorAberto == true){
			setcolor(LIGHTGREEN);
			outtextxy(TILE_W * 20, TILE_H * 14 + 16, "- Servidor está aberto!");
		} else{
			setcolor(LIGHTRED);
			outtextxy(TILE_W * 20, TILE_H * 14 + 16, "- O servidor não está aberto");
		}
		
		if(minhaRede.clienteConectado == true){
			setcolor(LIGHTGREEN);
			outtextxy(TILE_W * 20, TILE_H * 15 + 8, "- Cliente está conectado!");
		} else{
			setcolor(YELLOW);
			outtextxy(TILE_W * 20, TILE_H * 15 + 8, "- Aguardando cliente...");
		}
				

		
		minhaPg.Visual();
		
		// Verifica clicks nos botões rádio
		radioSpeed.VerificaClick(&radioSpeed);
		radioLider.VerificaClick(&radioLider);
		
		
		// --------------- Processamento do botão Jogar===================
		if(botaoJogar.CheckClick() == true){
			// Processamento de jogo via rede
		}
		//========================== Fim do processamento==================	
	
		// Processamento do botão voltar
		if(botaoVoltar.CheckClick() == true){
			escolha = MENU_DOIS_JOG;
			minhaRede.FechaConexaoClient();
			delay(100); // Delay para evitar duplo click
		}
		
		// Processamento do botão Abrir servidor
		if(botaoAbrirServ.CheckClick() == true){
			if(minhaRede.AceitaConexaoClient() == true){
				if(minhaRede.RecebeDoClient() == true)
					cout << minhaRede.recvBuf;
			}
		}
		

	
	}
	return escolha;	
}


