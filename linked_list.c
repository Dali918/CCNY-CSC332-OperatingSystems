#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *sentinel = NULL; // sentinel node
struct node *head, *tail;     // head and tail helper pointers
int length = 0;
// insertion functions
void insert_begin();
void insert_end();
void insert_pos();
// iteratiion function
void traverse();
void search();
// sort
void sort();
// delete function
void delete();
// free memory
void free_list(struct node *curr_head);
// data entry helper function
int data_entry();

int main(int argc, char *argv[])
{

    sentinel = (struct node *)malloc(sizeof(struct node)); // sentinel helper node
    sentinel->next = NULL;
    // tail pointer, head is implictly sentinel->next
    tail = sentinel;

    int choice;
    while (1)
    {
        // choose accordingly
         printf("\n---------------------------------\n");
        printf("\n                MENU                             \n");
        printf("1.Traverse     \n");
        printf("2.Insert Beginning    \n");
        printf("3.Insert End    \n");
        printf("4.Search    \n");
        printf("5.Delete   \n");
        printf("6.Insert at Position \n");
        printf("7.sort the linked list \n");
        printf("\npress any other key to exit \n");
        printf("------------------------------------\n");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            traverse();
            break;
        case 2:
            insert_begin();
            break;
        case 3:
            insert_end();
            break;
        case 4:
            search();
            break;
        case 5:
            delete ();
            break;
        case 6:
            insert_pos();
            break;
        case 7:
            sort();
            break;
        default:
            printf("Freeing up memory\n");
            free_list(sentinel->next);
            printf("Quitting\n");

            exit(0);
            break;
        }
    }

    return 0;
}

void traverse()
{
    struct node *curr = sentinel->next; // start at head
    if (curr == NULL)                   // no traverse if linked list is empty
    {
        printf("Empty list\n");
        return;
    }

    printf("\n------------------------\n");
    while (curr != NULL)
    {
        printf("%d\t", curr->data);
        curr = curr->next;
    }
    printf("\n------------------------\n");
}

// helper entry fuction
int data_entry()
{
    int data;
    printf("Enter the data value for the node\n");
    scanf("%d", &data);
    return data;
}

void insert_begin()
{
    struct node *temp;
    int data;

    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data_entry();

    if (temp == NULL)
    {
        printf("Out of memory\n");
    }
    else
    {
        // attach head to temp's next
        temp->next = sentinel->next;
        // make new head
        sentinel->next = temp;
    }

    length++;
}

void insert_end()
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data_entry();
    temp->next = NULL;

    if (temp == NULL)
    {
        printf("Out of memory\n");
    }
    else
    {
        // insert at end
        tail->next = temp;
        // make new tail
        tail = temp;
    }

    length++;
}

void insert_pos()
{

    printf("Enter the position of the node (1 based index) \t curr_length: %d\n", length);
    int pos;
    scanf("%d", &pos);

    if (pos < 1 || pos > length + 1)
    {
        printf("invalid position\n");
        return;
    }

    if (pos == 1)
    {
        insert_begin();
    }
    else
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->data = data_entry();
        temp->next = NULL;

        struct node *prev = sentinel;
        struct node *curr = sentinel->next;

        for (int i = 1; i < pos; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        temp->next = curr;
        prev->next = temp;

        length++;
    }
}

void search()
{
    int item = data_entry();
    struct node *curr = sentinel->next; // start at head
    if (curr == NULL)                   // no traverse if linked list is empty
    {
        printf("Empty list\n");
        return;
    }

    while (curr != NULL)
    {
        if (curr->data == item)
        {
            printf("%d\t found at address: ", curr->data);
            printf("%p\n", (void *)&curr);
            return;
        }

        curr = curr->next;
    }

    printf("%d\t not found in list", item);
}

struct node *ascend_sort(struct node *head, struct node *curr)
{
    // insert at front if head is null or item at head is greater (extend)
    if (head == NULL || head->data > curr->data)
    {
        curr->next = head;
        return curr;
    }
    else
    {
        struct node *temp = head;
        // find node that is just less than curr (worst case last node)
        while (temp->next != NULL && temp->next->data < curr->data)
        {
            temp = temp->next;
        }

        curr->next = temp->next;
        temp->next = curr;
    }

    return head;
}

struct node *descend_sort(struct node *head, struct node *curr)
{
    // insert at front if head is null or item at head is lesser (extend)
    if (head == NULL || head->data < curr->data)
    {
        curr->next = head;
        return curr;
    }
    else
    {
        struct node *temp = head;
        // find node that is just greater than curr (worst case last node)
        while (temp->next != NULL && temp->next->data > curr->data)
        {
            temp = temp->next;
        }

        curr->next = temp->next;
        temp->next = curr;
    }

    return head;
}

void sort()
{
    int choice;
    printf("Enter 1 for ascending else any key for descending order\n");
    scanf("%d", &choice);

    struct node *sorted_head = NULL;
    struct node *curr_head = sentinel->next;
    struct node *next = NULL;

    while (curr_head != NULL)
    {
        next = curr_head->next;
        if (choice == 1)
        {
            sorted_head = ascend_sort(sorted_head, curr_head);
        }
        else
        {
            sorted_head = descend_sort(sorted_head, curr_head);
        }

        curr_head = next;
    }

    sentinel->next = sorted_head;
}

void delete()
{
    int item = data_entry();
    struct node *prev = sentinel;
    struct node *curr = sentinel->next;

    if (curr == NULL) // no traverse if linked list is empty
    {
        printf("Empty list, cannot delete\n");
        return;
    }

    while (curr != NULL)
    {
        if (curr->data == item)
        {
            printf("%d\t Deleting at address: ", curr->data);
            printf("%p\n", (void *)&curr);
            // delete  node and dellocate memory
            prev->next = curr->next;
            free(curr);
            // decrement the length
            length--;
            // print new linked list
            printf("%d\t Printing new linked list: ", curr->data);
            traverse();
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    // alert if not found
    printf("%d\t not found in list", item);
}

void free_list(struct node *curr_head)
{
    while (curr_head != NULL)
    {
        struct node *next = curr_head->next;
        printf("Free: %d\t", curr_head->data);
        printf("Address: %p\n", curr_head);
        free(curr_head);
        curr_head = next;
    }
}
