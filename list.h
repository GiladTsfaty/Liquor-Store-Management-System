#pragma once
#include "Customer.h"

/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_


/*** Definitions ***/

typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
// Node
typedef struct node
{
    DATA key;
    struct node* next;
}NODE;


// Listc
typedef struct
{
    NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode, void (*freeFunc)(void*));					// erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*));		// return a pointer to the node

BOOL L_free(LIST* pList, void (*freeFunc)(void*));					// free list memory

int L_print(const LIST* pList, void(*print)(const void*));					// print the list content


int L_length(const LIST* pList);       //return list length

void L_insertByNameOrder(LIST* pList, Customer* pCustomer); //insert client by name 


#endif