/*#include <graphics.h>

// Passa ,por referência,o endereço de uma imagem
void GetImage(char name[], int width, int height, void *image){
	
	readimagefile(name,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	image = malloc(size);
	getimage(0,0,width,height,image); // Os dois 0s referem-se ao local onde a imagem será colocada 
}
*/
