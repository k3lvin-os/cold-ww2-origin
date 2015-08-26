#include <iostream>
#include <graphics.h>
using namespace std;

// Imprime a altura e largura da tela gráfica do BGI
void WidthHeight(){
	cout << "Largura da tela " << getmaxx() + 1 << "px\nAltura da tela " << getmaxy() + 1 << "px.";

}
