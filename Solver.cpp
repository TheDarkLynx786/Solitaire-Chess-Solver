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
    cout << "Set up the board with the pieces\n\n";
    
    // User Input
    string input;
    int counter = 1;
    
    while(input != "q") {
        cout << "Piece " << counter << ": " << endl;
        cout << "Enter board location in algebraic notation (e.g., \"a1\", \"b2\") or 'q' to quit: ";
        cin >> input;
        
        // Exit
        if (input == "q") { break; }
        
        // Invalid Input
        if (input.length() != 2 || char(input[0]) < 'a' || char(input[0]) > ('a' + board_size - 1) || char(input[1]) < '1' || char(input[1]) > ('1' + board_size - 1)) {
            cout << "\nInvalid input; enter a valid position in chess algebraic notation (e.g., \"a1\", \"d4\") restricted to your board size." << endl;
            continue;
        }

        // Process Input
        int x = int(char(input[0]) % 'a');
        int y = int(char(input[1]));

        // Check if position is already occupied        
        if (board.at(x).at(y) != nullptr) {
            cout << "Position already occupied!" << endl;
            continue;
        }

        // Chess Piece
        char piece_name;
        bool invalid_piece = false;
        cout << "Enter piece type (in algebraic chess notation):\n\nKey:\n"
             << "K - King\n"
             << "Q - Queen\n"
             << "R - Rook\n"
             << "B - Bishop\n"
             << "N - Knight\n"
             << "P - Pawn\n";
        cout << "---> ";
        cin >> piece_name;
        piece_name = toupper(piece_name);
        
        string piece_name_str;
        switch(piece_name) {
            case 'K':
                piece_name_str = "King";
                break;
            case 'Q':
                piece_name_str = "Queen";
                break;
            case 'R':
                piece_name_str = "Rook";
                break;
            case 'B':
                piece_name_str = "Bishop";
                break;
            case 'N':
                piece_name_str = "Knight";
                break;
            case 'P':
                piece_name_str = "Pawn";
                break;
            default:
                cout << "Invalid piece type; Enter a valid chess piece from the key." << endl;
                invalid_piece = true;
                break;
        }

        // Invalid Piece
        if (invalid_piece) { continue; }

        // Make New Piece and Add to Board
        Piece* piece = new Piece(piece_name);
        add_piece(piece);
        place_piece(x, y, piece_name);
        
        // Output
        cout << "\nPlaced a " << piece_name_str << " at " << input << "." << endl;
        counter++;
    }
    
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
    if (board.at(x).at(y) != nullptr) {
        cout << "Position already occupied!" << endl;
        return;
    }
    board.at(x).at(y) = new Piece(piece_name);
}
