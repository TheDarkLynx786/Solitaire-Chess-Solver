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
    board.resize(board_size, vector<Piece*>(boardSize, nullptr));
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
        int x = (board.size()) - int(input[1]-'0'); // (board.size()) - int(input[1]-'0') ;
        int y = int(char(input[0]) % 'a');

        cout << "Row/Col Pos: " << endl << x << ", " << y << endl << endl;

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
    board_setup();
    vector<string> solution_set;

    recursive_solver(this->piece_list, this->board, solution_set);
    
}

// This algorithm will send out capture "branches," and each branch will explore a potential possible/impossible solution set."
void Solver::recursive_solver(vector<Piece*> pieces, vector<vector<Piece*>> board, vector<string>& solution_set) {
    // Print board
    for(vector<Piece*> row : board) {
        for (Piece* col : row) {
            char board_loc = (col != nullptr)? col->get_piece() : '.';
            cout << board_loc << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Base Case
    cout << "Pieces left: " << pieces.size() << endl;
    if (pieces.size() <= 1) return;

    vector<pair<int, int>> possible_captures;

    // Find ALL possible captures in this position
    for(Piece* piece : pieces) {
        
        // Get type of piece, piece position, and init possible captures list.
        char piece_type = piece->get_piece();
        pair<int, int> position = piece->get_position();
        vector<pair<int,int>> piece_possible_captures;
        
        cout << piece_type << endl;

        // Determine possible captures
        switch(piece_type) {
            case 'K':
                piece_possible_captures = get_king_capturables(position, board);
                break;
            case 'Q':
                piece_possible_captures = get_queen_capturables(position, board);
                break;
            case 'R':
                piece_possible_captures = get_rook_capturables(position, board);
                break;
            case 'B':
                piece_possible_captures = get_bishop_capturables(position, board);
                break;
            case 'N':
                piece_possible_captures = get_knight_capturables(position, board);
                break;
            case 'P':
                piece_possible_captures = get_pawn_capturables(position, board);
                break;
            default:
                break;
        }

        // Add possible piece captures to all possible captures list
        for(pair<int, int> cap_coord : piece_possible_captures) {
            // Add to possible captures list
            possible_captures.push_back(cap_coord);
        }
        
    }

    // DEBUG
    cout << endl << "Possible captures: " << endl;
    for (pair<int, int> pos : possible_captures) {
        cout << pos.first << ", " << pos.second << endl;
    }
    cout << endl << endl;
    
    // If there are no captures in this position, then return NO SOL.
    if (possible_captures.size() == 0 && pieces.size() > 1) {
        solution_set.push_back("NO SOL.");
        return;
    }
    

    for(pair<int, int> capture_coord : possible_captures) {
        

        Piece* piece = piece_at(capture_coord.first, capture_coord.second, board);
        
        // Add move to solution set branch
        string move = piece->get_piece() + "x" + coords_to_notation(capture_coord.first, capture_coord.second);
        vector<string> new_sol_set = solution_set;
        new_sol_set.push_back(move);
        
        // Capture the Piece and update the board
        vector<Piece*> new_piece_list = capture_piece( piece_at(capture_coord.first, capture_coord.second, board), pieces);
        vector<vector<Piece*>> new_board = board;
        new_board.at(capture_coord.second).at(capture_coord.first) = piece;
        
        // DEBUG
        cout << endl;
        for (string str : new_sol_set) {
            cout << str << endl;
        }
        cout << endl;

        cout << new_piece_list.size();

        // Send off a branch
        recursive_solver(new_piece_list, new_board, new_sol_set);
    }

}

string Solver::coords_to_notation(int x, int y) {
    string x_char(1, char(int(x + 'a')) );
    int y_char = y + 1;
    

    return x_char + to_string(y_char);
}


vector<pair<int, int>> Solver::get_king_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    // Check if the king has any pieces it can capture
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            int x_check = x + piece_pos.first;
            int y_check = y + piece_pos.second;
            
            // Out of Bounds
            if (x_check < 0 || x_check >= board.size() || y_check < 0 || y_check >= board.size()) continue;

            // Skip Piece Coordinate
            if (x == 0 && y ==0) continue;

            // Check if there is a capturable piece
            if (board.at(x_check).at(y_check) != nullptr) possible_captures.push_back(make_pair(x_check, y_check));
        }
    }
    return possible_captures;
}

