#include "../graphutils.h"

typedef struct Node Node;

struct Node
{
    graphNode_t data;
    Node *next;
};

void push(Node **head, graphNode_t data)
{ 
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

graphNode_t pop(Node **head, graphNode_t graphNodeCount)
{
    if (*head != NULL)
    {
        Node newHead = **head;
        free(*head);
        *head = newHead.next;
        return newHead.data;
    }
    return graphNodeCount;
}

bool contains(Node **head, graphNode_t target, Node **printingStack)
{
    for (Node *node = *head; node != NULL; node = node->next)
    {
        push(printingStack, node->data);
        if (node->data == target)
            return true;
    }
    return false;
}

bool dfs(AdjacencyListNode *adjListNode, graphNode_t graphNodeCount, graphNode_t graphNodeNum, Node *visitingHead, bool *visited)
{
    Node *printingStack = NULL;
    if (contains(&visitingHead, graphNodeNum, &printingStack))
    {
        while (printingStack != NULL)
            printf("%ld ", pop(&printingStack, graphNodeCount));
        return true;
    }
    else
    {
        while (printingStack != NULL)
            pop(&printingStack, graphNodeCount);
    }
    if (visited[graphNodeNum])
        return false;
    else
    {
        push(&visitingHead, graphNodeNum);
        visited[graphNodeNum] = true;
        for(AdjacencyListNode *nbr = (adjListNode + graphNodeNum)->next; nbr != NULL; nbr = nbr->next)
        {
            if (dfs(adjListNode, graphNodeCount, nbr->graphNode, visitingHead, visited))
            {
                pop(&visitingHead, graphNodeCount);
                return true;
            }
        }
        pop(&visitingHead, graphNodeCount);
        return false;
    }
}

int main(int argc, char *argv[])
{
    AdjacencyListNode *adjacencyList;
    graphNode_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    Node *visitingHead = NULL;
    bool isCyclic = false;
    for (unsigned source = 0; source < graphNodeCount; source++)
    {
        bool *visited = calloc(graphNodeCount, sizeof(bool));
        if (dfs(adjacencyList + source, graphNodeCount, source, visitingHead, visited)){
            printf("\n");
            isCyclic = true;
        }
        free(visited);
        if (isCyclic)
            break;
    }
    printf("\n");
    if (!isCyclic)
    {
        printf("DAG\n");
    }

    freeAdjList(graphNodeCount, adjacencyList);
    return EXIT_SUCCESS;
}
