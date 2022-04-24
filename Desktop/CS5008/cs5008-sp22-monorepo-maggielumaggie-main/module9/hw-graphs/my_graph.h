// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h" 
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;
typedef struct graph_node{
    int data;
    int visited;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    graph_t* myGraph= malloc(sizeof(graph_t));
    if(myGraph == NULL) {
        return NULL;
    }
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// int initializeVisited(graph_node_t t) {
//     t.visited = 0;
// }

dll_t* getInNeighbors( graph_t * g, int value );
dll_t* getOutNeighbors( graph_t * g, int value );
graph_node_t * create_graph_node(int value);
dll_t* getInNeighbors( graph_t * g, int value);
dll_t* getOutNeighbors( graph_t * g, int value );

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node(graph_t * g, int value){
    if(g == NULL || g->nodes == NULL) {
        return NULL;
    }
    dll_t* nodes = g->nodes;
    int i;
    for(i = 0; i < nodes->count; i++) {
        graph_node_t* graphNode = (graph_node_t*)dll_get(nodes, i);
        if(graphNode->data == value) {
            return graphNode;
        }
    }
    return NULL;    
}


// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    graph_node->visited = 0;
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    // Returns -1 if the graph is NULL
    if ( g == NULL ) return -1;
    
    // Returns -1 if the value exists
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);

    // Returns -1 if the newNode is NULL
    if ( newNode == NULL ) return -1;
    
    //Returns 0 on failure
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}


// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.

    // Returns -1 if the graph is NULL.
    if(g == NULL || g->nodes == NULL) {
        return -1;
    }
    
    // Returns -1 if the value doesn't exist
    if (find_node(g, value) == NULL) {
        return 0;
    }
    int i;
    for(i = 0; i < getInNeighbors(g, value)->count; i++) {
        dll_remove(getOutNeighbors(g, value), value);
    }

    int j;
    for(j = 0; j < getOutNeighbors(g, value)->count; j++) {
        dll_remove(getInNeighbors(g, value), value);
    }

    
    graph_node_t* graphNode;
    int k;
    for(k = 0; k < g->nodes->count; k++) {
        graphNode = (graph_node_t*)dll_get(g->nodes, k);
        if(graphNode->data == value) {
            dll_remove(g->nodes, k);
        }
    }
    g->nodes--;
    g->numEdges--;
    return 1;
}

int contains_edge( graph_t * g, int source, int destination);

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if(g == NULL || g->nodes == NULL) {
        return -1;
    }
    if(find_node(g, source) == NULL || find_node(g, destination) == NULL || contains_edge(g, source, destination)) {
        return 0;
    }

    graph_node_t* sourceNode = find_node(g, source);
    graph_node_t* destinationNode = find_node(g, destination);
    dll_push_back(sourceNode->outNeighbors, destinationNode);
    dll_push_back(destinationNode->inNeighbors, sourceNode);
    g->numEdges++;
    //g->numEdges++;
    return 1; 
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if(g == NULL || g->nodes == NULL) {
        return -1;
    }

    if(find_node(g, source) == NULL || find_node(g, destination) == NULL || contains_edge(g, source, destination) == 0) {
        return 0;
    }

    graph_node_t* sourceNode = find_node(g, source);
    graph_node_t* destinationNode = find_node(g, destination);

    dll_t* sourceNeighbors = sourceNode->outNeighbors;
    int i;
    for(i = 0; i < sourceNeighbors->count; i++) {
        graph_node_t* graphNode = (graph_node_t*)dll_get(sourceNeighbors, i);
        //if(graphNode ->visited == 0 && 
        if(graphNode->data == destination) {
            dll_remove(sourceNeighbors, i);
        }
    }

    dll_t* destinationNeighbors = destinationNode->inNeighbors;
    int j;
    for(j = 0; j < destinationNeighbors->count; j++) {
        graph_node_t* graphNode = (graph_node_t*)dll_get(destinationNeighbors, j);
        //if(graphNode ->visited == 0 && 
        if(graphNode->data == source) {
            dll_remove(destinationNeighbors, j);
        }
    }
    g->numEdges--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    // Returns -1 if the graph is NULL.
    if(g == NULL || g->nodes == NULL) {
        return -1;
    }

    // Returns 0 on failure ( or if the source or destination nodes don't exist )
    if(find_node(g, source) == NULL || find_node(g, destination) == NULL) {
        return 0;
    }

    dll_t* outNeighbors = getOutNeighbors(g, source);
    int i;
    int found_first = 0;
    int found_second = 0;
    for(i = 0; i < outNeighbors->count; i++) {
        graph_node_t* graphNode = dll_get(outNeighbors, i);
        if(graphNode->data == destination) {
            found_first = 1;
        }
    }
    dll_t* inNeighbors = getInNeighbors(g, destination);

    int j;
    for(j = 0; j < inNeighbors->count; j++) {
        graph_node_t* graphNode = dll_get(inNeighbors, j);
        if(graphNode->data == source) {
            found_second = 1;
        }
    }

    if(found_first && found_second) {
        return 1;
    }
    return 0;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value){
    if(g == NULL || g->nodes == NULL || find_node(g, value) == NULL) {
        return NULL;
    }
    return find_node(g, value)->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    if(g == NULL || g->nodes == NULL || find_node(g, value) == NULL) {
        return -1;
    }
    return getInNeighbors(g, value)->count;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if(g == NULL || g->nodes == NULL || find_node(g, value) == NULL) {
        return NULL;
    }
    return find_node(g, value)->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if(g == NULL || g->nodes == NULL || find_node(g, value) == NULL) {
        return -1;
    }
    return getOutNeighbors(g, value)->count;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if(g == NULL) {
        return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if(g == NULL) {
        return -1;
    }
    return g->numEdges;
}


// helper function to initialize all the graph nodes->visited as unvisited
void reset(graph_t* g) {   
    int i;
    for ( i = 0; i < dll_size(g->nodes); i++) {
        graph_node_t* node = (graph_node_t*)dll_get(g->nodes, i);
        node->visited = 0;
    }
}

//Returns 1 if reachable
//Returns 0 if not reachable.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int is_reachable(graph_t * g, int source, int dest){
    //Implement using BFS.
    //Make sure you don't get stuck into an infinite loop.
    if(g == NULL || find_node(g, source) == NULL || find_node(g, dest) == NULL) {
        return -1;
    }
    if(source == dest) {
        return 1;
    }
    graph_node_t* sourceNode = find_node(g, source);
    sourceNode->visited = 1;

    dll_t* visited = create_dll();
    dll_push_front(visited, sourceNode);
    
    
    int count = visited->count;
    int i;
    for(i = 0; i < count; i++) {
        graph_node_t* node = (graph_node_t*)dll_pop_front(visited);
        node->visited = 1;
        if(node->data == dest) {
            return 1;
        }
        int k;
        dll_t* inNeiNodes = getInNeighbors(g, node->data);
        for(k = 0; k < inNeiNodes->count; k++) {
            dll_push_front(visited, dll_get(inNeiNodes, i));
        }
        
        int j;
        dll_t* outNeiNodes = getOutNeighbors(g, node->data);
        for(j = 0; j < outNeiNodes->count; j++) {
            dll_push_front(visited, dll_get(outNeiNodes, j));
        }
    }
    
    return 0;
}

