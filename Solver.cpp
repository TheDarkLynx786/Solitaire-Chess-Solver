#include "Solver.h"
#include <iostream>

using namespace std;

Solver::Solver() {
    board_size = 4;
    board.resize(board_size);
    for(vector<Piece*> row : board) {
        row.resize(board_size);
    }
}

Solver::Solver(int boardSize) {
    board_size = boardSize;
    board.resize(board_size);
    for(vector<Piece*> row : board) {
        row.resize(board_size);
    }
}

void Solver::board_setup() {
    
}

void Solver::solve() {
    
}

void Solver::add_piece(Piece* piece) { piece_list.push_back(piece); }

void Solver::capture_piece(Piece* piece) {
    for (auto target = piece_list.begin(); target != piece_list.end(); ++target) {
        if (*target == piece) {
            piece_list.erase(target);
            break;
        }
    }
}

void Solver::place_piece(int x, int y, char piece_name) {
    if (board[x][y] != nullptr) {
        cout << "Position already occupied!" << endl;
        return;
    }
    board[x][y] = new Piece(piece_name);
}
