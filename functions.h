#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct operation
{
    // used on the file reading process
    int* valueReadMachine; 
    int* valueReadOpTime;
    int counter; // to count the number of machines inside an operation
    // actual machines and operation time
    int* machineOperationTime;
    int* machineNumber;
    struct operation* next; // next position on the list
} operation;

// create nodes at run time
operation* createNode(int qt);
// create the list from the file
operation* createNodeFile(operation** head, int* valueReadMachine, int* valueReadOpTime, int qt);
// insert at the head
operation* insertAtHead(operation** head, operation* node_to_insert);
// insert at the tail or a specified position
operation* insertNodeList(operation** head, operation* node_to_insert, operation* position);
// calculate maximum operating time
int maximumOperationTime(operation* head);
// calculate minimum operating time
int minimumOperationTime(operation* head);
// calculate average operating time
int averageOperationTime(operation* head);
// delete the node chosen by the user
void deleteNode(operation** head, operation* value);
// modify an operation / add a machine, delete a machine or change the operation time of a machine
void modifyOperation(operation** head, operation* nodeToModify, int addMachine, int addOpTime, int option);
// find the node chosen by the user
operation* find_node(operation* head, int position);
// print all the list
void printLinkedList(operation* head);
// updates the file
void writeFile(operation* head);
// brings all the data from the file
operation* readFile(operation** head);
