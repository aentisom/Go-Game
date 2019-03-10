#include <iostream>
#include <conio.h>
#include "game.h"
#include "set_stone.h"

using namespace std;

GoGame go;
GoGame * Piece::goGame = &go;

void loop(void) {

	do {
		go.refresh();
		go.act((Command)getch());
	} while (true);
}

int main()
{
	loop();
}