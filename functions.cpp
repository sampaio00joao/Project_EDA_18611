#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

operation* createNode(int qt)
{
    operation* node = (operation*)malloc(sizeof(operation));

    int inputMachine;
    int inputOpTime;
    int previousMachine = 0;

    int counter = 0;
    //aloccating space for the machines and their operation time.
    node->machineNumber = (int*)malloc(sizeof(int) * qt);
    node->machineOperationTime = (int*)malloc(sizeof(int) * qt);
    
    for (int i = 0; i < qt; i++) {
        printf("Choose the machine to insert in the operation.\n");
        if (scanf("%d", &inputMachine) > 0) {
            if (previousMachine == inputMachine) {
                printf("Machine already in use!\n");
                i--;
            }
            else {
                printf("Choose the time of operation of machine: %d\n", inputMachine);
                if (scanf("%d", &inputOpTime) > 0) {
                    if(inputOpTime != 0) {
                        // adds the new node to the linked list
                        node->machineNumber[i] = inputMachine;  // adds a machine
                        node->machineOperationTime[i] = inputOpTime; //adds a operation time for the machine
                        counter++;
                        node->counter = counter;
                        previousMachine = inputMachine; //update the previous machine to block if the same machine is chosen again
                    }
                    else { 
                        printf("Operation time cant be 0. Starting Over.\n"); 
                        i--; 
                    }
                }
            }
        }
    }
    return node;
} // createNode

operation* createNodeFile(operation** head, int* valueReadMachine, int* valueReadOpTime, int qt)
{
    operation* node = (operation*)malloc(sizeof(operation));
    int counter = 0;

    //aloccating space for the machines and their operation time.
    node->machineNumber = (int*)malloc(sizeof(int)*qt);
    node->machineOperationTime = (int*)malloc(sizeof(int)*qt);
    
    for (int i = 0; i < qt; i++) {
        //printf("%p\n", valueReadMachine[i]);
        //printf("%p\n", valueReadOpTime[i]);
        node->machineNumber[i] = valueReadMachine[i];  // adds a machine
        node->machineOperationTime[i] = valueReadOpTime[i]; //adds a operation time for the machine
        //printf("%p\n", node->machineNumber[i]);
        //printf("%p\n", node->machineOperationTime[i]);
        counter++;
    }
    node->counter = counter;
    return node;
} // createNode

operation* insertAtHead(operation** head, operation* node_to_insert)
{
    // swap method
    node_to_insert->next = *head;
    // by passing a pointer to a pointer to the function, we are able to change the head value inside the function
    *head = node_to_insert;
    return node_to_insert; // returns the node inserted at the head of the list
}

operation* insertNodeList(operation** head, operation* node_to_insert, operation* position){

    operation* lastNode = *head; // the last node points to the head of the list

    if (*head == NULL) { // if the list doesnt have anything yet
        *head = node_to_insert; // add that value to the list
    }
    else if (position != NULL) { //insert node after node in the chosen position
        node_to_insert->next = position->next;
        position->next = node_to_insert;
        return node_to_insert;
    }
    else { // if the list already as one value
        while (lastNode->next != NULL) { // goes through all the list
            lastNode = lastNode->next;
        }
        // until it reaches the end and puts the value on the last position of the list
        lastNode->next = node_to_insert;
    }
    node_to_insert->next = NULL; // the next element is NULL
    return *head; // returns after adding the new node to the list
}

void deleteNode(operation** head, operation* value) {
    
    operation* temporary; //temporary is used to free the memory
    //key found on the head node.
    //move to head node to the next and free the head.
    if ((*head)->machineNumber == value->machineNumber)
    {
        temporary = *head;    //backup to free the memory
        *head = (*head)->next;
        free(temporary); // memory is free
    }
    else
    {
        operation* current = *head;
        while (current->next != NULL)
        {
            //if true, we need to delete the current->next node
            if (current->next->machineNumber == value->machineNumber)
            {
                temporary = current->next;
                //node will be disconnected from the linked list.
                current->next = current->next->next;
                free(temporary);
                break;
            }
            //Otherwise, move the current node and proceed
            else
                current = current->next;
        }
    }
}

