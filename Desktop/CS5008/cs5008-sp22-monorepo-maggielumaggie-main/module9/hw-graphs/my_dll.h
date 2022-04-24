// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H
#include <stdlib.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;              // count keeps track of how many items are in the DLL.
    node_t* head;           // head points to the first node in our DLL.
    node_t* tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    dll_t* myDLL= (dll_t*)malloc(sizeof(dll_t));
    if(myDLL == NULL) {
		return NULL;
	}
    myDLL->count = 0;	
	myDLL->head = NULL;
	myDLL->tail = NULL; 
    return myDLL;
}

int dll_size(dll_t* t);

// DLL Empty
// Check if the DLL is empty
// Exits if the DLL is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
    // TODO: Implement me!!
    if(l == NULL) {
        return -1;
    }
    return dll_size(l) == 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
    if(l == NULL) {
		return -1;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t*));
	if(new_node == NULL) {
		return 0;
	}
	new_node->data = item;
	// if the list is empty
	if(l->head == NULL) {
		l->head = new_node;
		l->tail = new_node;
	} else {
		// if the list is not empty
		new_node->next = l->head;
		l->head->previous = new_node;
		l->head = new_node;
	}
	l->count++;
	return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
    if(l == NULL) {
		return -1;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t*));
	if(new_node == NULL) {
		return 0;
	}
	new_node->data = item;
	new_node->next = NULL;
	// if the list is empty
    if (l->tail == NULL) {
        new_node->previous = NULL;
        l->tail = new_node;
		l->head = new_node;
    } else {
		// if the list is not empty
		l->tail->next = new_node;
    	new_node->previous = l->tail;
		l->tail = new_node;
	}
	l->count++;
	return 1; 
}

// Returns the first item in the DLL and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
    void* res;
    if (t == NULL) {
        return (void *)(-1);
    } 
	if(dll_empty(t) || t->head == NULL) {
		return 0;
	}
	res = t->head->data;
	node_t* temp = (node_t*)malloc(sizeof(node_t*));
	temp = t->head->next;
	if (temp != NULL) {
		temp->previous = NULL;
	}
	
	t->head->previous = NULL;
	t->head = temp;
	t->count--;
    return res;
}

// Returns the last item in the DLL, and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
    void* res;
    if (t == NULL) {
        return (void *)(-1);
    } 
	//Returns 0 on failure, i.e. there is noting to pop from the list
	if(dll_empty(t) || t->tail == NULL) {
		return 0;
	}
	res = t->tail->data;
	node_t* temp = (node_t*)malloc(sizeof(node_t*));
	temp = t->tail->previous;
	if (temp != NULL) {
		temp->next = NULL;
	}
	t->tail->previous = NULL;
	t->tail = temp;
	t->count--;
    return res; 
}

// Inserts a new node before the node at the specified position.
// Exits if the DLL is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
    if(l == NULL ) {
		return -1;
	} 
	node_t* new_node = (node_t*)malloc(sizeof(node_t*));
	// Retruns 0 on failure: if allocate memory for the new node is null,
	// or pos is negative or pos is past the size of the list
	if(new_node == NULL || pos < 0 || pos > dll_size(l)) {
		return 0;
	}
	if(pos == 0) {
		dll_push_front(l, item);
		return 1;
	}
	if(pos == dll_size(l)) {
		dll_push_back(l, item);
		return 1;
	}
	//pre is the node before the insertion position
	node_t* pre;
	pre = l->head;
	int i;
	for(i = 0; i < pos - 1; i++) {
		pre = pre->next;
	}
	//next is the node after the insertion position
	node_t* next = pre->next;
	new_node->data = item;
	pre->next = new_node;
	next->previous = new_node;
	new_node->previous = pre;
	new_node->next = next;
	l->count++;
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
    // TODO: Implement me!!
    if(l == NULL) {
        return (void *)(-1);
    }   
    // Returns 0 on failure: if pos is negative, or
	// pos is past the size of the list
	if(pos < 0 || pos >= dll_size(l)) {
		return 0;
	}
	int i;
	node_t* temp = l->head;
	for(i = 0; i < pos; i++) {
		temp = temp->next;
	}
	return temp->data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
    if(l == NULL) {
        return (void *)(-1);
    }
    //Returns 0 on failure: if pos is negative or pos is 
	//past the size of the list.
	if(pos < 0 || pos >= dll_size(l)) {
		return 0;
	}   
    if(pos == 0) {
		dll_pop_front(l);
	}
	if(pos == dll_size(l) - 1) {
		dll_pop_back(l);
	}
	//pre is the node before the removal position
	node_t* pre;
	pre = l->head;
	int i;
	for(i = 0; i < pos - 1; i++) {
		pre = pre->next;
	}
	//cur is the node on the removal position
	node_t* cur = pre->next;
	//next is the node after the removal position
	node_t* next = cur->next;
	pre->next = next;
	next->previous = pre;
	cur->next = NULL;
	cur->previous = NULL;
	l->count--;
	return cur->data;  
}

// DLL Size
// Exits if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
    if(t == NULL) {
        return -1;   
    }  
    return t->count; 
}

// Free DLL
// Exits if the DLL is NULL.
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    node_t* cur = t->head;
	while(cur != NULL) {
		node_t* next = cur->next;
		free(cur);
		cur = next;
	}   
}

// helper function to find the index of a node in a dll
int find_index_dll(dll_t* l, void* data) {
    if (l == NULL) {
        return -1;
    }
    node_t* itr = l->head;
    int index = 0;
    while (itr != NULL && itr->data != data) {
        itr = itr->next;
        index++;
    }
    if (index == dll_size(l)) {
        return -1;
    }
    return index;
}

#endif
