#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

struct Move;
void print_board(const std::vector<std::vector<char>>& board);
void player_move(std::vector<std::vector<char>>& board , char player);
void computer_move(std::vector<std::vector<char>>& board , char computer);
char winner(const std::vector<std::vector<char>>& board);
bool check_tie(const std::vector<std::vector<char>>& board);
std::vector<Move> available_spaces(const std::vector<std::vector<char>>& board);
int minmax(std::vector<std::vector<char>>& board,bool maximizingplayer);

struct Move {
    int rows;
    int cols;
};

int main(){
    using std::string,std::cout;

    std::vector<std::vector <char>> board = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
    };

    srand(time(nullptr));
    string turn;
    char human = 'X';
    char computer = 'O';
    char winner_sym = '-';
    
    print_board(board);
    while(true){
        cout <<"---- Your Turn ----" <<'\n';
        turn = "You";
        player_move(board,human);
        print_board(board);
        winner_sym = winner(board);

        if(winner_sym == 'X'){
            cout<< "You won this time , will not last long"<<'\n';
            break;
        }else if(check_tie(board)){
            break;
        }

        cout <<"My Turn Thinking......" <<'\n';
        turn = "Computer";
        computer_move(board ,computer);
        print_board(board);
        winner_sym = winner(board);

        if(winner_sym == 'O'){
            cout<< "I won Come next time :)"<<'\n';
            break;
        }else if(check_tie(board)){
            break;
        }
    }
    return 0;
}


void computer_move(std::vector<std::vector<char>>& board , char computer){
    int best_row = -1;
    int best_col = -1;
    int best_score = -10000;
    char winner_sym = winner(board);
    // vector of struct Move ----  available spaces
    std::vector<Move> moves = available_spaces(board);

    for(const Move& move: moves){
        board[move.rows][move.cols] = computer;
        int score = minmax(board,false);
        board[move.rows][move.cols] = ' ';
        if(score > best_score){
            best_score = score;
            best_row = move.rows;
            best_col = move.cols;
        }
    }
    board[best_row][best_col] = computer;
}

int minmax(std::vector<std::vector<char>>& board,bool maximizingplayer){
    int score;
    char winner_sym = winner(board);
    int best_score;

    if(winner_sym == 'O') return 10;
    if(winner_sym == 'X') return -10;
    if(check_tie(board)) return 0;
    
    std::vector<Move> moves = available_spaces(board); // vector of struct Move 

    if (maximizingplayer){
        //computer move
        best_score = -10000;
        for(const Move& move: moves){
            board[move.rows][move.cols] = 'O';
            score = minmax(board,false);
            board[move.rows][move.cols] = ' ';
            best_score = std::max(best_score,score);
        }
        return best_score;
    }
    else{
        //player move
        best_score = 10000;
        for(const Move& move: moves){
            board[move.rows][move.cols] = 'X';
            score = minmax(board,true);
            board[move.rows][move.cols] = ' ';
            best_score = std::min(best_score,score);
        }
        return best_score;
    }
}

std::vector<Move> available_spaces(const std::vector<std::vector<char>>& board){
    std::vector<Move> moves;
    for(int i = 0; i < board.size() ;i++){
        for(int j = 0; j < board[0].size();j++){
            if(board[i][j]==' '){
                moves.push_back({i,j});
            }
        }
    }
    return moves;
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
    for(int i = 0;i < board.size(); i++){
        for(int j = 0;j < board[0].size(); j++){
            if(board[i][j] == ' ') return false;
        }
    }
    return true;
}

char winner(const std::vector<std::vector<char>>& board){
    for(int i = 0;i < board.size(); i++){  // rows
        if( board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]){
            if(board[i][0] == 'X'){
                return 'X';
            }else{
                 return 'O';
            }
        } 
    }

    for(int j = 0;j < board[0].size(); j++){  // cols
        if( board[0][j] != ' ' &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]){
            if(board[0][j] == 'X'){
                return 'X';
            }else{
                return 'O';
            }
        } 
    }

    if( (board[0][0] == board[1][1]) && // diagonal elements
        (board[1][1] == board[2][2]) && 
        (board[0][0] != ' ')){
        if(board[0][0] == 'X'){
            return 'X';
        }else{
            return 'O';
        }
    }
    if( (board[0][2] == board[1][1]) && // anti diagonal elements
        (board[0][2] == board[2][0]) && 
        (board[0][2] != ' ')){
        if(board[0][2] == 'X'){
            return 'X';
        }else{
            return 'O';
        }
    }
    return '-';
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
