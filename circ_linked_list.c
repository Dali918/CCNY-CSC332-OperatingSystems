#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *create_node();
struct node *insert_begin();
struct node *insert_end();
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

struct node *sentinel = NULL; // sentinel node
struct node *head, *tail;     // head and tail helper pointers
int length = 0;

int main(int argc, char *arv[])
{
    sentinel = (struct node *)malloc(sizeof(struct node)); // sentinel helper node
    sentinel->next = NULL;
    // tail pointer, head is implictly sentinel->next
    tail = NULL;

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
            sentinel->next = insert_begin();
            break;
        case 3:
            tail = insert_end();
            break;
        case 4:
            insert_pos();
            break;
        case 5:
            search();
            break;
        case 6:
            sort();
        case 7:
            delete ();
            break;
            break;
        default:
            printf("Freeing up memory\n");
            // free_list(sentinel->next);
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
    struct node *curr = sentinel->next;
    if (tail == NULL)
    {
        printf("Empty List\n");
        return;
    }

    printf("\n------------------------\n");
    while (1)
    {
        printf("%d\t", curr->data);
        if (curr->next == tail->next)
        {
            break;
        }
        curr = curr->next;
    }
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
    if (tail == NULL)
    {
        // assign as head
        sentinel->next = node;
        // assign as tail
        tail = node;
        // assign to self
        node->next = tail;
    }
}

struct node *insert_begin()
{
    struct node *temp = create_node();
    if (tail == NULL)
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
        return temp;
    }

    length++;
}
struct node *insert_end()
{
    struct node *temp = create_node();
    if (tail == NULL)
    {
        insert_empty(temp);
    }
    else
    {
        // point node to current head
        temp->next = tail->next;
        // point tail to node
        tail->next = temp;
        // make node new tail
        return temp;
    }

    length++;
}
void insert_pos()
{
    printf("Enter the position of the node (1 based index) \t curr_length: %d\n", length);
    int pos;
    scanf("%d", &pos);

    if (length == 0 || pos == 1)
    {
        insert_begin();
    }
    else if (pos < 1 || pos > length)
    {
        printf("invalid position\n");
        return;
    }
    else if (pos == length)
    {
        insert_end();
    }
    else
    {
        struct node *temp = create_node();
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
    // get query data
    int query = data_entry();
    // get the current head
    struct node *curr = sentinel->next;
    // end search if empty list
    if (curr == NULL)
    {
        printf("\nEmpty List\n");
        return;
    }

    else
    {
        int count = 1;
        // search while not at end of loop
        while (count < length + 1)
        {
            // end search if query found
            if (curr->data == query)
            {
                traverse();
                printf("%d found at position:\t", curr->data);
                printf("%d\n", count);
                return;
            }
            count++;
            curr = curr->next;
        }
    }

    // alert if value not found in list

    printf("\nSearch Value not found\n");
}

struct node *ascend_sort(struct node *head, struct node *node)
{
    // insert at front if head is null or item at head is greater (extend)
    if (head == NULL || head->data > node->data)
    {
        node->next = head;
        return node;
    }
    else
    {
        struct node *curr = head;
        // find node that is just less than curr (worst case last node)
        while (curr->next != NULL && curr->next->data < node->data)
        {
            curr = curr->next;
        }
        // insert in position
        node->next = curr->next;
        curr->next = node;
        // adjust tail if this node is at the last
        if (node->next == NULL)
        {
            tail = node;
        }
    }

    return head;
}

// sort
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

// delete function
void delete()
{
}
// free memory
void free_list(struct node *curr_head)
{
}
