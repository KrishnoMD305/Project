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
    while(!valid){ //while is used to let us again choose if we select wrong cell
    scanf("%d",&choice);
    if(choice>=1 && choice<=9){
        int r=(choice-1)/3; //for row
        int c=(choice-1)%3; //for column
        if(board[r][c]!='X' && board[r][c]!='O'){ //Checking the cell if it is wrong or not
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
int main(){
    //Checking if the functions written above is correct
    display_board();
    int i=0;
    while(5){
        if(i%2==0){
            make_move('X');
            display_board();
        }else{
            make_move('O');
            display_board();
        }
        i++;
    }
    return 0;
}
//After executing it is shown that the functions are correct

