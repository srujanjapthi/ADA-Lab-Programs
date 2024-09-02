#include <stdio.h>
#include <limits.h>

void printAdjMatrix(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != INT_MAX) {
                printf("%-4d ", graph[i][j]);
            } else {
                printf("Inf ");
            }
        }
        printf("\n");
    }
}

void floydWarshalls(int n, int graph[n][n]) {
    int dist[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j] ? graph[i][j] : INT_MAX;
        }

        dist[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] != INT_MAX) {
                for (int j = 0; j < n; j++) {
                    if (dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    printAdjMatrix(n, dist);
}

int main() {
    int n;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    int graph[n][n];

    printf("Enter Adjacency Matrix [Note: Enter 0 indicating there is no Edge]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nAdjaceny Matrix:\n");
    printAdjMatrix(n, graph);

    printf("\nAll Pair shortest path:\n");
    floydWarshalls(n, graph);

    return 0;
}
