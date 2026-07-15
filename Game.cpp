#include <iostream>
#include <ctime>
#include <vector>

void print_board(std::vector<std::vector<char>>* board);
void player_move(std::vector<std::vector<char>>* board , char player);
bool check_winner(std::vector<std::vector<char>>& board);
void computer_move(std::vector<std::vector<char>>* board , char computer);

int main(){
    std::vector<std::vector <char>> board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
    };

    char human = 'X';
    char computer = 'O';
    
    
    print_board(&board);
    std::cout << check_winner(board);
    return 0;
}

void computer_move(std::vector<std::vector<char>>* board , char computer){
    srand(time(NULL));
    int row,col;
    do{
        int choice = rand() % 9 ;
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
    }while((*board)[row][col] != ' ');

    (*board)[row][col] = computer;
}

void player_move(std::vector<std::vector<char>>* board , char human){
    int choice;
    int row,col;
    do{
        std::cout << "Enter your choice num (1-9) :" <<'\n';
        std::cin >> choice;
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
    }while((*board)[row][col] != ' ');

    (*board)[row][col] = human;
}

bool check_winner(std::vector<std::vector<char>>& board){
    if((board[0][0] == board[0][1]) && (board[0][0] == board[0][2]) && (board[0][0] != ' ')) return true;

    if((board[1][0] == board[1][1]) && (board[1][0] == board[1][2]) && (board[1][0] != ' ')) return true;

    if((board[2][0] == board[2][1]) && (board[2][0] == board[2][2]) && (board[2][0] != ' ')) return true;

    if((board[0][0] == board[1][0]) && (board[0][0] == board[2][0]) && (board[0][0] != ' ')) return true;

    if((board[0][1] == board[1][1]) && (board[0][1] == board[2][1]) && (board[0][1] != ' ')) return true;

    if((board[0][2] == board[1][2]) && (board[0][2] == board[2][2]) && (board[0][2] != ' ')) return true;

    if((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] != ' ')) return true;

    if((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] != ' ')) return true;

    return false;
}

void print_board(std::vector<std::vector<char>>* board){
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< (*board)[0][0] <<"  "<< "|" <<"   "<< (*board)[0][1] <<"  "<< "|" <<"   "<< (*board)[0][2]<<"  "<<'\n';
    std::cout <<"______|______|______" <<'\n';
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< (*board)[1][0] <<"  "<< "|" <<"   "<< (*board)[1][1] <<"  "<< "|" <<"   "<< (*board)[1][2]<<"  "<<'\n';
    std::cout <<"______|______|______" <<'\n';
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< (*board)[2][0] <<"  "<< "|" <<"   "<< (*board)[2][1] <<"  "<< "|" <<"   "<< (*board)[2][2]<<"  "<<'\n';
    std::cout <<"      |      |      " <<'\n';
}
