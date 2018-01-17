#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 6
#define MAXPLAYERS 4
typedef struct gamevariables
{
	int boardSizeX;     //dimensions of the board
	int boardSizeY;
	int players;        //number of players and number of penguins each player has
	int penguins;
	int currentPlayer;  //the number of the player taking his
	char filename[50];
	int board[MAXSIZE * 2][MAXSIZE];  //array with the board state
	int score[MAXPLAYERS];      //scores of each player
	int maxmoves; // in interactive mode maximal number of movements or sth like that
}gameV;


void RandomBoard(gameV *parm)
{
    int x = parm->boardSizeX;
    int y = parm->boardSizeY;
    int board [x][y];
    int i,j;
    //fill board with random values
    srand(time(NULL));
      for(i = 0; i < parm->boardSizeX; i++){
        for(j = 0; j < parm->boardSizeY; j++){
            //generate values 0 - 3
            parm->board[i][j] = rand() % 4 ;
        }
      }



}

void display(gameV *parm)
{
    int i,j;
    for(i = 0; i < parm->boardSizeX; i++){
        for(j = 0; j < parm->boardSizeY; j++){
            printf("%d ", parm->board[i][j]);
        }
        printf("\n");
        //move to right every second row
        if(i%2 == 0)
            printf(" ");

    }
    printf("\n");
}



int main()
{
 gameV game;
     gameV *p;
     p= &game;
    p->boardSizeX = 6;
    p->boardSizeY = 6;
    RandomBoard( p);
    display(p);
}

void boardLoad(gameV *parm){
    FILE *input;
    int x, y;
    char temp;
    char Directory[128];

    strcat(Directory, parm->filename);
    input = fopen(Directory, "r");
    if (input == NULL) {
        printf ( "ERROR: '%s' does not exist!\n", parm->filename );
        return;
    }
    x = 0;
    y = 0;
    //ignores scores and current turn in file reading
    while(temp != ';'){
        fscanf(input, "%c", &temp);
    }
    fscanf(input, "%c", &temp);

    while(fscanf(input, "%d", &(parm->board[x][y])) > 0){
        fscanf(input, "%c", &temp);
        while(temp != ';'){
            fscanf(input, "%d", &(parm->board[++x][y]));
            fscanf(input, "%c", &temp);
        }
        while(x < parm->boardSizeX - 1){
            parm->board[++x][y] = 0;
        }
        x = 0;
        y++;
        fscanf(input, "%c", &temp); // ignore new line character and clear ';' from temp
    }
    fclose(input);
}
