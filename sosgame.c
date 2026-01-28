#include <stdio.h>
#include <stdlib.h>

#define EMPTY '.' // instead of writing . everywhere we give it a name

int N; //size of the board
char **board; // this initiates a dynamic size 2D array as a hierarchical memory structure
// char is a single character - either S, O, or .
// then by having 2 layers of pointers we make a 2D grid of characters

int score[2] = {0, 0}; // score vector {player1, player2}

// define the dx and dy for each of the 8 directions we check per move
int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

void init_board(){ //void explains that this function returns nothing
    // here we make the board
    board = malloc(N * sizeof(char *)); // asks the computer for space to store N rows where each row is pointers to N characters

    for (int i = 0; i < N; i++){ // loop 0 to N
        board[i] = malloc(N * sizeof(char)); // now allocate sufficient memory for each row of characters
        for (int j = 0; j < N; j++){ // loop 0 to N again
            board[i][j] = EMPTY; // now we empty each value
        }
    }
}

void print_board(){ //we print the board now

    //print column numbers:
    printf("\n  "); //print a blank line and make some space between column #s
    for (int j = 0; j < N; j++) printf("%d ", j); //print each column # at the top
    printf("\n"); // make new line

    //now print the actual board:
    for (int i = 0; i < N; i++) {
        printf("%d ", i); //print the row number at the start of each row
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j]); //print the actual values in the board 
        printf("\n"); //more space to make it clear
    }
}

int passes_bound_test(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
    //function to check if a (x, y) is in the board
}

// detect SOS
int count_sos(int x, int y, char c) {
    //runs each time a player PLACES something
    int found = 0;

    if (c == 'O') {
        // the O must be in the middle of each SOS
        for (int d = 0; d < 8; d++){ //8 options
            int x1 = x + dx[d];
            int y1 = y + dy[d];
            int x2 = x - dx[d];
            int y2 = y - dy[d];

            if (passes_bound_test(x1, y1) && passes_bound_test(x2, y2)) {
                if (board[x1][y1] == 'S' && board[x2][y2] == 'S'){
                    found++;
                }
            }
        }
    } else if (c == 'S'){
        // S must be in the side
        for (int d = 0; d < 8; d++){ //8 options
            int xo = x + dx[d];
            int yo = y + dy[d];
            int xs = x + 2 * dx[d];
            int ys = y + 2 * dy[d];

            if (passes_bound_test(xo, yo) && passes_bound_test(xs, ys)) {
                if (board[xo][yo] == 'O' && board[xs][ys] == 'S'){
                    found++;
                }
            }
        }
    }

    return found;
}

int board_full() {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (board[i][j] == EMPTY){
                return 0;
            }
        }
    }
    return 1;
    // loop thru all board spaces and see if any are non-empty
}

int main() {
    printf("Enter requested board size: ");
    scanf("%d", &N);

    init_board();

    int player = 0;

    while (!board_full()) {
        print_board();
        printf("\nScores: Player 1: %d | Player 2: %d\n", score[0], score[1]);

        int x, y;
        char c;

        printf("\nPlayer %d turn: Format is row col letter[S/O] (example: 3 1 S): ", player + 1);
        scanf("%d %d %c", &x, &y, &c);

        if (!passes_bound_test(x, y) || board[x][y] != EMPTY || (c != 'S' && c != 'O')) {
            printf("Invalid move. Either invalid coordinates or invalid input (S or O)\n");
            continue;
        }

        board[x][y] = c;

        int gained = count_sos(x, y, c);
        score[player] += gained; //a player could complete multiple SOS in one move, so it's important to add vali damount

        /* if no SOS formed, switch players */
        if (gained == 0)
            player = 1 - player;
    }

    print_board();
    printf("\nGame over! Final Scores: Player 1: %d | Player 2: %d\n", score[0], score[1]);

    if (score[0] > score[1]){
        printf("Player 1 wins!\n");
    }
    else if (score[1] > score[0]){
        printf("Player 2 wins!\n");
    }
    else{
        printf("It's a tie!\n");
    }

    return 0;
}
