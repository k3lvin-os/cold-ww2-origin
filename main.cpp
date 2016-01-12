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
#include <vector>

// Para usar a biblioteca Winsock (comunicação em rede)
#pragma comment (lib, "Ws2_32.lib")

// Funções que NÃO utilizam as estruturas dos arquivos header
void GetImage(void** pImg, char path[], int width, int height);
void* GetImage(char path[], int width, int height);

// Bibliotecas criados pela equipe de desenvolvimento
#include "header\td_defines.h"
#include "header\linguagem.h"
Linguagem linguagem;	// Variável que precisa ser inicializada aqui
#include "header\radiobutton.h"
#include "header\radiolist.h"
#include "header\enumeracoes.h"
#include "header\sprite.h"
#include "header\cenario.h"
#include "header\tdelay.h"
#include "header\soldado.h"
#include "header\pagina.h"
#include "header\lider.h"
#include "header\torre.h"
#include "header\jogador.h"
#include "header\ondaeixo.h"
#include "header\grade.h"
#include "header\botao.h"
#include "header\barra_vida.h"
#include "header\rede.h"
#include "header\cursor.h"
#include "header\keymap.h"

using namespace std;


/*Funções que utilizam conteúdo dos arquivos header*/
void EnviaSold(Jogador *meuJog, Jogador *outroJog, Cenario cenario);
void Avisa(TDelay gameTime, Lider Hitler);
void MostraLideres(Lider *meuLider, Lider *outroLider);
void DefesaTorre(Jogador *meuJog, Jogador *outroJog, Jogador *eixoIA);
bool SemTorrePerto(Torre *torre0, int tileCimaX,int tileCimaY);



// Variáveis globais
//======================================================
Jogador meuJog,  outroJog, eixoVsMeuJog,eixoVsOutroJog;
Cenario cenario;
char onda;			
Pagina minhaPg;		
TDelay gameTime;
Grade minhaGrd;
EscolhaEmMenu escolhaMenu;
Botao botaoUmJog, botaoDoisJog, botaoCredit, botaoJogar, botaoVoltar, botaoVoltar2,
botaoCliente, botaoServidor, botaoConexao, botaoOpcaoServ, botaoAlterar, botaoPtBr,
botaoEnglish, botaoLocalMulti ;
char *ladoMeuJog,*ladoOutroJog;
int gameSpeed;
RadioList radioSpeed, radioLider, radioModoIP;
Rede minhaRede;
char logDano[100];
char ipDoServidor[16],portaDoServidor[7];
Sprite telaPretaE,telaPretaD, campoJogo, menu, 
limpa2Tiles, logoEMenu, textoCreditos, splitscreen, botaoJog, 
imgCursor1, imgCursor2, fundoTorre;
Cursor cursor[2];
int jogNSold[2], jogNTorre[2];
//==========================================================

// Funções que usam variáveis globais
EscolhaEmMenu MenuUmJogador();
EscolhaEmMenu Menu();
EscolhaEmMenu MenuUmJog();
EscolhaEmMenu MenuDoisJog();
EscolhaEmMenu MenuCliente();
EscolhaEmMenu MenuServidor();
EscolhaEmMenu TelaCreditos();
EscolhaEmMenu MenuSplitscreen();
void Gameplay(TipoGameplay tipoGameplay);
void CarregaLogoMenu();
void IAOutroJog(int enviaSold);
void RecebePacoteJogo();
void SimulaOutroJog(TipoGameplay tipoGameplay,OndaEixo *ondaVsOutroJog,char* logAtira);
void EnviaPacoteJogo();
void ConfigIPEPorta();
void TelaGameOver(char *lado);
void TextoCreditos();
void Logo(int tileYSeek);
void CarregaSplitsceen();
void LimpaMemoria(TipoGameplay tipoGm);
void RotinaItemSplitscreen(int *qtdSold, int *qtdTorre);

#include "header\cutscenes.h"
Cutscenes cutscenes;



//============================================================================================
int main(){

	// Inicializa biblioteca de conexões em rede
	minhaRede.WinSockInit();
		
	// Carrega textos do jogo em modo default
	linguagem.TextoDefault();
	
	// Inicializa a estrutura página
	minhaPg.Init();	
	
	// Inicializa a janela gráfica
	initwindow(TELA_W,TELA_H, "Seek Of Peace: Cold WW2");
	
	KeyMap myKeyMap("txt/keymap.txt");
	myKeyMap.ShowKeys();
	
	bool flag = true;
	while(flag)
	{
		for(int i = 0; i <myKeyMap.TXT_TOTAL_NUMBER; i++)
		{
			if(GetKeyState(myKeyMap.value(i))& 0x80)
			{
				cout << myKeyMap.name(i) << endl;
				flag = false;
				
			}
		}
	}
	
	// A velocidade do jogo ainda não foi definida
	gameSpeed = NULL;
	
	// Busca o IP e Porta definidos por padrão em um .txt
	ConfigIPEPorta();

	// Fornece uma seed para o gerador de números pseudoaleatórios
	srand(time(NULL));	
	
	
	// Inicialize os botões que serão usados nos menus
	botaoUmJog.Init(BOTAO1_X,BOTAO1_Y,4,4);
	botaoDoisJog.Init(BOTAO2_X,BOTAO2_Y,5,4);
	botaoCredit.Init(BOTAO3_X,BOTAO3_Y,4,4);
	botaoJogar.Init(BOTAO_JOGAR_X,BOTAO_JOGAR_Y,3,1);
	botaoVoltar.Init(BOTAO_VOLTAR_X,BOTAO_VOLTAR_Y,3,1);
	botaoVoltar2.Init(TILE_W * 19, TILE_H * 20,3,1);
	botaoCliente.Init(BOTAO_CLIENTE_X, BOTAO_CLIENTE_Y, 5,4);
	botaoServidor.Init(BOTAO_SERV_X,BOTAO_SERV_Y ,5,4);
	botaoLocalMulti.Init(LOCALMULTI_X, LOCALMULTI_Y,5,4);
	botaoConexao.Init(TILE_W * 17,TILE_H * 12 + 8, 5,1);
	botaoOpcaoServ.Init(TILE_W * 11,TILE_H * 14,4,2);
	botaoAlterar.Init(TILE_W * 27 + 16, TILE_H  * 11,4,1);
	botaoEnglish.Init(TILE_W * 18, TILE_H * 13,4,1);
	botaoPtBr.Init(TILE_W * 17 , TILE_H * 15 ,6,1);

	
	// ============ FUNÇÕES QUE CARREGAM IMAGENS NA TELA ====================
	//* Já que carregam imagens, deve-se carrega-las nos "bastidores" do jogo,
	// sem a visualização do jogador
	
	minhaPg.Troca();
	minhaPg.Ativa();
	
	telaPretaE.Init(32,32,32 + TILE_W * 17, 32 + TILE_H * 18 );
	telaPretaD.image = telaPretaE.image;
	
	telaPretaE.x = TILE_W * 1;
	telaPretaE.y = TILE_H * 1;
	telaPretaD.x = TILE_W * 22 ;
	telaPretaD.y = TILE_H * 1;
	
	
	cenario.Init();	
	cutscenes.Carrega();
	
	cleardevice();
	cenario.PosLoad("menu.txt");	
	cenario.Mostrar();
	menu.Init(0,0,TELA_W,TELA_H);
	
	cenario.PosLoad("tower.txt");
	cenario.Mostrar();
	fundoTorre.Init(0,0,TELA_W,TELA_H);
	
		
	cleardevice();	
	cenario.PosLoad("mapa05.txt");
	cenario.Mostrar();
	limpa2Tiles.Init(0,0,32,64);
	campoJogo.Init(0,0,TELA_W,TELA_H);
	
	setfillstyle(1,LIGHTGRAY);
	bar(0,0,TILE_W / 2,TILE_W / 2);	
	botaoJog.Init(0,0,TILE_W / 2,TILE_W / 2);
	



	cenario.tipoTile[2].Show();
	imgCursor1.Init(0,0,32,32);
	cenario.tipoTile[4].Show();
	imgCursor2.Init(0,0,32,32);
	
	// ===========================================================================
	CarregaLogoMenu();
	logoEMenu.Init(0,0,TELA_W,TELA_H);
	
	CarregaSplitsceen();
	splitscreen.Init(0,0,TELA_W,TELA_H);
	
	cleardevice();
	logoEMenu.Show();

	minhaPg.Visual();

	
	
	// ================================== SELEÇÃO DE IDIOMA =====================
	
	outtextxy(TILE_W * 15 + 24, TILE_H * 11, "CHOOSE YOUR LANGUAGE");
	
	botaoEnglish.Show();
	botaoPtBr.Show();
	
	outtextxy(botaoEnglish.x + 16,botaoEnglish.y + 24,"ENGLISH");
	outtextxy(botaoPtBr.x + 6,botaoPtBr.y + 24, "PORTUGUÊS(BR)");
		
	Idioma idioma = SEM_IDIOMA;
	
	while(idioma == SEM_IDIOMA){
		
		if(botaoEnglish.CheckClick() == true){
		 	idioma = INGLES;
		}
		
		else if (botaoPtBr.CheckClick() == true){
			idioma = PORTUGUES;
		}
	}
	
	if(idioma == INGLES)
		linguagem.Init(INGLES);
	else
		linguagem.Init(PORTUGUES);	
	
	// ========================================================================
	minhaPg.Troca();
	minhaPg.Ativa();
	TextoCreditos();


	//Inicialize os radio buttons que serão usados nos menus
	radioSpeed = RadioList();
	radioLider = RadioList();
	radioModoIP = RadioList();
	radioSpeed.list.push_back(Radio("4",false,TILE_W * 20 + 16, TILE_H * 10 + 16));
	radioSpeed.list.push_back(Radio("8",true,TILE_W * 22 + 16, TILE_H * 10 + 16));
	radioLider.list.push_back(Radio("Stalin",true,TILE_W * 20 + 16, TILE_H * 12 + 16));
	radioLider.list.push_back(Radio("Roosevelt",false,TILE_W * 23 + 16,TILE_H * 12 + 16));
	radioModoIP.list.push_back(Radio(linguagem.GetText(20), true,TILE_W * 20 + 16, TILE_H * 10 + 16));
	radioModoIP.list.push_back(Radio(linguagem.GetText(21), false,TILE_W * 20 + 16, TILE_H * 11 + 16));

	
	escolhaMenu = MENU;
	
	// Loop do jogo
	while(escolhaMenu != SAIR ){
		
		delay(DELAY_TELA);
		switch(escolhaMenu){
			case MENU:
				escolhaMenu = Menu();
				break;
			case UM_JOGADOR:
				escolhaMenu = CREDITOS;
				Gameplay(SINGLEPLAYER);
				break;
			case DOIS_JOGADORES:
				escolhaMenu = CREDITOS;
				Gameplay(MULTIPLAYER_ONLINE);
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
			case MENU_SPLITSCREEN:
				escolhaMenu = MenuSplitscreen();
				break;	
			case SPLITSCREEN:
				escolhaMenu = CREDITOS;
				Gameplay(MULTIPLAYER_SPLIT);
				break;
			case CREDITOS:
				escolhaMenu = TelaCreditos();
				break;
				
		}	
	}
		
	
	minhaRede.EncerraWinSock();

	// Libera a memória
	cenario.LimpaMem();
	linguagem.LimpaMemoria();
	closegraph();
	return 0;	
}

