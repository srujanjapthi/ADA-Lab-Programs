#include <stdio.h>

void printAdjMatrix(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }
}

void warshallsTransitiveClosure(int n, int graph[n][n]) {
    int tClosure[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tClosure[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (tClosure[i][k] != 0) {
                for (int j = 0; j < n; j++) {
                    tClosure[i][j] |= tClosure[k][j];
                }
            }
        }
    }

    printAdjMatrix(n, tClosure);
}

int main() {
    int n;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    int graph[n][n];

    printf("Enter Adjacency Matrix [Enter the Binary Matrix]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nAdjaceny Matrix:\n");
    printAdjMatrix(n, graph);

    printf("\nTransitive Closure:\n");
    warshallsTransitiveClosure(n, graph);

    return 0;
}
