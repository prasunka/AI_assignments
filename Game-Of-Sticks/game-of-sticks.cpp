#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <ctime>
#include <map>

void HvH(int n){
    std::string player1,player2;

    std::cout <<"Enter player names\nPlayer 1: ";
    std::cin >> player1;
    std::cout << "Player 2: ";
    std::cin >>player2;

    srand(time(0));

    int toss = 1 + rand()%2;
    int num = 0;

    if(toss == 1){
        std::cout << player1 << " wins toss!\n\n";
        while(n>0){
            std::cout << player1 << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << player1 << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;
            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
            std::cout << player2 << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << player2 << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;

            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
        }
    }

    else{
        std::cout << player2 << " wins toss!\n\n";
        while(n>0){
            std::cout << player2 << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << player2 << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;

            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
            std::cout << player1 << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << player1 << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;

            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
        }
    }
}

int playAvA(int depth, bool wasMaxNode, int sticksLeft, int curr_option,
            std::map<std::pair<int,int>,int>&choices, int alpha, int beta){

    sticksLeft -= curr_option;

        //std::cout << "Currently at " << choices.size() << " entries!" << std::endl;
#ifdef DEBUG
    std::cout << "Called with\n"
                <<"\nDepth: " << depth+1
                <<"\nSticks left: " << sticksLeft
                <<"\nwasMaxNode: " << wasMaxNode
                <<"\nCurrent player: " << (wasMaxNode? "MinNode": "MaxNode")
                <<"\nArrived by path : " << curr_option
                <<std::endl << std::endl;

#endif
    if(sticksLeft < 1){
        if(wasMaxNode)return -1;

        return 1;
    }

    if(wasMaxNode && choices.find({2,sticksLeft})!=choices.end()) return choices[{2,sticksLeft}];
    if(!wasMaxNode && choices.find({1,sticksLeft})!=choices.end()) return choices[{1,sticksLeft}];
    int best_till_now = (wasMaxNode) ? 1 : -1;
    for( int i = 1; i <= 3; i++){
        if(sticksLeft < i)return best_till_now;


        if(wasMaxNode){
            int result = playAvA(depth+1,false,sticksLeft,i,choices,alpha,beta);
#ifdef DEBUG

            std::cout << "Returned to: " << result
                        <<"\nDepth: " << depth+1
                        <<"\nSticks left: " << sticksLeft
                        <<"\nwasMaxNode: " << wasMaxNode
                        <<"\nCurrent player: " << (wasMaxNode? "MinNode": "MaxNode")
                        <<"\nArrived by path : " << curr_option
                        << std::endl<< std::endl;
#endif

            if(result < best_till_now){
                best_till_now = result;
                choices[{2,sticksLeft}] = i;
                return best_till_now;
            }
            beta = std::min(beta,best_till_now);
            if(alpha>=beta) return best_till_now;
            if((i == 3)&&(best_till_now==1)){
                choices[{2,sticksLeft}] = 1;
                return 1;
            }
        }
        else{
            int result = playAvA(depth+1,true,sticksLeft,i,choices,alpha,beta);
#ifdef DEBUG

            std::cout << "Returned to: " << result
                        <<"\nDepth: " << depth+1
                        <<"\nSticks left: " << sticksLeft
                        <<"\nwasMaxNode: " << wasMaxNode
                        <<"\nCurrent player: " << (wasMaxNode? "MinNode": "MaxNode")
                        <<"\nArrived by path : " << curr_option
                        << std::endl<< std::endl;
#endif

            if(result > best_till_now){
                best_till_now = result;
                choices[{1,sticksLeft}] = i;
                return best_till_now;
            }

#ifdef PRUNING
            alpha = std::max(alpha,best_till_now);
            if(alpha>=beta) return best_till_now;
#endif

            if((i == 3)&&(best_till_now==-1)){
                choices[{1,sticksLeft}] = 1;
                return -1;
            }
        }
    }
    return best_till_now;

}
void AvAhelp(int sticks, std::map<std::pair<int,int>,int>&choices){
    int best_till_now = -1;
    for( int i = 1; i <= 3; i++){
        if(sticks < i)break;


        int result = playAvA(1,true,sticks,i,choices,-1,1);
#ifdef DEBUG

        std::cout << "Returned: " << result
                        <<"\nDepth: " << 1
                        <<"\nSticks left: " << sticks
                        <<"\nwasMaxNode: " << true
                        <<"\ncurrent option: " << i
                        << std::endl << std::endl;

#endif
        if(result > best_till_now){
            best_till_now = result;
            choices[{1,sticks}] = i;
        }
        else  choices[{1,sticks}] = 1;
    }
    return;

}
void AvA(int n){
    std::cout << "\n\nGame begins with " << n <<" sticks!\n\n";
    std::map<std::pair<int,int>,int> choices;

    AvAhelp(n,choices);
#ifdef DEBUG
    for (auto iter = choices.begin(); iter!=choices.end(); ++iter){
        std::cout << "{" <<iter->first.first << "," << iter->first.second << "} = " <<iter->second << std::endl;
    }
#endif

    int turn = 1;
    while(n > 0){
        if(turn==1 && n==1){
            std::cout << " AI 1 lost!\n\n";
            break;
        }

        std::cout << "AI 1 chooses " << choices[{1,n}] << " sticks.\n";
        n -= choices[{1,n}];
        if(turn==1 && n<1){
            std::cout << " AI 1 lost!\n\n";
            break;
        }
        std::cout << "Sticks left: " << n << std::endl;

        turn=2;
        if(turn==2 && n==1){
            std::cout << " AI 2 lost!\n\n";
            break;
        }
        std::cout << "AI 2 chooses " << choices[{2,n}] << " sticks.\n";
        n -= choices[{2,n}];
        if(turn==2 && n<1){
            std::cout << " AI 2 lost!\n\n";
            break;
        }
        std::cout << "Sticks left: " << n << std::endl;
        turn=1;
    }
    return;
}

