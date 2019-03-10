#include <iostream>
#include "game.h"

using namespace std;

Game::Game(bool is_black_, Pos cur) : is_black(is_black_) , cursor(cur){
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			Pos pos{ i, j };
			if (!pos.is_in_board()) board.get(pos) = WALL;
			else board.get(pos) = SPACE;
		}
	}
	// game_over = false;
}

void Game::act(Command c) {
	Pos new_pos;
	switch (c) {
	case Set:
		if (board.get(cursor) == SPACE) {
			if (is_black) board.get(cursor) = BLACK;
			else board.get(cursor) = WHITE;
			is_black = !is_black;
		}
		break;
	case Up:
		new_pos = { cursor.h - 1, cursor.w };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Right:
		new_pos = { cursor.h, cursor.w + 1 };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Left:
		new_pos = { cursor.h, cursor.w - 1 };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Down:
		new_pos = { cursor.h + 1, cursor.w };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	}
}

void Game::refresh(void) {
	system("cls");
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (i != cursor.h || j != cursor.w) {
				cout << board[i][j];
			}
			else {
				cout << CURSOR;
			}
			cout << ' ';
		}
		cout << endl;
	}
	// if (game_over) cout << (is_black ? "White" : "Black") << " Won The Game" << endl;
}