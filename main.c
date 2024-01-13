/*
    E-Commerce Application
    -> by Sidhartha Ananthula ~ 21MCME08
    -> on 05 Jan 2024
    -> last modified: 13-01-2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ecom.h"

int main( int argc, char *argv[] ) {

    int log = 1;
    int key = 0;

    if ((argc != 1) && (argc != 2)) {
        fprintf(stderr, "Usage: ./main [-owner]\n");
        exit(1);
    }

    if (argc == 2) {
        if ((strcmp(argv[1], "-owner") != 0)) {
            fprintf(stderr, "Usage: ./main [-owner]\n");
            exit(1);
        }
        else {
            log = 0;
        }
    }

    /* storing all the items in a linked list, head node is startItem */
    node *startItem = (node *) malloc(sizeof(node));
    startItem = getItemsListFromFile();
    printf("\n\t\t'WELCOME'\n\n");

    if (log == 0) {
        /* Login by owner */
        order *orderOne = getOrderDetails( );
        // orderOne = getOrdersFromFile( );
        while (1) {
            printf(" 1: To add an item\n");
            printf(" 2: To update stock\n");
            printf(" 3: To generate report\n");
            printf(" 4: To display all items\n");
            printf("-1: To exit\n");

            scanf("%d", &key);

            if (key == -1) {
                /* exit */
                break;
            }
            else if (key == 1) {
                /* add new item */
                FILE *fptr;
                char name[100];
                int id;
                int stock;
                double price;
                double gst = 0.18;

                printf("Specify the following details to add an item:\n");
                printf("Name (ENTER A NAME WITHOUT USING WHITESPACES): ");
                scanf("\n");
                scanf("%[^\n]s", name);
                printf("ID: ");
                scanf("%d", &id);
                printf("Stock: ");
                scanf("%d", &stock);
                printf("Price(per unit): ");
                scanf("%lf", &price);

                fptr = fopen("items.txt", "a");
                fprintf(fptr, "%-30s %-5d %-5d %-8.2f %-4.2f\n", name, id, stock, price, gst);
                fclose(fptr);

                addNewItem( startItem, name, id, stock, price, gst );

                key = 0;
            }
            else if (key == 2) {
                /* update item stock */
                int id = 0;
                printf("Enter Item ID to update stock: ");
                scanf("%d", &id);

                node *temp = startItem;
                while (temp != NULL && temp->current.id != id) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    int new_stock = 0;
                    printf("Enter new stock of item: ");
                    scanf("%d", &new_stock);
                    temp->current.stock = new_stock;
                    printf("New stock updated successfully!\n");
                }
                else {
                    printf("No item exist with given ID!\n");
                }

                key = 0;
            }
            else if (key == 3) {
                /* generate various reports */
                int option = 0;
                printf("Choose an option:\n");
                printf(" 1: To list items that are sold out completely\n");
                printf(" 2: To list orders that have total in a particular range\n");
                // printf(" 3: To get order details between given dates\n");
                printf("-1: To go back\n");
                scanf("%d", &option);
                while (option != 1 && option != 2 && option != -1) {
                    printf("Choose from given options only: ");
                    scanf("%d", &option);
                }

                if (option == 1) {
                    /* 1) sold out items */
                    printf("The following items are SOLD OUT:\n");
                    printNoStockItems( startItem );
                }
                else if (option == 2) {
                    /* 2) orders in given range */
                    double min = 0;
                    double max = 0;
                    printf("Enter min. total: ");
                    scanf("%lf", &min);
                    printf("Enter max. total: ");
                    scanf("%lf", &max);
                    printOrdersInCostRange( orderOne, min, max );
                }
                // else if (option == 3) {
                //     /* 3) orders between given dates */
                //     // not implented as of now
                // }
                else if (option == -1) {
                    /* go back */
                    key = 0;
                }

                key = 0;
            }
            else if (key == 4) {
                /* display all items */
                printf("All items in your shop:\n");
                printAllItems( startItem );

                key = 0;
            }
        }
    }
    else if (log == 1) {
        /* Login by customer to place order */
        node *cart = NULL;
        char name[100];
        printf("Enter your name (WITHOUT WHITESPACES): ");
        scanf("%s", name);
        while (1) {
            printf(" 1: To add an item to cart\n");
            printf(" 2: To remove an item from cart\n");
            printf(" 3: To show cart\n");
            printf(" 4: Checkout\n");
            printf(" 5: To display available items\n");
            printf("-1: To exit\n");

            scanf("%d", &key);

            if (key == -1) {
                /* exit */
                if (cart != NULL) { /* if cart is not empty, remove items from cart and update stock */
                    while (cart != NULL) {
                        node *temp = startItem;
                        while (temp != NULL && temp->current.id != cart->current.id) {
                            temp = temp->next;
                        }
                        temp->current.stock += cart->current.stock;
                        cart = removeFromCart( cart->current.id, cart );
                    }
                }

                /* free memory allocated to cart */
                while (cart != NULL) {
                    node *del = cart;
                    cart = cart->next;
                    free( del );
                }

                break;
            }
            else if (key == 1) {
                /* add item to cart */
                int id = 0;
                int quantity = 0;
                printf("Enter item ID: ");
                scanf("%d", &id);

                node *temp = startItem;
                while (temp != NULL && temp->current.id != id) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    while (quantity <= 0) {
                        printf("Enter quantity [ > 0 ]: ");
                        scanf("%d", &quantity);
                    }
                    if (quantity > temp->current.stock) {
                        printf("Quantity exceeding available Stock!! Try agian.\n");
                    }
                    else {
                        cart = addToCart( startItem, id, quantity, cart );
                        temp->current.stock -= quantity;
                        printf("Item added to cart successfully!\n");
                    }
                }
                else {
                    printf("No item exist with given ID!\n");
                }

                key = 0;
            }
            else if (key == 2) {
                /* remove item from cart */
                int id = 0;
                printf("Enter item ID: ");
                scanf("%d", &id);

                node *temp_cart = cart;
                while (temp_cart != NULL && temp_cart->current.id != id) {
                    temp_cart = temp_cart->next;
                }

                if (temp_cart != NULL) {
                    int removed_quantity = temp_cart->current.stock;
                    node *temp = startItem;
                    while (temp != NULL && temp->current.id != id) {
                        temp = temp->next;
                    }

                    cart = removeFromCart( id, cart );
                    temp->current.stock += removed_quantity;
                    printf("Item removed from cart successfully!\n");
                }
                else {
                    printf("No item in the cart of given ID!\n");
                }

                key = 0;
            }
            else if (key == 3) {
                /* show cart */
                if (cart != NULL) {
                    printf("Items present in your cart:\n");
                    displayCartItems( cart );
                }
                else {
                    printf("Your cart is empty!\n");
                }

                key = 0;
            }
            else if (key == 4) {
                /* checkout */
                if (cart != NULL) {
                    printf("Checkout:\n");
                    displayCartItems( cart );
                    
                    double total = 0;
                    node *temp_cart = cart;
                    while (temp_cart != NULL) {
                        total += temp_cart->current.price;
                        temp_cart = temp_cart->next;
                    }
                    printf("--------> Total: %.2f <--------\n", total);
                    
                    char ch;
                    printf("Are you sure you want to checkout? [y/n]: ");
                    scanf(" %c", &ch);
                    while (ch != 'y' && ch != 'n') {
                        printf("Are you sure you want to checkout? [y/n]: ");
                        scanf(" %c", &ch);
                    }

                    if (ch == 'y') {
                        time_t current_time;
                        time( &current_time );
                        struct tm *local_time = localtime( &current_time );
                        int day = local_time->tm_mday;
                        int month = local_time->tm_mon + 1;
                        int year = local_time->tm_year + 1900;

                        char date[10];
                        sprintf( date, "%02d-%02d-%d", day, month, year);

                        checkout( name, cart, total, date );
                        /* free memory allocated to cart */
                        while (cart != NULL) {
                            node *del = cart;
                            cart = cart->next;
                            free( del );
                        }

                        printf("\n\tTHANK YOU for shopping :)\n\n");
                    }
                }
                else {
                    printf("Please add items to your cart to checkout.\n");
                }

                key = 0;
            }
            else if (key == 5) {
                /* display available items */
                printf("Currently available items:\n");
                printAvailableItems( startItem );

                key = 0;
            }
        }
    }
    else {
        /* If 'log' value is changed knowingly or unknowingly */
        fprintf(stderr, "Unknown error!\n");
        exit(1);
    }

    /* write back updated item details to file */
    node *temp = startItem;
    FILE *fptr = fopen("items.txt", "w");
    while (temp != NULL) {
        fprintf(fptr, "%-30s %-5d %-5d %-8.2f %-4.2f\n", temp->current.name, temp->current.id, temp->current.stock, temp->current.price, temp->current.gst);
        temp = temp->next;
    }
    fclose(fptr);

    /* allocated memory for the linked list is freed below */
    temp = startItem;
    while (temp != NULL) {
        node *del = temp;
        temp = temp->next;
        free( del );
    }

    return 0;

}