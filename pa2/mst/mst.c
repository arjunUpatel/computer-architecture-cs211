#include "../graphutils.h"

int main(int argc, char *argv[])
{
    AdjacencyListNode *adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    graphNode_t *parents = calloc(graphNodeCount, sizeof(graphNode_t));
    for (size_t i = 0; i < graphNodeCount; i++)
    {
        parents[i] = -1;
    }

    graphNode_t root = rand() % graphNodeCount;
    parents[root] = root;

    for (unsigned iter = 0; iter < graphNodeCount - 1; iter++)
    {
        double minWeight = DBL_MAX;
        graphNode_t minSource = -1;
        graphNode_t minDest = -1;

        for (graphNode_t source = 0; source < graphNodeCount; source++)
        {
            if (parents[source] != -1)
            {
                for (AdjacencyListNode *node = adjacencyList + source; node != NULL; node = node->next)
                {
                    double currWeight = node->weight;
                    if (currWeight < minWeight && parents[node->graphNode] == -1)
                    {
                        minWeight = currWeight;
                        minDest = node->graphNode;
                        minSource = source;
                    }
                }
            }
        }
        parents[minDest] = minSource;
    }

    for (int i = 0; i < graphNodeCount; i++)
    {
        if (parents[i] != i)
            printf("%d %ld\n", i, parents[i]);
    }

    free(parents);
    freeAdjList(graphNodeCount, adjacencyList);

    return EXIT_SUCCESS;
}
