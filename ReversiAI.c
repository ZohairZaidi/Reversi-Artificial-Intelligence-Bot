//Zohair Zaidi

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 
//prints the board
void printBoard(char board[][26], int n) {
    printf("  ");
    for (int x = 0; x < n; x++)
        printf("%c", ('a' + x));
    printf("\n");
    for (int x = 0; x < n; x++) {
        printf("%c ", ('a' + x));
        for (int y = 0; y < n; y++) {
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

//setting up the board with the default start
void initializingboard(char board[][26], int n) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            board[x][y] = 'U';
            
            if ((x == n / 2 && y == n / 2 - 1) || (x == n / 2 - 1 && y == n / 2))
                board[x][y] = 'B';

            if ((x == n / 2 && y == n / 2) || (x == n / 2 - 1 && y == n / 2 - 1))
                board[x][y] = 'W';
        }
    }
}

//checks for opponent colour
char othercolour(char colour) {
    if (colour == 'B')
        return 'W';
    else{
        return 'B';
    }
}

//checks if the game is played within bounds
bool positionInBounds(int n, int row, int col) {
    if (row < n && col < n && row >= 0 && col >= 0)
        return true;
    return false;
}
//Checks direction from Lab7
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    char opposite = othercolour(colour);
    int z = 1;

    while (positionInBounds(n, row + (deltaRow * z), col + (deltaCol * z)) && (board[row + (deltaRow * z)][col + (deltaCol * z)] != colour) && board[row + (deltaRow * z)][col + (deltaCol * z)] != 'U') {
        z++;

        if (positionInBounds(n, row + (deltaRow * z), col + (deltaCol * z)) && board[row + (deltaRow * z)][col + (deltaCol * z)] == colour)
            return true;

        else {
            if (positionInBounds(n, row + (deltaRow * z), col + (deltaCol * z)) && board[row + (deltaRow * z)][col + (deltaCol * z)] == opposite)
                continue;

            else {
                if (!positionInBounds(n, row + (deltaRow * z), col + (deltaCol * z))) {
                    return false;

                } else {
                    if (board[row + (deltaRow * z)][col + (deltaCol * z)] == colour)
                        return true;

                    else
                        return false;
                }
            }
        }
    }
    return false;
}

//if its fine to flip
bool isoktoflip(char board[26][26], int n, char turn, int row, int col) {
    if (checkLegalInDirection(board, n, row, col, turn, 1, -1)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, 1, 0)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, 1, 1)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, 0, -1)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, 0, 1)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, -1, -1)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, -1, 0)){
        return true;
    }
    if (checkLegalInDirection(board, n, row, col, turn, -1, 1)){
        return true;
    }

    return false;
}

//after move has been done
void Afterturn(char board[][26], int n, char colour, int row, int col) {
    int Drow, Dcol, z;
    
    if (board[row][col] == 'U')
        board[row][col] = colour;

    for (Drow = -1; Drow <= 1; Drow++) {
        for (Dcol = -1; Dcol <= 1; Dcol++) {
            z = 1;
            if (Drow == 0 && Dcol == 0)
                continue;
            if (checkLegalInDirection(board, n, row, col, colour, Drow, Dcol) && positionInBounds(n, row + Drow*z, col + Dcol*z)) {
                while (board[row + (Drow * z)][col + (Dcol * z)] == othercolour(colour)) {
                    if (!positionInBounds(n, row + Drow*z, col + Dcol*z))
                        break;
                    board[row + (Drow * z)][col + (Dcol * z)] = colour;
                    z++;
                }
            }
        }
    }
}

//determining next possible moves
bool futureMoves (char board[26][26], int n, char colour) {
    int turnview = 0;
    int Unoccupied = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (isoktoflip(board, n, colour, x, y) && board[x][y] == 'U') {
                turnview++;
                Unoccupied++;
            }
        }
    }
    if (turnview != 0 && Unoccupied != 0)
        return true;
    return false;
}

//plays next turn
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    char boardz[26][26];
    int maximum = 0;
    int z;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            z = 0;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    boardz[x][y] = board[x][y];
                }
            }

            if (isoktoflip(boardz, n, turn, i, j)) {
                Afterturn(boardz, n, turn, i, j);
            }

            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (boardz[x][y] == turn)
                        if ((x == 0 && y == 1) || (x == 0 && y == n-2) || (x == 1 && y == 0) || (x == 1 && y == 1) || (x == 1 && y == n-2) || (x == 1 && y == n-1) ||(x == n-2 && y == 0) || (x == n-2 && y == 1) || (x == n-2 && y == n-2) || (x == n-2 && y == n-1) ||(x == n-1 && y == 1) || (x == n-1 && y == n-2)) {
                            z=1;
                        }
                        else if ((x == 0 && y == 0) || (x == n-1 && y == n-1) || (x == 0 && y == n-1) || (x == n-1 && y == 0)) {
                            z=5;
                        } 
                         else if (x == 1 || x == n-2 || y == 1 || y == n-2) {
                            z=3;
                        }
                         else if (x == 0 || x == n-1 || y == 0 || y == n-1) {
                            z=4;
                        }
                         else {
                            z=2;
                        }
                }
            }
            if (z > maximum && board[i][j] == 'U' && isoktoflip(board, n, turn, i, j)) {
                maximum = z;
                *row = i;
                *col = j;
            }
        }   
    }
    return 0;
}

//tracks who won the game and if it resulted in a tie
char winTracker (char board[26][26], int n) {
    int BlackScore = 0;
    int WhiteScore = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (board[x][y] == 'W')
                WhiteScore++;
            if (board[x][y] == 'B')
                BlackScore++;
        }
    }
    if (WhiteScore > BlackScore)
        return 'W';
    else if (BlackScore > WhiteScore)
        return 'B';
    else
        return 'T';
}