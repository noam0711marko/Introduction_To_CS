#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

#define BOARD_MAX_SIDE 9
#define BOARD_MIN_SIDE 3
#define MIN_TOKENS 3

#define FIRST_SYMBOL ('O')
#define SECOND_SYMBOL ('O')
#define EMPTY_SLOT_SYMBOL (' ')
#define PLAYER1 1
#define PLAYER2 2
#define MOVES_ARRAY_DIMENSIONS 3
#define SECOND 111
#define FIRST 222
#define INSERTION 1
#define UNDO -1
#define REDO 2
#define DONE 100
#define NO_WINNER_YET 0
#define TIE -1

//----------------------- Message Identifiers --------------------------//
#define MSG_GET_BOARD_ROWS   0
#define MSG_GET_BOARD_COLS   1
#define MSG_GET_NUMBER_TOKENS 2


//--------------------------- Board Edges ------------------------------//

#define BOARD_VERT_SEP  '|'
#define BOARD_LEFT_ANG '\\'
#define BOARD_RIGHT_ANG '/'
#define BOARD_BOTTOM  '-'
#define BOARD_BOTTOM_SEP '-'

/*-------------------------------------------------------------------------
                              Color Prints
-------------------------------------------------------------------------*/
void red () {
    printf("\033[1;31m");
}

void yellow (){
    printf("\033[1;33m");
}

void blue () {
    printf("\033[1;34m");
}

void green (){
    printf("\033[1;32m");
}

void purple (){
    printf("\033[1;35m");
}

void white (){
    printf("\033[1;37m");
}
void cyan (){
    printf("\033[1;36m");
}

void reset () {
    printf("\033[0m");
}

/*-------------------------------------------------------------------------
                        Function declaration
-------------------------------------------------------------------------*/


void print_welcome_message();
void print_read_game_params_message(int param);
void print_chose_color_message1();
void print_chose_color_message2();
void print_chose_color_message3();
void print_color_error();
void print_chose_move_message(int player, char player1_color, char player2_color);
void print_enter_column_message();
void print_full_column_message();
void print_unavailable_undo_redo_message();
void print_board(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color, char player1_color, char player2_color);
void printWinnerPlayer(char player_color, int player_id);
void print_winner(int player_id, char player1_color, char player2_color);

int getStartingColor(char* player1_color,  char* player2_color);
int getNumOfRows(int* rows);
int getNumOfColumns(int* columns, const int rows);
int min(int row, int col);
int getNumOfTokens(int* tokens, const int* rows, const int* columns);
int getGameParameters(int* tokens, int* rows, int* columns);
void initGameBoard(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int rows, int columns);
int firstSetOfGame(char* player1_color, char* player2_color, char* board_color, int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                   int board_side[]);

int checkWinInRow(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int columns);
int winnerFromRow(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                  const int board_side[]);
int checkWinInColumn(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int rows, int column);
int winnerFromColumn(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                     const int board_side[]);
void counterRowColUpdateRightDiagonal(int* row, int* col, int* counter, bool status);
int checkWinInRightDiagonal(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int col, int columns);
void checkFirstColumnRightDiagonal(char* curr, int rows, int columns, const int* tokens , char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter);
void checkFirstRowRightDiagonal(char* curr, int rows, int columns, const int* tokens , char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter);
int winnerFromRightDiagonal(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                            const int board_side[]);
void counterRowColUpdateLeftDiagonal(int* row, int* col, int* counter, bool status);
int checkWinInLeftDiagonal(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int col);
void checkLastColumnLeftDiagonal(char* curr, int rows,int columns, const int* tokens ,char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter);
void checkFirstRowLeftDiagonal(char* curr, int rows,int columns, const int* tokens ,char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter);
int winnerFromLeftDiagonal(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                           const int board_side[]);
int checkTie(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[]);
int firstNonZero(int a,int b,int c, int d, int e);
int checkWinner(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                const int board_side[]);

int getColumnFromUser(int* column);
char getCurrentPlayerColor(const char player1_color, const char player2_color, const int current_player);
void updateMovesArrayInGoodInsertion(int moves_array[][MOVES_ARRAY_DIMENSIONS], int col, int* moves_counter, const char player1_color,
                                     const char player2_color, const int current_player);
void insertToColumn(int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
                    const char player2_color, const int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter);
void undoAction(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int moves_array[][MOVES_ARRAY_DIMENSIONS], const int* moves_counter, int row, int col);
int undo(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter);
void redoInsertion(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter,
                   int row, int col);
int redo(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter);
int undoOrRedo(int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS],
               int* moves_counter);
int userInsertCheck(const int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
                    const char player2_color, const int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter);
int playerTurn(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
               const char player2_color, int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter);
void changePlayer(int* current_player);

int game(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char* player1_color, const char* player2_color,
         int* current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter, int* winner, int* tokens, char* board_color);
int gameLoop(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char* player1_color, const char* player2_color,
             int* current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter, int* winner, int* tokens, char* board_color);

