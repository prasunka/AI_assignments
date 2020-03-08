#include "classifier_gen.h"

#include <iostream>

//#define DEFAULT_VALUES

int main(int argc, char ** argv){
    srand(time(0));
    int n = 9;
    int k = 3;
    int m = 2;

    int TOTAL_ITERATIONS = 1000;
    int MAX_POPULATION = 100;
    double mut_prob = 0.01;

    if(argc>1 && argv[1]!=">"){
        std::cout << "Parsing arguements\n";
        TOTAL_ITERATIONS = std::atoi(argv[1]);
        MAX_POPULATION = std::atoi(argv[2]);
        mut_prob = std::atof(argv[3]);
    }

#ifdef DEFAULT_VALUES
    std::vector<std::vector<double>> marks{ {1,1},
                                            {2,2},
                                            {3,3},
                                            {4,4},
                                            {5,5},
                                            {6,6},
                                            {7,7},
                                            {8,8},
                                            {9,9} };
#endif
#ifndef DEFAULT_VALUES

    std::vector<std::vector<double>> marks;
    std::cerr << "Enter number of students: ";
    std::cin >> n;
    std::cerr << "Enter number of groups to classify into: ";
    std::cin >> k;
    std::cerr << "Enter number of subjects: ";
    std::cin >> m;

    std::cout << "Enter marks of students: " << std::endl;

    for(int i = 0; i < n; ++i){
        std::vector<double> student_marks;
        for(int j = 0; j < m; ++j){
            double mark;
            std::cin >> mark;
            student_marks.push_back(mark);
        }
        marks.push_back(student_marks);
    }

#endif

    GroupingGen* classifier = new GroupingGen(n,k,m,marks);

    classifier->generatePopulation(50);
    std::cout << "---------- Initial Population ----------\n" << std::endl;

    for(auto iter = classifier->Population.begin(); iter != classifier->Population.end(); ++iter){
        GroupingGen::chromosome temp = *iter;
        for(auto i = temp.groupNoOfStudent.begin(); i!=temp.groupNoOfStudent.end(); ++i){
            std::cout << *i << " ";
        }
        std::cout << "\n" << temp.fitness_val << "\n" << std::endl;
    }

    int iterations = 0;
    while(iterations < TOTAL_ITERATIONS){
        std::cout <<iterations << ": ---------- Generating new child ----------\n" << std::endl;

        classifier->crossover();

        std::cout <<iterations << ": ---------- Mutating ----------\n" << std::endl;

        int mut_num = classifier->mutate(mut_prob);

        std::cout << "Mutated " << mut_num << " chromosomes..\n\n";
        while(classifier->Population.size()>=MAX_POPULATION){
            int rand_index = rand()%(classifier->Population.size());
            classifier->Population.erase(classifier->Population.begin()+rand_index);
        }
        classifier->calculateSelectionProb();
        ++iterations;
    }

    std::cout << "---------- Final Results ----------\n" << std::endl;

    std::sort(classifier->Population.begin(),classifier->Population.end());
    GroupingGen::chromosome temp;
    for(auto iter = classifier->Population.begin(); iter != classifier->Population.end(); ++iter){
        temp = *iter;
        for(auto i = temp.groupNoOfStudent.begin(); i!=temp.groupNoOfStudent.end(); ++i){
            std::cout << *i << " ";
        }
        std::cout << "\n" << temp.fitness_val << "\n" << std::endl;
    }

    std::cerr << "\nBest chromosome in final population" << std::endl;
    for(auto i = temp.groupNoOfStudent.begin(); i!=temp.groupNoOfStudent.end(); ++i){
        std::cerr << *i << " ";
    }
    std::cerr << "\nFitness value: " << temp.fitness_val << "\n" << std::endl;

    std::cerr << "\nStudent Classification:\n\n";
    for(int j = 1; j <= k; ++j){
        std::cerr << "Group " << j << ": ";
        for(auto i = temp.groupNoOfStudent.begin(); i!=temp.groupNoOfStudent.end(); ++i){
            if(*i == j)std::cerr << i - temp.groupNoOfStudent.begin() + 1 << " ";
        }
        std::cerr << "\n" << std::endl;
    }

    return 0;
}