#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef struct cityNode {

    std::vector <int> parentPath;
    int city;
    double dist_from_initial;
    double obj_fn;

}cityNode;

struct compare{
    bool operator()(cityNode n1,cityNode n2){
        return n1.obj_fn > n2.obj_fn;
    }
};

int isGoal(cityNode node, int n){
    for(int i = 0; i < n; i++){
        if(i==node.city)continue;
        if(node.parentPath.size() == n){
            if(std::find(node.parentPath.begin(),node.parentPath.end(),i) == node.parentPath.end())return 0;
        }
        else return 0;
    }
    return 1;
}

int isExpandable(cityNode node, int i){
    if(std::find(node.parentPath.begin(),node.parentPath.end(),i) != node.parentPath.end()){
        return 0;
    }
    if(i == node.city)return 0;
    return 1;
}
int main(){
    int N = 4;
    int graph[N][N] = {
        {0,2,3,5,},
        {2,0,3,2,},
        {3,3,0,1,},
        {5,2,1,0 }
    };
    
    cityNode initial;
    initial.city = 0;
    initial.dist_from_initial = 0;
    initial.obj_fn = 0;
    initial.parentPath.push_back(-1);

    std::priority_queue <cityNode, std::vector<cityNode>, compare> open;
    std::vector <cityNode> closed;

    open.push(initial);
    while(!open.empty()){
        cityNode tmp = open.top();
        open.pop();
        //std::cout << "Popped : " << tmp.city << "Obj_fn: " << tmp.obj_fn<<"\nChildren: \n"; 
        if(isGoal(tmp,N)){
            for(int i:tmp.parentPath){
                if(i!=-1)std::cout << i <<"->";
            }
            std::cout << tmp.city <<"->" << initial.city << std::endl;
            std::cout << "Total cost : "<<(tmp.dist_from_initial + graph[tmp.city][0]) << std::endl;
            break;
        }
        for(int i = 0; i < N; i++){
            if(isExpandable(tmp,i)){
                //cityNode *newCity = (struct cityNode *)malloc(sizeof(cityNode));
                cityNode nextcity;
                nextcity.city = i;
                nextcity.dist_from_initial = tmp.dist_from_initial+graph[tmp.city][i];
                nextcity.parentPath = tmp.parentPath;
                nextcity.parentPath.push_back(tmp.city);
                nextcity.obj_fn = nextcity.dist_from_initial + graph[i][initial.city];

                //std::cout << i << "\n";

                open.push(nextcity);
            }
        }
    }
    return 0;
}