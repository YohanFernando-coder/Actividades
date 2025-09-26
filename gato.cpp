#include <iostream>
#include <vector>
#include <string>
using namespace std;

void update_board(const vector<string>& board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

string validate_playerTurn(string cell, const vector<string>& board) {
    if (cell.size() == 1 && isdigit(cell[0])) {
        int num = stoi(cell);
        if (num > 0 && num < 10) {
            if (board[num-1] != "x" && board[num-1] != "o")
                return "OK";
            else
                return "Casilla no disponible, elija otra";
        }
    }
    return "Invalido, ingrese solo numeros del 1 al 9";
}

vector<string> players_turn(string player, vector<string> board) {
    string cell;
    cout << "Jugador " << player << " - Elija una casilla 1-9: ";
    cin >> cell;
    string msg = validate_playerTurn(cell, board);
    if (msg == "OK") {
        board[stoi(cell)-1] = player;
        return board;
    } else {
        cout << msg << endl;
        return players_turn(player, board);
    }
}

bool player_winner(const vector<string>& b, string player) {
    // filas
    if (b[0]==player && b[1]==player && b[2]==player) return true;
    if (b[3]==player && b[4]==player && b[5]==player) return true;
    if (b[6]==player && b[7]==player && b[8]==player) return true;
    // columnas
    if (b[0]==player && b[3]==player && b[6]==player) return true;
    if (b[1]==player && b[4]==player && b[7]==player) return true;
    if (b[2]==player && b[5]==player && b[8]==player) return true;
    // diagonales
    if (b[0]==player && b[4]==player && b[8]==player) return true;
    if (b[2]==player && b[4]==player && b[6]==player) return true;

    return false;
}

int main() {
    vector<string> board = {"1","2","3","4","5","6","7","8","9"};
    bool game_over = false;
    int turn = 1;
    string player_one = "x";
    string player_two = "o";

    update_board(board);

    while (!game_over) {
        if (turn % 2 == 1) {
            board = players_turn(player_one, board);
            update_board(board);
            if (player_winner(board, player_one)) {
                cout << "Gano el jugador " << player_one << endl;
                game_over = true;
            }
        } else {
            board = players_turn(player_two, board);
            update_board(board);
            if (player_winner(board, player_two)) {
                cout << "Gano el jugador " << player_two << endl;
                game_over = true;
            }
        }

        if (turn == 9 && !game_over) {
            cout << "EMPATE!" << endl;
            game_over = true;
        }
        turn++;
    }
    return 0;
}
