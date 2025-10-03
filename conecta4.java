import java.util.Scanner;

public class conecta4 {
    static final int FILAS = 6;
    static final int COLUMNAS = 7;
    static final String VACIO = " "; // espacio en blanco
    static final String JUGADOR_X = "X";
    static final String JUGADOR_O = "O";

    public static void main(String[] args) {
        String[][] tablero = new String[FILAS][COLUMNAS];
        inicializarTablero(tablero);

        Scanner sc = new Scanner(System.in);
        boolean juegoTerminado = false;
        String jugadorActual = JUGADOR_X;

        while (!juegoTerminado) {
            imprimirTablero(tablero);
            System.out.print("Jugador " + jugadorActual + " - Elija una columna (1-7): ");
            int columna = sc.nextInt() - 1;

            if (columna >= 0 && columna < COLUMNAS) {
                if (insertarFicha(tablero, columna, jugadorActual)) {
                    if (verificarGanador(tablero, jugadorActual)) {
                        imprimirTablero(tablero);
                        System.out.println("¡Jugador " + jugadorActual + " ha ganado!");
                        juegoTerminado = true;
                    } else if (tableroLleno(tablero)) {
                        imprimirTablero(tablero);
                        System.out.println("¡Empate!");
                        juegoTerminado = true;
                    } else {
                        jugadorActual = (jugadorActual.equals(JUGADOR_X)) ? JUGADOR_O : JUGADOR_X;
                    }
                } else {
                    System.out.println("Columna llena, elija otra.");
                }
            } else {
                System.out.println("Columna inválida. Intente de nuevo.");
            }
        }
        sc.close();
    }

    static void inicializarTablero(String[][] tablero) {
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                tablero[i][j] = VACIO;
            }
        }
    }

static void imprimirTablero(String[][] tablero) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            System.out.print("| " + tablero[i][j] + " ");
        }
        System.out.println("|");
    }
    System.out.println("-----------------------------");
    for (int j = 1; j <= COLUMNAS; j++) {
        System.out.print(" " + j + "  ");
    }
    System.out.println();
}

    static boolean insertarFicha(String[][] tablero, int columna, String jugador) {
        for (int i = FILAS - 1; i >= 0; i--) {
            if (tablero[i][columna].equals(VACIO)) {
                tablero[i][columna] = jugador;
                return true;
            }
        }
        return false;
    }

    static boolean tableroLleno(String[][] tablero) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[0][j].equals(VACIO)) {
                return false;
            }
        }
        return true;
    }

    static boolean verificarGanador(String[][] tablero, String jugador) {
        // Horizontales
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS - 3; j++) {
                if (tablero[i][j].equals(jugador) &&
                        tablero[i][j + 1].equals(jugador) &&
                        tablero[i][j + 2].equals(jugador) &&
                        tablero[i][j + 3].equals(jugador)) {
                    return true;
                }
            }
        }
        // Verticales
        for (int i = 0; i < FILAS - 3; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (tablero[i][j].equals(jugador) &&
                        tablero[i + 1][j].equals(jugador) &&
                        tablero[i + 2][j].equals(jugador) &&
                        tablero[i + 3][j].equals(jugador)) {
                    return true;
                }
            }
        }
        // Diagonal ↘
        for (int i = 0; i < FILAS - 3; i++) {
            for (int j = 0; j < COLUMNAS - 3; j++) {
                if (tablero[i][j].equals(jugador) &&
                        tablero[i + 1][j + 1].equals(jugador) &&
                        tablero[i + 2][j + 2].equals(jugador) &&
                        tablero[i + 3][j + 3].equals(jugador)) {
                    return true;
                }
            }
        }
        // Diagonal ↙
        for (int i = 3; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS - 3; j++) {
                if (tablero[i][j].equals(jugador) &&
                        tablero[i - 1][j + 1].equals(jugador) &&
                        tablero[i - 2][j + 2].equals(jugador) &&
                        tablero[i - 3][j + 3].equals(jugador)) {
                    return true;
                }
            }
        }
        return false;
    }
}
