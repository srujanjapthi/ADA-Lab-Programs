#include <stdio.h>
#include <stdbool.h>

int k = 0;
bool isCycle = false;

void topSortDFSUtil(int n, int graph[n][n], int vertex, bool vis[n], bool recStack[n], int *topSort) {
    vis[vertex] = recStack[vertex] = true;

    for (int i = 0; i < n; i++) {
        if (graph[vertex][i]) {
            if (!vis[i]) {
                topSortDFSUtil(n, graph, i, vis, recStack, topSort);
            } else if (recStack[i]) {
                isCycle = true;
                return;
            }
        }
    }

    recStack[vertex] = false;
    topSort[--k] = vertex;
}

void topSortDFS(int n, int graph[n][n]) {
    int topSort[n];
    bool vis[n], recStack[n];

    for (int i = 0; i < n; i++) {
        vis[i] = recStack[i] = false;
    }

    k = n, isCycle = false;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            topSortDFSUtil(n, graph, i, vis, recStack, topSort);
            if (isCycle) {
                printf("\nCycle Exists...\n");
                return;
            }
        }
    }

    printf("\nTopological Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", topSort[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("\nEnter the number of vertices in the Graph: ");
    scanf("%d", &n);

    int graph[n][n];

    printf("Enter the Adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nAdjacency Matrix (Graph):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }

    topSortDFS(n, graph);

    return 0;
}