//Helper function: check whether there is a cycle using DFS
int has_cycle_dfs(graph_node_t* node) {
    if(node->visited == 1) {
        return 1;
    }
    node->visited = 1;

    int k;
    for(k = 0; k < dll_size(node->outNeighbors); k++) {
        graph_node_t* outNeiNode = dll_get(node->outNeighbors, k);
        if(outNeiNode->visited == 0) {
            int res = has_cycle_dfs(outNeiNode);
            if(res == 1) {
                return res;
            }
        }
    }
    return 0;
}


//Returns 1 if the graph has a cycle.
//Returns 0 if the graph doesn't have a cycle.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int has_cycle(graph_t * g){
    //Implement using DFS.
    //Make sure you don't get stuck into an infinite loop.
    if(g == NULL || g->nodes == NULL) {
        return -1;
    }
    return has_cycle_dfs(dll_get(g->nodes, 0));
}

// helper function for print_path
void print_helper(graph_t* g, graph_node_t* sourceNode, int dest, dll_t*stack) {
    if (g == NULL) {
        return;
    }
    if(sourceNode == NULL) {
        return;
    }

    reset(g);
    dll_push_back(stack, &sourceNode->data);
    if(sourceNode->data == dest) {
        node_t* root = stack->head;
        while(root != NULL) {
            printf("%d ->", *((int*)(root->data)));
            root = root->next;
        }
        printf("\n");
        sourceNode->visited = 1;
        return;
    }
    node_t* itr = sourceNode->outNeighbors->head;
    while(itr != NULL) {
        graph_node_t* itr_graph_node = (graph_node_t*)(itr->data);
        if( itr_graph_node->visited == 0) {
            print_helper(g, itr_graph_node, dest, stack);     
        }
        itr = itr->next;
    }
    dll_pop_back(stack);
}

//Prints all the nodes from source to destination ( including the source and destination),
//i.e. print_path(1,5) => 1 2 3 4 5
//otherwise it prints "path does not exit" or if source or dest nodes do not exist or if the graph is NULL.
void print_path(graph_t * g, int source, int dest){
    if(g == NULL || !is_reachable(g, source, dest)) {
        printf("Path does not exist\n");
    }

    graph_node_t* sourceNode = find_node(g, source);
    dll_t* stack = create_dll();
    print_helper(g, sourceNode, dest, stack);
    free_dll(stack);
}


//helper function: free a node from a graph
void free_helper(graph_t* g, graph_node_t* node) {
    if (node->inNeighbors != NULL) {
        free_dll(node->inNeighbors);
    }
    if (node->outNeighbors != NULL) {
        free_dll(node->outNeighbors);
    }
    int index = find_index_dll(g->nodes, node);
    dll_remove(g->nodes, index);
    free(node);
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if (g == NULL) {
        return;
    }
    node_t* itr = g->nodes->head;
    node_t* temp;
    int i;
    for(i = 0; i < g->numNodes; i++) {
        temp = itr->next;
        free_helper(g, itr->data);
        itr = temp;
    }
    free_dll(g->nodes);
    free(g);
}

#endif
