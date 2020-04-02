# AI_assignments

**1. N-Queen problem using uniform cost search:**

    The code solves the N-queen problem using UCS. First an empty chessboard is taken which is considered
    the initial state. The children of the state are the possible queen positions in the next unfilled
    column to the right. The step cost for each child is 1 units and the open list is implemented using
    a min priority queue.
    Edit the N value in the code and recompile to generate solutions.



**2. Travelling Salesman Problem using A\* algorithm:**

    Given n cities and the distance between them, this program finds the path with least distance which
    passes through each city once. A sample dataset of 4 cities has been coded in the program and an
    additional dataset of 15 cities has been provided in a text file.

    Dataset from: https://people.sc.fsu.edu/~jburkardt/datasets/cities/lau15_dist.txt


**3. Student classifier using Genetic Algorithm:**

    Given N students's marks in M subjects, this classifier groups them into K groups using Genetic
    Algorithm. For implementation details and build instructions, see the README inside the
    Genetic-Student-Classifier directory.

**4. Game of Sticks:**

    A game of sticks using Min/Max game tree and Alpha-Beta pruning.

    Compile:
    g++ game-of-sticks.cpp -o gos -Wall

    Run:
    ./gos