operation* find_node(operation* head, int position)
{
    operation* temporary = head;
    // receives the head / no need for double pointer since we dont need
    // to apply changes to the head.
    int counter = 0; // counter used to count repeat the loop until it reaches the operation
    int numberCheck = 0;
    // it will repeat until the return value, and its only true when temporary is allocated
    while (temporary != NULL) 
    {
        if ((counter + 1) == position) {
            return temporary; // returns the operation when it reaches the position/operation inputed by the user
        }
        counter++; //if false, keeps counting
        temporary = temporary->next; // and passing to the next node/operation in the list
    }
    return NULL;
}

void modifyOperation(operation** head, operation* nodeToModify, int addMachine, int addOpTime, int option){

    int bufferMachine[100];
    int bufferOpTime[100];
    int i = 0;
    int counter = 0;
    int previousMachine = 0;
    switch (option) {
    case 1: // add new item
        //adds the new machine and operation time, to the last position inside the operation
        nodeToModify->machineNumber[nodeToModify->counter] = addMachine;
        nodeToModify->machineOperationTime[nodeToModify->counter] = addOpTime;
        nodeToModify->counter++;
        break;
    case 2: // remove machine 
        option = 0;
        printf("Machine to delete: ");
        while (counter < nodeToModify->counter) {
            printf("{%d} ", nodeToModify->machineNumber[counter]);
            counter++;
        }
        counter = 0;
        printf("\n");
        if (scanf("%d", &option) > 0) {
            while (counter < nodeToModify->counter) {
                if (nodeToModify->machineNumber[counter] == option) {
                    bufferMachine[counter] = 0; // the machine to remove will have the value 0
                    bufferOpTime[counter] = 0; // value 0 on the operation time
                }
                else {
                    bufferMachine[counter] = nodeToModify->machineNumber[counter]; // save the node in a buffer
                    bufferOpTime[counter] = nodeToModify->machineOperationTime[counter]; // save the node in a buffer
                }
                counter++;
            }
            for (counter = 0; counter < nodeToModify->counter; counter++) {
                if (bufferMachine[counter] != 0) { // rebuild the operation without the machine deleted
                    nodeToModify->machineNumber[counter] = bufferMachine[counter];
                    nodeToModify->machineOperationTime[counter] = bufferOpTime[counter];
                }
            }
        }
        nodeToModify->counter = counter-1; // decrease one number on the operation counter variable
        // make sure to delete the operation if we delete the last machine available
        if (nodeToModify->counter != 0) { // true if the operation as one or more machines available
            printf("Machine deleted\n");
        }
        else { // delete the operation since there is no machines left
            printf("Last machine available deleted.\n"); 
            printf("Operation deleted.\n");
            deleteNode(head, nodeToModify); // function call to delete, sending nodeToModify, as the node to delete parameter.
        }
        break;

    case 3: // modify the operation time from a machine
        option = 0;
        for (i = 0; i < nodeToModify->counter; i++) {
            if (nodeToModify->machineNumber[i] == option) { // identify the machine chosen
                printf("\nPrevious operation time: %d\n", nodeToModify->machineOperationTime[i]);
                printf("New operation time: ");
                if(scanf("%d", &option) > 0) // reutilizing the option variable
                nodeToModify->machineOperationTime[i] = option; // update the operation time of said machine
            }
            else if(option == 0){ // only choosing an available machine is permited
                printf("Machine to mofify: ");
                while (counter < nodeToModify->counter) { // prints all the machines available
                    printf("{%d} ", nodeToModify->machineNumber[counter]);
                    counter++;
                }
                counter = 0;
                option = 0;
                printf("\n");
                if(scanf("%d", &option) > 0) // user input
                i--;
            }
        }
        break;
    }
}

