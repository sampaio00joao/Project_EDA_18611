#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main()
{
    int option, machineNumber[5], machineOpTime[5], option_2;
    int receiveMaxOpTime;
    int addMachine = 0, addOpTime = 0; // modify
    int qt = 0;
    int counterOperation = 0; // print the values available for deletion
    int optionNode = 0;

    operation* temporary;
    operation* head = NULL; // Linked list 
    readFile(&head); // load the table

    while (1) { // infinite cycle
        printf("Main Menu: (one job)\n");
        printf("1. Add an Operation\n");
        printf("2. Remove an Operation\n");
        printf("3. Modify an Operation\n");
        printf("4. Save the changes\n");
        printf("5. Show the list\n");
        printf("6. Maximum operating time (for one job)\n");
        printf("7. Minimum operating time (for one job)\n");
        printf("8. Average operating time (for one job)\n");

        if (scanf("%d", &option) > 0) {
            switch (option) {
            case 0: break;
            case 1: // create node 
                system("cls");
                printf("Choose the option: (Press 0 to cancel)\n");
                printf("1. Insert at the tail of the list.\n");
                printf("2. Insert at the head of the list.\n");
                printf("3. Insert on a specified position.\n");
                if (scanf("%d", &optionNode) > 0) {

                    switch (optionNode) {
                    case 0:
                        break;
                    case 1:
                        printf("How many machines?.\n");
                        if (scanf("%d", &qt) > 0) {
                            temporary = createNode(qt);
                            insertNodeList(&head, temporary, NULL);
                        }
                        break;
                    case 2:
                        printf("How many machines?.\n");
                        if (scanf("%d", &qt) > 0) {
                            temporary = createNode(qt);
                            insertAtHead(&head, temporary);
                        }
                        break;
                    case 3:
                        system("cls");
                        optionNode = 0;
                        printLinkedList(head);
                        printf("Choose the position: (Press 0 to cancel)");
                        if (scanf("%d", &optionNode) > 0) {
                            if (optionNode > 0) {
                                printf("How many machines?.\n");
                                if (scanf("%d", &qt) > 0) {
                                    temporary = createNode(qt);
                                    insertNodeList(&head, temporary, find_node(head, optionNode - 1)); // -1 because otherwise it would place in the following node
                                }
                            }
                            else break;
                        }
                        break;
                    }
                }
                break;
            case 2: // delete node
                option_2 = 0;
                system("cls");
                printLinkedList(head);
                printf("Choose the operation to delete.(Press 0 to go back)\n");
                if (scanf("%d", &option_2) > 0) {
                    if (option_2 > 0) {
                        deleteNode(&head, find_node(head, option_2));
                    }
                    else break;
                }
                break;
            case 3: // Modify an operation
                system("cls");
                printLinkedList(head);
                option = 0;
                option_2 = 0;
                printf("Choose the operation you want to modify: (Press 0 to go back)\n");
                if (scanf("%d", &option_2) > 0) {
                    if(option_2 > 0){
                        system("cls");
                        printf("1. Insert new machine\n");
                        printf("2. Remove an existing machine\n");
                        printf("3. Change the operation time from a machine\n");
                        scanf("%d", &option);
                        switch (option) {
                        case 1: // Insert a machine to add
                            printf("Machine to add to the operation: ");
                            scanf("%d", &addMachine);
                            printf("Machine operation time: ");
                            scanf("%d", &addOpTime);
                            modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                            break;
                        case 2:
                            // Remove a machine
                            addMachine = 0;
                            addOpTime = 0;
                            modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                            break;
                        case 3:
                            // Modify the time from a machine
                            addMachine = 0;
                            addOpTime = 0;
                            modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                            break;
                        }//switch
                        break;
                    }else break; // if the user presses 0 to go back.
                }
                break;
            case 4: // save changes
                option_2 = 1;
                while (option_2 != 0) {
                    writeFile(head);
                    printf("Press 1 to go back.\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 5: // print the linked list
                option_2 = 1;
                while (option_2 != 0) {
                    printLinkedList(head); // function call to print
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 6: // Max. Operation time
                option_2 = 1;
                while (option_2 != 0) {
                    printf("Maximum job time:\t%d\n", maximumOperationTime(head));
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 7: // Min. Operation time
                option_2 = 1;
                while (option_2 != 0) {
                    printf("Minimum job time:\t%d\n", minimumOperationTime(head));
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 8: // Avg. Operation time
                option_2 = 1;
                while (option_2 != 0) {
                    printf("Average job time:\t%d\n", averageOperationTime(head));
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break; 
            }
        }
        else printf("You did not enter a valid number!");
        system("cls");
    }
    system("pause");
    return 0;
} // main