vector<pair<int, int>> Solver::get_queen_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    // Check if the queen has any pieces it can capture
    for (int x = 0; x < board.size(); ++x) {
        for (int y = 0; y < board.size(); ++y) {
            // Skip square if not covered by queen
            if (x != piece_pos.first || y != piece_pos.second || (x - piece_pos.first) != (y - piece_pos.second) ) continue;

            // Skip the queen coordinate
            if (x == piece_pos.first && y == piece_pos.second) continue;

            // Check if there is a capturable piece
            if (board.at(x).at(y) != nullptr) possible_captures.push_back(make_pair(x,y));
        }
    }
    return possible_captures;
}

vector<pair<int, int>> Solver::get_knight_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    // Check if the knight has any pieces it can capture
    for (int x = -2; x < 3; ++x) {
        for (int y = -2; y < 3; ++y) {
            int x_check = x + piece_pos.first;
            int y_check = y + piece_pos.second;

            // Out of Bounds
            if (x_check < 0 || x_check >= board.size() || y_check < 0 || y_check >= board.size()) continue;

            // Squares that the knight does not touch
            if ( (abs(x) == 1 && abs(y) == 1) || (abs(x) == 2 && abs(y) == 2) || x == 0 || y == 0 ) continue;

            // Check if there is a capturable piece
            if (board.at(x_check).at(y_check) != nullptr) possible_captures.push_back(make_pair(x_check, y_check));
        }
    }
    return possible_captures;
}

vector<pair<int, int>> Solver::get_bishop_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    // Check if the bishop has any pieces it can capture
    for (int x = 0; x < board.size(); ++x) {
        for (int y = 0; y < board.size(); ++y) {
            // Skip any square not covered by bishop
            if ( (x - piece_pos.first) != (y - piece_pos.second) ) continue;

            // Skip the bishop coordinate
            if (x == piece_pos.first && y == piece_pos.second) continue;

            // Check if there is a capturable piece
            if (board.at(x).at(y) != nullptr) possible_captures.push_back(make_pair(x, y));
        }
    }
    return possible_captures;
}

vector<pair<int, int>> Solver::get_rook_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    // Check if the rook has any pieces it can capture
    for (int x = 0; x < board.size(); ++x) {
        for (int y = 0; y < board.size(); ++y) {
            // Skip any square not covered by rook
            if (x != piece_pos.first || y != piece_pos.second) continue;

            // Skip the rook coordinate
            if (x == piece_pos.first && y == piece_pos.second) continue;

            // Check if there is a capturable piece
            if (board.at(x).at(y) != nullptr) possible_captures.push_back(make_pair(x, y));
        }
    }
    return possible_captures;
}

vector<pair<int, int>> Solver::get_pawn_capturables(pair<int, int> piece_pos, vector<vector<Piece*>> board) {
    vector<pair<int, int>> possible_captures;
    
    // Last row edge case
    if(piece_pos.second == 0) return possible_captures;
    
    // Check if the pawn has any pieces it can capture
    int x_check_L = piece_pos.first - 1, x_check_R = piece_pos.first + 1;
    int y_check = piece_pos.second - 1;

    if(x_check_L > -1 && board.at(x_check_L).at(y_check) != nullptr) possible_captures.push_back(make_pair(x_check_L, y_check));
    if(x_check_R < board.size() && board.at(x_check_R).at(y_check) != nullptr) possible_captures.push_back(make_pair(x_check_R, y_check));

    return possible_captures;
}

void Solver::add_piece(Piece* piece) { piece_list.push_back(piece); }

Piece* Solver::piece_at(int x, int y, vector<vector<Piece*>> board) { return board.at(y).at(x); }

vector<Piece*> Solver::capture_piece(Piece* piece, vector<Piece*> pieces) {
    for (auto target = pieces.begin(); target != pieces.end(); ++target) {
        if (*target == piece) {
            pieces.erase(target);
            break;
        }
    }
    return pieces;
}

// Place piece and set piece position to row_col position (absolute position)
void Solver::place_piece(int x, int y, char piece_name) {
    if (board.at(x).at(y) != nullptr) {
        cout << "Position already occupied!" << endl;
        return;
    }
    board.at(x).at(y) = new Piece(piece_name);
    board.at(x).at(y)->set_position(x, y);
}

