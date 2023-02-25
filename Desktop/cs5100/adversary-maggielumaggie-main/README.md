[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10224643&assignment_repo_type=AssignmentRepo)
# Homework- Adversarial Search ♞🎲♠️🁽🎰🀄

Topics: Minimax and AlphaBeta

## Part 0 - Pre-req

The code uses the NetworkX library [networkx.org](https://networkx.org/) for graph generation and rendering. Documentation can be found [here](https://networkx.org/documentation/stable/tutorial.html). To install, use the command:

```bash
pip install networkx[default]
```

## Part 1 - Instructions

This assignment is meant to ensure that you:

* Understand the concepts of adversarial search
* Can program an agent to traverse a graph along edges
* Experience developing different pruning algorithms
* Apply the basics of Game Theory
* Can argue for chosing one algorithm over another in different contexts

You will update the [adversary.py](adversary.py) file to:

1. Implement a Minimax and AlphaBeta pruning algorithms. Visit [algorithm.md](algorithm.md) for more info.
2. Complete the functions `minimax` and `alphabeta` functions to return their respective results.
    * With Minimax it should return player 0's utility for the game tree.
    * With AlphaBeta it will return a pruned version of the game tree so that edges that are not explored are instead removed.
    * Both of these algorithms should return `None` when the trees are empty
3. Answer the questions in the reflection.

You can use the following code to print the structure of a game tree:

```python
    G = gen.exampleGameTree()
    print(nx.forest_str(G))
    for node in G.nodes():
        print(node,G.nodes[node]["utility"])
```

You may notice the call to `gen.exampleGameTree()`, this creates the tree example given in your textbook. There are other games you can generate using `createRandomGame(rounds, actions, seed=0, isZeroSum=True)` that are completely random i.e. `createRandomGame(3,3,seed=1)` for testing purposes.

Modify the documentation in the program's comments to describe the changes you made.

## Part 2 - Reflection

Update the README to answer the following questions:

1. Describe your experiences implementing these algorithms. What things did you learn? What aspects were a challenge?

    I feel implementing these algorithms weren't very difficult, I wrote my code of min value and max value based on the pseudocode given in the pdf. I learned
    that it really helps to write helper functions, this can seperate code into small boxes then arrange them together. I feel that the prune part is more challenging, because I need to pay more attention on exactly which subtree is valid or not. 

2. These algorithms assumed that you could reach the leaves of the tree and then reverse your way through it to "solve" the game. What if all of the leaves were hundreds of nodes deep? Would you still want to use pruning algorithms? Explain why or why not?

    I think it is still efficient to apply pruning and minmax algorithms even if the tree has hundereds of leaves. Because pruning can actually cut a large amount of subtrees and focus on more necessary and promising branches. Anyway, we can add on some helpful heuristic functions to further reduce the search space.

3. Imagine that you are an agent maximizing their own payoff in the tree, meanwhile your opponent is randomly picking actions. How will this impact the results of the game?

    I have a higher possibily to win the game, since I will have a higher payoff.

4. Explain the what would happen against an opponent who tries to maximize their own utility instead of minimizing yours.

    I need to maximize my utility while preventing opponent from reaching high utility. In the algorithm level, I need to minimize the opponent's utility and
    make some adjustments on pruning and minmax algorithms.


5. What is the "horizon" and how is it used in adversarial tree search?

    Horizon is the depth of the game tree in adversarial tree search, it can used as a maximum number of moves that the algorithm will consider.

---

## Running Tests Locally

You do not have to wait for test results from GitHub because you can run tests on your own computer. The tester uses the program `pytest` which can be installed using the command `pip install -U pytest` (more info available at [https://docs.pytest.org](https://docs.pytest.org/en/stable/getting-started.html)). Use the following command in the terminal.

```bash
pytest
```
