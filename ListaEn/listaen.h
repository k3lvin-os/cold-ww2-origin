/*Uma lista encadeada é uma sequência de células;
Cada célula contém um objeto de algum tipo e o
endereço da célula seguinte.*/

struct cel{
	int conteudo;
	struct cel *prox;
};


typedef struct cel Celula;

 /*Para criar uma lista vazia
 celula c, *ini;
 c.prox = NULL;
 ini = &c;
 */
 
 /*Ou, se preferir alocar dinamicamente:
 celula *ini
 ini = malloc (sizeof(celula));
 ini->prox = NULL;*/
 
 /*Protótipos das funções*/
 void Insere(int x, Celula *p);
 Celula* InsereR(int x, Celula *cel);
 void Imprime(Celula *ini);
 void Remove(Celula *p);


 

