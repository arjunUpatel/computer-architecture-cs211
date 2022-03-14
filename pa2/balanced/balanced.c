#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct element
{
    char data;
    struct element *next;
};

void push(struct element **stack, char close)
{
    struct element *newHead = (struct element *)malloc(sizeof(struct element));
    newHead->data = close;
    newHead->next = *stack;
    *stack = newHead;
}

char pop(struct element **stack)
{
    if (*stack != NULL)
    {
        struct element head = **stack;
        free(*stack);
        *stack = head.next;
        return head.data;
    }
    return '\0';
}

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element *root = NULL;
    bool balanced = true;

    char buff;
    while (fscanf(fp, "%c", &buff) == 1)
    {
        switch (buff)
        {
        case '<':
            push(&root, '<');
            break;
        case '(':
            push(&root, '(');
            break;
        case '[':
            push(&root, '[');
            break;
        case '{':
            push(&root, '{');
            break;
        case '>':
            if (pop(&root) != '<')
                balanced = false;
            break;
        case ')':
            if (pop(&root) != '(')
                balanced = false;
            break;
        case ']':
            if (pop(&root) != '[')
                balanced = false;
            break;
        case '}':
            if (pop(&root) != '{')
                balanced = false;
            break;
        default:
            printf("Invalid character\n");
        }
    }
    struct element *head = root;
    struct element *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->next);
        free(tmp);
    }
    printf(balanced ? "yes" : "no");
    fclose(fp);
    return 0;
}
