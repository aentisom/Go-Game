#ifndef SET_STONE_H
#define SET_STONE_H

#include <vector>
#include "game.h"
using namespace std;
struct GoGame : public Game {
    bool isKo;
    Pos ko;
    Pos lastDel;
    GoGame(void);
    int delAroundPiece(Pos pos);
    void act(Command c) override;
    int set_stone(Pos pos); 
};

struct Piece {
    static GoGame * goGame;
    vector<Pos> piece;
    vector<Pos> liberty;
    char color;

    Piece(Pos pos, bool ifSet);
    void Piece_(Pos pos);
    int delPiece();
};

#endif
