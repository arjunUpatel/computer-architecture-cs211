#include "../graphutils.h"

bool isTreeDFS(size_t graphNodeCount, AdjacencyListNode *adjacencyList, bool *visited, graphNode_t parent, graphNode_t current)
{
    if (visited[current] == true)
    {
        return false;
    }
    visited[current] = true;
    
    AdjacencyListNode *neighbor = adjacencyList[current].next;
    while (neighbor != NULL)
    {
        if (neighbor->graphNode != parent)
        {
            return isTreeDFS(graphNodeCount, adjacencyList, visited, current, neighbor->graphNode);
        }
        neighbor = neighbor->next;
    }
    return true;
}

int main(int argc, char *argv[])
{
    AdjacencyListNode *adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    bool *visited = calloc(graphNodeCount, sizeof(bool));

    printf(isTreeDFS(graphNodeCount, adjacencyList, visited, adjacencyList->graphNode, adjacencyList->graphNode) ? "yes" : "no");

    free(visited);
    freeAdjList(graphNodeCount, adjacencyList);
    return EXIT_SUCCESS;
}
