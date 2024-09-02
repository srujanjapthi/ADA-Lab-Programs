#include <stdio.h>

// graph[n][n] is boolean matrix consisting of only 0's and 1's.
void topSortSRM(int n, int graph[n][n]) {
    int topSort[n], stack[n], indeg[n];
    int top = -1, k = 0;

    for (int i = 0; i < n; i++) {
        indeg[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            indeg[j] += graph[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (!indeg[i]) {
            stack[++top] = i;
        }
    }

    while (top != -1) {
        int curr = stack[top--];

        topSort[k++] = curr;
        for (int i = 0; i < n; i++) {
            if (graph[curr][i] && --indeg[i] == 0) {
                stack[++top] = i;
            }
        }
    }

    if (k != n) {
        printf("\nCycle Exists...\n");
    } else {
        printf("\nTopological Sorting: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", topSort[i]);
        }
        printf("\n");
    }
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

    topSortSRM(n, graph);

    return 0;
}
