/*#include <graphics.h>

// Passa ,por refer�ncia,o endere�o de uma imagem
void GetImage(char name[], int width, int height, void *image){
	
	readimagefile(name,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	image = malloc(size);
	getimage(0,0,width,height,image); // Os dois 0s referem-se ao local onde a imagem ser� colocada 
}
*/
