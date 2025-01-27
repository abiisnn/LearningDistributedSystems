/*
	Compilar:
	gcc gfx.c -c 
	g++ animacion.cpp -c
	g++ gfx.0 animacion.o -o animacion 1X11
*/
#include "gfx.h"
#include<unistd.h>
using namespace std;

int main() {
	int t;
	gfx_open(800, 600, "Ejemplo Micro Animacion GFX");
	gfx_color(0, 200, 100);

	for(t = 0; t < 100; t++) {
		gfx_clear();
		gfx_line(t*1+80, t*2+40, t*2+40, t*3+80);
		gfx_line(t*5+80, t*3+40, t*3+40, t*5+80);
		gfx_flush();
		usleep(41666); // 24 por segundo
	}
	return 0;
}