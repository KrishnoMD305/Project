#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void display_board();
void reset_board();
void make_move(char play);
bool check_win();
bool check_draw();
int minimax(char board[3][3], bool isMaximizing, char p, char c);
void computer_move(char play, char c);
int evaluate_board(char board[3][3], char c, char p);
void clear();
void save_score(const char *mode, int score);
int load_score(const char *mode);
void reset_scores();

void display_menu();
void start_game();
void show_high_scores();
void show_tutorial();

int main() {
    char selection; bool v=true;
    while (v) {
        display_menu();
        scanf(" %c", &selection);

        switch (selection) {
            case 's':
            case 'S':
                start_game();
                v=false;
                break;
            case 'h':
            case 'H':
                show_high_scores();
                printf("Press any number and Enter to return main menu:");
                int p; scanf("%d",&p);
                break;
            case 't':
            case 'T':
                show_tutorial();
                printf("Press any number and Enter to return main menu:");
                int r; scanf("%d",&r);
                break;
            case 'e':
            case 'E':
                printf("Exiting the game. Goodbye!\n");
                return 0;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }
}

void display_menu() {
    clear();
    printf("Welcome to the Ultimate Tic-Tac-Toe Game.\n");
    printf("Start Game: Type 's' or 'S'\n");
    printf("High Scores: Type 'h' or 'H'\n");
    printf("Tutorials: Type 't' or 'T'\n");
    printf("Exit: Type 'e' or 'E'\n");
    printf("Enter your selection: ");
}

void start_game() {
    int mode;
    char difficulty;
    char player, computer;
    char name1[20],name2[20];
    printf("Player vs. Player : Enter 1\n");
    printf("Player vs. Computer: Enter 2\n");
    printf("Exit: Enter 0 (Zero)\n");
    printf("Enter your selection: ");

    while (true) {
        scanf("%d", &mode);
        if (mode == 0) return;
        if (mode == 1 || mode == 2) break;
        Beep(750,500);
        printf("Invalid selection. Try again: ");
    }

    if(mode==1){
            printf("Enter the Nickname for the player:");
            scanf("%s",name1);
            printf("Enter the Nickname for the opponent:");
            scanf("%s",name2);
    }


    printf("Easy: Type 'e' or 'E'\n");
    printf("Medium: Type 'm' or 'M'\n");
    printf("Hard: Type 'h' or 'H'\n");
    printf("Enter difficulty level: ");

    while (true) {
        scanf(" %c", &difficulty);
        if (difficulty == 'e' || difficulty == 'E' || difficulty == 'm' || difficulty == 'M' || difficulty == 'h' || difficulty == 'H') {
            break;
        }
        Beep(750,500);
        printf("Invalid difficulty level. Try again: ");
    }

    int player_score = 0, opponent_score = 0;
    int num_matches = (difficulty == 'e' || difficulty == 'E') ? 8 : (difficulty == 'm' || difficulty == 'M') ? 5 : 3;

    for (int match = 0; match < num_matches; match++) {
        reset_board();
        clear();

        printf("Match %d of %d\n", match + 1, num_matches);
        display_board();

        int moves = 0;

        while (true) {
            if (mode == 1) {
                char p1, p2;
                if (moves == 0) {
                    printf("%s choose (X or O): ",name1);

                    bool k=true;
                    while(k){
                        scanf(" %c", &p1);
                        if(p1=='X' || p1=='O'){
                            k=false;
                        }else{
                            Beep(750,500);
                            printf("Invalid!!! Try Again:");
                        }
                    }
                    p2 = (p1 == 'X') ? 'O' : 'X';
                }
                if (moves % 2 == 0) {
                    printf("%s (%c), your move: ",name1, p1);
                    make_move(p1);
                } else {
                    printf("%s (%c), your move: ",name2, p2);
                    make_move(p2);
                }
            } else if (mode == 2) {
                if (moves == 0) {
                    printf("Player choose (X or O): ");
                    bool f=true;
                    while(f){
                        scanf(" %c", &player);
                        if(player=='X' || player=='O'){
                            f=false;
                        }else{
                            Beep(750,500);
                            printf("Invalid!!! Try Again:");
                        }
                    }
                    computer = (player == 'X') ? 'O' : 'X';
                }
                if (moves % 2 == 0) {
                    printf("Player (%c), your move: ", player);
                    make_move(player);
                } else {
                    printf("Computer's turn...\n");
                    computer_move(player, computer);
                }
            }

            clear();
            printf("Match %d of %d\n", match + 1, num_matches);
            display_board();

            if (check_win()) {
                if (mode == 1) {
                    if (moves % 2 == 0) {
                        printf("%s wins this match!\n",name1);
                        printf("\a");
                        player_score += 10;
                    } else {
                        printf("%s wins this match!\n",name2);
                        printf("\a");
                        opponent_score += 10;
                    }
                } else {
                    if (moves % 2 == 0) {
                        printf("Player wins this match!\n");
                        printf("\a");
                        player_score += 10;
                    } else {
                        printf("Computer wins this match!\n");
                        printf("\a");
                        opponent_score += 10;
                    }
                }
                break;
            }

            if (check_draw()) {
                printf("The match is a draw!\n");
                Beep(750,1000);
                player_score += 5;
                opponent_score += 5;
                break;
            }

            moves++;
        }

        printf("\nCurrent Scores:\n");
        printf("Player: %d\n", player_score);
        printf("Opponent: %d\n\n", opponent_score);

        if (match < num_matches - 1) {
            printf("Type 'n' or 'N' to go to the next match: ");
            char next;
            while (true) {
                scanf(" %c", &next);
                if (next == 'n' || next == 'N') break;
                printf("Invalid input. Type 'n' or 'N' to proceed: ");
            }
        }
    }

    printf("\nGame Over. Final Scores:\n");
    printf("Player: %d\n", player_score);
    printf("Opponent: %d\n", opponent_score);

    if(mode==1){
    if(player_score>opponent_score){
        printf("Congratulation %s !!! You have won the game.\n",name1);
        printf("\a\a");
    }else if(player_score<opponent_score){
        printf("Congratulation %s !!! You have won the game.\n",name2);
        printf("\a\a");
    }else{
        printf("The match is a total draw!!!\n");
        Beep(750,1000);
    }
    }else{
        if(player_score>opponent_score){
        printf("Congratulation !!! You have won the game.\n");
        printf("\a\a");
    }else if(player_score<opponent_score){
        printf("Sorry !!! Computer have won the game.\n");
        printf("\a\a");
    }else{
        printf("The match is a total draw!!!\n");
        Beep(750,1000);
    }
    }

    // Determine the final score and difficulty level
    int finalscore = (player_score > opponent_score) ? player_score : opponent_score;

    char dif[20];
    if (difficulty == 'e' || difficulty == 'E') {
        strcpy(dif, "Easy");
    } else if (difficulty == 'm' || difficulty == 'M') {
        strcpy(dif, "Medium");
    } else {
        strcpy(dif, "Hard");
    }

    // Load high score and save if new high score is achieved
    int highScore = load_score(dif);
    printf("Current high score for %s difficulty: %d\n", dif, highScore);
    if (highScore < finalscore) {
        printf("New high score! Saving...\n");
        save_score(dif, finalscore);
    } else {
        printf("No new high score.\n");
    }

}


void show_high_scores() {
    clear();
    printf("High Scores:\n");
    printf("Easy: %d\n", load_score("Easy"));
    printf("Medium: %d\n", load_score("Medium"));
    printf("Hard: %d\n", load_score("Hard"));

    printf("Reset: Type 'r' or 'R'\n");
    printf("Exit: Type 'e' or 'E'\n");
    printf("Enter your selection: ");

    char selection;
    scanf(" %c", &selection);

    if (selection == 'r' || selection == 'R') {
        reset_scores();
        printf("Scores have been reset.\n");
    }
}

void show_tutorial() {
    clear();
    printf("Computer VS Player\n");
    printf("1. Choose one kind of sign 'X' or 'O'.\n");
    printf("2. To defeat the computer, the player must make moves in such a way that there are three selected symbols in a line (horizontally, vertically, or diagonally).\n");
    printf("3. If the computer manages to do this, you will lose.\n");
    printf("4. Winner will get 10 points and Looser will get 0 points.\n");
    printf("5. If the game is Drawed, each will get 5 points.\n\n");

    printf("Two Players\n");
    printf("1. Set the nicknames of two players.\n");
    printf("2. Choose one kind of sign 'X' or 'O'.\n");
    printf("3. To defeat any player, other must make moves in such a way that there are three selected symbols in a line (horizontally, vertically, or diagonally).\n");
    printf("4. Winner will get 10 points and Looser will get 0 points.\n");
    printf("5. If the game is Drawed, each will get 5 points.\n\n");

    printf("General Rules\n");
    printf("1. Try to avoid invalid moves.\n");
    printf("2. There are 3 modes of play:\n");
        printf("    (i). Easy  : It has 10 rounds.\n");
        printf("    (ii) Medium: It has 5 rounds.\n");
        printf("    (iii)Hard  : It has 3 rounds.\n");
}

void reset_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + (i * 3 + j);
        }
    }
}