/*
stats for style check:
//main function is 8 rows long
//the longest row - 148 characters
//the longest function - 12 rows
*/

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

//---------------------- Printing Functions ----------------------------//

// message number 0 = "Welcome to 4-in-a-row game! \n"
//1 line
void print_welcome_message()
{
    printf("Welcome to 4-in-a-row game! \n");
}


// message number 1 = "Please enter number of rows:"
// message number 2 = "Please enter number of columns:"
// message number 3 = "Please enter number of tokens strike for a win:"
//2 lines
void print_read_game_params_message(int param)
{
    char const* const possible_params[] = {"rows", "columns", "tokens"};

    printf("Please enter number of %s", possible_params[param]);
}

// message number 4 = "Please choose starting color (Y)ellow or (R)ed: "
//1 line
void print_chose_color_message1()
{
    printf("Please choose a different color for player #1!\n(Y)ellow, (R)ed, (B)lue, (G)reen, (C)yan, (P)urple or (W)hite: ");
}

void print_chose_color_message2()
{
    printf("Please choose a different color for player #2!\n(Y)ellow, (R)ed, (B)lue, (G)reen, (C)yan, (P)urple or (W)hite: ");
}

void print_chose_color_message3()
{
    printf("Please choose board color!\n(Y)ellow, (R)ed, (B)lue, (G)reen, (C)yan, (P)urple or (W)hite: ");
}

void print_color_error()
{
    printf("\nOh no! This color have been chosen before! Please choose another color! ¯\\_( ͡❛ ͜ʖ ͡❛)_/¯");
}

// message number 5 = "Your move, player <player>. "
//1 line
void print_chose_move_message(int player, char player1_color, char player2_color)
{
    printf("Your move, player ");
    if(player==PLAYER1){
        printWinnerPlayer(player1_color, player);
        printf(" \n");
    }
    if(player==PLAYER2){
        printWinnerPlayer(player2_color, player);
        printf(" \n");
    }
}

// message number 6
//1 line
void print_enter_column_message()
{
    printf("Please enter column, -1 for undo or -2 for redo: ");
}

//1 line
void print_full_column_message()
{
    printf("Column full. ");
}

//1 line
void print_unavailable_undo_redo_message()
{
    printf("No moves to undo/redo. ");
}

