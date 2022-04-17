#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct operation
{
    int* valueReadMachine;
    int* valueReadOpTime;
    int counter; // to count the number of machines inside an operation
    int* machineOperationTime;
    int* machineNumber;
    struct operation* next; // next position on the list
} operation;

operation* createNode(int qt);

operation* createNodeFile(operation** head, int* valueReadMachine, int* valueReadOpTime, int qt);

operation* insertAtHead(operation** head, operation* node_to_insert);

operation* insertNodeList(operation** head, operation* node_to_insert, operation* position);

int maximumOperationTime(operation* head);

int minimumOperationTime(operation* head);

int averageOperationTime(operation* head);

void deleteNode(operation** head, operation* value);

void modifyOperation(operation** head, operation* nodeToModify, int addMachine, int addOpTime, int option);

operation* find_node(operation* head, int position);

void printLinkedList(operation* head);

void writeFile(operation* head);

operation* readFile(operation** head);
