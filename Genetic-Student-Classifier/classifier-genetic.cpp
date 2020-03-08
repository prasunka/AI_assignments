#include <iostream>
#include <time.h>
#include <cmath>

#include "classifier_gen.h"

GroupingGen::GroupingGen(int n, int k, int m, std::vector<std::vector<double>>marks){
    this->n = n;
    this->k = k;
    this->m = m;

    this->marksofStudent = marks;
}

void GroupingGen::generatePopulation(int p){
    int gen_no = 0;
    while(gen_no < p){
        chromosome generated;
        int groups[k] = {0};
        while(generated.groupNoOfStudent.size()!=this->n){
            int group_no = (rand() % this->k) + 1;
            if(groups[group_no-1] < ((double)this->n/this->k)){
                generated.groupNoOfStudent.push_back(group_no);
                ++groups[group_no - 1];
            }
        }
        calculateFitness(&generated);
        Population.push_back(generated);
        ++gen_no;
    }
    calculateSelectionProb();
}

void GroupingGen::calculateFitness(chromosome *c){
    double groups_attributes[k][m]={0};
    for(int i = 0; i < k; ++i){
        for(int j = 0; j < c->groupNoOfStudent.size(); ++j){
           if(c->groupNoOfStudent[j]==i+1){
                for(int a = 0; a < m; ++a){
                    groups_attributes[i][a]+=marksofStudent[j][a];
                }
           }
        }
    }

    double fitness_value = 0;
    for(int i = 0; i < k-1; ++i){
        for(int j = i+1; j < k; ++j){
            double sqrt_inside = 0;
            for(int a = 0; a < m; ++a){
                sqrt_inside += pow((groups_attributes[i][a] - groups_attributes[j][a]),2);
            }
            fitness_value += pow(sqrt_inside,0.5);
        }
    }
    c->fitness_val = fitness_value;
}

void GroupingGen::calculateSelectionProb(){
    double sum = 0;
    for(auto iter=Population.begin(); iter!=Population.end(); ++iter){
        sum += iter->fitness_val;
    }
    for(auto iter=Population.begin(); iter!=Population.end(); ++iter){
        iter->selection_prob = iter->fitness_val/sum;
    }
}

GroupingGen::chromosome GroupingGen::rolltheDice()
{
	double prob_dist[Population.size()];
    prob_dist[0] = Population[0].selection_prob*100;
    for(int i = 1; i < Population.size(); ++i){
        prob_dist[i] = prob_dist[i-1]+Population[i].selection_prob*100;
    }
    int rand_val = (rand()%100) + 1;
    if(rand_val <= prob_dist[0]) return Population[0];

    for(int i = 1; i < Population.size(); ++i){
        if(rand_val > prob_dist[i-1] && rand_val <= prob_dist[i]){
            return Population[i];
        }
    }
    //Something here
    return Population[Population.size()-1];
}

void GroupingGen::printChromosome(GroupingGen::chromosome &temp){
    for(auto i = temp.groupNoOfStudent.begin(); i!=temp.groupNoOfStudent.end(); ++i){
            std::cout << *i << " ";
        }
        std::cout << "\n" << temp.fitness_val << "\n" << std::endl;
}

void GroupingGen::crossover(){

        chromosome parent,second_parent;
        parent = rolltheDice();
        second_parent = rolltheDice();

        std::cout << "Parent pairs : " << std::endl;
        printChromosome(parent);
        printChromosome(second_parent);

        chromosome child;
        int rand_index = rand()%n;
        for(int i = 0; i < rand_index + 1; ++i){
            child.groupNoOfStudent.push_back(parent.groupNoOfStudent[i]);
            for(int j = 0; j < second_parent.groupNoOfStudent.size(); ++j){
                if(second_parent.groupNoOfStudent[j]==parent.groupNoOfStudent[i]){
                    second_parent.groupNoOfStudent.erase(second_parent.groupNoOfStudent.begin()+j);
                    break;
                }
            }
        }

        for(int i = 0; i < second_parent.groupNoOfStudent.size(); ++i){
            child.groupNoOfStudent.push_back(second_parent.groupNoOfStudent[i]);
        }

        calculateFitness(&child);
        std::cout << "Crossover point : " << rand_index << std::endl;
        printChromosome(child);

        Population.push_back(child);

}

int GroupingGen::mutate(double probability){
    int count = 0;
    for(auto iter = Population.begin(); iter != Population.end(); ++iter){

        double rand_val = (double)rand() / RAND_MAX;
        if(rand_val <= probability){
            int rand_index1 = rand() % n;
            int rand_index2 = rand() % n;

            double temp = iter->groupNoOfStudent[rand_index1];
            iter->groupNoOfStudent[rand_index1] = iter->groupNoOfStudent[rand_index2];
            iter->groupNoOfStudent[rand_index2] = temp;
            ++count;

            std::cout << "Mutation: fitness before " << iter->fitness_val<< std::endl;
            calculateFitness(&(*iter));

            std::cout << "Mutation: fitness after " << iter->fitness_val << std::endl;
        }

    }
    return count;
}