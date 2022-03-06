#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
char Player;
char Computer;

struct leaderboard{
    char name[50];
    int moves;
}player;

//Functions list

void playerSelect(); //V
void printBoard(); //V
void resetBoard(); //V
int checkFreeSpace(); //V
void playerMoves(); //V
void computerMoves(); //V
void displayWinner(char winner); //V
char checkWinner(); //V
void leaderboardSaves();



int main(){

    char winner = ' ';
    char response = ' ';

   do
   {
        player.moves = 0;

        printf("\nWELCOME TO TIC TAC TOE\n");
        printf("\npress to start\n");
        getchar();
        
        playerSelect();


        winner = ' ';
        response = ' ';
        resetBoard();

      while(winner == ' ' && checkFreeSpace() != 0)
      {
         if(Player == 'X'){

            printBoard();

            playerMoves();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }

            computerMoves();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }
         }else if(Player == 'O'){

            computerMoves();
            printBoard();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }

            playerMoves();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }

         }
      }

      printBoard();
      displayWinner(winner);
    
      getchar();
      puts("Would you like to play again? (Y/N)");
      scanf("%c", &response);
      getchar();

      response = toupper(response);
   } while (response == 'Y');

    if(winner == Player) leaderboardSaves();

   printf("Thanks for playing!");
    

    return 0;
}



void playerSelect(){

    printf("Please Select 'X' Or 'O' : ");
    scanf("%c", &Player);
    getchar();
    if(Player == 'X'){
        printf("Player as 'X', Computer as 'O'.");
        printf("\n");
        Computer = 'O';
    }
    else if(Player == 'O'){
        printf("Player as 'O', Computer as 'X'.");
        printf("\n");
        Computer = 'X';
    }
    else{
        printf("Error\n");
    }
}

void printBoard(){

    puts("");
    printf(" %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
    puts("---|---|---");
    printf(" %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
    puts("---|---|---");
    printf(" %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
    puts("");

}

void resetBoard(){

    system("cls");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j] = ' ';
        }
    }
   
}

int checkFreeSpace(){
    
    int freeSpaces = 9;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!=' '){
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}

void playerMoves(){

    int x, y;
    
    do
    {
        puts("Enter row 1-3 (x) >>");
        scanf("%d",&x);
        puts("Enter coloumn 1-3 (y) >>");
        scanf("%d",&y);
        x--; y--;

        

        if(board[x][y] !=' '){
            puts("Invalid Move!");
        }
        else{
            board[x][y] = Player;
            player.moves++;
            break;
        }

    } while (board[x][y] !=' ');
    
}

void computerMoves(){

    srand(time(0));
    int x, y;

    if(checkFreeSpace()){

        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = Computer;
        
    }else{
        displayWinner(' ');
    }
}

//print winner
void displayWinner(char winner){

    if(winner == Player){
        puts("You Win!!");
    }else if(winner == Computer){
        puts("You Lose!!");
    }else{
        puts("Draw!!");
    }
}

char checkWinner(){

    //check rows
    for(int i=0;i<3;i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            return board[i][0];
        } 
    }
    //check coloumns
    for(int i=0;i<3;i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            return board[0][i];
        } 
    }
    //check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        return board[0][2];
    }

    return ' ';
}

void leaderboardSaves(){

    // if win , option to save data (name and moves) is available
    puts("Save data?  (Y/N)");
    char answer;
    scanf("%c",&answer);
    getchar();

    answer = toupper(answer);

    if(answer == 'Y'){
        FILE *fp = fopen("saves.txt","a");
        puts("Enter your name : ");
        scanf("%[^\n]",&player.name);
        getchar();

        fprintf(fp,"%s - %d moves\n",player.name,player.moves);

        fclose(fp);

        FILE *file = fopen("saves.txt","r");

        while(!feof(file)){
            char temp[50];
            int Temp;
            fscanf(fp,"%s - %d moves\n",&temp,&Temp);
            if(strcmp(temp, player.name)){
                puts("Data Successfully Saved !");
                break;
            }
        }

        fclose(file);
    
    }else{
        return;
    }

}
