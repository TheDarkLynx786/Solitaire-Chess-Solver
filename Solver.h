#ifndef SOLVER_H
#define SOLVER_H

#include "Piece.h"
#include <string>
#include <vector>

using namespace std;

class Solver {
    private:
        int board_size;
        vector<vector<Piece*>> board;
        vector<Piece*> piece_list;

    public:
        Solver();

        Solver(int boardSize);

        void board_setup();

        void solve();

        void add_piece(Piece*);

        void capture_piece(Piece*);

        void place_piece(int x, int y, char piece_name);
};

#endif