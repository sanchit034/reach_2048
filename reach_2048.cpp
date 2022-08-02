#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

class game2048
{
public:
    int board[4][4], boxFilled, gameOver, gameWon, score;
    game2048();
    void initiate();
    void printBoard();
    void applyMove(int, int, int, int);
    bool noMoveLeft();
};



void instructionSet(){
	cout<<"-------------------------------------------------------------------------------------"<<endl;
    cout<<"|Press n for new game, q to quit game, w for up, s for down, a for left, d for right|"<<endl;
    cout<<"-------------------------------------------------------------------------------------"<<endl;
}

void startMenu(){
	cout<<"----------------------"<<endl;
	cout<<"| Can You reach 2048 |"<<endl;
	cout<<"|Press n for new game|"<<endl;
	cout<<"----------------------"<<endl;
}

int main(){
    startMenu();
    char input;
    cout<<"Enter your move: ";
    cin>>input;
    while(input!='n'&&input!='N'){
    	cin>>input;
	}
	game2048 game;
	game.printBoard();
	cout<<"Enter your move: ";
	cin>>input;
    while(input!='q'&&input!='Q'){            
        if(input=='n'||input=='N'){
            memset(game.board, 0, sizeof(game.board));
            game.boxFilled=0;
            game.initiate();
            game.gameOver=0;
            game.gameWon=0;
            game.printBoard();
        }
        if(game.gameOver==0&&game.gameWon==0){
            if(input=='w'||input=='W'){
                game.applyMove(0, 0, 1, 0);
                game.printBoard();
            }
            else if(input=='s'||input=='S'){                
                game.applyMove(3, 0, -1, 0);
                game.printBoard();
            }
            else if(input=='a'||input=='A'){
                game.applyMove(0, 0, 0, 1);
                game.printBoard();
            }
            else if(input=='d'||input=='D'){
                game.applyMove(0, 3, 0, -1);
                game.printBoard();
            }
        }
        if(game.gameWon==1){
            game.printBoard();
            game.gameWon=2;
            cout<<"--------------------------------------------------------------------"<<endl;
            cout<<"|You won the game the game. Press n to start new game or q to quit.|"<<endl;
            cout<<"--------------------------------------------------------------------"<<endl;
        }
        cout<<"Enter your move: ";
        cin>>input;
    }
    cout<<"------------"<<endl;
    cout<<"|Game Ended|"<<endl;
    cout<<"------------"<<endl;
}


game2048::game2048(){
    memset(board, 0, sizeof(board));
    boxFilled=0;
    gameOver=0;
    gameWon=0;
    score=0;
    this->initiate();
}
void game2048::initiate(){
    int exist=2, row, col;
    while(exist){
        row=(rand()%4);
        col=(rand()%4);
        exist=board[row][col];
        }
    board[row][col]=2;
    boxFilled++;
}
void game2048::printBoard(){
	instructionSet();
    int i, j, k;
    for(i=0; i<4; i++){
        for(k=0; k<25; k++){
                cout<<"-";
            }
            cout<<endl;
        for(j=0; j<4; j++){
            cout<<"|";
            if(board[i][j])
                cout<<setw(5)<<board[i][j];
            else
                cout<<setw(5)<<" ";
        }
        cout<<"|"<<endl;
    }
    for(k=0; k<25; k++){
        cout<<"-";
    }
    cout<<endl;
    cout<<"|       Score"<<setw(5)<<score<<"      |"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<endl;
}
void game2048::applyMove(int startRow, int startCol, int rowChange, int colChange){
    int i, j, k, endRow=startRow+4*rowChange, endCol=startCol+4*colChange, change=0;
    for(i=endRow-2*rowChange; i!=startRow-rowChange; i-=rowChange){
        for(j=0; j<4; j++){
            k=i+rowChange;
            while(k!=endRow){
                if(board[k][j]==0){

                }
                else if(board[i][j]==0){
                    board[i][j]=board[k][j];
                    board[k][j]=0;
                    change=1;
                }
                else if(board[i][j]!=board[k][j]){
                    break;
                }
                else{
                    board[i][j]*=2;
                    board[k][j]=0;
                    score+=board[i][j];
                    change=1;
                    if(board[i][j]==2048)
                        gameWon=1;
                    boxFilled--;
                }
                k+=rowChange;
            }
        }
    }
    for(j=0; j<4; j++){
        i=startRow+rowChange;
        k=i+rowChange;
        while(k!=endRow){
            if(board[i][j]==0){
                if(board[k][j]!=0){
                    board[i][j]=board[k][j];
                    board[k][j]=0;
                    k+=rowChange;
                    i+=rowChange;
                }
                else{
                    k+=rowChange;
                }
            }
            else{
                i+=rowChange;
                if(i==k)
                    k+=rowChange;
            }
        }
    }
    
    for(i=endCol-2*colChange; i!=startCol-colChange; i-=colChange){
        for(j=0; j<4; j++){
                k=i+colChange;
            while(k!=endCol){
                if(board[j][k]==0){

                }
                else if(board[j][i]==0){
                    board[j][i]=board[j][k];
                    board[j][k]=0;
                    change=1;
                }
                else if(board[j][i]!=board[j][k]){
                    break;
                }
                else{
                    board[j][i]*=2;
                    board[j][k]=0;
                    score+=board[j][i];
                    change=1;
                    if(board[j][i]==2048)
                        gameWon=1;
                    boxFilled--;
                }
                k+=colChange;
            }
        }
    }
    for(j=0; j<4; j++){
        i=startCol+colChange;
        k=i+colChange;
        while(k!=endCol){
            if(board[j][i]==0){
                if(board[j][k]!=0){
                    board[j][i]=board[j][k];
                    board[j][k]=0;
                    k+=colChange;
                    i+=colChange;
                }
                else{
                    k+=colChange;
                }
            }
            else{
                i+=colChange;
                if(i==k)
                    k+=colChange;
            }
        }
    }
    if(gameWon){
        return ;
    }
    if(boxFilled==16){
        if(noMoveLeft()){
        	cout<<"---------------------------------------------------"<<endl;
            cout<<"|Game Over. Press n to start new game or q to quit|"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            gameOver=1;
        }
        else if(change){
            initiate();
        }
    }
    else if(change)
        initiate();
}
bool game2048::noMoveLeft(){
    int i, j;
    for(i=0; i<4; i++){
        for(j=0; j<3; j++){
            if(board[i][j]==board[i][j+1])
                return false;
            if(board[j][i]==board[j+1][i])
                return false;
        }
    }
    return true; 
}
