

// Relação entre os números da enum/array de imagens e nomes para as imagens
enum ImgCutscenes{
	ESTATUA_TIOSAM = 0, 
	ESTATUA_LENIN,
	ESTATUA_HITLER,
	STALIN_QUADRO,
	ROOSEV_QUADRO,
	STALIN_BRAVO,
	ROOSEV_BRAVO,
	HITLER_QUADRO,
	ROOSEV_GAME,
	STALIN_GAME,
	HILTER_GAME,
	BOMBA_NUCLEAR1,
	BOMBA_NUCLEAR2,
	LIDERES_IALTA1,
	LIDERES_IALTA2,
	qtdImgCutscenes
};


// Relação entre números da enum e nomes para os finais do jogo
enum Final{
	FINAL_EUA,FINAL_URSS,FINAL_NAZI,FINAL_GUERRAFRIA, SEM_FINAL
};



// Trabalha com as animações não interativas da introdução e dos finais do jogo
struct Cutscenes{
	
	// Propriedades
	
	// Imagens utilizadas nas cutscenes
	Sprite sprites[qtdImgCutscenes];
	
	// Métodos
	void Carrega();
	void MostraFinal(Final meuFinal);
	void FinalEua();
	void FinalUrss();
	void FinalNazi();
	void FinalGuerraFria();
	bool EscreveDevagar(int x0, int y0, char* msg, int delayPorLetra, bool checkClick);
	
};


// Carrega as imagens utilizadas nas cutscenes
void Cutscenes::Carrega(){
	
	int i, indiceH, width, height;
	char pathImg[40], temp[3];
	for( i = 0; i < qtdImgCutscenes; i++){
		
		indiceH = i + 1;
	
		strcpy(pathImg,ASSETS);
		strcat(pathImg,CUTSCENES);	
			
		if(indiceH < 10)
			strcat(pathImg,"0");
			
		itoa(indiceH,temp,10);
		strcat(pathImg,temp);
		strcat(pathImg,BITMAP);

		if(indiceH >= 1 && indiceH <= 3){
			width = 513;
			height = 720;
		}
		
		else if(indiceH >= 4 && indiceH <= 8){
			width = 316;
			height = 436;			
		} 
		
		else if(indiceH >= 9 && indiceH <= 11){
			width = 64;
			height = 96;
		}
				
		else if(indiceH == 12){
			width = 682;
			height = 436;			
		}
		
		else if(indiceH == 13){
			width = 420;
			height = 573;			
		}
		
		else if(indiceH == 14){
			width = 884;
			height = 673;
		}
		
		else if(indiceH == 15)	{
			width = 608;
			height = 673;
		}	
		
		sprites[i].Init();	
		sprites[i].GetImage(pathImg,width,height);
	}
}


// Recebe um final como parâmetro e mostra o final solicitado
void Cutscenes::MostraFinal(Final meuFinal){
	
	Pagina minhaPg;
	minhaPg.Init();
	minhaPg.Troca();
	minhaPg.Ativa();
	cleardevice();
	
	if(meuFinal != FINAL_GUERRAFRIA){
		setcolor(WHITE);
		settextstyle(BOLD_FONT,HORIZ_DIR,3);
		if(meuFinal == FINAL_NAZI)
			outtextxy(TELA_W / 2 - 80,TELA_H / 2,linguagem.GetText(63));
		else if(meuFinal == FINAL_EUA)
			outtextxy(TELA_W / 2 - 80,TELA_H / 2,linguagem.GetText(64));
		else if(meuFinal == FINAL_URSS)
			outtextxy(TELA_W / 2 - 80,TELA_H / 2,linguagem.GetText(65));
		settextstyle(BOLD_FONT,HORIZ_DIR,1);
	}
	
	minhaPg.Visual();
	delay(2000);
	
	if(meuFinal == FINAL_NAZI)
		FinalNazi();
	else if(meuFinal == FINAL_URSS)
		FinalUrss();
	else if(meuFinal == FINAL_EUA)	
		FinalEua();
	else if(meuFinal == FINAL_GUERRAFRIA)
		FinalGuerraFria();
	
	PlaySound(NULL, NULL, 0); 

}




