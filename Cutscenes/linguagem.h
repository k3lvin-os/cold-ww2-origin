
// Idiomas do jogo
enum Idioma{
	PORTUGUES,
	INGLES,
	qtdIdioma
};

struct Linguagem{
	
	// Indica a quantidade de textos que o jogo contém
	static const int QTD_TEXTO_JOGO = 92;
	
	// Armazena os textos do jogo 
	char *texto[qtdIdioma][QTD_TEXTO_JOGO];
	Idioma idiomaAtual;
	
	
	//Funções
	char* GetText(int indiceDoTexto);
	bool CarregaIdioma(char *arquivoIdioma);
	void TextoDefault();
	void LimpaMemoria();
	
	// "Construtor"
	void Init(Idioma escolha);

	
};


// Inicializa a estrutura
void Linguagem::Init(Idioma escolha){
	
	idiomaAtual = escolha;
	
	if(escolha == PORTUGUES)
		CarregaIdioma("pt-br.txt");	
	
	else if(escolha == INGLES)
		CarregaIdioma("en.txt");		
}

// Carrega um idioma a partir de um arquivo de idioma
bool Linguagem::CarregaIdioma(char *arquivoIdioma){
	
	std::ifstream leitor;
	char c;
	bool recebeTxt, recebeNTxt;
	char buffer[70], temp[2], nTextoChar[4] ;
	int nTexto;
	
	leitor.open(arquivoIdioma);
	
	if(!leitor.is_open()){
		std::cout << "ERROR: Could not find " << arquivoIdioma << " language text file";
		return false;
	}
	
	recebeTxt = false;
	recebeNTxt = false;
	nTexto = NULL;
	strcpy(nTextoChar,"");
	strcpy(buffer,"");
	
	while(leitor.get(c)){
	
		if(c == '_' )
			recebeNTxt = true;	
		
		else if(recebeNTxt == true){
			
			if( c >= 48 && c <= 57){
				temp[0] = c;
				temp[1] = '\0';	
				strcat(nTextoChar,temp);		
			}
			else{
				nTexto = atoi(nTextoChar);
				strcpy(nTextoChar,"");
				recebeNTxt = false;
			}
		} 
		

		else if(c == '\"'){
			
			if(recebeTxt == false){
				recebeTxt = true;
			} 
			
			else{
				texto[idiomaAtual][nTexto - 1] = (char *) malloc(sizeof(buffer));
				strcpy(texto[idiomaAtual][nTexto - 1],buffer);
				// TESTE
				//std::cout << texto[idiomaAtual][nTexto - 1] << std::endl;
				strcpy(buffer,"");
				recebeTxt = false;	
			}			
		}
		
		else if(recebeTxt == true){
			temp[0] = c;
			temp[1] = '\0';
			strcat(buffer,temp);
		}

	}
	
	leitor.close();
	
	return true;
	
}

// Coloca um texto default / erro para cada texto do jogo
void Linguagem::TextoDefault(){
	int j, i;
	
	i = 0;
	while(i < qtdIdioma){
		
		j = 0;
		while(j < QTD_TEXTO_JOGO){
			texto[i][j] = "[FAIL IN TEXT LOAD]";
			j++;
		}
		i++;
	}
}

// Limpa a memória alocada para o texto do jogo
void Linguagem::LimpaMemoria(){
	int i, j;
	
	i = idiomaAtual;
	for(j = 0; j < QTD_TEXTO_JOGO; j++)
		free(texto[i][j]);
}


// Retorna o texto correspondente ao indice do idioma atual
char* Linguagem::GetText(int indiceDoTexto){
	int indiceMaquina;
	indiceMaquina = indiceDoTexto - 1;
	return texto[idiomaAtual][indiceMaquina];
}


