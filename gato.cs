using System;

class Program
{
    static void UpdateBoard(string[] board)
    {
        Console.WriteLine($" {board[0]} | {board[1]} | {board[2]}");
        Console.WriteLine("---+---+---");
        Console.WriteLine($" {board[3]} | {board[4]} | {board[5]}");
        Console.WriteLine("---+---+---");
        Console.WriteLine($" {board[6]} | {board[7]} | {board[8]}");
    }

    static string ValidatePlayerTurn(string cell, string[] board)
    {
        if (int.TryParse(cell, out int num) && num > 0 && num < 10)
        {
            if (board[num - 1] != "x" && board[num - 1] != "o")
                return "OK";
            else
                return "Casilla no disponible, elija otra";
        }
        return "Invalido, ingrese solo numeros del 1 al 9";
    }

    static void PlayersTurn(string player, string[] board)
    {
        Console.Write($"Jugador {player} - Elija una casilla 1-9: ");
        string cell = Console.ReadLine();
        string msg = ValidatePlayerTurn(cell, board);
        if (msg == "OK")
        {
            board[int.Parse(cell) - 1] = player;
        }
        else
        {
            Console.WriteLine(msg);
            PlayersTurn(player, board);
        }
    }

    static bool PlayerWinner(string[] b, string player)
    {
        return
            (b[0] == player && b[1] == player && b[2] == player) ||
            (b[3] == player && b[4] == player && b[5] == player) ||
            (b[6] == player && b[7] == player && b[8] == player) ||
            (b[0] == player && b[3] == player && b[6] == player) ||
            (b[1] == player && b[4] == player && b[7] == player) ||
            (b[2] == player && b[5] == player && b[8] == player) ||
            (b[0] == player && b[4] == player && b[8] == player) ||
            (b[2] == player && b[4] == player && b[6] == player);
    }

    static void Main()
    {
        string[] board = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        bool gameOver = false;
        int turn = 1;
        string playerOne = "x";
        string playerTwo = "o";

        UpdateBoard(board);

        while (!gameOver)
        {
            if (turn % 2 == 1)
            {
                PlayersTurn(playerOne, board);
                UpdateBoard(board);
                if (PlayerWinner(board, playerOne))
                {
                    Console.WriteLine($"Gano el jugador {playerOne}");
                    gameOver = true;
                }
            }
            else
            {
                PlayersTurn(playerTwo, board);
                UpdateBoard(board);
                if (PlayerWinner(board, playerTwo))
                {
                    Console.WriteLine($"Gano el jugador {playerTwo}");
                    gameOver = true;
                }
            }

            if (turn == 9 && !gameOver)
            {
                Console.WriteLine("EMPATE!");
                gameOver = true;
            }
            turn++;
        }
    }
}