void make_move(char play) {
    int choice;
    bool valid = false;

    while (!valid) {
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 9) {
            int r = (choice - 1) / 3;
            int c = (choice - 1) % 3;
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                board[r][c] = play;
                valid = true;
            } else {
                printf("The cell is already taken. Try again!\n");
            }
        } else {
            printf("Invalid input. Choose a number from 1 to 9.\n");
        }
    }
}

bool check_win() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

bool check_draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}
int evaluate_board(char board[3][3], char c, char p) {
    // Check rows and columns for win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == c) return 1;
            if (board[i][0] == p) return -1;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == c) return 1;
            if (board[0][i] == p) return -1;
        }
    }

    // Check diagonals for win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == c) return 1;
        if (board[0][0] == p) return -1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == c) return 1;
        if (board[0][2] == p) return -1;
    }

    return 0;
}
int minimax(char board[3][3], bool isMaximizing, char p, char c) {
    int score = evaluate_board(board, c, p);
    if (score != 0) {
            return score; // Return win/loss value directly
    }
    if (check_draw()){
            return 0;  // If draw, return 0
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = c;
                    int score = minimax(board, false, p, c);
                    board[i][j] = backup;
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = p;
                    int score = minimax(board, true, p, c);
                    board[i][j] = backup;
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

void computer_move(char p, char c) {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = c;
                int score = minimax(board, false, p, c);
                board[i][j] = backup;
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

void save_score(const char *mode, int score) {
    FILE *file = fopen("highscores.txt", "r");
    char lines[50][50];
    int count = 0;
    bool updated = false;

    // If the file exists, read its content
    if (file) {
        while (fgets(lines[count], sizeof(lines[count]), file)) {
            char file_mode[20];
            int file_score;
            sscanf(lines[count], "%[^:]: %d", file_mode, &file_score);

            // If the mode matches, update the score if necessary
            if (strcmp(file_mode, mode) == 0) {
                if (score > file_score) {
                    snprintf(lines[count], sizeof(lines[count]), "%s: %d\n", mode, score);
                }
                updated = true;
            }
            count++;
        }
        fclose(file);
    }

    // Add the new mode if it doesn't exist
    if (!updated) {
        snprintf(lines[count], sizeof(lines[count]), "%s: %d\n", mode, score);
        count++;
    }

    // Write the updated content back to the file
    file = fopen("highscores.txt", "w");
    if (!file) {
        perror("Failed to save score");
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(lines[i], file);
    }
    fclose(file);
}

int load_score(const char *mode) {
    FILE *file = fopen("highscores.txt", "r");
    if (!file) return 0; // Return 0 if the file does not exist

    char line[50];
    int high_score = 0;

    // Parse each line to find the matching mode
    while (fgets(line, sizeof(line), file)) {
        char file_mode[20];
        int score;
        if (sscanf(line, "%[^:]: %d", file_mode, &score) == 2) {
            if (strcmp(file_mode, mode) == 0 && score > high_score) {
                high_score = score;
            }
        }
    }

    fclose(file);
    return high_score;
}


void reset_scores() {
    FILE *file = fopen("highscores.txt", "w");
    if (!file) return;
    fclose(file);
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
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


