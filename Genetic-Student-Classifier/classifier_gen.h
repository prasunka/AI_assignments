#include <vector>
#include <algorithm>
#include <string>



class GroupingGen{
    public:

    typedef struct chromosome{
        double fitness_val;
        double selection_prob;
        std::vector <int>groupNoOfStudent;

        bool operator<(const chromosome& c) const{
            return fitness_val < c.fitness_val;
        }
    }chromosome;

    GroupingGen(int n, int k, int m, std::vector<std::vector<double>> marks);
    void printChromosome(GroupingGen::chromosome &temp);
    GroupingGen::chromosome rolltheDice();
    void calculateFitness(chromosome *);
    void generatePopulation(int n);
    void calculateSelectionProb(void);
    void crossover(void);
    int mutate(double);
    int generationCount;

    //private:

    int n; // Total students
    int k; // Total groups
    int m; // Total subjects
    std::vector< std::vector<double> > marksofStudent;

    std::vector<chromosome> Population;

};