//============================================================================================
// Menu de dois jogadores
EscolhaEmMenu MenuDoisJog(){
	
	EscolhaEmMenu escolha;

	minhaPg.Troca();
	minhaPg.Ativa();
	
	cleardevice();
	logoEMenu.Show();
	

	botaoCliente.Show();
	botaoServidor.Show();
	botaoLocalMulti.Show();	
	botaoVoltar.Show();
	outtextxy(botaoCliente.x + 32, botaoCliente.y + 72,linguagem.GetText(1));
	outtextxy(botaoServidor.x + 24,botaoServidor.y + 72,linguagem.GetText(2));
	outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,linguagem.GetText(3));
	outtextxy(botaoLocalMulti.x + 8, botaoLocalMulti.y + 72 , linguagem.GetText(108));

	minhaPg.Visual();
	
	escolha = SEM_ESCOLHA;	
	
	while(escolha == SEM_ESCOLHA){
		
		if(botaoCliente.CheckClick() == true)
			escolha = MENU_CLIENTE;
			
		if(botaoServidor.CheckClick() == true)
			escolha = MENU_SERVIDOR;
			
		if(botaoVoltar.CheckClick() == true)
			escolha = MENU;
		
		if(botaoLocalMulti.CheckClick() == true)
			escolha = MENU_SPLITSCREEN;	
		
	}
		
	return escolha;
}


