#include <graphics.h>

// Detecta e inicializa o modo gr�fico
void GraphicInit(){
	int driver, mode;
	detectgraph(&driver, &mode);
	initgraph(&driver,&mode,"");
}


