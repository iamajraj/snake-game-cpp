#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int COLUMN = 20;
const int ROW = 10;
const int OFFSET = 1;
const int start_row = 4;
const int start_column = 14;

int player_row = start_row;
int player_column = start_column;
bool gameOver = true;
char board[ROW][COLUMN];
int food_row, food_column;
int score = 1;

enum DIRECTION {
    LEFT = 1,
    RIGHT = 2,
    TOP = 3,
    BOTTOM = 4
};

void logic(DIRECTION dir);

void instruction(){
   cout << "LEFT = 1" << endl;
   cout << "RIGHT = 2" << endl;
   cout << "TOP = 3" << endl;
   cout << "BOTTOM = 4" << endl;
}

void generateFood(){
   food_row = rand() % ROW;
   food_column = rand() % COLUMN;

   if(food_row == 0 || food_column == 0 || food_column == COLUMN-1){
        cout << food_row << food_column << endl;
        generateFood();
   }
}

void setup(){
   gameOver = false;
   generateFood();
   cout << "#### SNAKE GAME ####" << endl;
   cout << "To PLAY do the following steps" << endl;
}

void draw(){
    cout << "Score: " << score <<endl;
     for(int i = 0; i<ROW; i++)
    {
        for(int j = 0; j<COLUMN; j++){
            if(i == 0){
                board[i][j] = '#';
            }
            else if(i == ROW - 1){
                board[i][j] = '#';
            }else if(j == 0 || j == COLUMN - 1){
                board[i][0] = '#';
                board[i][COLUMN - 1] = '#';
            }else if(i == player_row && j == player_column){
                    board[i][j] = 'a';
            }else{
                board[i][j] = ' ';
            }
            if(i == food_row && j == food_column){
                board[i][j] = '*';
            }
        }
    }
     for(int i = 0; i<ROW; i++){
        for(int j = 0; j<COLUMN; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}

void input(){
    instruction();
    start:
    int direction;
    cout << "Move: ";
    cin >> direction;
    cout << endl;
    switch(direction){
        case LEFT:
            logic(LEFT);
            break;
        case RIGHT:
            logic(RIGHT);
            break;
        case TOP:
            logic(TOP);
            break;
        case BOTTOM:
            logic(BOTTOM);
            break;
        default:
            cout << "Wrong Move" << endl;
            cout << "Try again!" << endl;
            goto start;
    }
}

void check(){
    if(player_row == food_row && player_column == food_column){
        score++;
        generateFood();
    }
}

void logic(DIRECTION dir){
    switch (dir){
        case LEFT:
            if((player_column - 1) < OFFSET){
                cout << "You died" << endl;
                gameOver = true;
            }else{
                player_column--;
                check();
            }
            break;
        case RIGHT:
            if((player_column + 1) > (COLUMN-2)){
                cout << "You died" << endl;
                gameOver = true;
            }else{
                player_column++;
                check();
            }
            break;
        case TOP:
             if((player_row - 1) < OFFSET){
                cout << "You died" << endl;
                gameOver = true;
            }else{
                player_row--;
                check();
            }
            break;
        case BOTTOM:
             if((player_row + 1) > (ROW-2)){
                cout << "You died" << endl;
                gameOver = true;
            }else{
                player_row++;
                check();
            }
            break;
        default:
            break;
    }
}

int main(){
    srand ( time(NULL) );
    setup();
    while(!gameOver){
        draw();
        input();
    }
}