//============================================================================================
// Rotina de envio de soldados para outro jogador 
void EnviaSold(Jogador *meuJog, Jogador *outroJog, Cenario cenario){

	Soldado *novoIni;
	Soldado *pSold, *anterior;
	Soldado *soldado0;
	TDelay *tempoEspera;
	BarraVida meuHP;
	
	soldado0 = meuJog->soldado0;
	tempoEspera = &(outroJog->esperaIni);
	
	for(pSold = soldado0->prox; pSold != NULL; pSold = pSold->prox){
	
		if(pSold->vida > 0 && pSold->chegou != true){
			
			pSold->IA(cenario, tempoEspera);
			pSold->Show();
			meuHP.Show(pSold->x,pSold->y,pSold->vida,"soldado");
			
		} 
		
		else{
			
			anterior = pSold->Anterior(soldado0);
			
			if(pSold->chegou == true){
				
				pSold->Remove(anterior);
				outroJog->vida -= DANO_CHEGOU;
				
				if(outroJog->vida < 0)
					outroJog->vida = 0;
					
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
	
	int gTimeInt, timer;
	char timerChar[3];
	
	setcolor(YELLOW);
	gTimeInt = gameTime.GameTime();
	timer = 92 - gTimeInt;
	itoa(timer,timerChar,10);
	
	if(timer > 30)
		setcolor(YELLOW);
	else
		setcolor(LIGHTRED);
		
	
	
	if(gTimeInt >= BEGIN && gTimeInt <= BEGIN + 1){
		outtextxy(TILE_W * 17 + 8,TILE_H * 1,linguagem.GetText(4));
		if(gTimeInt == BEGIN)
			putimage(TILE_W * 19, TILE_H * 2,Hitler.imagens[NORMAL],COPY_PUT);
		else
			putimage(TILE_W * 19 , TILE_H * 2,Hitler.imagens[BRAVO],COPY_PUT);	
	}
		
	else if(gTimeInt >= ONDA1 && gTimeInt <= ONDA1 + 1){
		outtextxy(TILE_W * 14,TILE_H * 1,linguagem.GetText(5));
			putimage(TILE_W * 19 , TILE_H * 2,Hitler.imagens[BRAVO],COPY_PUT);
	}
	else if(gTimeInt >= ONDA3 && gTimeInt <= ONDA3 + 1){
		
		outtextxy(TILE_W * 13 + 8,TILE_H * 1,linguagem.GetText(6));
		if(gTimeInt == ONDA3)
			putimage(TILE_W * 19, TILE_H * 2,Hitler.imagens[NORMAL],COPY_PUT);
		else
			putimage(TILE_W * 19 , TILE_H * 2,Hitler.imagens[BRAVO],COPY_PUT);	
	}
	
	else if(gTimeInt >= ONDA5 && gTimeInt <= ONDA5 + 1){
		
		setcolor(LIGHTRED);
		outtextxy(TILE_W * 15 ,TILE_H * 1,linguagem.GetText(9));
		putimage(TILE_W * 19 , TILE_H * 2,Hitler.imagens[BRAVO],COPY_PUT);	

	}
	
	else if(gTimeInt >= END){
		outtextxy(TILE_W * 17 + 8,TILE_H * 1,linguagem.GetText(10));
		putimage(TILE_W * 19, TILE_H * 2,Hitler.imagens[MORTO],COPY_PUT);
	}
	
	else{
		if(timer < 10)
			outtextxy(TILE_W * 19 + 28,TILE_H * 1,timerChar);
		else
			outtextxy(TILE_W * 19 + 20,TILE_H * 1,timerChar);

	}
	
	if(timer <= 30 && timer > 0){
		putimage(TILE_W * 19, TILE_H * 2,Hitler.imagens[BRAVO],COPY_PUT);
	}
		

		
	


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


/*Busca e retorna uma imagem com as informações passadas por parâmetro*/
void* GetImage(char path[], int width, int height){
		
	void *pImg;
	readimagefile(path,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	pImg = malloc(size);
	getimage(0,0,width,height,pImg); 
	return pImg;
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



/*Procedimento de defesa da torre*/
void DefesaTorre(Jogador *meuJog, Jogador *outroJog, Jogador *eixoIA, bool atira){
	
	int dano;
	Torre *torre0;
	Soldado *soldado0, *alvo;
	Torre *pTorre;
	char temp[3];
	char logTemp[100];
	int id, i,count;
	char c;
	
	i = 0;
	
	torre0 = meuJog->torre0;
	strcpy(logTemp,"");
	strcpy(temp,"");
	
	for(pTorre = torre0->prox; pTorre != NULL;pTorre = pTorre->prox){
		
		alvo = NULL;
		pTorre->tipoAnimCanhao = 0;
		soldado0 = eixoIA->soldado0;
		
		alvo = pTorre->BuscaAlvo(soldado0);	
		
		if(alvo == NULL){
				
			soldado0 = outroJog->soldado0;
			
			alvo = pTorre->BuscaAlvo(soldado0);	
			if(alvo == NULL);
				pTorre->AnimacaoPatrulha();	
							
		}
			
		if(alvo != NULL){
			
			pTorre->AnimacaoMira(alvo);
			
			if(pTorre->reload.PassouDelay(TORRE_RELOAD)){
				pTorre->reload.Atualiza();
				pTorre->tipoAnimCanhao = 2;
				
				if(atira == true){
					dano = pTorre->Atira(alvo);
					
					if(soldado0 == eixoIA->soldado0)
						strcat(logTemp,EIXO_ID);
					else
						strcat(logTemp,OUTROJOG_ID);
					
					strcat(logTemp,"|");
	
						
					id = soldado0->GetId(soldado0,alvo);
					itoa(id,temp,10);
					strcat(logTemp,temp);
					strcat(logTemp,"|");	
					itoa(dano,temp,10);
					strcat(logTemp,temp);
					strcat(logTemp,"|");
				}
			}	
		}
		
		pTorre->MostraTorre();	 	
	}
	
	if(strcmp(logTemp,"") != 0){
		strcpy(logDano,"DANO|");
		strcat(logDano,logTemp);
	}			
}
		




// Modo de um jogador
 void Gameplay(TipoGameplay tipoGameplay){
	char *logAtira;
	OndaEixo ondaVsMeuJog, ondaVsOutroJog;
	Final meuFinal;
	int enviaSold;
	
	if(tipoGameplay == SINGLEPLAYER)
		enviaSold = rand() % 2;
	
	// Troca a página atual
	minhaPg.Troca();	
	
	// Trabalha com a página nos "bastidores"
	minhaPg.Ativa();
	
	// Atribui times aos jogadores
	meuJog.Init(ladoMeuJog,&gameSpeed);
	outroJog.Init(ladoOutroJog,&gameSpeed);
	eixoVsMeuJog.Init(LADONAZI,&gameSpeed);
	eixoVsOutroJog.Init(LADONAZI,&gameSpeed);
	
	// Inicializa gerenciador de ondas do eixo
	ondaVsMeuJog.Init(&eixoVsMeuJog,&gameSpeed,meuJog.lado);
	ondaVsOutroJog.Init(&eixoVsOutroJog,&gameSpeed,outroJog.lado);
	
	// Limpa a tela
	cleardevice();
	
	// Deixa a página visual
	minhaPg.Visual();
	
	// Mostra o tutorial
	cutscenes.Tutorial(meuJog, tipoGameplay);
		
	// Começa a contar o tempo de jogo
	gameTime.Atualiza();	
	
	//Loop do jogo
	do{
	
		// Troca e ativa uma nova página para modificações
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo	
		campoJogo.Show();	
			
		if(meuJog.vida > 0){
			
			
			// Mostra gui do jogador
			meuJog.MostraGUI(tipoGameplay); 
						
			if(tipoGameplay != MULTIPLAYER_SPLIT)
			{
		
				// Verifica o input do usuário com a GUI
				meuJog.InputGUI ();
						
				// Executa procedimento de colocar torre
				meuJog.ArrastaTorre(cenario);
			}
			
			else
			{
				cursor[0].Show();
			}

			// Rotina de defesa da torre 
			DefesaTorre(&meuJog,&outroJog,&eixoVsMeuJog,true);
		
			// Rotina de envio de soldados do Eixo contra o jogador
			EnviaSold(&eixoVsMeuJog,&meuJog,cenario);	
		} 
		
		else{
			
			TelaGameOver(meuJog.lado);	

		}
		
		if(outroJog.vida > 0){
			
			// Rotina de envio de soldados do jogador
			EnviaSold(&meuJog,&outroJog,cenario);
		}	
				
		// Verifica se é hora de enviar uma onda de soldados do Eixo
		onda = gameTime.SoldOnda();	
				
		// Verifica o tipo de envio de soldados do Eixo
		ondaVsMeuJog.Verifica(onda,cenario);
		
		// Simula a IA no Singleplayer 
		if(tipoGameplay == SINGLEPLAYER)
			IAOutroJog(enviaSold);
		
		//Ou recebe/envia dados no Multiplayer
		else if(tipoGameplay == MULTIPLAYER_ONLINE){
			EnviaPacoteJogo();
			RecebePacoteJogo();
		}
					
		// Simula o comportamento do outro jogador	
		SimulaOutroJog(tipoGameplay,&ondaVsOutroJog,logAtira);
		
		// Faz verificações de entrada no modo splitscreen
		if(tipoGameplay == MULTIPLAYER_SPLIT)
			RotinaItemSplitscreen(jogNSold,jogNTorre);

		
		if(outroJog.vida  == 0)
			meuJog.outroJogMorto = true;
			
		// Avisa momentos importantes para o jogador
		Avisa(gameTime, eixoVsMeuJog.lider);
					
		// Mostra os lideres
		MostraLideres(&meuJog.lider,&outroJog.lider);
		
		// Limpa zona de carregamento de imagens
		limpa2Tiles.Show();
							
		//Deixa a página visual
		minhaPg.Visual();
		
		if(gameSpeed == 8)
			delay(FPS);
		else
			delay(FPS2);	
				
	} while((onda != 'F') && (meuJog.vida > 0 || outroJog.vida > 0));
	
	PlaySound(NULL, NULL, 0); 
	

	if(onda == 'F'){
		if(meuJog.vida <= 0 && meuJog.lado == LADOEUA){
			telaPretaD.Show();
			meuFinal = FINAL_URSS;
		} else if(meuJog.vida <= 0 && meuJog.lado == LADOURSS){
			telaPretaE.Show();
			meuFinal = FINAL_EUA;
		} else if(outroJog.vida <= 0 && outroJog.lado == LADOEUA){
			telaPretaD.Show();	
			meuFinal = FINAL_URSS;
		} else if(outroJog.vida <= 0 && outroJog.lado == LADOURSS){
			telaPretaD.Show();
			meuFinal = FINAL_EUA;
		} else{
			meuFinal = FINAL_GUERRAFRIA;
		}
	}
	else{	
		telaPretaD.Show();
		telaPretaE.Show();
		meuFinal = FINAL_NAZI;	
	}
	Avisa(gameTime, eixoVsMeuJog.lider);
	MostraLideres(&meuJog.lider,&outroJog.lider);
	
	delay(2000);
	cutscenes.MostraFinal(meuFinal);

	LimpaMemoria(tipoGameplay);
	
	settextjustify(LEFT_TEXT,CENTER_TEXT);

}

//============================================================================================
// Envia dados no modo multiplayer 
void EnviaPacoteJogo(){
	
	bool enviei;
	char pacote[70];
	char temp[4];
	
	
	strcpy(pacote,"");
	
	if(meuJog.qtdSoldEspera == 1){
		strcat(pacote,"NEW_SOLD|");
		meuJog.qtdSoldEspera = 0;
	}
	
	if(meuJog.novaTorreXeY[0][0] != UNDEFINED && 
	meuJog.novaTorreXeY[0][1] != UNDEFINED){
		
		strcat(pacote,"TORRE|");
		itoa(meuJog.novaTorreXeY[0][0],temp,10);
		strcat(pacote,temp);
		strcat(pacote,"|");
		itoa(meuJog.novaTorreXeY[0][1],temp,10);
		strcat(pacote,temp);
		strcat(pacote,"|");
		
		meuJog.novaTorreXeY[0][0] = UNDEFINED;
		meuJog.novaTorreXeY[0][1] = UNDEFINED;
	}
	
	strcat(pacote,logDano);
	
	if(strcmp(pacote,"") == 0)
		strcpy(pacote,"_");
	
	if(minhaRede.clienteOuServidor == "cliente"){
	
		//do{
			enviei = minhaRede.EnviaParaOServer(pacote);
		//} while(enviei == false);*/

	}
		
	else if(minhaRede.clienteOuServidor == "servidor"){
		
		//do{
			enviei = minhaRede.EnviaParaOClient(pacote);
		//} while(enviei == false);
	}		
}

// Simula a IA no modo Singleplayer
void IAOutroJog(int enviaSold){

	int chance, qtd, posXMin, posXMax, posYMin, posYMax, tileX, tileY, meuX, meuY, i;
	bool posValida;
	
	if(onda == '0' || onda == 'F' || onda == SEM_ONDA || outroJog.vida <= 0)
		return;
		
	chance = rand()%10 + 1;
			
	if ((chance >= 1  && chance <= 3) || (meuJog.vida <= 0))
	{
		
		qtd = outroJog.dinheiro / PRECO_TORRE;
				
		if(qtd != 0)
		{
			

			
			if(outroJog.lado == LADOEUA)
			{
				posXMin = 23;
				posXMax = 37;
				posYMin = 2; 
				posYMax = 18;
			} 
			
			else if(outroJog.lado == LADOURSS)
			{
				posXMin = 2;
				posXMax = 16;
				posYMin = 2;
				posYMax = 18;
			}
			
			for(i = 0; i < qtd; i++)
			{
			
				do{
					tileX = rand() % posXMax + posXMin;
					tileY = rand() % posYMax + posYMin;
					posValida = cenario.PosExist(tileX,tileY); 
					
					if(posValida == true)
					{
						
						posValida = cenario.CheckPosTorre(tileX,tileY,outroJog.lado);
						meuX = tileX * TILE_W;
						meuY = tileY * TILE_H; 
						
						if(posValida == true)
						{
							posValida = outroJog.torre0->SemTorrePerto(outroJog.torre0,meuX,meuY);
							outroJog.Compra(PRECO_TORRE);
							outroJog.novaTorreXeY[i][0] = meuX;
							outroJog.novaTorreXeY[i][1] = meuY;
						}
						
					}
					
				} while(posValida == false);
			}
			

		}			
	}	
		
	else if (enviaSold != 0 && chance == 4){
		
		if(outroJog.Compra(PRECO_SOLDADO) == true);
			outroJog.qtdSoldEspera++;
	}


}
	

	
		
	

//============================================================================================
// Recebe dados no modo multiplayyer
void RecebePacoteJogo(){
	
	int i;
	char c;
	char temp[2];
	char buffer[100];
	TipoPacote tipoPacote;
	char pacote[30];
	int contador;
	bool recebi;
	
	strcpy(logDano,"");

	
	if(minhaRede.clienteOuServidor == "cliente")
		recebi = minhaRede.RecebeDoServer();
		
	else if(minhaRede.clienteOuServidor == "servidor")
		recebi = minhaRede.RecebeDoClient();	
		
	if(recebi == true){
		
		
		c = minhaRede.pacote[0];
		i = 0;
		tipoPacote =  SEM_TIPO;
		strcpy(buffer,"");
		contador = 0;
		
		while(c != '\0'){
			
			if(c == '|' && tipoPacote == SEM_TIPO ){
				
				if(strcmp(buffer,"NEW_SOLD") == 0){
					outroJog.qtdSoldEspera = 1;
				}
				
				if(strcmp(buffer,"TORRE") == 0){
					tipoPacote = TORRE;
				}
				
				if(strcmp(buffer,"DANO") == 0){
					tipoPacote = DANO;
				} 
					
				strcpy(buffer,"");			
			} 
			
			else if(c == '|' && tipoPacote != SEM_TIPO){
				
				if(tipoPacote == TORRE){
					
					outroJog.novaTorreXeY[0][contador] = atoi(buffer);
					contador++;
					
					if(contador > 1){
						contador = 0;
						tipoPacote = SEM_TIPO;
					}
				}
				
				if(tipoPacote == DANO){
					strcat(logDano,buffer);
					strcat(logDano,"|");
				}
				
				
				strcpy(buffer,"");
				
			} 
			
			
			else{
				temp[0] = c;
				temp[1] = '\0';
				strcat(buffer,temp);
			}
			
			i++;
			c = minhaRede.pacote[i];
		
		}
	}
}



// Simula o comportamento do outro jogador
void SimulaOutroJog(TipoGameplay tipoGameplay, OndaEixo *ondaVsOutroJog,char* logAtira){
	
	char c;
	int i, id, dano;
	int tempCount;
	int danoCount;
	char temp[3];
	Soldado *danoSoldado0, *alvo;
	
	if(meuJog.vida > 0){
		
		EnviaSold(&outroJog,&meuJog,cenario);
	}

	
	if(outroJog.vida > 0)
	{
		
		if(tipoGameplay == MULTIPLAYER_SPLIT){
			cursor[1].Show();
			outroJog.MostraGUI(MULTIPLAYER_SPLIT);
		}
		
		if(outroJog.qtdSoldEspera > 0){
		
		    if(outroJog.envioSold.PassouDelay(ESPERA_DELAY) == true)
			{
		     	outroJog.envioSold.Atualiza();
			    outroJog.soldado0->Insere(outroJog.soldado0,&outroJog.soldGUI,gameSpeed);
			    outroJog.qtdSoldEspera--;
			}
				
		}
	
		for(i = 0; i < QTD_NOVATORRE; i++){
		
			if(outroJog.novaTorreXeY[i][0] != UNDEFINED
	 		&& outroJog.novaTorreXeY[i][1] != UNDEFINED)
		   {

				outroJog.torre0->Insere(outroJog.torre0,outroJog.lado,
				outroJog.novaTorreXeY[i][0],outroJog.novaTorreXeY[i][1]);
				outroJog.novaTorreXeY[i][0] = UNDEFINED;
				outroJog.novaTorreXeY[i][1] = UNDEFINED;	
			}
		
		}

		ondaVsOutroJog->Verifica(onda,cenario);
		
		EnviaSold(&eixoVsOutroJog,&outroJog,cenario);
	
		if(tipoGameplay != MULTIPLAYER_ONLINE)
			DefesaTorre(&outroJog,&meuJog,&eixoVsOutroJog,true);
		else
		{
			DefesaTorre(&outroJog,&meuJog,&eixoVsOutroJog,false);
			
			if(strcmp(logDano,"") != 0)
			{
				
				
				c = logDano[0];
				danoCount = 1;
				tempCount = 0;
				i = 0;
				strcpy(temp,"");
									
				while(c != '\0')
				{
					
					if(c != '|')
					{
						temp[tempCount] = c;
						temp[tempCount + 1] = '\0';
						tempCount++;
					} 
					
					else
					{
						
						tempCount = 0;
						switch(danoCount)
						{				
							case 1:
								
								if(strcmp(temp,EIXO_ID) == 0)
									danoSoldado0 = eixoVsOutroJog.soldado0;
								else	
									danoSoldado0 = meuJog.soldado0;							
								danoCount = 2;
								break;
								
							case 2:
								id =  atoi(temp);
								alvo = alvo->GetSoldById(danoSoldado0,id);
								danoCount = 3;
								break;
							case 3:
								dano = atoi(temp);
								if(alvo != NULL)
									alvo->vida -= dano;
								danoCount = 1;
								break;	
						}
						strcpy(temp,"");
					}
					
				
					i++;
					c = logDano[i];
				}	
			}
		
		}
		
	}
	 
	else 
	{
		TelaGameOver(outroJog.lado);
	}
		
}





//=============================================================
// Menu de jogo
EscolhaEmMenu Menu(){

	
	EscolhaEmMenu escolha;
	int mouseX,mouseY;

	minhaPg.Troca();
	minhaPg.Ativa();
	
	logoEMenu.Show();
	
	// Botoões do menu
	botaoUmJog.Show();
	botaoDoisJog.Show(); 
	botaoCredit.Show();
	
	outtextxy(BOTAO1_X + 48  ,BOTAO1_Y + (TILE_H * 2), linguagem.GetText(11)); 
	outtextxy(BOTAO1_X + 8 ,BOTAO1_Y + (TILE_W * 2) + 16, linguagem.GetText(12)); 
	outtextxy(BOTAO2_X + 56  ,BOTAO2_Y + (TILE_H * 2), linguagem.GetText(13)); 
	outtextxy(BOTAO2_X  + 16,BOTAO2_Y + (TILE_W * 2) + 16,linguagem.GetText(14));
	outtextxy(BOTAO3_X + 8  ,BOTAO3_Y + 72 , linguagem.GetText(15)); 
			
	minhaPg.Visual(); 
	
	escolha = SEM_ESCOLHA;
	while(escolha == SEM_ESCOLHA){
		
		if( botaoUmJog.CheckClick() == true)  
			escolha = MENU_UM_JOG;
			
		if(botaoDoisJog.CheckClick() == true)
			escolha = MENU_DOIS_JOG;
			
		if(botaoCredit.CheckClick() == true)	
			escolha = CREDITOS;
			
	}
	
	return escolha;
}

//============================================================================================
// Menu de um jogador
EscolhaEmMenu MenuUmJog(){
	
	EscolhaEmMenu escolha;
	escolha = SEM_ESCOLHA;
	
	while(escolha == SEM_ESCOLHA){
	
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		logoEMenu.Show();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 24,TILE_H * 11 );
		bar(TILE_W * 20, TILE_H * 12, TILE_W * 28, TILE_H * 13);
	
		// Mostra os botões 
		botaoJogar.Show();
		botaoVoltar.Show();
				
		// Mostra botões radio
		radioSpeed.ShowList();
		radioLider.ShowList();
		
		// Mostra o texto dos botões 
		outtextxy(TILE_W * 11, TILE_H * 12 + 16,linguagem.GetText(16));
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, linguagem.GetText(17));
		outtextxy(BOTAO_JOGAR_X + 8,BOTAO_JOGAR_Y + 24,linguagem.GetText(18));
		outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,linguagem.GetText(19));
		
		minhaPg.Visual();
		
		// Verifica clicks nos botões rádio
		radioSpeed.CheckClick();
		radioLider.CheckClick();
		
		
		// --------------- Processamento do botão Jogar===================
		if(botaoJogar.CheckClick() == true){
			escolha = UM_JOGADOR;			
				
			if( radioLider.RadioChecked()->label == "Roosevelt"){
				ladoMeuJog = LADOEUA;
				ladoOutroJog = LADOURSS;
			} 
			else{
				ladoMeuJog = LADOURSS;
				ladoOutroJog = LADOEUA;
			}
				
				
			if(radioSpeed.RadioChecked()->label == "4")
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

//============================================================================================
// Desenha o logo e menu
void CarregaLogoMenu(){
	menu.Show();
	Logo(LOGOY1);
}


//===================================================================================================
// Mostra o logo do jogo
void Logo(int tileYSeek)
{
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	settextstyle(BOLD_FONT,HORIZ_DIR,7);
	setcolor(GREEN);
	outtextxy(LOGO_X,tileYSeek,"SEEK OF PEACE");
	setcolor(DARKGRAY);
	outtextxy(LOGO2_X,tileYSeek + TILE_H  * 3 - 16,"COLD WW2");
	setfillstyle(1,LIGHTGRAY);
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	setcolor(LIGHTGREEN);	
}

//============================================================================================
// Menu do cliente
EscolhaEmMenu MenuCliente(){
	
	EscolhaEmMenu escolha;
	bool ipEPortaDefault;

	
	//==============================================
	// Dados do display, que são mostrados após a conexão 
	char nomeMeuLider[30];
	char liderDele[30];		
	char velocidJogo[27];
	
	//===============================================
	// Variáveis utilziadas para destrinchar o pacote que foi recebido
	char c, temp[2], buffer[15], ipEPorta[25];
	TipoPacote tipoPacote;
	int i;						
	//================================================
	
	strcpy(nomeMeuLider, linguagem.GetText(49));
	strcpy(liderDele, linguagem.GetText(50));
	strcpy(velocidJogo, linguagem.GetText(17));
	
	escolha = SEM_ESCOLHA;
	
	ipEPortaDefault = true;
	while(escolha == SEM_ESCOLHA){
		
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		logoEMenu.Show();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 27,TILE_H * 12 );
		
		// Informações do jogo
		if(minhaRede.clienteConectado == true){
			bar(TILE_W * 12, TILE_H * 14, TILE_W * 26, TILE_H * 17);
			setcolor(LIGHTBLUE);
			outtextxy(TILE_W * 12 + 8,TILE_H * 14 + 16,nomeMeuLider);
			setcolor(LIGHTRED);
			outtextxy(TILE_W * 12 + 8,TILE_H * 15 + 16 ,liderDele);
			setcolor(LIGHTGREEN);
			outtextxy(TILE_W * 12 + 8,TILE_H * 16 + 16 ,velocidJogo);	
		}
		
		
		// Mostra botões
		botaoVoltar.Show();
		botaoJogar.Show();
		
		// Mostra radio buttons
		radioModoIP.ShowList();
		
		if(	radioModoIP.RadioChecked()->label  == linguagem.GetText(21) && minhaRede.clienteConectado == false ){
			botaoAlterar.Show();
			outtextxy(botaoAlterar.x + 16,botaoAlterar.y + 20 , linguagem.GetText(22));
		}
		
		if(radioModoIP.RadioChecked()->label == linguagem.GetText(20) && ipEPortaDefault == false){
			ipEPortaDefault = true;
			ConfigIPEPorta();
		}
				
		
		// Processa e mostra texto
		strcpy(ipEPorta,ipDoServidor);
		strcat(ipEPorta,":");
		strcat(ipEPorta,portaDoServidor);
		outtextxy(TILE_W * 11, TILE_H * 10 + 24, linguagem.GetText(23));
		outtextxy(TILE_W * 27 + 8, TILE_H * 10 + 24, ipEPorta);
		outtextxy(botaoJogar.x + 8,botaoJogar.y + 24,linguagem.GetText(18));
		outtextxy(botaoVoltar.x + 4,botaoVoltar.y + 24,linguagem.GetText(19));
		
		if(minhaRede.clienteConectado == false)
		{
			botaoConexao.Show();
			outtextxy(botaoConexao.x + 16,botaoConexao.y + 24,linguagem.GetText(24));
		} 
		
		else
		{
			outtextxy(botaoConexao.x - 32,botaoConexao.y + 24,linguagem.GetText(25));
		}
		
		minhaPg.Visual();
		
		if(radioModoIP.RadioChecked()->label  == linguagem.GetText(21) && minhaRede.clienteConectado == false){
			if(botaoAlterar.CheckClick() == true){
				
				ipEPortaDefault = false;

				setcolor(YELLOW);
				outtextxy(botaoVoltar.x, botaoVoltar.y + 64, linguagem.GetText(26));
				cout << endl << endl << endl <<
				linguagem.GetText(27) << endl << linguagem.GetText(28);
				cin >> ipDoServidor;
				cout << linguagem.GetText(29);
				cin >> portaDoServidor;
				cout << linguagem.GetText(30) << endl << linguagem.GetText(31) <<
				ipDoServidor << endl << linguagem.GetText(32) << portaDoServidor << endl; 
			}
		}
		
		
		//Verificação de entrada nos radio buttons				
		if(minhaRede.clienteConectado == false)
			radioModoIP.CheckClick();
			
			

		
		//===========================================================================	
		// Verificação de entrada no botão Jogar	
		
		if(botaoJogar.CheckClick() == true){
			
			if(minhaRede.clienteConectado == true){
				if(minhaRede.EnviaParaOServer("CLIENT_OK|true|") == true){
					
					setcolor(YELLOW);
					outtextxy(botaoVoltar.x, botaoVoltar.y + 64, linguagem.GetText(33));
					delay(750);
					
					if(minhaRede.RecebeDoServer() == true){
						
						//===========================================================
						// Análise do pacote que o servidor envia para inciar o jogo
						//===========================================================
													
						c = minhaRede.pacote[0];
						i = 0;
						tipoPacote = SEM_TIPO;
						strcpy(buffer,"");	
						
						while(c != '\0'){
							
							if(c == '|' && tipoPacote == SEM_TIPO){
								
								if(strcmp(buffer,"SERVER_OK") == 0){
									tipoPacote = SERVER_OK;
								}
								
								strcpy(buffer,"");
								
							} else if(c == '|' && tipoPacote != SEM_TIPO){
								
								if(tipoPacote == SERVER_OK){
									if(strcmp(buffer,"true") == 0){
										
										minhaRede.servOk = true;
										escolha = DOIS_JOGADORES; 
										
									} 
									else if(strcmp(buffer,"false") == 0){
										minhaRede.servOk = false;
									}
								}
								strcpy(buffer,"");
								tipoPacote = SEM_TIPO;	
								
							} else{
								temp[0] = c;
								temp[1] = '\0';
								strcat(buffer,temp);
							}
							
							i++;
							c = minhaRede.pacote[i];	
						}
					}
			
				
				}		
			}
			 else{
				setcolor(LIGHTRED);
				outtextxy(botaoVoltar.x, botaoVoltar.y + 64, linguagem.GetText(34));
				delay(750);
			}
		}
		
		
		//=================================================================================
		// Verificação de entrada no botão Conectar/Conecta
		else if(botaoConexao.CheckClick() == true){

			if(minhaRede.clienteConectado == false){
				
				minhaRede.ClientInit(ipDoServidor,atoi(portaDoServidor));
				
				if(minhaRede.clienteInit == true){
										
					minhaRede.ConectaServer();
					
					if(minhaRede.clienteConectado == true){
					
						if(minhaRede.RecebeDoServer() == true){
													
							//==============================================
							// Análise do pacote de configuração de jogo
							//==============================================
							c = minhaRede.pacote[0];
							i = 0;
							tipoPacote = SEM_TIPO;
							strcpy(buffer,"");
							
							while(c != '\0'){
			
								if(c == '|' && tipoPacote == SEM_TIPO){
									
																
									if(strcmp(buffer,"LIDER") == 0){
										tipoPacote = LIDER_SERV;	
									}
									
									else if(strcmp(buffer,"GAMESPEED") == 0){
										tipoPacote = GAMESPEED;
									}
									
									strcpy(buffer,"");
								} 
								
								else if(c == '|' && tipoPacote != SEM_TIPO){
									
									if(tipoPacote == LIDER_SERV){
										strcat(liderDele,buffer);
										
										if(strcmp(buffer,"Stalin") == 0){
											strcat(nomeMeuLider,"Roosevelt");
											ladoMeuJog = LADOEUA;
											ladoOutroJog = LADOURSS;
										} 
										
										else{
											strcat(nomeMeuLider,"Stalin");
											ladoMeuJog = LADOURSS;
											ladoOutroJog = LADOEUA;
										}			
									}
									
									else if(tipoPacote == GAMESPEED){
										
										strcat(velocidJogo,buffer);
										
										if(strcmp(buffer,"4") == 0)
											gameSpeed = 4;
										 else
											gameSpeed = 8;										
									}
									
								strcpy(buffer,"");	
								tipoPacote = SEM_TIPO;
								}
								else{
									temp[0] = c;
									temp[1] = '\0';
									strcat(buffer,temp);	
								}
								
								i++;
								c = minhaRede.pacote[i];
							}				
						}
					}
				} 		
			} 		
		}		
		else if(botaoVoltar.CheckClick() == true){

			escolha = MENU_DOIS_JOG;
			delay(150);
		}
		
	}
	
	return escolha;

}

//============================================================================================
EscolhaEmMenu MenuServidor(){
	
	char pacote[30], tempGmSpeed[2], *tempLider;
	char buffer[15];
	TipoPacote tipoPacote;
	char c;
	int i;
	char temp[2];
	
	// Inicializa as flags e o servidor
	minhaRede.FlagsInit();
	
	minhaRede.ServerInit(atoi(portaDoServidor));
	
	EscolhaEmMenu escolha;
	escolha = SEM_ESCOLHA;
	
	
	while(escolha == SEM_ESCOLHA){
			
		minhaPg.Troca();
		minhaPg.Ativa();
		
		cleardevice();
		
		// Desenha o background básico do menu
		logoEMenu.Show();
				
		// Barras de contraste para os botões radio
		setfillstyle(1,BLACK);
		setcolor(BLACK);
		bar(TILE_W * 20, TILE_H * 10,TILE_W * 24,TILE_H * 11 );
		bar(TILE_W * 20, TILE_H * 12, TILE_W * 28, TILE_H * 13);
		bar(TILE_W * 20, TILE_H * 14, TILE_W * 32, TILE_H * 17);
	
		// Mostra os botões 
		botaoJogar.Show();
		botaoVoltar.Show();
				
		// Mostra botões radio
		radioSpeed.ShowList();
		radioLider.ShowList();
		
		// Mostra o texto dos botões 
		outtextxy(TILE_W * 11, TILE_H * 12 + 16,linguagem.GetText(16) );
		outtextxy(TILE_W * 11, TILE_H * 10 + 24,linguagem.GetText(17));
		outtextxy(BOTAO_JOGAR_X + 8,BOTAO_JOGAR_Y + 24,linguagem.GetText(18));
		outtextxy(BOTAO_VOLTAR_X + 4,BOTAO_VOLTAR_Y + 24,linguagem.GetText(19));
		
		
		// Botão de conexão
		if(minhaRede.clienteConectado == false){
			botaoOpcaoServ.Show();
			outtextxy(botaoOpcaoServ.x + 24,botaoOpcaoServ.y + 24, linguagem.GetText(35));
			outtextxy(botaoOpcaoServ.x + 8,botaoOpcaoServ.y + 40,linguagem.GetText(43));
		}

		
		// Primeira mensagem do log
		if(minhaRede.servidorInit == true){
			setcolor(LIGHTGREEN);
			outtextxy(TILE_W * 20, TILE_H * 14 + 16, linguagem.GetText(37));
		} else{
			setcolor(LIGHTRED);
			outtextxy(TILE_W * 20, TILE_H * 14 + 16, linguagem.GetText(38));
		}
		
		
		// Segunda mensagem do log
		if(minhaRede.clienteConectado == true){
			setcolor(LIGHTBLUE);
			outtextxy(TILE_W * 20, TILE_H * 15 + 8, linguagem.GetText(39));
		} 
		
		minhaPg.Visual();
		
		
		// Verifica clicks nos botões rádio (funcionam apenas antes do cliente se conectar)
		if(minhaRede.clienteConectado == false){
			radioSpeed.CheckClick();
			radioLider.CheckClick();
		}

		
		
		// ============== Processamento do botão Jogar  ===================
		if(botaoJogar.CheckClick() == true){
			
			if(minhaRede.clienteOk == false){
				setcolor(YELLOW);
				outtextxy(TILE_W * 20, TILE_H * 16 + 8, linguagem.GetText(40));
				if(minhaRede.RecebeDoClient() == true){
						c = minhaRede.pacote[0];
						i = 0;
						tipoPacote = SEM_TIPO;
						strcpy(buffer,"");
						
						
						while( c != '\0' ){
							
							if( c == '|' && tipoPacote == SEM_TIPO){
								
								if(strcmp("CLIENT_OK",buffer) == 0){
									
									tipoPacote = CLIENT_OK;
								}
								
								strcpy(buffer,"");
								
							} else if(c == '|' && tipoPacote != SEM_TIPO){
								
								if(tipoPacote == CLIENT_OK){
									
									if(strcmp("true",buffer) == 0){
										minhaRede.clienteOk = true;
									} else if(strcmp("false",buffer) == 0){
										minhaRede.clienteOk = false;
									}
								}
								
								strcpy(buffer,"");
								tipoPacote = SEM_TIPO;
							}
							else{
								temp[0] = c;
								temp[1] = '\0';
								strcat(buffer,temp);
							}
							
							i++;
							c = minhaRede.pacote[i];
							
						}						
				}
				if(minhaRede.clienteOk == true){
					minhaRede.servOk = true;
					minhaRede.EnviaParaOClient("SERVER_OK|true|");
					escolha = DOIS_JOGADORES;
				}
			}
		}
	
		//===============Processamento do botão voltar =================
		if(botaoVoltar.CheckClick() == true){
			escolha = MENU_DOIS_JOG;
			delay(100);
		}
		

		
		// ===============Processamento do botão Abrir servidor===============
		if(minhaRede.clienteConectado == false){

			if(botaoOpcaoServ.CheckClick() == true){
			
				outtextxy(TILE_W * 20, TILE_H * 14 + 16, linguagem.GetText(41));
				setcolor(YELLOW);
				outtextxy(TILE_W * 20, TILE_H * 15 + 8, linguagem.GetText(42));
			
				if(minhaRede.AceitaConexaoClient() == true){
					
					strcpy(tempGmSpeed ,radioSpeed.RadioChecked()->label);
					gameSpeed = atoi(tempGmSpeed);
					tempLider = radioLider.RadioChecked()->label; 
					
					if( tempLider == "Roosevelt"){
						ladoMeuJog = LADOEUA;
						ladoOutroJog = LADOURSS;
					} 
					else{
						ladoMeuJog = LADOURSS;
						ladoOutroJog = LADOEUA;
					}
					

					strcpy(pacote,"LIDER|");
					strcat(pacote,tempLider);
					strcat(pacote,"|GAMESPEED|");
					strcat(pacote,tempGmSpeed);
					strcat(pacote,"|");									
					minhaRede.EnviaParaOClient(pacote);
				}
			}

		}
	}
	return escolha;	
}

//============================================================================================
// Carrrega o IP e a porta definida no arquivo config.txt
void ConfigIPEPorta(){

	std::ifstream leitor;
	char c, temp[2], buffer[20];
	LeituraIPEPorta leitura;
	bool registra;
	
	strcpy(ipDoServidor,LOCALHOST);
	itoa(PORTA_PADRAO,portaDoServidor,10);
	
	leitor.open("txt/config.txt");
	
	if(!leitor.is_open())
		return;
	
	
	strcpy(buffer,"");
	leitura = SEM_LEITURA;
	registra = false;
	
	while(leitor.get(c)){
					
		if(c == '=' && leitura == SEM_LEITURA ){
			
			if(strcmp(buffer,"IP") == 0){
				leitura = LEITURA_IP;
			}
			
			else if(strcmp(buffer,"PORT") == 0){
				leitura = LEITURA_PORTA;
			}
			
			strcpy(buffer,"");
		}
		
		else if(c == '\"'){
			
			if(registra == false){ // Abre aspas
				registra = true;
				strcpy(buffer,"");
			}
			else{
				registra = false; // Fecha aspas
				
				if(leitura == LEITURA_IP)
					strcpy(ipDoServidor,buffer);
				else if(leitura == LEITURA_PORTA)
					strcpy(portaDoServidor,buffer);	
				strcpy(buffer,"");
				leitura = SEM_LEITURA;
			}
			
		}
		
		else if(c != '\n' && c != ' '){
			temp[0] = c;
			temp[1] = '\0';
 			strcat(buffer,temp);
		}
			
	}
	
	leitor.close();

}


//============================================================================================
// Mostra uma tela de Gameover no lado passado como parâmetro
void TelaGameOver(char *lado){
	
	if(lado == LADOEUA){
		telaPretaD.Show();
		setcolor(RED);
		outtextxy(TILE_W * 28 + 16, TILE_H * 8, "GAMEOVER"); 
		putimage(TILE_W * 29 + 16 ,TILE_H * 10,eixoVsOutroJog.lider.imagens[BRAVO],0);			
	
	} 
	
	else if(lado == LADOURSS){
		
		telaPretaE.Show();
		setcolor(RED);
		outtextxy(TILE_W * 7 + 16, TILE_H * 8, "GAMEOVER"); 
		putimage(TILE_W * 8  + 16 ,TILE_H * 10,eixoVsMeuJog.lider.imagens[BRAVO],0);
			
	}
	
}

//===================================================================================
//Mostra a tela de créditos do jogo
EscolhaEmMenu TelaCreditos(){
	EscolhaEmMenu escolha;
	
	minhaPg.Troca();
	minhaPg.Ativa();
	cleardevice();
	menu.Show();
	botaoVoltar2.Show();
	setfillstyle(1,BLACK);
	
	outtextxy(botaoVoltar2.x + 4 ,botaoVoltar2.y + 24,linguagem.GetText(3));
	textoCreditos.GoTo(TILE_W  * 16 + 16 , TILE_H * 2 + 16);
	textoCreditos.Show();
	
	setcolor(LIGHTGREEN);
	outtextxy(16 , TILE_H * 6, linguagem.GetText(44));
	outtextxy(TILE_W * 13 , TILE_H * 6, "KELVIN OLIVEIRA");
	outtextxy(TILE_W * 3 + 16 , TILE_H * 8, linguagem.GetText(45));
	outtextxy(TILE_W * 13 , TILE_H * 8, "CHRISTIAN MOURA");
	outtextxy(TILE_W * 3 + 4 , TILE_H * 10, linguagem.GetText(47));
	outtextxy(TILE_W * 13, TILE_H * 10, "ANDERSON ARAUJO");
	outtextxy(TILE_W * 1 + 16  , TILE_H * 12, linguagem.GetText(46));
	outtextxy(TILE_W * 13, TILE_H * 12, " THE STAR SPANGLED BANNER / DIE FAHNE HOCH / SOVIET UNION ANTHEM ");
	outtextxy(TILE_W * 15 + 16 , TILE_H * 15, linguagem.GetText(48));
	outtextxy(TILE_W * 5 + 16 , TILE_H * 17, "ADRIANO FELIX / MARCELO HENRIQUE / SÉRGIO SCHAPOWAL / VICTOR AMARAL");

	minhaPg.Visual();
	
	
	escolha = SEM_ESCOLHA;
	while(escolha == SEM_ESCOLHA){
	
		if(botaoVoltar2.CheckClick() == true)
			escolha = MENU;
	}
	
	return escolha;
	
}

// Mostra o título da tela de créidtos
void TextoCreditos()
{
	cleardevice();
	setcolor(GREEN);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(BOLD_FONT,HORIZ_DIR,5);
	outtextxy(2, 0, linguagem.GetText(15));
	textoCreditos.Init(0,0,TILE_W * 8,TILE_H * 1 + 16);
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
}

// Menu do jogo para o modo splitscreen
EscolhaEmMenu MenuSplitscreen()
{
	
	int i, jogNSold[2], jogNTorre[2];
	bool badPos;
	EscolhaEmMenu escolha;
	
	gameSpeed = 8;
	minhaPg.Troca();
	minhaPg.Ativa();
	
	meuJog.Init(LADOURSS,&gameSpeed);
	outroJog.Init(LADOEUA,&gameSpeed);
	eixoVsMeuJog.Init();	
	cleardevice();
	splitscreen.Show();
	minhaPg.Visual();

	cursor[0].Init(&cenario, &meuJog,&imgCursor1);
	cursor[1].Init(&cenario,&outroJog,&imgCursor2);
	ladoMeuJog = meuJog.lado;
	ladoOutroJog = outroJog.lado;
	
	for(i = 0; i < 2; i++)
	{
		cursor[i].helpMode = true;
		cursor[i].meuJog->dinheiro = 1000;	
		jogNSold[i] = 0;
		jogNTorre[i] = 0;
	}
	badPos = false;	

	escolha = SEM_ESCOLHA;
	
	while(escolha == SEM_ESCOLHA)
	{
		minhaPg.Troca();
		minhaPg.Ativa();
		cleardevice();
		splitscreen.Show();
		
		
		DefesaTorre(&meuJog,&outroJog,&eixoVsMeuJog,true);
		DefesaTorre(&outroJog,&meuJog,&eixoVsMeuJog,true);
		EnviaSold(&meuJog,&outroJog,cenario);
		EnviaSold(&outroJog,&meuJog,cenario);
		
		meuJog.MostraGUI(MULTIPLAYER_SPLIT);
		outroJog.MostraGUI(MULTIPLAYER_SPLIT);
		setcolor(YELLOW);
		outtextxy(TILE_W * 11, TILE_H * 19  + 8,linguagem.GetText(113));
	
		
		for(i = 0; i < 2; i++)
		{
			cursor[i].Show();
			
			if(jogNTorre[i] >= 1 && jogNSold[i] >= 1)
			{
				
				cursor[i].meuJog->lider.Show();

				if(cursor[i].meuJog->lado == LADOEUA)
				{
					setcolor(LIGHTGREEN);
					outtextxy(outroJog.lider.x - 180 ,outroJog.lider.y - 20,linguagem.GetText(112));
				}
				
				else
				{
					setcolor(WHITE);
					outtextxy(meuJog.lider.x + 20,meuJog.lider.y - 20,linguagem.GetText(111));			
				}
				
			}
			
			if(GetKeyState(VK_ESCAPE) & 0x80){
				escolha = MENU_DOIS_JOG;
			}
			
		}
		
		RotinaItemSplitscreen(jogNSold,jogNTorre);

		
		limpa2Tiles.Show();
		minhaPg.Visual();
		delay(FPS);
	
		
		if(jogNTorre[0] >= 1 && jogNTorre[1] >= 1 && 
		jogNSold[0] >= 1 && jogNSold[1] >= 1)
		{
			escolha = SPLITSCREEN;
		}
		
		
		
	}
	
	LimpaMemoria(TUTORIAL_SPLIT);
	
	cursor[0].Init(&cenario, &meuJog,&imgCursor1);
	cursor[1].Init(&cenario,&outroJog,&imgCursor2);
	
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	
	return escolha;
}


// Limpa a memória alocada dinamicamente
void LimpaMemoria(TipoGameplay tipoGm)
{
	
	meuJog.soldado0->LimpaNo(meuJog.soldado0);
	outroJog.soldado0->LimpaNo(outroJog.soldado0);
	meuJog.torre0->LimpaNo(meuJog.torre0);
	outroJog.torre0->LimpaNo(outroJog.torre0);

	
	if(tipoGm != TUTORIAL_SPLIT )
	{	
		eixoVsMeuJog.soldado0->LimpaNo(eixoVsMeuJog.soldado0);
		eixoVsOutroJog.soldado0->LimpaNo(eixoVsOutroJog.soldado0);	
	}
}


// Processamento que deve ser realizado para utilizar itens no modo
// splitscreen
void RotinaItemSplitscreen(int *qtdSold, int *qtdTorre)
{
	
	int i;
	
	for(i = 0; i < 2; i++)
	{
		cursor[i].CheckInput();
					
		if(cursor[i].AnyItemWasUsed())
		{
				
			if(cursor[i].tipo == C_SOLDADO)
			{
				if(cursor[i].meuJog->envioSold.PassouDelay(ESPERA_DELAY) == true)
				{				
					if(cursor[i].meuJog->Compra(PRECO_SOLDADO) == true)
					{
						
						cursor[i].meuJog->envioSold.Atualiza();

						cursor[i].meuJog->soldado0->Insere(cursor[i].meuJog->soldado0,
						&cursor[i].meuJog->soldGUI,gameSpeed);
						qtdSold[i]++;
					}
					
					else
					{
						cursor[i].faltaDinSold = true;
					}					
				}			
			}
				
			else if(cursor[i].tipo == C_TORRE)
			{
				
				if(cenario.CheckPosTorre(cursor[i].tileX,cursor[i].tileY,
				cursor[i].meuJog->lado) == true	)			
				{
					
					if(cursor[i].meuJog->torre0->SemTorrePerto(cursor[i].meuJog->torre0,
					cursor[i].meuX, cursor[i].meuY) == true)
					{
						
						if(cursor[i].meuJog->Compra(PRECO_TORRE))
						{
							cursor[i].meuJog->torre0->Insere(cursor[i].meuJog->torre0,
							cursor[i].meuJog->lado,cursor[i].meuX,cursor[i].meuY);
							qtdTorre[i]++;		
						}
						else
						{
							cursor[i].faltaDinTorre = true;
						}
	
					}
					
					else
					{
						cursor[i].posInvalid = true;
					}
			
				}
				
				else
				{
					cursor[i].posInvalid = true;
				}
				
			}
				
		}
		
	}
}

// Carrega a tela de splitscreen
void CarregaSplitsceen()
{		
	campoJogo.Show();
	Logo(LOGOY2);		
}

