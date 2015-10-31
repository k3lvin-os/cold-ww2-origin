#include <iostream>
#include <stdlib.h> // Para gerar n�meros aleat�rios
#include <fstream> // E / S de arquivos
#include <iomanip> // Para ler em caracter a caracter
#include <time.h> // Para trabalhar com o tempo
#include <math.h> // Para usar a fun��o potencia��o e raiz quadrada
#include <windows.h> // Para trabalhar com fun��es de som do Windows
#include <graphics.h>

// Fun��es que N�O utilizam as estruturas dos arquivos header
void Carrega(void *arrayImg, void *arrayMask, char *rPath);
void GetImage(void** pImg, char path[], int width, int height);
void* GetImage(char path[], int width, int height);

// Bibliotecas criados pela equipe de desenvolvimento
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
#include "..\..\header\barra_vida.h"


/*Fun��es que utilizam as fun��es dos arquivos header*/
void EnviaSold(Jogador *meuJog, Jogador *outroJog, CampoJogo meuCampo);
void Avisa(TDelay gameTime, Lider Hitler);
void MostraLideres(Lider *meuLider, Lider *outroLider);
void Aviso(int posX, int posY, char * msg, int color, Lider hitler);
void DefesaTorre(Jogador *meuJog, Jogador *outroJog, Jogador *eixoIA);
bool SemTorrePerto(Torre *torre0, int tileCimaX,int tileCimaY);

using namespace std;
int main(){
	
	// Declara��o de vari�veis
	Jogador meuJog,  outroJog, eixoIA;
	char onda;
	int mouseX, mouseY;
	CampoJogo meuCampo;
	Pagina minhaPg;
	bool gameLoop = true;
	time_t agora = NULL;
	TDelay gameTime;
	OndaEixo ondaEixo;
	int teste = 2;
	Grade minhaGrd;
		
	// Fornece uma seed para o gerador de n�meros pseudoaleat�rios
	srand(time(NULL));

	// Inicialize a janela gr�fica
	initwindow(TELA_W,TELA_H, "Seek Of Peace: Cold WW2");

	minhaPg.Init();	// Inicializa a estrutura p�gina
	minhaPg.Troca();	// Troca a p�gina atual

	// Trabalha com a p�gina nos "bastidores"
	minhaPg.Ativa();
	
	// Atribui times aos jogadores
	meuJog.Init(LADO1);
	outroJog.Init(LADO2);
	eixoIA.Init(LADO3);
	
	// Inicializa gerenciador de ondas do eixo
	ondaEixo.Init(&eixoIA);
	
	// Inicializa��o do campo de jogo a partir de um arquivo de coordenadas
	meuCampo.Init("mapa05.txt");
	
	// Mostra campo de jogo
	meuCampo.Mostrar();
	
	// Deixa a p�gina visual
	minhaPg.Visual();
	
	// Come�a a contar o tempo de jogo
	gameTime.Atualiza();
	
	// M�sica do gameplay 
	PlaySound("../../Assets/Music/gameplay.wav",NULL,SND_LOOP | SND_ASYNC);	
		
	//Loop do jogo
	while(gameLoop == true){
	
		
		// Troca e ativa uma nova p�gina para modifica��es
		minhaPg.Troca();
		minhaPg.Ativa();
		
		// Limpa a tela
		cleardevice();
		
		// Mostra campo de jogo	
		meuCampo.Mostrar();	
		
		// Mostra gui do jogador
		meuJog.MostraGUI(); 
	
		// Verifica se � hora de enviar uma onda de soldados do Eixo
		onda = gameTime.SoldOnda();	
		
		// Verifica o tipo de envio de soldados do Eixo
		ondaEixo.Verifica(onda,meuJog.lado,meuCampo);

		// Avisa momentos importantes para o jogador
		Avisa(gameTime, eixoIA.lider);
			
		// Verifica o input do usu�rio com a GUI
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
							
		//Deixa a p�gina visual
		minhaPg.Visual();
	
		// Delay de FPS
		delay(FPS);	
	}
	// Libera a mem�ria
	meuCampo.LimpaMem();
	meuJog.soldado0->LimpaNo(meuJog.soldado0);
	outroJog.soldado0->LimpaNo(outroJog.soldado0);
	eixoIA.soldado0->LimpaNo(eixoIA.soldado0);
	meuJog.torre0->LimpaNo(meuJog.torre0);
	outroJog.torre0->LimpaNo(outroJog.torre0);
	eixoIA.torre0->LimpaNo(eixoIA.torre0);
	
	closegraph();
	return 0;	
}


/*Fun��es*/

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
		Aviso(480,30,"Cuidado! A� vem o primeiro soldado do Eixo", YELLOW,Hitler);
				
	else if(gTimeInt >= ONDA2 && gTimeInt <= ONDA2 + 2)
		Aviso(480,30,"Faltam 3 m para o ataque final do EIXO",YELLOW,Hitler);
	
	else if(gTimeInt >= ONDA5 && gTimeInt <= ONDA5 + 2)
		Aviso(480,30,"Faltam 2 m para o ataque final do EIXO",YELLOW,Hitler);

	else if(gTimeInt >= ONDA8 && gTimeInt <= ONDA8 + 2)
		Aviso(480,30,"Falta 1 m para o ataque final do EIXO",YELLOW,Hitler);

	else if(gTimeInt >= ONDA10 && gTimeInt <= ONDA10 + 2)
		Aviso(480,30,"� hora do ataque final do EIXO...",YELLOW,Hitler);

	else if(gTimeInt >= END && gTimeInt <= END + 2)
		Aviso(590,10,"Fim de Jogo.", YELLOW, Hitler);
}

/*Busca uma imagem com as informa��es passadas por par�metro*/
void GetImage(void** pImg, char path[], int width, int height){
	
	// L� e coloca na tela uma imagem
	readimagefile(path,0,0,width,height); 
	
	/// Calcula o tamanho da imagem com base na posi��o
	int size = imagesize(0,0,width,height);
	
	// Aloca mem�ria para a vari�vel que vai recebe-la
	*pImg = malloc(size);
	
	// Recebe a imagem
	getimage(0,0,width,height,*pImg); 
}


/*Mostra os l�ders/ avatares dos jogadores*/
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

/*Busca e retorna uma imagem com as informa��es passadas por par�metro*/
void* GetImage(char path[], int width, int height){
		
	void *pImg;
	readimagefile(path,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	pImg = malloc(size);
	getimage(0,0,width,height,pImg); 
	return pImg;
}	


/*Texto e outros recursos gr�ficos mostrados pela fun��o Avisa*/
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