void printBoardVertSep1(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color){
    if(board_color=='C'){
        cyan();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='R'){
        red();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='G'){
        green();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='Y'){
        yellow();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='B'){
        blue();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='P'){
        purple();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
    else{
        white();
        printf("\n%c", BOARD_VERT_SEP);
        reset();
    }
}

void printBoardVertSep2(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color){
    if(board_color=='C'){
        cyan();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='R'){
        red();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='G'){
        green();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='Y'){
        yellow();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='B'){
        blue();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else if(board_color=='P'){
        purple();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
    else{
        white();
        printf("%c", BOARD_VERT_SEP);
        reset();
    }
}

void printBoardLeftAng(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color){
    if(board_color=='C'){
        cyan();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else if(board_color=='R'){
        red();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else if(board_color=='G'){
        green();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else if(board_color=='Y'){
        yellow();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else if(board_color=='B'){
        blue();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else if(board_color=='P'){
        purple();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
    else{
        white();
        printf("\n%c", BOARD_LEFT_ANG);
        reset();
    }
}

void printBoardBottomSep(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color){
    if(board_color=='C'){
        cyan();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else if(board_color=='R'){
        red();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else if(board_color=='G'){
        green();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else if(board_color=='Y'){
        yellow();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else if(board_color=='B'){
        blue();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else if(board_color=='P'){
        purple();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
    else{
        white();
        for (int ii = 0; ii < board_side[1] - 1; ++ii)
            printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
        reset();
    }
}

void printBoardRightAng(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color){
    if(board_color=='C'){
        cyan();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else if(board_color=='R'){
        red();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else if(board_color=='G'){
        green();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else if(board_color=='Y'){
        yellow();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else if(board_color=='B'){
        blue();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else if(board_color=='P'){
        purple();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
    else{
        white();
        printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
        reset();
    }
}


void printTokenPlayer(char board[][BOARD_MAX_SIDE], const int board_side[], char player_color, char token){
    if(player_color=='C'){
        cyan();
        printf("%c", token);
        reset();
    }
    else if(player_color=='R'){
        red();
        printf("%c", token);
        reset();
    }
    else if(player_color=='G'){
        green();
        printf("%c", token);
        reset();
    }
    else if(player_color=='Y'){
        yellow();
        printf("%c", token);
        reset();
    }
    else if(player_color=='B'){
        blue();
        printf("%c", token);
        reset();
    }
    else if(player_color=='P'){
        purple();
        printf("%c", token);
        reset();
    }
    else{
        white();
        printf("%c", token);
        reset();
    }
}

void printToken(char board[][BOARD_MAX_SIDE], const int board_side[], char player1_color, char player2_color, char token){
    if(token==player1_color){
        printTokenPlayer(board, board_side, player1_color,token);
    }
    else if(token==player2_color){
        printTokenPlayer(board, board_side, player2_color, token);
    }
    else{
        printf(" ");
    }
}

void print_board(char board[][BOARD_MAX_SIDE], const int board_side[], char board_color, char player1_color, char player2_color)
{
    for (int row = 0; row < board_side[0]; ++row)
    {
        printBoardVertSep1(board, board_side, board_color);
        for (int col = 0; col < board_side[1]; ++col) {
            printToken(board, board_side, player1_color, player2_color,board[row][col]);
            printBoardVertSep2(board, board_side, board_color);
        }
    }
    printBoardLeftAng(board, board_side, board_color);
    printBoardBottomSep(board, board_side, board_color);
    printBoardRightAng(board, board_side, board_color);
}

void printWinnerPlayer(char player_color, int player_id){
    if(player_color=='C'){
        cyan();
        printf("%d", player_id);
        reset();
    }
    else if(player_color=='R'){
        red();
        printf("%d", player_id);
        reset();
    }
    else if(player_color=='G'){
        green();
        printf("%d", player_id);
        reset();
    }
    else if(player_color=='Y'){
        yellow();
        printf("%d", player_id);
        reset();
    }
    else if(player_color=='B'){
        blue();
        printf("%d", player_id);
        reset();
    }
    else if(player_color=='P'){
        purple();
        printf("%d", player_id);
        reset();
    }
    else{
        white();
        printf("%d", player_id);
        reset();
    }
}

/*
 * Outputs winner or tie message.
 *
 * player_id - the id to be output. Pass <0 for tie.
 */
//4 lines
void print_winner(int player_id, char player1_color, char player2_color)
{
    if (player_id >= 0) {
        if (player_id == PLAYER1) {
            printf("Player ");
            printWinnerPlayer(player1_color, player_id);
            printf(" won! \n");
        }
        else {
            printf("Player ");
            printWinnerPlayer(player2_color, player_id);
            printf(" won! \n");
        }
    }
    else
        printf("That's a tie. \n");
}

int getBoardColor(char* board_color){ //V
    do{
        print_chose_color_message3();
        if(scanf(" %c", board_color)!=1){
            return ERROR;
        }
    }while(*board_color != 'R' && *board_color != 'G' && *board_color != 'Y' && *board_color != 'B' && *board_color != 'P' && *board_color != 'C' &&
            *board_color != 'W');
    return SUCCESS;
}

int getFirstPlayerColor(char* player1_color, char board_color){ //V
    do{
        print_chose_color_message1();
        if(scanf(" %c", player1_color)!=1){
            return ERROR;
        }
    }while(*player1_color != 'R' && *player1_color != 'G' && *player1_color != 'Y' && *player1_color != 'B' && *player1_color != 'P' && *player1_color != 'C' &&
           *player1_color != 'W');
    if (*player1_color==board_color){
        print_color_error();
        getFirstPlayerColor(player1_color, board_color);
    }
    return SUCCESS;
}

int getSecondPlayerColor(char* player2_color, char player1_color, char board_color){ //V
    do{
        print_chose_color_message2();
        if(scanf(" %c", player2_color)!=1){
            return ERROR;
        }
    }while(*player2_color != 'R' && *player2_color != 'G' && *player2_color != 'Y' && *player2_color != 'B' && *player2_color != 'P' && *player2_color != 'C' &&
           *player2_color != 'W');
    if (*player2_color==board_color || *player2_color==player1_color){
        print_color_error();
        getSecondPlayerColor(player2_color, player1_color, board_color);
    }
    return SUCCESS;
}
/*
 * Gets starting color from user and sets it to the first player, and the other color to the second player.
 *
 * player1_color - pointer to char which will sign first player's color.
 * player2_color - pointer to char which will sign second player's color.
 */
//10 lines
int getGameColors(char* player1_color, char* player2_color, char* board_color){ //V
    if(getBoardColor(board_color)!=SUCCESS || getFirstPlayerColor(player1_color, *board_color)!=SUCCESS
        || getSecondPlayerColor(player2_color, *player1_color, *board_color)!=SUCCESS){
        return ERROR;
    }
    return SUCCESS;
}

/*
 * Gets num of rows from user.
 *
 * rows - pointer to int which we will enter the number of rows from user to it.
 */
//5 lines
int getNumOfRows(int* rows){
    while(*rows<BOARD_MIN_SIDE || *rows>BOARD_MAX_SIDE){
        print_read_game_params_message(MSG_GET_BOARD_ROWS);
        yellow();
        printf("\nnote: should be between 3 to 9\n");
        reset();
        printf("Num of Rows:");
        if(scanf(" %d", rows)!=1){
            return ERROR;
        }
    }
    return SUCCESS;
}

/*
 * Gets num of columns from user.
 *
 * columns - pointer to int which we will enter the number of columns from user to it.
 */
//5 lines
int getNumOfColumns(int* columns, const int rows){
    while(*columns<BOARD_MIN_SIDE || *columns>BOARD_MAX_SIDE || *columns<rows){
        print_read_game_params_message(MSG_GET_BOARD_COLS);
        yellow();
        printf("\nnote: should be between 3 to 9 and at least equal to (or bigger than) number of rows\n");
        reset();
        printf("Num of Columns:");
        if(scanf(" %d", columns)!=1){
            return ERROR;
        }
    }
    return SUCCESS;
}

/*
 * Returns the minimum between rows and columns.
 *
 * row - number of rows.
 * col - number of columns.
 */
//3 lines
int min(int row, int col){
    if (row<col){
        return row;
    }
    return col;
}

/*
 * Gets num of tokens from user and checks if it's valid.
 *
 * tokens - pointer to int which we will enter the number of tokens from user to it.
 * rows - pointer to int which contains number of rows.
 * columns - pointer to int which contains number of columns.
 */
//5 lines
int getNumOfTokens(int* tokens, const int* rows, const int* columns){
    while(*tokens<MIN_TOKENS || *tokens>min(*rows,*columns)){
        print_read_game_params_message(MSG_GET_NUMBER_TOKENS);
        yellow();
        printf("\nnote: should be at least 3 and no more than number of rows\n");
        reset();
        printf("Num of Tokens:");
        if(scanf(" %d", tokens)!=1){
            return ERROR;
        }
    }
    return SUCCESS;
}

/*
 * Gets all parameters from user by using all the separate "get" functions.
 *
 * tokens - pointer to int which we will enter the number of tokens from user to it.
 * rows - pointer to int which we will enter the number of rows from user to it.
 * columns - pointer to int which we will enter the number of columns from user to it.
 */
//3 lines
int getGameParameters(int* tokens, int* rows, int* columns){
    if(getNumOfRows(rows)!=SUCCESS || getNumOfColumns(columns, *rows)!= SUCCESS || getNumOfTokens(tokens,rows,columns) != SUCCESS){
        return ERROR;
    }
    return SUCCESS;
}

/*
 * Initializing the game board by sizes given by user.
 *
 * board - a max-size X max size- dimension array which symbols a max-sized game board.
 * rows - the number of rows entered by user.
 * columns - the number of columns entered by user.
 */
//3 lines
void initGameBoard(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int rows, int columns){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            board[i][j]=EMPTY_SLOT_SYMBOL;
        }
    }
}

/*
 * Initializing game:
 * - Print's welcome message.
 * - Get game parameters from user.
 * - Sets each player to it's color.
 * - Initializing game board in the requested size and prints it.
 * - Prints first move message
 *
 * player1_color - pointer to char which will sign first player's color.
 * player2_color - pointer to char which will sign second player's color.
 * tokens - pointer to int which contains number of tokens in a row count as win,
 * board - a max-size X max size- dimension array which symbols a max-sized game board.
 * board_side - an array which contains board real dimension as entered by user.
 * curr_player - an int which contains 1 or 2, depends on which player turn is it currently.
 */
//6 lines
int firstSetOfGame(char* player1_color, char* player2_color, char* board_color, int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                   int board_side[]){
    print_welcome_message();
    if(getGameColors(player1_color, player2_color, board_color)!= SUCCESS || getGameParameters(tokens,&board_side[0],&board_side[1])!= SUCCESS){
        return ERROR;
    }
    initGameBoard(board, board_side[0],board_side[1]);
    system("cls");
    print_board(board, board_side, *board_color, *player1_color, *player2_color);

    return SUCCESS;
}

/*
 * Checks if there is a long enough strike for a win in a specific row
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * row - the row to check.
 * columns - the number of columns entered by user.
 */
//12 lines
int checkWinInRow(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int columns){
    int counter=1;
    for(int j=0; j<columns-1; j++){
        if(board[row][j]==board[row][j+1] && counter<tokens){
            *curr=board[row][j];
            counter++;
            continue;
        }
        if(counter==tokens){
            break;
        }
        else{
            counter=1;
            continue;
        }
    }
    return counter;
}

/*
 * Checks if there is a long enough row-strike for a win in the board
 *
 * player1_color - char of first player's color.
 * player2_color - char of second player's color.
 * tokens - num of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//11 lines
int winnerFromRow(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                  const int board_side[]){
    int rows=board_side[0], columns=board_side[1], counter=0;
    char curr='\n';
    for(int i=rows-1; i>=0; i--){
        counter= checkWinInRow(&curr, *tokens, board, i, columns);
        if(counter==*tokens){
            break;
        }
    }
    if (counter==*tokens && curr == *player1_color){
        return PLAYER1;
    }
    else if (counter==*tokens && curr == *player2_color){
        return PLAYER2;
    }
    return NO_WINNER_YET;
}

/*
 * Checks if there is a long enough strike for a win in a specific column.
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * rows - the number of rows entered by user
 * column - the column to check.
 */
//12 lines
int checkWinInColumn(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int rows, int column){
    int counter=1;
    for(int j=rows-1; j>=0; j--){
        if(board[j][column]==board[j-1][column] && counter<tokens){
            *curr=board[j][column];
            counter++;
            continue;
        }
        if(counter==tokens){
            break;
        }
        else{
            counter=1;
            continue;
        }
    }
    return counter;
}

/*
 * Checks if there is a long enough column-strike for a win in the board
 *
 * player1_color - char of first player's color.
 * player2_color - char of second player's color.
 * tokens - num of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//11 lines
int winnerFromColumn(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                     const int board_side[]){
    int rows=board_side[0], columns=board_side[1], counter=0;
    char curr='\n';
    for(int i=0; i<columns; i++){
        counter= checkWinInColumn(&curr, *tokens, board, rows, i);
        if(counter==*tokens){
            break;
        }
    }
    if (counter==*tokens && curr == *player1_color){
        return PLAYER1;
    }
    else if (counter==*tokens && curr == *player2_color){
        return PLAYER2;
    }
    return NO_WINNER_YET;
}

/*
 * Updates row, column and counter by status of check in right-diagonal winner check.
 *
 * row - pointer to current row checked.
 * col - pointer to current column checked.
 * counter - pointer to current counter.
 * status - check status: true if the 2 tokens checked were equal, false otherwise
 */
// 6 lines
void counterRowColUpdateRightDiagonal(int* row, int* col, int* counter, bool status){
    if(status==true){
        *counter+=1;
    }
    if(status==false){
        *counter=1;
    }
    *row-=1;
    *col+=1;
}

/*
 * Checks if there is a long enough strike for a win in a specific right diagonal.
 *
 * curr - pointer in which we will insert the current symbol we checked
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * row - the row of the first item of the right diagonal.
 * column - the column of the first item of the right diagonal.
 * columns - the number of columns entered by user.
 */
//12 lines
int checkWinInRightDiagonal(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int col, int columns){
    int counter=1;
    while(row-1>=0 && col+1<columns && board[row-1][col+1]!=EMPTY_SLOT_SYMBOL){
        if(board[row][col]==board[row-1][col+1] && counter<tokens){
            *curr=board[row][col];
            counterRowColUpdateRightDiagonal(&row, &col, &counter, true);
            continue;
        }
        if(counter==tokens){
            break;
        }
        else{
            counterRowColUpdateRightDiagonal(&row, &col, &counter, false);
            continue;
        }
    }
    return counter;
}

/*
 * Checks if there is a long enough right-diagonal strike for all right diagonals at the upper half of the board.
 *
 * curr - pointer in which we will insert the current symbol we checked.
 * rows - the number of rows entered by user.
 * columns - the number of columns entered by user.
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * counter - pointer in which we will enter the count of equal elements in the diagonal.
 */
//6 lines
void checkFirstColumnRightDiagonal(char* curr, int rows, int columns, const int* tokens , char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter){
    for(int i=rows-1; i>=0; i--){
        if(board[i][0]==EMPTY_SLOT_SYMBOL){
            continue;
        }
        *counter = checkWinInRightDiagonal(curr, *tokens, board, i, 0, columns);
        if(*counter==*tokens){
            break;
        }
    }
}

/*
 * Checks if there is a long enough right-diagonal strike for all right diagonals at the lower half of the board.
 *
 * curr - pointer in which we will insert the current symbol we checked.
 * rows - the number of rows entered by user.
 * columns - the number of columns entered by user.
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * counter - pointer in which we will enter the count of equal elements in the diagonal.
 */
//6 lines
void checkFirstRowRightDiagonal(char* curr, int rows, int columns, const int* tokens , char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter){
    for(int j=0; j<columns; j++){
        if(board[rows-1][j]==EMPTY_SLOT_SYMBOL){
            continue;
        }
        *counter= checkWinInRightDiagonal(curr, *tokens, board, rows-1, j, columns);
        if(*counter==*tokens){
            break;
        }
    }
}

/*
 * Checks if there is a long enough right-diagonal-strike for a win in the board
 *
 * player1_color - char of first player's color.
 * player2_color - char of second player's color.
 * tokens - num of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//10 lines
int winnerFromRightDiagonal(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                            const int board_side[]){
    int rows=board_side[0], columns=board_side[1], counter=0;
    char curr='\n';
    checkFirstColumnRightDiagonal(&curr, rows, columns, tokens, board, &counter);
    if(counter!=*tokens){
        checkFirstRowRightDiagonal(&curr, rows, columns, tokens, board, &counter);
    }
    if (counter==*tokens && curr == *player1_color){
        return PLAYER1;
    }
    else if (counter==*tokens && curr == *player2_color){
        return PLAYER2;
    }
    return NO_WINNER_YET;
}

/*
 * Updates row, column and counter by status of check in left-diagonal winner check.
 *
 * row - pointer to current row checked.
 * col - pointer to current column checked.
 * counter - pointer to current counter.
 * status - check status: true if the 2 tokens checked were equal, false otherwise
 */
//6 lines
void counterRowColUpdateLeftDiagonal(int* row, int* col, int* counter, bool status){
    if(status==true){
        *counter+=1;
    }
    if(status==false){
        *counter=1;
    }
    *row-=1;
    *col-=1;
}

/*
 * Checks if there is a long enough strike for a win in a specific left diagonal.
 *
 * curr - pointer in which we will insert the current symbol we checked
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * row - the row of the first item of the left diagonal.
 * column - the column of the first item of the left diagonal.
 * columns - the number of columns entered by user.
 */
//12 lines
int checkWinInLeftDiagonal(char* curr, int tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int row, int col){
    int counter=1;
    while(row-1>=0 && col-1>=0 && board[row-1][col-1]!=EMPTY_SLOT_SYMBOL){
        if(board[row][col]==board[row-1][col-1] && counter<tokens){
            *curr=board[row][col];
            counterRowColUpdateLeftDiagonal(&row, &col, &counter, true);
            continue;
        }
        if(counter==tokens){
            break;
        }
        else{
            counterRowColUpdateLeftDiagonal(&row, &col, &counter, false);
            continue;
        }
    }
    return counter;
}

/*
 * Checks if there is a long enough left-diagonal strike for all left diagonals at the upper half of the board.
 *
 * curr - pointer in which we will insert the current symbol we checked.
 * rows - the number of rows entered by user.
 * columns - the number of columns entered by user.
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * counter - pointer in which we will enter the count of equal elements in the diagonal.
 */
//6 lines
void checkLastColumnLeftDiagonal(char* curr, int rows,int columns, const int* tokens ,char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter){
    for(int i=rows-1; i>=0; i--){
        if(board[i][columns-1]==EMPTY_SLOT_SYMBOL){
            continue;
        }
        *counter = checkWinInLeftDiagonal(curr, *tokens, board, i, columns-1);
        if(*counter==*tokens){
            break;
        }
    }
}

/*
 * Checks if there is a long enough left-diagonal strike for all left diagonals at the lower half of the board.
 *
 * curr - pointer in which we will insert the current symbol we checked.
 * rows - the number of rows entered by user.
 * columns - the number of columns entered by user.
 * tokens - number of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * counter - pointer in which we will enter the count of equal elements in the diagonal.
 */
//6 lines
void checkFirstRowLeftDiagonal(char* curr, int rows,int columns, const int* tokens ,char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int* counter){
    for(int j=columns-1; j>=0; j--){
        if(board[rows-1][j]==EMPTY_SLOT_SYMBOL){
            continue;
        }
        *counter= checkWinInLeftDiagonal(curr, *tokens, board, rows-1, j);
        if(*counter==*tokens){
            break;
        }
    }
}

/*
 * Checks if there is a long enough left-diagonal-strike for a win in the board
 *
 * player1_color - char of first player's color.
 * player2_color - char of second player's color.
 * tokens - num of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//10 lines
int winnerFromLeftDiagonal(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                           const int board_side[]){
    int rows=board_side[0], columns=board_side[1], counter=0;
    char curr='\n';
    checkLastColumnLeftDiagonal(&curr, rows, columns, tokens, board, &counter);
    if(counter!=*tokens){
        checkFirstRowLeftDiagonal(&curr, rows, columns, tokens, board, &counter);
    }
    if (counter==*tokens && curr == *player1_color){
        return PLAYER1;
    }
    else if (counter==*tokens && curr == *player2_color){
        return PLAYER2;
    }
    return NO_WINNER_YET;
}

/*
 * Checks if the board is full already (when no winner has declared yet)
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//7 lines
int checkTie(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[]){
    int counter=0;
    for(int i=0; i<board_side[1]; i++){
        if(board[0][i]!=EMPTY_SLOT_SYMBOL){
            counter++;
        }
    }
    if(counter==board_side[1]){
        return TIE;
    }
    return NO_WINNER_YET;
}

/*
 * Returns the first non-zero number between 5 numbers given
 *
 * a - first number
 * b - second number
 * c - third number
 * d- fourth number
 * e- fifth number
 */
//10 lines
int firstNonZero(int a,int b,int c, int d, int e){
    if (a!=0){
        return a;
    }
    else if (b!=0){
        return b;
    }
    else if (c!=0){
        return c;
    }
    else if (d!=0){
        return d;
    }
    else{
        return e;
    }
}

/*
 * Checks if there is a winner in the game yet. If there is - returns him, otherwise returns NO_WINNER_YET.
 *
 * player1_color - char of first player's color.
 * player2_color - char of second player's color.
 * tokens - num of tokens strike needed for a win
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 */
//5 lines
int checkWinner(const char* player1_color,const char* player2_color,const int* tokens, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE],
                const int board_side[]){
    return firstNonZero(winnerFromRow(player1_color, player2_color, tokens, board, board_side),
                        winnerFromColumn(player1_color, player2_color, tokens, board, board_side),
                        winnerFromLeftDiagonal(player1_color, player2_color, tokens, board, board_side),
                        winnerFromRightDiagonal(player1_color, player2_color, tokens, board, board_side),
                        checkTie(board, board_side));
}

/*
 * Gets the column to insert token into from user
 *
 * column - pointer to int which we will enter the col to insert into.
 */
//4 lines
int getColumnFromUser(int* column){
    print_enter_column_message();
    if(scanf("%d", column)!=1){
        return ERROR;
    }
    return SUCCESS;
}

/*
 * Gets the current player's color
 *
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 */
//3 lines
char getCurrentPlayerColor( const char player1_color, const char player2_color, const int current_player){
    if(current_player==PLAYER1) {
        return player1_color;
    }
    return player2_color;
}

/*
 * Updates the array which saves all the game moves after an insertion
 *
 * moves_array - array which saves all the game's moves
 * col - the column in which the token inserted
 * moves_counter - pointer to counter of game moves
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 */
//8 lines
void updateMovesArrayInGoodInsertion(int moves_array[][MOVES_ARRAY_DIMENSIONS], int col, int* moves_counter, const char player1_color,
                                     const char player2_color, const int current_player){
    moves_array[*moves_counter][0]=col;
    moves_array[*moves_counter][MOVES_ARRAY_DIMENSIONS-1]=INSERTION;
    if(getCurrentPlayerColor(player1_color, player2_color, current_player) == FIRST_SYMBOL){
        moves_array[*moves_counter][1]=FIRST;
        *moves_counter+=1;
        return;
    }
    moves_array[*moves_counter][1]=SECOND;
    *moves_counter+=1;
}

/*
 * Inserts a token at the top of a column
 *
 * column - the column in which the token should be inserted.
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//7 lines
void insertToColumn(int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
                    const char player2_color, const int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter){
    int i=board_side[0]-1;
    for (; i>=0; i--){
        if(board[i][column-1]!=EMPTY_SLOT_SYMBOL){
            continue;
        }
        board[i][column-1]= getCurrentPlayerColor(player1_color, player2_color, current_player);
        updateMovesArrayInGoodInsertion(moves_array, column, moves_counter, player1_color, player2_color, current_player);
        break;
    }
}

/*
 * Undo last game's move
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 * row - row of token to undo
 * col - col of token to undo
 */
//2 lines
void undoAction(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int moves_array[][MOVES_ARRAY_DIMENSIONS], const int* moves_counter, int row, int col){
    board[row][col]=EMPTY_SLOT_SYMBOL;
    moves_array[*moves_counter][MOVES_ARRAY_DIMENSIONS-1]=UNDO;
}

/*
 * Undo last game's move
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//11 lines
int undo(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter){
    if(*moves_counter==0){
        print_unavailable_undo_redo_message();
        return ERROR;
    }
    *moves_counter-=1;
    int col_to_undo=moves_array[*moves_counter][0]-1;
    for(int i=0; i<board_side[0]; i++){
        if(board[i][col_to_undo]==EMPTY_SLOT_SYMBOL){
            continue;
        }
        undoAction(board, moves_array, moves_counter, i, col_to_undo);
        break;
    }
    return SUCCESS;
}

/*
 * Redo last game's move
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//10 lines
int redo(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter){
    if(moves_array[*moves_counter][MOVES_ARRAY_DIMENSIONS-1]==INSERTION || moves_array[*moves_counter][MOVES_ARRAY_DIMENSIONS-1]==0){
        print_unavailable_undo_redo_message();
        return ERROR;
    }
    else{
        for(int i=board_side[0]-1; i>=0; i--){
            if(board[i][moves_array[*moves_counter][0]-1]!=EMPTY_SLOT_SYMBOL){
                continue;
            }
            redoInsertion(board, moves_array, moves_counter, i, moves_array[*moves_counter][0]-1);
            break;
        }
    }
    return SUCCESS;
}

/*
 * Insert back token in a redo action
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 * row - row of token to redo
 * col - col of token to redo
 */
//8 lines
void redoInsertion(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], int moves_array[][MOVES_ARRAY_DIMENSIONS],int* moves_counter,
                   int row, int col){
    if(moves_array[*moves_counter][1] == FIRST){
        board[row][col]=FIRST_SYMBOL;
    }
    else if(moves_array[*moves_counter][1] == SECOND){
        board[row][col]=SECOND_SYMBOL;
    }
    else{
        board[row][col]=EMPTY_SLOT_SYMBOL;
    }
    moves_array[*moves_counter][MOVES_ARRAY_DIMENSIONS-1]=REDO;
    *moves_counter+=1;
}

/*
 * Navigate between undo and redo in case of negative value inserted by user.
 *
 * column - the value inserted by user
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//5 lines
int undoOrRedo(int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], int moves_array[][MOVES_ARRAY_DIMENSIONS],
               int* moves_counter){
    if (column==-1){
        return undo(board, board_side, moves_array, moves_counter);
    }
    if(column==-2){
        return redo(board, board_side, moves_array, moves_counter);
    }
    return ERROR;
}

/*
 * Checks user insertion and navigate the program to the command which fits the insertion value.
 *
 * column - the value inserted by user
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//11 lines
int userInsertCheck(const int column, char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
                    const char player2_color, const int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter){
    if(column<0){
        return undoOrRedo(column, board, board_side, moves_array, moves_counter);
    }
    else if(column==0 || column > board_side[1]){
        return ERROR;
    }
    else{
        if(board[0][column-1]!=EMPTY_SLOT_SYMBOL){
            print_full_column_message();
            return ERROR;
        }
        else{
            insertToColumn(column, board, board_side, player1_color, player2_color, current_player, moves_array, moves_counter);
            return SUCCESS;
        }
    }
}

/*
 * Full player turn - print messages, collect command, checks it, navigates the program to the correct command and does it.
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game moves
 */
//10 lines
int playerTurn(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char player1_color,
               const char player2_color, int current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter){
    print_chose_move_message(current_player, player1_color, player2_color);
    int user_insert=0;
    if(getColumnFromUser(&user_insert)!=SUCCESS){
        return ERROR;
    }
    int insert_check=userInsertCheck(user_insert, board, board_side, player1_color, player2_color,current_player, moves_array, moves_counter);
    while(insert_check!=SUCCESS){
        if(getColumnFromUser(&user_insert)!=SUCCESS){
            return ERROR;
        }
        insert_check=userInsertCheck(user_insert, board, board_side, player1_color, player2_color,current_player, moves_array, moves_counter);
    }
    return SUCCESS;
}

/*
 * Switch between player 1 and player 2 after a turn.
 *
 * current_player - pointer to current player which need to change
 */
//4 lines
void changePlayer(int* current_player){
    if(*current_player==PLAYER1){
        *current_player=PLAYER2;
        return;
    }
    *current_player=PLAYER1;
}

/*
 * Full game loop - checks for a winner, and if there isn't one - navigates to current player turn and so on until the game ends.
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game's moves
 * winner - pointer to current winner of the game, which sets to 0 at beginning and stays 0 until one player wins.
 * tokens - pointer to amount of tokens-strike needed for a win,
 */
//9 lines
int game(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char* player1_color, const char* player2_color,
         int* current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter, int* winner, int* tokens, char* board_color){
    *winner=checkWinner(player1_color,player2_color,tokens,board, board_side);
    if(*winner!=0){
        print_winner(*winner, *player1_color, *player2_color);
        return DONE;
    }
    if(playerTurn(board, board_side, *player1_color, *player2_color, *current_player, moves_array, moves_counter)==ERROR){
        return ERROR;
    }
    print_board(board, board_side, *board_color, *player1_color, *player2_color);
    changePlayer(current_player);
    return SUCCESS;
}

/*
 * Runs a game and returns success/fail value to return at the end of the program.
 *
 * board - a max-size X max size- dimension array which contains the (might be smaller) game board.
 * board_side - an array which contains board real dimension as entered by user.
 * player1_color - first player's symbol of color.
 * player2_color - second player's symbol of color.
 * current_player - current player whom it's his turn to play.
 * moves_array - array which saves all the game's moves
 * moves_counter - pointer to counter of game's moves
 * winner - pointer to current winner of the game, which sets to 0 at beginning and stays 0 until one player wins.
 * tokens - pointer to amount of tokens-strike needed for a win.
 */
//8 lines
int gameLoop(char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], const int board_side[], const char* player1_color, const char* player2_color,
             int* current_player, int moves_array[][MOVES_ARRAY_DIMENSIONS], int* moves_counter, int* winner, int* tokens, char* board_color){
    int game_res=game(board, board_side, player1_color, player2_color, current_player, moves_array, moves_counter, winner, tokens, board_color);
    while(game_res!=DONE){
        if(game_res==SUCCESS){
            game_res=game(board, board_side, player1_color, player2_color, current_player, moves_array, moves_counter, winner, tokens, board_color);
            continue;
        }
        else {
            return ERROR;
        }
    }
    return SUCCESS;
}

//--------------------------- Main Program -----------------------------//

//8 lines
int main() {
    do{
        system("cls");
        char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE]={{0},{0}};
        int board_side[]={0,0};
        int moves_counter=0, winner=0, curr_player=PLAYER1, tokens=0;
        int moves_array[BOARD_MAX_SIDE*BOARD_MAX_SIDE][MOVES_ARRAY_DIMENSIONS]={{0}, {0}, {0}};
        char player1_color='\n', player2_color='\n', board_color='\n';
        if(firstSetOfGame(&player1_color, &player2_color,&board_color, &tokens, board, board_side)==ERROR){
            return ERROR;
        }
        if(gameLoop(board, board_side, &player1_color, &player2_color, &curr_player, moves_array, &moves_counter, &winner, &tokens, &board_color)==ERROR)
            return ERROR;
        printf("\nWow! That was an exiting game!\n");
        printf("Do you want to play again? (Y/N):");
        char play_again='\n';
        while(play_again!='Y' &&play_again!='N') {
            if (scanf(" %c", &play_again) != 1)
                return ERROR;
        }
        if(play_again=='Y'){
            continue;
        }
        else{
            break;
        }
    }while(1);

    return 0;
}
