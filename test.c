#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *sentinel;    // sentinel node
struct node *head, *tail, *curr; // head and tail helper pointers
struct node *temp;
int length = 0;

int data_entry()
{
    int data;
    printf("Enter the data value for the node\n");
    scanf("%d", &data);
    return data;
}

struct node *create_node()
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data_entry();
    temp->next = NULL;
    return temp;
}

void insert_empty(struct node *node)
{

    // point node's next to itself
    node->next = node;
    // make node head
    head = node;
    // make node tail
    tail = node;
}

int main(int argc, char *argv[])
{
    sentinel = (struct node *)malloc(sizeof(struct node)); // sentinel helper node
    // set the head and tail of the linked list to null
    head = NULL;
    tail = NULL;
    // set the sentinel node to head
    sentinel->next = head;
    //create a node
    temp = create_node();
    //insert it in the list
    insert_empty(temp);
    curr = head;
    printf("\n------------------------\n");
    //print the list
    do
    {
        printf("%d\t", curr->data);
        curr = curr->next;

    } while ( curr!= head);
    printf("\n------------------------\n");

    return 0;
}
