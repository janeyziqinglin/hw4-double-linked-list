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
typedef struct node
{
    int data;
    struct node *next;
    struct node *previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL
{
    int count;    // count keeps track of how many items are in the DLL.
    node_t *head; // head points to the first node in our DLL.
    node_t *tail; // tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t *create_dll()
{
    // Modify the body of this function as needed.
    dll_t *myDLL = (dll_t*)malloc(sizeof(dll_t));
    
    // TODO: Implement me!!
    myDLL -> count = 0;
    myDLL -> head = NULL;
    myDLL ->tail = NULL;

    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t *l)
{
    // TODO: Implement me!!
    if (l->count == 0){
        return 1;
    }
    else if (l->count > 0){
        return 0;
    }
    return -1;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t *l, int item)
{
    // TODO: Implement me!!
    if (l == NULL) return -1;

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) return 0; 

    newNode -> data = item;
    newNode -> previous = NULL;
    newNode -> next = NULL;
    //insert node in an empty list
    if (dll_empty(l)==1){
        l -> head = newNode;
    }
    //push front 
    else {
        newNode -> next = l -> head;
        l -> head -> previous = newNode;
        l -> head = newNode;
    }
    l -> count++;
    return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t *l, int item)
{
    // TODO: Implement me!!
    //inserted l is NULL case
    if (l == NULL) return -1;

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) return 0; 

    newNode -> data = item;
    newNode -> previous = NULL;
    newNode -> next = NULL;
    //insert node in an empty list
    if (dll_empty(l)==1){
        l -> head = newNode;
    }
    //push back 
    else {
        l ->tail = l -> head;
        while (l ->tail -> next != NULL){
            l ->tail = l ->tail -> next;
        }
        l ->tail -> next = newNode;
        newNode -> previous = l ->tail;
    }

    // else {
    //     node_t* tmp = l->head; 
    //     while (tmp -> next != NULL){
    //         tmp = tmp -> next;
    //     }
    //     tmp -> next = newNode;
    //     newNode -> previous = tmp;
    // }
    l -> count++;
    return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t *t)
{
    int tmp = -1;
    // TODO: Implement me!!
    if (t == NULL) return -1;

    if (dll_empty(t)==1) return 0; 

    //if head is the only node to be deleted
    if (dll_size(t)==1){
        tmp = t -> head -> data;
        t -> head = NULL;
        t -> count--;
        return tmp;
    }
    else{
        tmp = t -> head -> data;
        t -> head = t -> head -> next;
        free(t -> head -> previous);
        t -> head -> previous = NULL;
        t -> count--;
        return tmp;
    }
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t *t)
{
    // TODO: Implement me!!
    int tmp = -1;
    if (t == NULL) return -1;

    if (dll_empty(t)==1) return 0; 

    t -> tail  = t -> head;
    //if tail is the only node to be deleted
    if (dll_size(t)==1){
        tmp = t -> tail -> data;
        t -> tail = NULL;
        t -> count--;
        return tmp;
    }

    else{
        node_t* newtail;
        while (t ->tail -> next != NULL){
            t ->tail = t ->tail -> next;
        }
        tmp = t -> tail -> data;
        newtail = t -> tail -> previous;
        newtail -> next = NULL;
        free(t -> tail);

        t -> count--;
        return tmp;
    }
}

//pos starting at 0
// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t *l, int pos, int item)
{
    // TODO: Implement me!!
    if (l == NULL) return -1;

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) return 0; 
    if (pos < 0 || pos > dll_size(l)-1) return 0;

    newNode -> data = item;
    newNode -> previous = NULL;
    newNode -> next = NULL;

    //insert node in an empty list
    if (dll_empty(l)==1){
        l -> head = newNode;
        l -> count++;
        return 1;
    }
    if (pos == dll_size(l)-1){
        dll_push_back(l,item);
    }
    //insert intermediate
    else {
        node_t* tmp = l->head; 
        node_t* tmp2;
        while (pos != 0){
            tmp = tmp -> next;
            pos--;
        }
        tmp2 = tmp-> next;
        tmp -> next = newNode;
        tmp2 -> previous = newNode;
        newNode -> next = tmp2;
        newNode -> previous = tmp;
        l -> count++;
        return 1;
    }
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_get(dll_t *l, int pos)
{
    // TODO: Implement me!!
    int res = -1;
    if (l == NULL) return -1;

    if (pos < 0 || pos > dll_size(l)-1) return 0;

    node_t* tmp = l->head; 
    while (pos != 0){
            tmp = tmp -> next;
            pos--;
        }
    res = tmp -> data;

    return res;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
// Otherwise returns the value of the node removed.
int dll_remove(dll_t *l, int pos)
{
    // TODO: Implement me!!
    if (l == NULL) return -1;

    if (pos < 0 || pos > dll_size(l)-1) return 0;

    //if only 1 node 
    if (dll_size(l)==1){
        dll_pop_front(l);
    }
    //remove intermediate
    else {
        node_t* tmp = l->head; 
        node_t* tmp2;
        while (pos != 0){
            tmp = tmp -> next;
            pos--;
        }
        //if remove last node
        if (tmp -> next == NULL){
            dll_pop_back(l);
        } else {
            tmp2 = tmp-> previous;
            tmp2 -> next = tmp -> next; 
            tmp -> next ->previous = tmp2;
            free(tmp);
        }
        l -> count--;
        return 1;
    }
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t *t)
{
    if (t == NULL) return -1;
    // TODO: Implement me!!
    return t -> count; // Note: This line is a 'filler' so the code compiles.
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t *t)
{
    // TODO: Implement me!!
    node_t* itr1 = t->head; 
    node_t* tmp; 
    while (itr1 != NULL){
        tmp =itr1->next;
        free(itr1);
        itr1 = tmp;
    }
    free(t);
}

#endif