// Escreve o texto devagar com base em um delay
bool Cutscenes::EscreveDevagar(int x0, int y0, char* msg, int delayPorLetra, bool checkClick){
	
	char buffer[101], temp[2], c;
	int i, x;
	bool continua=true;
	
	if(strlen(msg) <= 100){
		
		strcpy(buffer,msg);
		i = 0;
		x = x0;
		c = buffer[0];
		
		while(c != '\0' && continua != false){
			
			temp[0] = c;
			temp[1] = '\0';
			
			if(c != ' ')
				outtextxy(x,y0,temp);		
			delay(delayPorLetra);
			
			if(c == ' ')
				x += 15;
				
			else if( c == 'â')
				x += 5;
			else
				x += 19;
			if(checkClick == true){
				if(GetKeyState(VK_LBUTTON)& 0X80)
				{
					continua = false;
				}	
			}
			
			i++;
			c = buffer[i];	
		} 
		return continua;
		
	}
	
	
}

// Mostra o final dos nazistas
void Cutscenes::FinalNazi(){
	PlaySound("../../Assets/Music/diefahne.wav",NULL,SND_LOOP | SND_ASYNC);
	Pagina minhaPg;
	minhaPg.Init();
	minhaPg.Troca();
	minhaPg.Ativa();
	setbkcolor(WHITE);
	setcolor(BLACK);
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	cleardevice();
	minhaPg.Visual();
	
	sprites[ESTATUA_HITLER].GoTo(TELA_W - 513,0);
	sprites[ESTATUA_HITLER].Show();
	delay(1500);
	
	EscreveDevagar(0,80,linguagem.GetText(66),75,false);
	EscreveDevagar(0,160,linguagem.GetText(67),75,false);
	EscreveDevagar(0,190,linguagem.GetText(68),75,false);
	delay(100);
	
	EscreveDevagar(0,270,linguagem.GetText(69),75,false);
	EscreveDevagar(0,300,linguagem.GetText(70),75,false);
	EscreveDevagar(0,330,linguagem.GetText(71),75,false);
	EscreveDevagar(0,360,linguagem.GetText(72),75,false);
	EscreveDevagar(0,390,linguagem.GetText(73),75,false);
	delay(200);
	
	EscreveDevagar(0,480,linguagem.GetText(74),75,false);
	EscreveDevagar(0,510,linguagem.GetText(75),75,false);
	EscreveDevagar(0,540,linguagem.GetText(76),75,false);
	
	delay(8000);
	setbkcolor(BLACK);
	cleardevice();
}


// Final dos Eua
void Cutscenes::FinalEua(){
	PlaySound("../../Assets/Music/star_spangled.wav",NULL,SND_LOOP | SND_ASYNC);
	Pagina minhaPg;
	minhaPg.Init();
	minhaPg.Troca();
	minhaPg.Ativa();
	
	setbkcolor(WHITE);
	setcolor(BLACK);
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	cleardevice();
	minhaPg.Visual();

	sprites[ESTATUA_TIOSAM].GoTo(TELA_W - 513, 0);
	sprites[ESTATUA_TIOSAM].Show();
	delay(1500);
	
	EscreveDevagar(0,80,linguagem.GetText(77),75,false);
	EscreveDevagar(0,110,linguagem.GetText(78),75,false);
	delay(100);

	
	EscreveDevagar(0,200,linguagem.GetText(79),75,false);
	EscreveDevagar(0,230,linguagem.GetText(80),75,false);
	EscreveDevagar(0,260,linguagem.GetText(81),75,false);
	EscreveDevagar(0,290,linguagem.GetText(82),75,false); 
	delay(200);

	EscreveDevagar(0,380,linguagem.GetText(83),75,false);
	EscreveDevagar(0,410,linguagem.GetText(84),75,false);
	EscreveDevagar(0,440,linguagem.GetText(85),75,false);
	
	delay(200);
	EscreveDevagar(0,530,linguagem.GetText(86),75,false);
	EscreveDevagar(0,560,linguagem.GetText(76),75,false);
	
	delay(2800);
	setbkcolor(BLACK);
	cleardevice();
}


