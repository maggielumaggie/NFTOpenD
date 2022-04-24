#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free
#include "my_graph.h"

// Tests create
int unitTest1(int status){
    int passed = 0;
    graph_t* test = create_graph();
    if (graph_num_nodes(test) == 0){
        passed = 1;
    } else{
        passed = 0;
    }
    free_graph(test);

    return passed;
}


// Tests add_mode
int unitTest2(int status){
    int passed = 0;
    graph_t* test = create_graph();
    graph_add_node(test, 1);
    if (graph_num_nodes(test) == 1){
        passed = 1;
    } else{
        passed = 0;
    }
    free_graph(test);

    return passed;
}


// Tests add_mode and remove_node
int unitTest3(int status){
    int passed = 0;
    graph_t* test = create_graph();
    graph_add_node(test, 1);
    graph_remove_node(test, 1);
    if (graph_num_nodes(test) == 0){
        passed = 1;
    } else{
        passed = 0;
    }
    free_graph(test);

    return passed;
}

// Tests contains_edge
int unitTest4(int status){
    int passed = 0;
    graph_t* test = create_graph();
    graph_add_node(test, 1);
    graph_add_node(test, 2);
    graph_add_edge(test, 1, 2);
    if (contains_edge(test, 1, 2) == 1){
        passed = 1;
    } else{
        passed = 0;
    }
    free_graph(test);

    return passed;
}

// An array of function pointers to all of the tests
// that main() can use iterate over them.
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
    	printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1)){
    		printf("passed test\n");
    		testsPassed++;	
    	}else{
    		printf("failed test, missing functionality, or incorrect test\n");
    	}
    counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    return 0;
}