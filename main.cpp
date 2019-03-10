#include <iostream>
#include <conio.h>
#include "game.h"
#include "set_stone.h"

using namespace std;

GoGame go;
GoGame * Piece::goGame = &go;

void loop(void) {

	Command c;
	do {
		go.refresh();
		if (c = (Command)getch()) {
			go.act(c);
		}
	} while (true);
}

int main()
{
	loop();
}