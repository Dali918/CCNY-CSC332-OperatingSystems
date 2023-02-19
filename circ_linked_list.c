#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *create_node();
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
// insertion sort
void insertionSort(struct node **head);

struct node *sentinel = NULL; // sentinel node
struct node *head, *tail;     // head and tail helper pointers
int length = 0;

int main(int argc, char *arv[])
{
    sentinel = (struct node *)malloc(sizeof(struct node)); // sentinel helper node
    // set the head and tail of the linked list to null
    head = NULL;
    tail = NULL;
    // set the sentinel node to head
    sentinel->next = head;

    int choice;
    while (1)
    {
        // choose accordingly
        printf("\n                MENU                             \n");
        printf("1.Traverse     \n");
        printf("2.Insert Beginning    \n");
        printf("3.Insert End    \n");
        printf("4.Insert at Position\n");
        printf("5.Search   \n");
        printf("6.Sort\n");
        printf("7.Delete \n");
        printf("Other: Exit Program\n");
        printf("-----------------\n\n");

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
            insert_pos();
            break;
        case 5:
            search();
            break;
        case 6:
            sort();
            break;
        case 7:
            delete ();
            break;
        default:
            printf("Quitting\n");
            exit(0);
            break;
        }
    }

    return 0;
}

// helper data entry fuction
int data_entry()
{
    int data;
    printf("Enter the data value for the node\n");
    scanf("%d", &data);
    return data;
}
// node creation helper function
void traverse()
{
    struct node *curr = head;

    if (head == NULL)
    {
        printf("Empty List\n");
        return;
    }

    printf("\n------------------------\n");

    do
    {
        printf("%d\t", curr->data);
        curr = curr->next;

    } while (curr != head);

    // while (1)
    // {
    //     printf("%d\t", curr->data);
    //     if (curr->next == tail->next)
    //     {
    //         break;
    //     }
    //     curr = curr->next;
    // }

    printf("\n------------------------\n");
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
    // adjust sentinel
    sentinel->next = head;
}

void insert()
{
    struct node *temp = create_node();
    if (head == NULL)
    {
        insert_empty(temp);
    }
    else
    {
        // point node to current head
        temp->next = tail->next;
        // point tail to node
        tail->next = temp;
        // make node new head
    }

    length++;
}

void insert_begin()
{
    // insert node
    insert();
    // adjust head
    head = tail->next;
    // adjust sentinel
    sentinel->next = head;
}
void insert_end()
{
    // insert node
    insert();
    // adjust tail
    tail = tail->next;
}
void insert_pos()
{
    printf("Enter the position of the node (1 based index) \t curr_length: %d\n", length);
    int pos;
    scanf("%d", &pos);

    if (length == 0 || pos == 1)
    {
        insert_begin();
        return;
    }

    if (pos < 1 || pos > length + 1)
    {
        printf("invalid position\n");
        return;
    }

    struct node *temp = create_node();
    struct node *prev = tail;
    struct node *curr = tail->next;

    for (int i = 0; i < pos; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    temp->next = curr;
    curr = prev;
    length++;
}

void search()
{
    // get query data
    int query = data_entry();
    struct node *curr = head;
    if (curr == NULL)
    {
        printf("\nEmpty List\n");
        return;
    }
    // search for node, stop when back at head
    int count = 1;
    do
    {
        if (curr->data == query)
        {
            traverse();
            printf("%d found at position:\t", curr->data);
            printf("%d\n", count);
            return;
        }
        count++;
        curr = curr->next;

    } while (curr != head);

    printf("\nSearch Value not found\n");
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
    if (head == NULL)
    {
        printf("Empty list\n");
        return;
    }

    int choice;
    struct node *curr = head;
    struct node *next = NULL;
    struct node *sorted = NULL;
    // flatten circular linked list
    tail->next = NULL;

    printf("Enter 1 for ascending else any key for descending order\n");
    scanf("%d", &choice);
    // sort list
    while (curr != NULL)
    {
        // get next
        next = curr->next;
        // insert curr in new sorted linked list
        if (choice == 1)
        {
            sorted = ascend_sort(sorted, curr);
        }
        else
        {
            sorted = descend_sort(sorted, curr);
        }
        // insert next node
        curr = next;
    }
    // find tail
    curr = sorted;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    // adjust head and tail
    curr->next = sorted;
    tail = curr;
    head = sorted;
    sentinel->next = head;
}

// delete function
void delete()
{

    if (head == NULL) // do not delete from empty linked list
    {
        printf("Empty list, cannot delete\n");
        return;
    }

    int item = data_entry();
    // prev and curr pointers
    struct node *prev = tail;
    struct node *curr = tail->next;

    do
    {
        if (curr->data == item)
        {
            printf("%d\t Deleting at address: ", curr->data);
            printf("%p\n", (void *)&curr);

            if (curr == head && head == tail)
            {
                head = NULL;
                tail = NULL;
            }
            // adjust head if deleting head
            if (curr == head)
            {
                head = curr->next;
            }
            // adjust tail if deleting tail
            if (curr == tail)
            {
                tail = prev;
            }
            // delete  node and dellocate memory
            prev->next = curr->next;
            curr->next = NULL;
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

    } while (prev != tail);

    // alert if not found
    printf("%d\t not found in list", item);
}
