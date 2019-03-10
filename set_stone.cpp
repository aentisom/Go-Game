
#include <iostream>
#include <vector>
#include <algorithm>
#include "set_stone.h"
#include "game.h"





using namespace std;



GoGame::GoGame(void) : Game(), isKo(false) { }



int Piece::delPiece() {
    for (int i=0; i<piece.size(); i++) {
        goGame->board.get(piece[i]) = SPACE;
        goGame->lastDel = piece[i];
    }
    return piece.size();
}


Piece::Piece( Pos pos, bool ifSet) {
    if (ifSet) goGame->board.get(pos) = (goGame->is_black ? BLACK : WHITE);
    color = goGame->board.get(pos);
    Piece_(pos);
    if (ifSet) goGame->board.get(pos) = SPACE;
    
}

void Piece::Piece_(Pos pos) {

    if (!pos.is_in_board()) return;
    if (find(piece.begin(), piece.end(), pos) != piece.end()) return ;
    if (find(liberty.begin(), liberty.end(), pos) != liberty.end()) return ;

    char thisPoint = goGame->board.get(pos);

    if (color == BLACK && thisPoint == WHITE ||
     color == WHITE && thisPoint == BLACK) return ;

    if (thisPoint == SPACE) {
        liberty.push_back(pos);
        return ;
    } 
    else if (thisPoint == color) {
        piece.push_back(pos);
    }
    else cout<<"Piece_ Error"<<endl;

    Piece_({pos.h, pos.w+1});
    Piece_({pos.h, pos.w-1});
    Piece_({pos.h+1, pos.w});
    Piece_({pos.h-1, pos.w});

    return ;
}

int GoGame::delAroundPiece(Pos pos) {
    int delNum = 0;
    char col = is_black ? BLACK : WHITE;

    Piece r({pos.h, pos.w+1}, false);
    if (r.color != col && r.liberty.size() == 1) delNum += r.delPiece();

    Piece l({pos.h, pos.w-1}, false);
    if (l.color != col && l.liberty.size() == 1) delNum += l.delPiece();

    Piece d({pos.h+1, pos.w}, false);
    if (d.color != col && d.liberty.size() == 1) delNum += d.delPiece();

    Piece u({pos.h-1, pos.w}, false);
    if (u.color != col && u.liberty.size() == 1) delNum += u.delPiece();

    return delNum;
}

    
int GoGame::set_stone(Pos pos) 
{
    if (isKo && pos == ko) {
        return 1;
    }

    int delNum = delAroundPiece(pos);
    Piece ifSetPiece(pos, true); 

    if (delNum == 0 && ifSetPiece.liberty.size() == 0) {
        return 2;
    }
    

    if (delNum == 1 && ifSetPiece.liberty.size() == 1 && ifSetPiece.piece.size() == 1) {
        ko = lastDel;
        isKo = true;
    }
    
    else isKo = false;   
    return 0;
}

void GoGame::act(Command c) {
	Pos new_pos;
	switch (c) {
	case Set:
		if (board.get(cursor) == SPACE) {
            switch(set_stone(cursor)) {
                case 0: break;
                case 1: return ;
                case 2: return ;
            }
			if (is_black) board.get(cursor) = BLACK;
			else board.get(cursor) = WHITE;
			is_black = !is_black;
		}
		break;
	case Up:
		new_pos = (Pos){ cursor.h - 1, cursor.w };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Right:
		new_pos = (Pos){ cursor.h, cursor.w + 1 };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Left:
		new_pos = (Pos){ cursor.h, cursor.w - 1 };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	case Down:
		new_pos = (Pos){ cursor.h + 1, cursor.w };
		if (new_pos.is_in_board()) cursor = new_pos;
		break;
	}
}