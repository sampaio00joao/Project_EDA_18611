#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main()
{
    int option = 0, option_2 = 0;
    int receiveMaxOpTime;
    int addMachine = 0, addOpTime = 0; // modify
    int qt = 0;
    int counterOperation = 0; // print the values available for deletion
    int optionNode = 0;
    int counter = 0;

    operation* temporary;
    operation* head = NULL; // Linked list 
    readFile(&head); // load the values from the file

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
                        system("cls");
                        printf("How many machines?.\n");
                        if (scanf("%d", &qt) > 0) {
                            temporary = createNode(qt); // creates the node
                            insertNodeList(&head, temporary, NULL); // inserts the node on the list / last position
                        }
                        break;
                    case 2:
                        system("cls");
                        printf("How many machines?.\n");
                        if (scanf("%d", &qt) > 0) {
                            temporary = createNode(qt); // creates the node
                            insertAtHead(&head, temporary); // inserts the node on the list / first position
                        }
                        break;
                    case 3:
                        system("cls");
                        optionNode = 0;
                        printLinkedList(head);
                        printf("Choose the position: (Press 0 to cancel)\n");
                        if (scanf("%d", &optionNode) > 0) {
                            if (optionNode > 0) {
                                system("cls");
                                printf("How many machines?.\n");
                                if (scanf("%d", &qt) > 0) {
                                    temporary = createNode(qt); // creates the node
                                    insertNodeList(&head, temporary, find_node(head, optionNode - 1)); // -1 because otherwise it would place in the following node
                                }
                            }
                        }
                        else break;
                        break;
                    }
                }
                break;
            case 2: // delete node
                option_2 = 0;
                system("cls");
                printLinkedList(head);
                printf("Choose the operation to delete.(Press 0 to go back)\n");
                if (scanf("%d", &option_2) > 0)
                    if (option_2 > 0) {
                        temporary = head;
                        while (temporary != NULL) { // used to restrict the user from choosing an operation that doenst exist
                            counterOperation++; // counts how many operations there are
                            temporary = temporary->next;
                        }
                        if (option_2 != 0 && option_2 <= counterOperation) { // if the value isnt 0 or higher than the valid operations
                        // as the node paramater in the deleteNode function, i use the return of the finfNode function
                        // which corresponds to the node chosen by the user
                            deleteNode(&head, find_node(head, option_2));
                        }
                    }
                    else break;
                break;
            case 3: // Modify an operation
                system("cls");
                printLinkedList(head);
                option = 0;
                option_2 = 0;
                printf("Choose the operation you want to modify: (Press 0 to go back)\n");
                if (scanf("%d", &option_2) > 0) {
                    temporary = head;
                    while (temporary != NULL) { // used to restrict the user from choosing an operation that doenst exist
                        counterOperation++; // counts how many operations there are
                        temporary = temporary->next;
                    }
                    if (option_2 != 0 && option_2 <= counterOperation) { // if the value isnt 0 or higher than the valid operations
                        option = 0;
                        system("cls");
                        printf("1. Insert new machine\n");
                        printf("2. Remove an existing machine\n");
                        printf("3. Change the operation time from a machine\n");
                        printf("(Press 0 to cancel)\n");
                        if (scanf("%d", &option) > 0) {
                            if (option < counterOperation) {
                                switch (option) {
                                case 0: break; // back to menu
                                case 1: // Insert a machine to add
                                    printf("Machine to add to the operation: ");
                                    if (scanf("%d", &addMachine) > 0)
                                        printf("Machine operation time: ");
                                    if (scanf("%d", &addOpTime) > 0)
                                        // sends as parameters the head, the node the user wants and the variables to update the operation
                                        modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                                    break;
                                case 2:
                                    // Remove a machine
                                    addMachine = 0;
                                    addOpTime = 0;
                                    // sends as parameters the head, the node the user wants and the variables to update the operation
                                    modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                                    break;
                                case 3:
                                    // Modify the time from a machine
                                    addMachine = 0;
                                    addOpTime = 0;
                                    // sends as parameters the head, the node the user wants and the variables to update the operation
                                    modifyOperation(&head, find_node(head, option_2), addMachine, addOpTime, option);
                                    break;
                                }//switch
                                break;
                            }
                        }
                        counterOperation = 0;
                    }
                    else break; // if the user presses 0 to go back, or the wrong number is choosen.
                }
                break;
            case 4: // save changes
                system("cls");
                printf("Press 1 to confirm changes: (Press 0 to cancel)\n");
                if (scanf("%d", &option_2) > 0) {
                    if (option_2 != 0) { // confirmation
                        writeFile(head);
                        printf("Saved Sucessfully!\n");
                        printf("Press 0 to go back.\n");
                        if (scanf("%d", &option_2) > 0) option_2 = 0;
                    }
                }
                break;
            case 5: // print the linked list
                system("cls");
                option_2 = 1;
                while (option_2 != 0) {
                    printLinkedList(head); // function call to print
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 6: // Max. Operation time
                system("cls");
                option_2 = 1;
                while (option_2 != 0) {
                    printf("Maximum job time:\t%d\n", maximumOperationTime(head));
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 7: // Min. Operation time
                system("cls");
                option_2 = 1;
                while (option_2 != 0) {
                    printf("Minimum job time:\t%d\n", minimumOperationTime(head));
                    printf("(Press 0 to go back)\n");
                    if (scanf("%d", &option_2) > 0) option_2 = 0;
                }
                break;
            case 8: // Avg. Operation time
                system("cls");
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
