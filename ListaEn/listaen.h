/*Uma lista encadeada � uma sequ�ncia de c�lulas;
Cada c�lula cont�m um objeto de algum tipo e o
endere�o da c�lula seguinte.*/

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
 
 /*Prot�tipos das fun��es*/
 void Insere(int x, Celula *p);
 Celula* InsereR(int x, Celula *cel);
 void Imprime(Celula *ini);
 void Remove(Celula *p);


 