void HvA(int n){
    std::cout << "\n\nGame begins with " << n <<" sticks!\n\n";
    std::map<std::pair<int,int>,int> choices;

    AvAhelp(n,choices);
    std::string human;
    std::cout <<"Enter player name: ";
    std::cin >> human;

    srand(time(0));

    int toss = 1 + rand()%2;
    int num = 0;

    if(toss == 1){
        std::cout << human << " wins toss!\n\n";
        while(n>0){
            std::cout << human << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << human << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;
            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
            std::cout <<"AI chooses " << choices[{2,n}] << std::endl;
            n -= choices[{2,n}];
            if(n < 1) {
                std::cout <<"AI lost! " << human <<" wins." << std::endl;
                break;
            }
        }
    }

    else{
        std::cout << "AI wins toss!\n\n";
        while(n>0){
            if(n==1){
                std::cout <<"AI lost! " << human <<" wins." << std::endl;
                break;
            }
            std::cout <<"AI chooses " << choices[{1,n}] << std::endl;
            n -= choices[{1,n}];
            if(n < 1) {
                std::cout <<"AI lost! " << human <<" wins." << std::endl;
                break;
            }

            std::cout << human << ", choose a number between 1 and 3: ";
            std::cin >> num;
            if(num>=1 && num <=3){
                if(num >= n){
                    std::cout << "\n" << human << " lost!\n";
                    break;
                }
                n -= num;
                std::cout << "Sticks left: " << n << '\n' << std::endl;

            }
            else{
                std::cout << "Wrong value!\n";
                break;
            }
        }
    }

}


int main(){

    int mode = 0;
    std::cout << "\n\t\tWelcome to the Game of Sticks!\n\n";
    sleep(1);
    std::cout   <<"Select game mode :\n"
                <<"1. Human vs Human\n"
                <<"2. Human vs AI\n"
                <<"3. AI vs AI\n"
                <<"\nEnter game mode: ";

    std::cin >> mode;
    sleep(1);
    int n;
    std::cout << "\nHow many sticks in the game? Enter n: ";
                // <<"1. 14\n"
                // <<"2. 21\n"
                // <<"3. 53\n"
                // <<"\nEnter option: ";

    std::cin >> n;
   /* switch(n){
        case 1: n = 14;
                break;
        case 2: n = 21;
                break;
        case 3: n = 53;
                break;

        default: std::cout << "Wrong option!\n";
                exit(EXIT_FAILURE);
    }*/

    switch(mode) {
        case 1: HvH(n);
                break;

        case 2: HvA(n);
                break;

        case 3: AvA(n);
                break;

        default: std::cout << "Incorrect mode selected!\n" << std::endl;
    }

    return 0;
}
