#ifndef PIECE_H
#define PIECE_H

#include <string>

using namespace std;

class Piece {
    private:
        /*
        Following Algebraic Chess Notation:
            K - King
            Q - Queen
            R - Rook
            B - Bishop
            N - Knight
            P - Pawn
        */
        char piece_type;
        pair<int, int> position;
    
        public:
        Piece() {piece_type = ' ';}
    
        Piece(char piece) : piece_type(piece) {};    

        char get_piece();

        void set_piece(char piece);

        pair<int, int> get_position();

        void set_position(int x, int y);
};


#endif