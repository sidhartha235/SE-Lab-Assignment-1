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

/* function to get name, date, and cost of orders */
order *getOrderDetails( ){
    FILE *fptr = fopen("orders.txt", "r");
    if (fptr == NULL) {
        printf("Unable to get items!\n");
        return NULL;
    }

    order *one = NULL;
    char *name = (char *) malloc(30 * sizeof(char));
    int day;
    int month;
    int year;
    char *date = (char *) malloc(11 * sizeof(char));
    double total;
    char *items = (char *) malloc(300 * sizeof(char));

    while (fscanf(fptr, "%s %d-%d-%d %lf %[^\n]s\n", name, &day, &month, &year, &total, items) == 6) {
        sprintf(date, "%02d-%02d-%d", day, month, year);

        order *new_order = (order *) malloc(sizeof(order));
        new_order->next_ = NULL;

        new_order->user = strdup( name );
        new_order->date = strdup( date );
        new_order->total_price = total;
        new_order->items = NULL;

        if (one == NULL) {
            one = new_order;
        }
        else {
            order *temp = one;
            while (temp->next_ != NULL) {
                temp = temp->next_;
            }
            temp->next_ = new_order;
        }
    }

    free(name);
    free(date);
    free(items);
    fclose(fptr);

    return one;
}

/* function to print items that have no stock left */
void printNoStockItems( node *start ){
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
        if (temp->current.stock <= 0) {
            printf("%-30s |%-5d |%-5d |%-8.2f |%-4.2f\n", temp->current.name, temp->current.id, temp->current.stock, temp->current.price, temp->current.gst);
        }
        temp = temp->next;
    }
    for(int i = 0; i < 60; i++){
        printf("-");
    }
    printf("\n");
}

/* function to print order details in given total cost range */
void printOrdersInCostRange( order *one, double min, double max ){
    order *temp = one;
    for (int i = 0; i < 45; i++) {
        printf("-");
    }
    printf("\n");
    printf("%-20s |%-9s |%s\n", "Customer", "Date", "Total cost");
    for (int i = 0; i < 45; i++) {
        printf("-");
    }
    printf("\n");
    if (temp == NULL) {
        printf("No orders placed in given range!\n");
    }
    else {
        while (temp != NULL) {
            printf("%-20s |%-9s |%s\n", temp->user, temp->date, temp->total_price);
            temp = temp->next_;
        }
    }
    for (int i = 0; i < 45; i++) {
        printf("-");
    }
    printf("\n");
}