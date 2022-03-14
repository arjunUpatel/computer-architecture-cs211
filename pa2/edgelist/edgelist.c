#include "../graphutils.h"

int main(int argc, char *argv[])
{

    AdjacencyListNode *adjacencyList = NULL;
    size_t numOfNodes = adjMatrixToList(argv[1], &adjacencyList);
    for (size_t i = 0; i < numOfNodes; i++)
    {
        for (AdjacencyListNode *node = adjacencyList + i; node != NULL; node = node->next)
        {
            graphNode_t graphNode = node->graphNode;
            if(i < graphNode)
            {
                printf("%ld %ld\n", i, graphNode);
            }
        }
    }
    printf("\n");
    freeAdjList(numOfNodes, adjacencyList);
    return EXIT_SUCCESS;
}
