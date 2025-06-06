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

        vector<string> Solver::solver(vector<Piece*> pieces, vector<vector<Piece*>> board, vector<string> solution_set);

    public:
        Solver();

        Solver(int boardSize);

        void board_setup();

        void solve();

        void add_piece(Piece* piece);

        void capture_piece(Piece* piece, vector<Piece*> pieces);

        void place_piece(int x, int y, char piece_name);
};

#endif