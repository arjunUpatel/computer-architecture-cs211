#include <stdlib.h>
#include <stdio.h>

struct Node
{
    signed int data;
    struct Node *next;
};

void push(struct Node **stack, int close)
{
    struct Node *newHead = (struct Node *)malloc(sizeof(struct Node));
    newHead->data = close;
    newHead->next = *stack;
    *stack = newHead;
}

signed int pop(struct Node **stack)
{
    if (*stack != NULL)
    {
        struct Node head = **stack;
        free(*stack);
        *stack = head.next;
        return head.data;
    }
    return 0;
}

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return 0;
    }
    struct Node *head = NULL;
    signed int input;
    signed int mask = 15;

    fscanf(fp, "%d", &input);
    for (signed int shift = 0; shift < 16; shift += 4)
    {
        int bit_val = (input & (mask << shift)) >> (shift);
        push(&head, bit_val);
    }
    while (head != NULL)
    {
        int val = pop(&head);
        printf("%X", val);
    }
    return EXIT_SUCCESS;
}
