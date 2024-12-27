#include<stdio.h>
#include<stdbool.h>
char board[3][3]={'1','2','3','4','5','6','7','8','9'};
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
int main(){
    display_board();
    int i=0;
    while(5){
        if(i%2==0){
            printf("Player 1st: Your Move:");
            make_move('X');
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
            printf("Player 2nd: Your Move:");
            make_move('O');
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
    printf("Game Completed");
    return 0;
}
