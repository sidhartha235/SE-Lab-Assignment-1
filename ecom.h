/*
    E-Commerce Application
    -> by Sidhartha Ananthula ~ 21MCME08
    -> on 05 Jan 2024
    -> last modified: 12-01-2024
*/


#ifndef E_COMMERCE_APP
#define E_COMMERCE_APP

// structure for an item
typedef struct Item {
    int id;
    char *name;
    int stock;
    double price;
    double gst;
} item;

// structure for an order
typedef struct Order {
    char *user;
    item *items;
    double total_price;
    char *date;
    struct Order *next_;
} order;

// structure for linked list
typedef struct Node {
    item current;
    struct Node *next;
} node;


// functions
/* item.c */
void addNewItem( node *start, char *name, int id, int atock, double price, double gst );
node *getItemsListFromFile( );
void printAllItems( node *start );

/* order.c */
node *addToCart( node *start, int id, int quantity, node *cart );
node *removeFromCart ( int id, node *cart );
void displayCartItems( node *cart );
void checkout( char *name, node *cart, double total, char *date );
void printAvailableItems( node *start );

/* report.c */
order *getOrderDetails( );
void printNoStockItems( node *start );
void printOrdersInCostRange( order *one, double min, double max );

#endif