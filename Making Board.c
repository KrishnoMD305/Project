#include<stdio.h>
char board[3][3]={'1','2','3','4','5','6','7','8','9'};
int main(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf(" %c ", board[i][j]); // There are one space beside each side of %c
            if(j<2){ printf("|");}
        }
        printf("\n");
        if(i<2){printf("---|---|---\n"); }
    }
    return 0;
}
