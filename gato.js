const readlineSync = require("readline-sync");

function updateBoard(board) {
    console.log(` ${board[0]} | ${board[1]} | ${board[2]}`);
    console.log("---+---+---");
    console.log(` ${board[3]} | ${board[4]} | ${board[5]}`);
    console.log("---+---+---");
    console.log(` ${board[6]} | ${board[7]} | ${board[8]}`);
}

function validatePlayerTurn(cell, board) {
    let num = parseInt(cell);
    if (!isNaN(num) && num > 0 && num < 10) {
        if (board[num - 1] !== "x" && board[num - 1] !== "o") {
            return "OK";
        } else {
            return "Casilla no disponible, elija otra";
        }
    }
    return "Invalido, ingrese solo numeros del 1 al 9";
}

function playersTurn(player, board) {
    let cell = readlineSync.question(`Jugador ${player} - Elija una casilla 1-9: `);
    let msg = validatePlayerTurn(cell, board);
    if (msg === "OK") {
        board[parseInt(cell) - 1] = player;
    } else {
        console.log(msg);
        playersTurn(player, board);
    }
}

function playerWinner(b, player) {
    return (
        (b[0] === player && b[1] === player && b[2] === player) ||
        (b[3] === player && b[4] === player && b[5] === player) ||
        (b[6] === player && b[7] === player && b[8] === player) ||
        (b[0] === player && b[3] === player && b[6] === player) ||
        (b[1] === player && b[4] === player && b[7] === player) ||
        (b[2] === player && b[5] === player && b[8] === player) ||
        (b[0] === player && b[4] === player && b[8] === player) ||
        (b[2] === player && b[4] === player && b[6] === player)
    );
}

// Inicio
let board = ["1", "2", "3", "4", "5", "6", "7", "8", "9"];
let gameOver = false;
let turn = 1;
let playerOne = "x";
let playerTwo = "o";

updateBoard(board);

while (!gameOver) {
    if (turn % 2 === 1) {
        playersTurn(playerOne, board);
        updateBoard(board);
        if (playerWinner(board, playerOne)) {
            console.log(`Gano el jugador ${playerOne}`);
            gameOver = true;
        }
    } else {
        playersTurn(playerTwo, board);
        updateBoard(board);
        if (playerWinner(board, playerTwo)) {
            console.log(`Gano el jugador ${playerTwo}`);
            gameOver = true;
        }
    }

    if (turn === 9 && !gameOver) {
        console.log("EMPATE!");
        gameOver = true;
    }
    turn++;
}
