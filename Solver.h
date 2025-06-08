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

        vector<string> recursive_solver(vector<Piece*> pieces, vector<vector<Piece*>> board, vector<string> solution_set);

        string coords_to_notation(int x, int y);

        vector<pair<int, int>> get_king_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);

        vector<pair<int, int>> get_queen_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);

        vector<pair<int, int>> get_bishop_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);

        vector<pair<int, int>> get_rook_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);

        vector<pair<int, int>> get_knight_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);
        
        vector<pair<int, int>> get_pawn_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board);

        void add_piece(Piece* piece);

        Piece* piece_at(int x, int y, vector<vector<Piece*>> board);

        void capture_piece(Piece* piece, vector<Piece*> pieces);

        void place_piece(int x, int y, char piece_name);
};

#endif