void printLinkedList(operation* head)
{
    operation* temporary = head;
    int counter = 0;
    int i = 0;
    //temporary->machineNumber = (int*)malloc(sizeof(int));
    // temporary->machineOperationTime = (int*)malloc(sizeof(int));

    while (temporary != NULL)
    { // while its not at the end of the list
        counter++;
        printf("Operation %d:\n", counter);
        for (int i = 0; i < temporary->counter; i++) {
            printf("\tMachine: %d \n", temporary->machineNumber[i]);
            printf("\tOperation Time: %d \n", temporary->machineOperationTime[i]);
        }
        temporary = temporary->next;
    }
    printf("\n");
}

void writeFile(operation* head) {

    int counter = 0;
    operation* temporary = head; // access the data from the linked list 

    char space = '\n'; // used to organize the txt 
    FILE* file = fopen("saveSystem.txt", "w"); // open file in writing mode
    if (file == NULL) {
        printf("Cannot open file."); // error if it fails to open
    }

    while(temporary != NULL){
        counter++; // for printing purposes
        fprintf(file, "%d ", temporary->counter); // used as a reference when reading
        for (int i = 0; i < temporary->counter; i++) {
            // prints all the machines and their operation time inside every operation/node
            fprintf(file, "%d ", temporary->machineNumber[i]);
            fprintf(file, "%d ", temporary->machineOperationTime[i]);
        }
        fprintf(file, "\n", space);
        temporary = temporary->next; // continues through the list
    }
    fclose(file); // closes the file in the end
    //return 1;
}

int maximumOperationTime(operation* head) {
    int sum = 0, max = 0;
    operation* temporary = head;
    while (temporary != NULL) {   
        for (int i = 0; i < temporary->counter; i++) {
            if (i == 0) {
                max = temporary->machineOperationTime[i];
            }
            else if (max <= temporary->machineOperationTime[i]) {
                max = temporary->machineOperationTime[i];
            }
        }
        sum += max;
        temporary = temporary->next;
    }
    return sum;
}

int minimumOperationTime(operation* head) {
    int sum = 0, max = 0;
    operation* temporary = head;
    while (temporary != NULL) {
        for (int i = 0; i < temporary->counter; i++) {
            if (i == 0) {
                max = temporary->machineOperationTime[i];
            }
            else if (max >= temporary->machineOperationTime[i]) {
                max = temporary->machineOperationTime[i];
            }
        }
        sum += max;
        temporary = temporary->next;
    }
    return sum;
}

int averageOperationTime(operation* head) {
    int sum = 0;
    int count = 0;
    operation* temporary = head;
    while (temporary != NULL) {
        for (int i = 0; i < temporary->counter; i++) {
            sum += temporary->machineOperationTime[i];
        }
        count += temporary->counter;
        temporary = temporary->next;
    }
    sum = sum / count;
    return(sum);
}

operation* readFile(operation** head) {
    int saveValue = 0;
    operation* temporary = (operation*)malloc(sizeof(operation));
    operation* createOp; // to record the data on the list

    FILE* file = fopen("saveSystem.txt", "r");
    if (file == NULL) {
        printf("Cannot open file.");
    }
    if (file != 0) { // safety
        while (!feof(file)) {
            // reads the counter variable to know how many machines machines are in the operation
            fscanf(file, "%d ", &saveValue);
            temporary->valueReadMachine = (int*)malloc(sizeof(int) * saveValue);
            temporary->valueReadOpTime = (int*)malloc(sizeof(int) * saveValue);
            for (int i = 0; i < saveValue; i++) { // loops the amount of times needed to fill the operation
                fscanf(file, "%d ", &temporary->valueReadMachine[i]);
                fscanf(file, "%d ", &temporary->valueReadOpTime[i]); 
            }
            // calls the function to create the list, with all the values and the counter
            createOp = createNodeFile(head, temporary->valueReadMachine, temporary->valueReadOpTime, saveValue);
            *head = insertNodeList(head, createOp, NULL);
            createOp->next = NULL;
        }
    }
    free(temporary->valueReadMachine);
    free(temporary->valueReadOpTime);
    fclose(file);
    return *head;
}