#ifndef GAME_H
#define GAME_H
constexpr auto height = 19;
constexpr auto width = 19;
constexpr auto BLACK = '*';
constexpr auto WHITE = 'O';
constexpr auto SPACE = '+';
constexpr auto CURSOR = 'X';
constexpr auto WALL = '#';
constexpr auto cursor_init_h = 10;
constexpr auto cursor_init_w = 10;







typedef enum { Set = 'j', Up = 'w', Left = 'a', Down = 's', Right = 'd', } Command;

struct Pos {
	int h;
	int w;

	inline bool is_in_board() const { return 1 <= h && h <= height && 1 <= w && w <= width; }
	bool operator==(Pos pos) {
		if (h == pos.h && w == pos.w) return true;
		else return false;
	}
};


struct map {
	char board[height + 2][width + 2];

	char ( & operator[](size_t n)) [width + 2] { return board[n]; }
	inline char & get(Pos pos) { return board[pos.h][pos.w]; }
};

struct Game {
	map board;

	Pos cursor;

	bool is_black;
	// bool game_over;

	Game(bool is_black_ = true, Pos cur = {cursor_init_h, cursor_init_w});
	virtual void act(Command c);
	void refresh(void);
};
#endif 