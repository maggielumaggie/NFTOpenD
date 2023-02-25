from re import sub
import matplotlib.pyplot as plt
import networkx as nx
import generator as gen
"""
These are Function Headers
Complete the functions to ensure they return expected results
Replace these comments with documenation about the program
@author [Mengqi Lu]
"""
def max_value(G, node):
    """
    Computes the maximum possible payoff for player 0 in the subtree rooted at node
    """
    # If a node is a leaf, return the payoff of player 0
    if G.out_degree(node) == 0: 
        return G.nodes[node]['utility'][0] 

    # initialize value to negative infinity 
    value = float('-inf')

    # Update the value with the maximin of the children
    for child in G.successors(node):
        value = max(value, min_value(G, child))
    return value

def min_value(G, node):
    """ 
    Computes the minimum possible payoff for player 0 in the subtree rooted at node
    """
    # If a node is a leaf, return the payoff of player 0
    if G.out_degree(node) == 0:  
        return G.nodes[node]['utility'][0] 

    # initialize value to positive infinity  
    value = float('inf')

    # Update the value with the minmax of the children
    for child in G.successors(node):
        value = min(value, max_value(G, child))
    return value

def minimax(G):
    """
    Returns player 0's payoff of Game Tree G after minimax has run
    """

    # Corner case: G is empty
    if len(G) == 0:
        return None
    
    # Assume player 0 wants to maximize score
    return max_value(G, list(G.nodes)[0])

def alphabeta_helper(G, node, alpha, beta, maximizing_player, edges_to_remove):
    """
    Return the utility, prune G
    """
    # If the current node has no children, return its utility value
    if G.out_degree(node) == 0:
        return G.nodes[node]['utility'][0]

    if maximizing_player:   
        v = float('-inf')
        for child in G.successors(node):
            # Since it's the next player's turn, switch the maximizing player flag to False
            child_value = alphabeta_helper(G, child, alpha, beta, False, edges_to_remove)
            v = max(v, child_value)
            alpha = max(alpha, v)
            # If alpha is greater than or equal to beta, we can stop evaluating other nodes
            # because the opponent will never choose this path
            if alpha >= beta:
                # Add the remaining edges to edges_to_remove to prune them
                edges_to_remove += ([(node, c) for c in G.successors(node) if c != child])
                break  # beta cutoff
        return v
    else:
        v = float('inf')
        for child in G.successors(node):
            # Since it's the our turn, switch the maximizing player flag to True
            child_value = alphabeta_helper(G, child, alpha, beta, True, edges_to_remove)
            v = min(v, child_value)
            beta = min(beta, v)
            # If alpha is greater than or equal to beta, we can stop evaluating other nodes
            # because we will never choose this path
            if alpha >= beta:
                # Add the remaining edges to edges_to_remove to prune them
                edges_to_remove += ([(node, c) for c in G.successors(node) if c != child])
                break  # alpha cutoff
        return v

def alphabeta(G):
    # Corner case: G is empty
    if len(G) == 0:
        return None

    root = list(G.nodes())[0]  
    alpha = float('-inf')
    beta = float('inf')
    # Assume the root node is a maximizing player
    maximizing_player = True  
    # Initialize a list to store edges to remove
    edges_to_remove = []
    alphabeta_helper(G, root, alpha, beta, maximizing_player, edges_to_remove)
    # Remove the edges that were pruned
    G.remove_edges_from(edges_to_remove)
    return G


def main():
    """
    Main body of your code below.
    """
    G = gen.exampleGameTree()
    print(nx.forest_str(G))
    for node in G.nodes():
        print(node,G.nodes[node]["utility"])



### Do NOT remove the following lines of code
if __name__ == "__main__":
    main()