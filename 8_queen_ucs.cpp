#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

#define N 14

typedef struct boardState{
    int chessBoard[N][N];
    int curr_row;
    int cost;
}boardState;

struct compare{
    bool operator()(const boardState &n1,const boardState &n2){
        return n1.cost > n2.cost;
    }
};

bool isValid(boardState node, int c){
    int r = node.curr_row;
    for(int i = 0; i < r; i++){
        if(node.chessBoard[i][c])return false;
    }
    for(int i = 0; i < c; i++){
        if(node.chessBoard[r][i])return false;
    }
    for(int i = r-1, j=c-1; i >= 0 && j >=0; i--,j--){
        if(node.chessBoard[i][j])return false;
    }
    for(int i = r-1, j=c+1; i >= 0 && j < N; i--,j++){
        if(node.chessBoard[i][j])return false;
    }
    return true;
}

bool isGoal(boardState node){
    if(node.curr_row == N)
        return true;
    return false;

}

int main(){
    
    int solution_count = 0;

    auto start = std::chrono::steady_clock::now();

    boardState initial;
    initial.cost = 0;
    initial.curr_row = 0;

    for(int i = 0; i < N; i++){
        for(int j=0; j < N;j++){
            initial.chessBoard[i][j]=0;
        }
    }

    std::priority_queue <boardState, std::vector<boardState>, compare> open;

    open.push(initial);
    while(!open.empty()){
        boardState tmp = open.top();
        open.pop();
        
        if(isGoal(tmp)){
            ++solution_count;
            for(int i = 0; i < N; i++){
                for(int j =0; j < N; j++){
                    std::cout << tmp.chessBoard[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        for(int i = 0; i < N; i++){
            if(isValid(tmp,i)){
                boardState child = tmp;
                child.chessBoard[child.curr_row][i] = 1;
                child.cost += 1;
                ++child.curr_row;
             
                open.push(child);
            }
        }
    }
    std::cout << "No. of solutions: " << solution_count << std::endl;

    auto end = std::chrono::steady_clock::now(); 
    std::cout << "Total time taken : " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              <<" ms" << std::endl;
   
    return 0;
}
