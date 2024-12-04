
#ifndef _Ultimate_Tic_Tac_Toe_H
#define _Ultimate_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"

template <typename T>
class Ultimate_Tic_Tac_Toe_Board:public Board<T> {
    private:
    int BoardNumber;
    vector<vector<vector<char>>> MiniBoards;
    bool firsttime;
    vector<bool>chosenboards;
    int mini_moves;
    bool alreadyDisplayed;
public:
    Ultimate_Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool mini_win();
    void fill_board(T symbol);
    bool mini_draw();

};
template <typename T>
class Ultimate_Tic_Tac_Toe_Player : public Player<T> {

public:
    Ultimate_Tic_Tac_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Ultimate_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    Ultimate_Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <sstream>

using namespace std;

// Constructor for Ultimate_Tic_Tac_Toe_Board
template <typename T>
Ultimate_Tic_Tac_Toe_Board<T>::Ultimate_Tic_Tac_Toe_Board() {
    MiniBoards.assign(9, vector<vector<char>>(3, vector<char>(3, 0)));
 // 9 grids, each 3x3, initialized with 0
    alreadyDisplayed=false;
    firsttime=true;
    this->n_moves = 0;
    chosenboards.resize(9);
    BoardNumber=0;
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    mini_moves=0;
}
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::mini_draw(){
    return mini_moves==9;

}
template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::fill_board(T symbol){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            MiniBoards[BoardNumber][i][j]=symbol;
        }
    }
}
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::mini_win(){
    int boardnumber = BoardNumber;
        for (int i = 0; i < this->rows; i++) {
        if ((MiniBoards[boardnumber][i][0] == MiniBoards[boardnumber][i][1] && MiniBoards[boardnumber][i][1] == MiniBoards[boardnumber][i][2] && MiniBoards[boardnumber][i][0] != 0) ||
            (MiniBoards[boardnumber][0][i] == MiniBoards[boardnumber][1][i] && MiniBoards[boardnumber][1][i] == MiniBoards[boardnumber][2][i] && MiniBoards[boardnumber][0][i] != 0)) {
            return true;
        }
    }
    if ((MiniBoards[boardnumber][0][0] == MiniBoards[boardnumber][1][1] && MiniBoards[boardnumber][1][1] == MiniBoards[boardnumber][2][2] && MiniBoards[boardnumber][0][0] != 0) ||
        (MiniBoards[boardnumber][0][2] == MiniBoards[boardnumber][1][1] && MiniBoards[boardnumber][1][1] == MiniBoards[boardnumber][2][0] && MiniBoards[boardnumber][0][2] != 0)) {
        return true;
    }

    return false;
}
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    if(mini_win()||mini_draw()){
        alreadyDisplayed=true;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (MiniBoards[BoardNumber][x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
        }
        else {
            MiniBoards[BoardNumber][x][y]=toupper(mark);
            mini_moves++;
            if(mini_win()){
                fill_board(mark);
                 this->n_moves++;
                this->board[BoardNumber/3][BoardNumber%3]=toupper(mark);
            }
        }

        return true;
    }
    return false;
}
// Display the board and the pieces on it
template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::display_board() {
    if(alreadyDisplayed){
        return;
    }
    int board_count = MiniBoards.size();
int grids_per_row = 3;

for (int row = 0; row < grids_per_row; ++row) {
    for (int col = 0; col < grids_per_row; ++col) {
        int grid_index = row * grids_per_row + col;
        if (grid_index < board_count) {
            cout << "              Board " << grid_index + 1 << setw(34);
        }
    }
    cout << "\n";
    cout<<endl;

    for (int i = 0; i < 3; ++i) {
        for (int col = 0; col < grids_per_row; ++col) {
            int grid_index = row * grids_per_row + col;
            if (grid_index < board_count) {
                cout << "| ";
                for (int j = 0; j < 3; ++j) {
                    cout << "(" << i << "," << j << ") "<<MiniBoards[grid_index][i][j]<<setw(5) << " |";
                }
            }
            cout << "  ";
        }
        cout << "\n";
        cout<<endl;
    }
    cout << string(110, '-') << "\n";
}

}

// Returns true if there is any winner
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::game_is_over() {
    if( is_win() || is_draw()){
        return true;
    }
    else{
    if(mini_win() || firsttime ||mini_draw())
    {
        int n;
        cout<<"Enter the boardnumber from (1-9): ";
        while(true){
            cin>>n;
            if(chosenboards[n-1] ||n<=0 ||n>9){
                cout<<"please enter a valid value: ";
            
            }
            else {
                break;
            }
            
        }
        mini_moves=0;
        BoardNumber=n-1;
        firsttime=false;
        chosenboards[BoardNumber]=true;
        alreadyDisplayed=false;
    }
    return false;
    }
}
//--------------------------------------

// Constructor for Ultimate_Tic_Tac_Toe_Player
template <typename T>
Ultimate_Tic_Tac_Toe_Player<T>::Ultimate_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {
}
template <typename T>
void Ultimate_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    
    if(!this->boardPtr->update_board(-1,-1,this->symbol)){
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    }
    
    
    
}

// Constructor for Ultimate_Tic_Tac_Toe_Random_Player
template <typename T>
Ultimate_Tic_Tac_Toe_Random_Player<T>::Ultimate_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Ultimate_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //_3X3Ultimate_Tic_Tac_Toe_H

