import java.util.Scanner;

public class gato {
    static Scanner sc = new Scanner(System.in);

    public static void updateBoard(String[] board) {
        System.out.println(" " + board[0] + " | " + board[1] + " | " + board[2]);
        System.out.println("---+---+---");
        System.out.println(" " + board[3] + " | " + board[4] + " | " + board[5]);
        System.out.println("---+---+---");
        System.out.println(" " + board[6] + " | " + board[7] + " | " + board[8]);
    }

    public static String validatePlayerTurn(String cell, String[] board) {
        if (cell.matches("[1-9]")) {
            int num = Integer.parseInt(cell);
            if (!board[num - 1].equals("x") && !board[num - 1].equals("o")) {
                return "OK";
            } else {
                return "Casilla no disponible, elija otra";
            }
        }
        return "Invalido, ingrese solo numeros del 1 al 9";
    }

    public static void playersTurn(String player, String[] board) {
        System.out.print("Jugador " + player + " - Elija una casilla 1-9: ");
        String cell = sc.nextLine();
        String msg = validatePlayerTurn(cell, board);
        if (msg.equals("OK")) {
            board[Integer.parseInt(cell) - 1] = player;
        } else {
            System.out.println(msg);
            playersTurn(player, board);
        }
    }

    public static boolean playerWinner(String[] b, String player) {
        // filas
        if (b[0].equals(player) && b[1].equals(player) && b[2].equals(player))
            return true;
        if (b[3].equals(player) && b[4].equals(player) && b[5].equals(player))
            return true;
        if (b[6].equals(player) && b[7].equals(player) && b[8].equals(player))
            return true;
        // columnas
        if (b[0].equals(player) && b[3].equals(player) && b[6].equals(player))
            return true;
        if (b[1].equals(player) && b[4].equals(player) && b[7].equals(player))
            return true;
        if (b[2].equals(player) && b[5].equals(player) && b[8].equals(player))
            return true;
        // diagonales
        if (b[0].equals(player) && b[4].equals(player) && b[8].equals(player))
            return true;
        if (b[2].equals(player) && b[4].equals(player) && b[6].equals(player))
            return true;

        return false;
    }

    public static void main(String[] args) {
        String[] board = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        boolean gameOver = false;
        int turn = 1;
        String playerOne = "x";
        String playerTwo = "o";

        updateBoard(board);

        while (!gameOver) {
            if (turn % 2 == 1) {
                playersTurn(playerOne, board);
                updateBoard(board);
                if (playerWinner(board, playerOne)) {
                    System.out.println("Gano el jugador " + playerOne);
                    gameOver = true;
                }
            } else {
                playersTurn(playerTwo, board);
                updateBoard(board);
                if (playerWinner(board, playerTwo)) {
                    System.out.println("Gano el jugador " + playerTwo);
                    gameOver = true;
                }
            }

            if (turn == 9 && !gameOver) {
                System.out.println("EMPATE!");
                gameOver = true;
            }
            turn++;
        }
    }
}
