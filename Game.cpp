#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>

void print_board(const std::vector<std::vector<char>>& board);
void player_move(std::vector<std::vector<char>>& board , char player);
void computer_move(std::vector<std::vector<char>>& board , char computer);
bool check_winner(const std::vector<std::vector<char>>& board ,const std::string& turn);
bool winning_combinations(const std::vector<std::vector<char>>& board);
bool check_tie(const std::vector<std::vector<char>>& board);

int main(){
    std::vector<std::vector <char>> board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
    };

    srand(time(nullptr));
    std::string turn;
    char human = 'X';
    char computer = 'O';
    
    print_board(board);
    while(true){
        std::cout <<"---- Your Turn ----" <<'\n';
        turn = "You";
        player_move(board,human);
        print_board(board);
        if(check_winner(board,turn)) break;

        std::cout <<"My Turn Thinking......" <<'\n';
        std::this_thread::sleep_for(std::chrono::seconds(2)); // delay 2 secs
        turn = "Computer";
        computer_move(board ,computer);
        print_board(board);
        if(check_winner(board,turn)) break;
    }
    return 0;
}

bool check_winner(const std::vector<std::vector<char>>& board ,const std::string& turn){
    if(winning_combinations(board)){
        std::cout << "Winner is :" << turn <<'\n';
        return true;
    }
    else if(check_tie(board)){
        std::cout << "It is a Tie" << '\n';
        return true;
    }
    return false;
}

void computer_move(std::vector<std::vector<char>>& board , char computer){
    // --- Change in future with minmax algorithm ---
    int row,col;
    do{
        int choice = rand() % 9+1; //selects the random num btw 1- 9
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
    }while(board[row][col] != ' ');
    board[row][col] = computer;
}

void player_move(std::vector<std::vector<char>>& board , char human){
    int choice,row,col;
    while(true){
        std::cout << "Enter your choice num (1-9) :" <<'\n';
        std::cin >> choice;
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
        if((choice < 10 && choice > 0) && ((board[row][col] == ' '))){
            break;
        }else{
            std::cout << "Invalid Choice Enter again .." <<'\n';
        }
    }
    board[row][col] = human;
}

bool check_tie(const std::vector<std::vector<char>>& board){
    for(int i = 0;i < 3; i++){
        for(int j = 0;j < 3; j++){
            if(board[i][j] == ' ') return false;
        }
    }
    return true;
}

bool winning_combinations(const std::vector<std::vector<char>>& board){
    for(int i = 0;i < 3; i++){  // rows
        if( board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        return true;
    }

    for(int j = 0;j < 3; j++){  // cols
        if( board[j][0] != ' ' &&
            board[j][0] == board[j][1] &&
            board[j][1] == board[j][2])
        return true;
    }

    if( (board[0][0] == board[1][1]) && // diagonal elements
        (board[1][1] == board[2][2]) && 
        (board[0][0] != ' ')) 
        return true;

    if( (board[0][2] == board[1][1]) && // anti diagonal elements
        (board[0][2] == board[2][0]) && 
        (board[0][2] != ' ')) 
        return true;

    return false;
}

void print_board(const std::vector<std::vector<char>>& board){
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< board[0][0] <<"  "<< "|" <<"   "<< board[0][1] <<"  "<< "|" <<"   "<< board[0][2]<<"  "<<'\n';
    std::cout <<"______|______|______" <<'\n';
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< board[1][0] <<"  "<< "|" <<"   "<< board[1][1] <<"  "<< "|" <<"   "<< board[1][2]<<"  "<<'\n';
    std::cout <<"______|______|______" <<'\n';
    std::cout <<"      |      |      " <<'\n';
    std::cout <<"   "<< board[2][0] <<"  "<< "|" <<"   "<< board[2][1] <<"  "<< "|" <<"   "<< board[2][2]<<"  "<<'\n';
    std::cout <<"      |      |      " <<'\n';
}
