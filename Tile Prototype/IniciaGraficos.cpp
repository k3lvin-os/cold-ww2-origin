#include <graphics.h>

// Detecta e inicializa o modo gráfico
void GraphicInit(){
	int driver, mode;
	detectgraph(&driver, &mode);
	initgraph(&driver,&mode,"");
}


