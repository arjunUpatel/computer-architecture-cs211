#include <stdlib.h>
#include <stdio.h>

struct BSTNode
{
    int key;
    struct BSTNode *l_child;
    struct BSTNode *r_child;
};

struct Node
{
    struct BSTNode *data;
    struct Node *next;
};

struct Queue
{
    struct Node *front;
    struct Node *end;
};

void enqueue(struct Queue *queue, struct BSTNode *data)
{
    if (data == NULL)
        return;
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if (queue->end == NULL)
    {
        queue->front = newNode;
    }
    else
    {
        queue->end->next = newNode;
    }
    queue->end = newNode;
}

struct BSTNode *dequeue(struct Queue *queue)
{
    if (queue->front != NULL)
    {
        struct Node *temp = queue->front;
        struct BSTNode *res = queue->front->data;
        queue->front = temp->next;
        if (queue->end == temp)
        {
            queue->end = NULL;
        }
        free(temp);
        return res;
    }
    return NULL;
}

struct BSTNode *insert(struct BSTNode *root, int key)
{
    if (root == NULL)
    {
        root = malloc(sizeof(struct BSTNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->key = key;
    }

    if (key < root->key)
    {
        root->l_child = insert(root->l_child, key);
    }
    else if (key > root->key)
    {
        root->r_child = insert(root->r_child, key);
    }
    return root;
}

void delete_bst(struct BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    delete_bst(root->r_child);
    delete_bst(root->l_child);
    free(root);
}

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    struct BSTNode *root = NULL;
    int key;
    while (fscanf(fp, "%d", &key) != EOF)
    {
        root = insert(root, key);
    }
    fclose(fp);

    struct Queue queue = {.front = NULL, .end = NULL};
    struct BSTNode *currBSTNode = root;
    printf("%d", currBSTNode->key);
    enqueue(&queue, currBSTNode->l_child);
    enqueue(&queue, currBSTNode->r_child);
    currBSTNode = dequeue(&queue);
    while (currBSTNode != NULL)
    {
        printf(" %d", currBSTNode->key);
        enqueue(&queue, currBSTNode->l_child);
        enqueue(&queue, currBSTNode->r_child);
        currBSTNode = dequeue(&queue);
    }
    printf("\n");
    delete_bst(root);
    return EXIT_SUCCESS;
}
