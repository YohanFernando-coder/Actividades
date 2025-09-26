# funcion para validar el tablero 
def update_board(board):
    print(f" {board[0]} | {board[1]} | {board[2]}")
    print("---+---+---")
    print(f" {board[3]} | {board[4]} | {board[5]}")
    print("---+---+---")
    print(f" {board[6]} | {board[7]} | {board[8]}")

# funcion para indicar la casilla
def players_turn(player, board):
    cell = input(f"Jugador {player} - Elija una casilla 1-9: ")
    msg = validate_playerTurn(cell, board)
    if msg == "OK":
        board[int(cell)-1] = player
        return board
    else:
        print(msg)
        return players_turn(player, board)

# funcion para validar si se pone un caracter y un numero del 1-9
def validate_playerTurn(cell, board):
    if cell.isdigit() and int(cell) > 0 and int(cell) < 10:
        if board[int(cell)-1] != "x" and board[int(cell)-1] != "o":
            return "OK"
        else:
            return "Casilla no disponible, elija otra"
    else:
        return "Invalido, ingrese solo numeros del 1 al 9"

# funcion para validar que jugador ganó
def player_winer(board, player):
    b = board 
    #evaluar las fials
    if b[0] == b[1] == b[2] and b[0] in player: return True
    if b[3] == b[4] == b[5] and b[3] in player: return True
    if b[6] == b[7] == b[8] and b[6] in player: return True
    # evaluar columnas
    if b[0] == b[3] == b[6] and b[0] in player: return True
    if b[1] == b[4] == b[7] and b[1] in player: return True
    if b[2] == b[5] == b[8] and b[2] in player: return True
    # evaluar diagonales
    if b[0] == b[4] == b[8] and b[0] in player: return True
    if b[2] == b[4] == b[6] and b[2] in player: return True

    return False

# variables de inicio
initial_board = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]

game_over = False
turn = 1
player_one = "x"
player_two = "o"

# funcion que contiene el tablero
update_board(initial_board)

# ciclo para indicar turnos de los jugadores
while(game_over == False):
    # validar turno de jugador
    if turn % 2 == 1:
        initial_board = players_turn(player_one, initial_board)
        winner = player_winer(initial_board, player_one)
        # actualizar tablero
        update_board(initial_board)
        if winner:
            print(f"Gano el jugador {player_one}")
            game_over = True

    else:
        initial_board = players_turn(player_two, initial_board)
        winner = player_winer(initial_board, player_two)
        # actualizar tablero
        update_board(initial_board)
        if winner:
            print(f"Gano el jugador {player_two}")
            game_over = True

    # indica que los jugadores se quedaron sin movimientos
    if turn == 9:
        print("EMPATE!")
        game_over = True

    turn += 1