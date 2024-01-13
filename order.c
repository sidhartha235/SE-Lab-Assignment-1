/*
    E-Commerce Application
    -> by Sidhartha Ananthula ~ 21MCME08
    -> on 05 Jan 2024
    -> last modified: 13-01-2024
*/


#include "ecom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function to add an item to cart */
node *addToCart( node *start, int id, int quantity, node *cart ){
    node *temp = start;
    while (temp != NULL && temp->current.id != id) {
        temp = temp->next;
    }

    if (temp != NULL) {
        node *new_node = (node *) malloc(sizeof(node));
        new_node->next = NULL;
        new_node->current.name = temp->current.name;
        new_node->current.id = temp->current.id;
        new_node->current.stock = quantity;
        new_node->current.gst = temp->current.gst;
        new_node->current.price = (quantity * temp->current.price) + (quantity * new_node->current.gst * temp->current.price);

        if (cart == NULL) {
            cart = new_node;
        }
        else {
            node *temp_cart = cart;
            while (temp_cart->next != NULL) {
                temp_cart = temp_cart->next;
            }
            temp_cart->next = new_node;
        }
    }

    return cart;
}

/* function to remove an item from cart */
node *removeFromCart ( int id, node *cart ){
    if (cart == NULL) {
        return NULL;
    }

    node *temp_cart = cart;
    node *prev_cart = NULL;
    while (temp_cart != NULL && temp_cart->current.id != id) {
        prev_cart = temp_cart;
        temp_cart = temp_cart->next;
    }

    if (temp_cart != NULL) {
        if (prev_cart == NULL) {
            cart = temp_cart->next;
        }
        else {
            prev_cart->next = temp_cart->next;
        }
        free( temp_cart );
    }

    return cart;
}

/* function to print cart items */
void displayCartItems( node *cart ){
    node *temp_cart = cart;
    for(int i = 0; i < 70; i++){
        printf("-");
    }
    printf("\n");
    printf("%-30s |%-5s |%-8s |%-8s\n", "Item-name", "ID", "Quantity", "Price(including GST)");
    for(int i = 0; i < 70; i++){
        printf("-");
    }
    printf("\n");
    while (temp_cart != NULL) {
        printf("%-30s |%-5d |%-8d |%-8.2f\n", temp_cart->current.name, temp_cart->current.id, temp_cart->current.stock, temp_cart->current.price);
        temp_cart = temp_cart->next;
    }
    for(int i = 0; i < 70; i++){
        printf("-");
    }
    printf("\n");
}

/* function to save order details when checked out */
void checkout( char *name, node *cart, double total, char *date ){
    FILE *fptr;
    int gst = 0.18;

    fptr = fopen("orders.txt", "a");
    fprintf(fptr, "%s %lf %s ", name, total, date);

    node *temp_cart = cart;
    while ( temp_cart != NULL ) {
        fprintf(fptr, "%s %d %d %lf ", temp_cart->current.name, temp_cart->current.id, temp_cart->current.stock, temp_cart->current.price);
        temp_cart = temp_cart->next;
    }
    fprintf(fptr, "\n");

    fclose(fptr);
}

/* function to print available items */
void printAvailableItems( node *start ){
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
        if (temp->current.stock > 0) {
            printf("%-30s |%-5d |%-5d |%-8.2f |%-4.2f\n", temp->current.name, temp->current.id, temp->current.stock, temp->current.price, temp->current.gst);
        }
        temp = temp->next;
    }
    for(int i = 0; i < 60; i++){
        printf("-");
    }
    printf("\n");
}