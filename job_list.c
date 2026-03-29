#include "main.h"

Node *head = NULL;

/* remove and return first job */
Node *delete_at_first(void)
{
    if (head == NULL)
        return NULL;

    Node *temp = head;
    head = head->link;

    temp->link = NULL;
    return temp;
}

/* print stopped jobs */
void print_list(void)
{
    if (head == NULL) {
        printf("No stopped jobs\n");
        return;
    }

    Node *temp = head;
    int job_no = 1;

    while (temp) {
        printf("[%d]  Stopped  %s  [%d]\n",
               job_no++, temp->command, temp->pid);
        temp = temp->link;
    }
}

