// Estrutura GUI do programa editor
struct GUI{
	
	int x, y;
	
	// "Construtor" que recebe o tipo de gui e constói baseado nele
	void Init(char *nomeGUI);
		
};

// Constroi a GUI
void GUI::Init(char *nomeGUI){
		
		if(nomeGUI == "Console"){
			// GUI
			setcolor(WHITE);
			x =getmaxx() / 2 - 60;
			y = getmaxy() - 30;
			moveto( x,y);
			outtext("Use o console para gerenciar a janela gráfica");
		}
		
		if(nomeGUI == "Desenho"){
			
			// GUI
			setcolor(WHITE);
			x =getmaxx() / 2 - 60;
			y = getmaxy() - 30;
			moveto( x,y);
			outtext("MODO DESENHO (F5 para sair)");
		}
	}