void Cutscenes::FinalUrss(){
	PlaySound("../../Assets/Music/soviet-anthem.wav",NULL,SND_LOOP | SND_ASYNC);
	Pagina minhaPg;
	minhaPg.Init();
	minhaPg.Troca();
	minhaPg.Ativa();
	
	setbkcolor(WHITE);
	setcolor(BLACK);
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	cleardevice();
	minhaPg.Visual();

	sprites[ESTATUA_LENIN].GoTo(TELA_W - 513, 0);
	sprites[ESTATUA_LENIN].Show();
	delay(1500);
		
	EscreveDevagar(0,80,linguagem.GetText(87),75,false);
	EscreveDevagar(0,110,linguagem.GetText(78),75,false);
	delay(100);
	
	EscreveDevagar(0,200,linguagem.GetText(88),75,false);
	EscreveDevagar(0,230,linguagem.GetText(80),75,false);
	EscreveDevagar(0,260,linguagem.GetText(89),75,false);
	EscreveDevagar(0,290,linguagem.GetText(82),75,false); 
	delay(200);

	EscreveDevagar(0,380, linguagem.GetText(90),75,false);
	EscreveDevagar(0,410, linguagem.GetText(91),75,false);
	EscreveDevagar(0,440, linguagem.GetText(92),75,false);
	
	delay(200);
	EscreveDevagar(0,530,linguagem.GetText(86),75,false);
	EscreveDevagar(0,560,linguagem.GetText(76),75,false);


	
	
	delay(2000);
	setbkcolor(BLACK);
	cleardevice();	
}


// Final aonde os dois jogadores sobrevivem ao ataque dos nazistas
void Cutscenes::FinalGuerraFria(){
	PlaySound("../../Assets/Music/ColdWar.wav",NULL,SND_LOOP | SND_ASYNC);
	sprites[BOMBA_NUCLEAR1].GoTo(TELA_W - 717, 0);
	sprites[BOMBA_NUCLEAR1].Show();
	setcolor(WHITE);
	settextstyle(BOLD_FONT,HORIZ_DIR,3);
	
	EscreveDevagar(0, TILE_H * 16,linguagem.GetText(93),75,false);
	EscreveDevagar(0,TILE_W * 16 + 30,linguagem.GetText(94),75,false);
	delay(1000);
	
	setfillstyle(1,BLACK);
	bar(TILE_W * 0, TILE_H * 16, TILE_W * 39, TILE_H * 18);
	delay(100);
	cleardevice();
	delay(200);
	sprites[BOMBA_NUCLEAR2].Show();
	EscreveDevagar(TILE_W * 14 + 16, 30, linguagem.GetText(95),75,false);
	EscreveDevagar(TILE_W * 14 + 16, 80, linguagem.GetText(96),75,false);
	EscreveDevagar(TILE_W * 14 + 16, 130, linguagem.GetText(97),75,false);
	delay(2000);
	cleardevice();
	sprites[LIDERES_IALTA1].Show();
	settextstyle(BOLD_FONT,HORIZ_DIR,1);
	EscreveDevagar(0, TILE_H * 19 - 10, linguagem.GetText(98),75,false);
	EscreveDevagar(0,TILE_H * 19 + 30, linguagem.GetText(99),75,false);
	EscreveDevagar(0,TILE_H * 19 + 70, linguagem.GetText(100),75,false);
	delay(500);
	cleardevice();
	sprites[LIDERES_IALTA2].Show();
	settextstyle(BOLD_FONT,HORIZ_DIR,2);
	EscreveDevagar(600,30, linguagem.GetText(101),75,false);
	EscreveDevagar(600,80,linguagem.GetText(102) ,75,false);
	EscreveDevagar(600,130,linguagem.GetText(103),75,false);
	delay(250);
	sprites[ROOSEV_QUADRO].GoTo(600, 150);
	sprites[ROOSEV_QUADRO].Show();
	sprites[STALIN_QUADRO].GoTo(916, 150);
	sprites[STALIN_QUADRO].Show();
	delay(3000);
	cleardevice();
	sprites[ROOSEV_BRAVO].GoTo(802, 142);
	sprites[STALIN_BRAVO].GoTo(162, 142);	
	sprites[ROOSEV_BRAVO].Show();
	sprites[STALIN_BRAVO].Show();
	EscreveDevagar(TILE_W * 7,30,linguagem.GetText(104),75,false);
	EscreveDevagar(TILE_W * 8,60,linguagem.GetText(105),75,false);
	delay(3000);
	bar(0,0,TILE_W * 39, 100);
	delay(1000);

	delay(30);
	cleardevice();
}


