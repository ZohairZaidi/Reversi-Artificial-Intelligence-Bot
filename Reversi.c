//Zohair Zaidi

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

//A function required to print the board
void printBoard(char board[][26], int n){
    int x, y;
    printf("  ");
    for (x=0;x<n;x++){  
        printf("%c", 'a' + x);
    }
    printf("\n");

//printing the board to n dimesions
    for (int x = 0; x<n;x++){
        printf("%c ", 'a'+ x);
        for(int y =0; y<n;y++){
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

//function to check the same tile colour
char determineColour (char colour){
    if (colour == 'B')
        return 'W';
    return 'B';
}

//A required helper function for checking if the specified (row, col) lies within the boarder dimensions.
bool positionInBounds(int n , int row, int col){
    return !(row<0||col<0||row>=n||col>=n); //checks if it exceeds the boundaries of the board in any way
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    bool game; 
    bool value;

    //while checking direction if it is outside of the board it will be declared false
    if (!positionInBounds(n, row+deltaRow, col+deltaCol)){
        return false;
    }
    //if the colour to its right is not the same then it will be declared false
    if(board[row+deltaRow][col+deltaCol] != determineColour(colour)){
        return false;
    }

    game = false;
    value = false;  //return value

    row = row + deltaRow*2;
    col = col + deltaCol*2;

    while (game == false){
        if (!positionInBounds(n,row,col)){ //out of bounds
            game = true;
        }
        else if (board[row][col] == colour){ //matches colour
            game = true;
            value = true; //one we need
        }
        else if (board[row][col] == 'U'){ //unoccupied
            game = true;
        }
        else{ //keep checking
            row = row +deltaRow; //to check all possibilities 
            col= col + deltaCol;
        }
    }
    return value;
}

//to flip peices
int peicesFlip (char board[][26], int row, int col, char colour, int rowStep, int colStep, bool proceed){
    row = row+rowStep; 
    col = col+colStep;

    while (board[row][col] == determineColour(colour))
    {
        if (proceed == true){
            board[row][col] = colour; //switch
        }
        row = row+rowStep; //keep checking
        col = col+colStep;
    }
}

int DirectionCheck (char board[][26],int row, int col, char colour, int n, bool switchpeice){
    int z = 0;
    if (board[row][col] != 'U'){
        return z;
    }
    if (!positionInBounds(n,row, col)){
        return z;
    }
    if (switchpeice){
        board[row][col] = colour;
    }

// Check each direction
    if (checkLegalInDirection(board, n, row, col, colour, -1, 0)){
        z = peicesFlip(board, row, col, colour, -1, 0, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 1)){
        z = peicesFlip(board, row, col, colour, -1, 1, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, -1)){
        z = peicesFlip(board, row, col, colour, -1, -1, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 1)){
        z = peicesFlip(board, row, col, colour, 1, 1, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, 1)){
        z = peicesFlip(board, row, col, colour, 0, 1, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, -1)){
        z = peicesFlip(board, row, col, colour, 0, -1, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0)){
        z = peicesFlip(board, row, col, colour, 1, 0, switchpeice);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, -1)){
        z = peicesFlip(board, row, col, colour, 1, -1, switchpeice);
    }

    return z;
}

void Available(char board[][26], int n, char colour){
    int row, col;
    for (row=0;row<n;row++){
        for (col=0;col<n;col++){
            if (DirectionCheck(board, row, col, colour, n, false)){
                printf("%c%c\n", 'a' + row, 'a' + col); //if available
            }
        }
    }
}

int main(void){
    char board[26][26]; //board size
    int n; 
    char colour, row, col;

    printf("Enter the board dimension: ");
    scanf("%d", &n);

    for (int i =0; i<n;i++){
        for (int j =0;j<n;j++){
            board[i][j] = 'U'; //setting up the board as unoccupied
        }
    }

    //setting up the board colours
    board[n/2-1][n/2] = 'B';
    board[n/2][n/2-1] = 'B';
    board[n/2-1][n/2-1] = 'W';
    board[n/2][n/2] = 'W';


    printBoard(board,n); //prints updated board

    printf("Enter board configuration:\n");
    colour = 'a';
    while (colour!= '!'){ //while ! is not inputted
        scanf(" %c%c%c", &colour, &row, &col);
        if (colour != '!'){
            board[row-'a'][col-'a'] = colour;
        }
    }

    printBoard(board,n); //prints updated board
     
    printf("Available moves for W:\n");
    Available(board, n, 'W'); //prints available moves
    printf("Available moves for B:\n");
    Available(board, n, 'B'); //prints available moves

    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &row, &col);

    if (DirectionCheck(board, row - 'a', col - 'a', colour, n, false)){//checks if move is legal
        printf("Valid move.\n"); 
        DirectionCheck(board, row - 'a', col - 'a', colour, n,true);
    }
    else{
        printf("Invalid move.\n"); //prints if move is illegal
    }
    printBoard(board,n); //prints updated board
}