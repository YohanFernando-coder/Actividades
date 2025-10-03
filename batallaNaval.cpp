#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int SIZE = 10;

struct Ship
{
    string name;
    int size;
    int hits;
};

struct Player
{
    string name;
    vector<vector<char>> board;
    vector<vector<char>> tracking;
    vector<Ship> ships;
};

void printBoard(vector<vector<char>> &board)
{
    cout << "   ";
    for (int i = 0; i < SIZE; i++)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < SIZE; i++)
    {
        if (i < 10)
            cout << " ";
        cout << i << " ";
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeShipOnBoard(Player &player, Ship &ship, int x, int y, char dir)
{
    if (dir == 'h')
    {
        if (y + ship.size > SIZE)
            return false;
        for (int i = 0; i < ship.size; i++)
            if (player.board[x][y + i] != '~')
                return false;
        for (int i = 0; i < ship.size; i++)
            player.board[x][y + i] = ship.name[0];
    }
    else if (dir == 'v')
    {
        if (x + ship.size > SIZE)
            return false;
        for (int i = 0; i < ship.size; i++)
            if (player.board[x + i][y] != '~')
                return false;
        for (int i = 0; i < ship.size; i++)
            player.board[x + i][y] = ship.name[0];
    }
    else
    {
        return false;
    }
    return true;
}

void placeShips(Player &player)
{
    cout << player.name << ", coloca tus barcos." << endl;
    for (auto &ship : player.ships)
    {
        bool placed = false;
        while (!placed)
        {
            printBoard(player.board);
            int x, y;
            char dir;
            cout << "Coloca el " << ship.name << " (tamaño " << ship.size << ") fila y columna: ";
            cin >> x >> y;
            cout << "Horizontal(h) o Vertical(v)? ";
            cin >> dir;

            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
            {
                cout << "Coordenadas inválidas.\n";
                continue;
            }

            placed = placeShipOnBoard(player, ship, x, y, dir);
            if (!placed)
                cout << "No se puede colocar ahí, intenta otra posición.\n";
        }
    }
}

bool takeTurn(Player &attacker, Player &defender)
{
    while (true)
    {
        int x, y;
        cout << attacker.name << ", ingresa coordenadas para disparar (fila columna): ";
        cin >> x >> y;

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        {
            cout << "Coordenadas inválidas.\n";
            continue;
        }

        if (attacker.tracking[x][y] != '~')
        {
            cout << "Ya disparaste aquí. Intenta otra coordenada.\n";
            continue;
        }

        if (defender.board[x][y] != '~' && defender.board[x][y] != 'X' && defender.board[x][y] != 'O')
        {
            cout << "¡Tocado!" << endl;
            char hitChar = defender.board[x][y];
            attacker.tracking[x][y] = 'X';
            defender.board[x][y] = 'X';

            // Actualizar hits del barco
            for (auto &ship : defender.ships)
            {
                if (ship.name[0] == hitChar)
                {
                    ship.hits++;
                    if (ship.hits == ship.size)
                        cout << "¡Hundido " << ship.name << "!" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Agua." << endl;
            attacker.tracking[x][y] = 'O';
        }

        // Verificar si el defensor tiene barcos restantes
        bool anyLeft = false;
        for (auto &ship : defender.ships)
            if (ship.hits < ship.size)
                anyLeft = true;
        return !anyLeft;
    }
}

int main()
{
    Player player1 = {"Jugador 1", vector<vector<char>>(SIZE, vector<char>(SIZE, '~')), vector<vector<char>>(SIZE, vector<char>(SIZE, '~')), {{"Destructor", 2, 0}, {"Submarino", 3, 0}, {"Portaaviones", 5, 0}}};
    Player player2 = {"Jugador 2", vector<vector<char>>(SIZE, vector<char>(SIZE, '~')), vector<vector<char>>(SIZE, vector<char>(SIZE, '~')), {{"Destructor", 2, 0}, {"Submarino", 3, 0}, {"Portaaviones", 5, 0}}};

    placeShips(player1);
    placeShips(player2);

    bool gameOver = false;
    while (!gameOver)
    {
        cout << "\n--- Tablero de seguimiento de " << player1.name << " ---\n";
        printBoard(player1.tracking);
        gameOver = takeTurn(player1, player2);
        if (gameOver)
        {
            cout << player1.name << " ¡ganó!\n";
            break;
        }

        cout << "\n--- Tablero de seguimiento de " << player2.name << " ---\n";
        printBoard(player2.tracking);
        gameOver = takeTurn(player2, player1);
        if (gameOver)
        {
            cout << player2.name << " ¡ganó!\n";
            break;
        }
    }

    return 0;
}