/*
    E-Commerce Application
    -> by Sidhartha Ananthula ~ 21MCME08
    -> on 05 Jan 2024
    -> last modified: 12-01-2024
*/


#include "ecom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// /* function to update stock */
// void updateItemStock( item *currentItem, int newStock ){
//     currentItem->stock = newStock;
// }

/* add new item to the list */
void addNewItem( node *start, char *name, int id, int stock, double price, double gst ){
    node *temp = start;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    node *new_node = (node *) malloc(sizeof(node));
    new_node->next = NULL;

    new_node->current.name = strdup( name );
    new_node->current.id = id;
    new_node->current.stock = stock;
    new_node->current.price = price;
    new_node->current.gst = gst;

    temp->next = new_node;
    return;
}

/* function to read items info from file and generate a list of all items */
node *getItemsListFromFile( ){
    FILE *fptr = fopen("items.txt", "r");
    if (fptr == NULL) {
        printf("Unable to get items!\n");
        return NULL;
    }

    node *start = NULL;
    char *name = (char *) malloc(30 * sizeof(char));
    int id;
    int stock;
    double price;
    double gst;

    // printf("%d\n", fscanf(fptr, "%s %d %d %lf %lf\n", name, &id, &stock, &price, &gst));
    while (fscanf(fptr, "%s %d %d %lf %lf\n", name, &id, &stock, &price, &gst) == 5) {
        // printf("hello\n");
        node *new_node = (node *) malloc(sizeof(node));
        new_node->next = NULL;

        new_node->current.name = strdup( name );
        new_node->current.id = id;
        new_node->current.stock = stock;
        new_node->current.price = price;
        new_node->current.gst = gst;

        if (start == NULL) {
            start = new_node;
        }
        else {
            node *temp = start;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }

    free(name);
    fclose(fptr);

    return start;
}

/* function to print all items */
void printAllItems( node *start ){
    node *temp = start;
    for(int i = 0; i < 60; i++){
        printf("-");
    }
    printf("\n");
    printf("%-30s |%-5s |%-5s |%-8s |%s\n", "Item-name", "ID", "Stock", "Price", "GST");
    for(int i = 0; i < 60; i++){
        printf("-");
    }
    printf("\n");
    while (temp != NULL) {
        printf("%-30s |%-5d |%-5d |%-8.2f |%-4.2f\n", temp->current.name, temp->current.id, temp->current.stock, temp->current.price, temp->current.gst);
        temp = temp->next;
    }
    for(int i = 0; i < 60; i++){
        printf("-");
    }
    printf("\n");
}