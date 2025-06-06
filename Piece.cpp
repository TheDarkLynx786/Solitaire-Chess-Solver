#include "Piece.h"

using namespace std;

char Piece::get_piece() { return piece_type; }

void Piece::set_piece(char piece) { piece_type = piece; }

pair<int, int> Piece::get_position() { return position; }

void Piece::set_position(int x, int y) {
    position.first = x;
    position.second = y;
}