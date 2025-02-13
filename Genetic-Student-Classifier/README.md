# Student Classifier using Genetic Algorithm

## The Problem:

Classify N students into K groups on the basis of their marks in M subjects such that inter-group diversity is maximised and intra-group diversity is minimised.

## The Genetic Approach:

Genetic Algorithm is inspired by the process of natural selection found in nature. It is a way to solve optimisation problems by evolving a set of initial population (candidate solutions) in each generation. To prevent the algorithm from getting stuck in a local minima, randomness is introduced in each step of the algorithm.

## The Implementation:

This implementation of Genetic algorithm has the following flow:

1. Generate inital population
2. Choose two parents from the current population
3. Crossover
4. Add the generated child to the population(keep the parents)
5. Apply a limit on the maximum population(default: 100) after which random death occurs.
6. Mutate a small percentage of population (Default probability: 0.001, configured by variable **mut_prob**)
7. Go to step 2 till No. of iterations < TOTAL_ITERATIONS (default : 1000)

The fitness function uses the n-dimensional euclidean distance formula to calculate distance between groups.
## Build and Run


> git clone https://github.com/prasunka/AI_assignments
>
> cd Genetic-Student-Classifier
>
> make

To run:
> ./student-classifier <TOTAL_ITERATIONS> <MAX_POPULATION> <MUT_PROB>

for e.g.
> ./student-classifier 1000 100 0.1

Or run with default configuration:

> ./student-classifier

**Note**: To run the built-in test case given below, go to **classifier-tool.cpp** and on line **5**, remove the comment.

### Inbuilt test case:
No. of student: 9 <br/>
No. of groups: 3 <br/>
No. of subjects: 2 <br/>
Marks: <br/>
1 1 <br/>
2 2 <br/>
3 3 <br/>
4 4 <br/>
5 5 <br/>
6 6 <br/>
7 7 <br/>
8 8 <br/>
9 9 <br/>

**Optimal solution:**

Fitness value: 50.9117

Student Classification:

Group 1: 4 5 6 <br/>
Group 2: 7 8 9 <br/>
Group 3: 1 2 3 <br/>

**Note:** See **test-output** file for complete output (big file! go to end for final result).

## References

1. *Artificial Intelligence: A Modern Approach (Stuart J. Russell, Stuart Jonathan Russell, Peter Norvig, Ernest Davis)*

2. *CROSSOVER OPERATORS IN GENETIC ALGORITHMS: A REVIEW (A.J. Umbarkar and P.D. Sheth)*

3. *Clustering by a genetic algorithm with biased mutation operator (Benjamin Auffarth)*