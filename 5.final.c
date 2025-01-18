#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
char board[3][3]={'1','2','3','4','5','6','7','8','9'};
void display_board();
void make_move(char play);
bool check_win();
bool check_Draw();
int minimax(char board[3][3], bool isMaximizing,char p,char c);
void computer_move(char play,char c);
void clear();

int main(){
    int mode; char c,p,p1,p2; bool valid=true;
    printf("Enter Mode:\n1.Player vs. Player\n2.Player vs. Computer\n");
    printf("Enter your selection: ");
    while(valid){
    scanf("%d",&mode);
    if(mode == 1 || mode == 2){
        valid=false;
    }else{
        clear();
        printf("Invalid!!You have entered %d. Enter between 1 and 2.\n",mode);
        printf("Enter Mode:\n1.Player vs. Player\n2.Player vs. Computer\n");
        printf("Enter your selection: ");
    }
    }

    if(mode==1){
            bool v=true;
            printf("Enter 1st Player and 2nd Player Choice accordingly:");
            while(v){
                    scanf(" %c %c",&p1,&p2);

                if((p1 != p2) && ((p1=='X' && p2=='O') || (p1=='O' && p2=='X'))){
                    v=false;
                }else{
                    clear();
                    printf("Invalid input..Try again\n");
                    printf("Enter 1st Player and 2nd Player Choice accordingly:");
                }
            }
        clear();
        display_board();
        int i=0;
    while(i<9){
        if(i%2==0){
            printf("Player 1st(%c): Your Move:",p1);
            make_move(p1);
            clear();
            display_board();
            //Checking winning or draw after each move
            if(check_win()){
                printf("1st Player, you have won!!\n");
                break; // After winning the loop will break and avoid infinite loop
            }
            if(check_Draw()){
                printf("The match is draw!\n");
                break; //After being draw the loop will break and avoid infinite loop
            }
        }else{
            printf("Player 2nd(%c): Your Move:",p2);
            make_move(p2);
            clear();
            display_board();
            //Checking winning or draw after each move
            if(check_win()){
                printf("2nd Player, you have won!!\n");
                break; // After winning the loop will break and avoid infinite loop
            }
            if(check_Draw()){
                printf("The match is draw!\n");
                break; //After being draw the loop will break and avoid infinite loop
            }
        }
        i++;
    }
    }else{
        bool d=true;
            printf("Enter Player Choice (X or O):");
            while(d){
                    scanf(" %c",&p);
                    if(p=='X' || p=='O'){
                        d=false;
                    }else{
                        printf("Invalid Selection!! Please select X or O.\n");
                        printf("Enter Player Choice (X or O):");
                    }
            }

        if(p=='X'){
            c='O';
        }else{
            c='X';
        }
        clear();
        display_board();
        int i=0;
        while(i<9){
            if(i%2==0){ //For player's move
                printf("Player(%c) your move: ",p);
                make_move(p);
                clear();
                display_board();
                if(check_win()){
                    printf("Player you have won!!\n");
                    break;
                }
                if(check_Draw()){
                    printf("The match is draw !!\n");
                    break;
                }
            }else{ //For computer's move
                printf("Computer move:\n");
                computer_move(p,c);
                clear();
                display_board();
                if(check_win()){
                    printf("Computer have won!!\n");
                    break;
                }
                if(check_Draw()){
                    printf("The match is draw !!\n");
                    break;
                }

            }
            i++;
        }
    }

    return 0;
}

void display_board(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf(" %c ", board[i][j]); // There are one space beside each side of %c
            if(j<2){ printf("|");}
        }
        printf("\n");
        if(i<2){printf("---|---|---\n"); }
    }
}
void make_move(char play){
    int choice; bool valid=false;
    while(!valid){
    scanf("%d",&choice);
    if(choice>=1 && choice<=9){
        int r=(choice-1)/3;
        int c=(choice-1)%3;
        if(board[r][c]!='X' && board[r][c]!='O'){
            board[r][c]=play;
            valid=true;
        }else{
            printf("The cell is already taken. Try again!\n");
        }
    }else{
        printf("Invalid Input.Choose from 1 to 9\n");
    }
    }
}
bool check_win(){ //To check if a player has won or not
    for(int i=0; i<3; i++){
            //Checking column and row
        if((board[i][0]==board[i][1]&&board[i][1]==board[i][2]) || (board[0][i]==board[1][i]&&board[1][i]==board[2][i])){
            return true;
        }
    }
    //Checking diagonal
    if((board[0][0]==board[1][1]&&board[1][1]==board[2][2])||(board[0][2]==board[1][1]&&board[1][1]==board[2][0])){
        return true;
    }
    return false;
}
bool check_Draw(){//Check if the game is draw or not
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]!='X' && board[i][j]!='O'){
                return false;
            }
        }
    }
    return true;
}
//Algorithm for computer to make a optimal move
int minimax(char board[3][3], bool isMaximizing,char p,char c) {
    /*if isMaximizing is true then the last move was given by player for that player has won
    and this is the negetive point for computer. So returns -1 */
    if (check_win()) {
        return isMaximizing ? -1 : 1;
    }
    if (check_Draw()) { //Checks draw
        return 0;
    }

    if (isMaximizing) { // For computer move virtually
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = c;
                    int score = minimax(board, false,p,c); //false mean that computer has given it's move, next is player's
                    board[i][j] = backup;
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else { //For player move virtually
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = p;
                    int score = minimax(board, true,p,c); //True means player has given his/her move,next is computer's
                    board[i][j] = backup;
                    bestScore = (score < bestScore) ? score : bestScore; //As we want to minimize the score of player
                }
            }
        }
        return bestScore;
    }
}
//For making move if the computer
void computer_move(char play,char c) {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    // Iterate through all cells to find the best move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if the cell is empty
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = play; // Simulate the move
                int score = minimax(board, false, play, c); //false mean that computer has given it's move, next is player's
                board[i][j] = backup; // Undo the move
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = c;
    }
}
void clear(){
    #ifdef _WIN32
            system("cls"); // Clear console in Windows
    #else
        printf("\033[H\033[J"); // Clear console in Unix/Linux/MacOS
    #endif
}

