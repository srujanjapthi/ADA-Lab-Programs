#include <stdio.h>

int cycles = 0;

void dfsUtil(int n, int graph[n][n], int curr, int parent, int vis[]) {
    vis[curr] = parent != -1 ? vis[parent] + 1 : 1;

    printf("%d ", curr);
    for (int i = 0; i < n; i++) {
        if (graph[curr][i]) {
            if (!vis[i]) {
                dfsUtil(n, graph, i, curr, vis);
            } else if (vis[curr] - vis[i] > 1) {
                cycles++;
            }
        }

        i += (i == curr - 1);
    }
}

void dfs(int n, int graph[n][n]) {
    int vis[n];
    int components = 0;

    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            printf("Component %d: ", ++components);
            dfsUtil(n, graph, i, -1, vis);
            printf("\n");
        }
    }

    printf("\nTotal Connected Components: %d\n", components);
    printf("Total Independant Cycles / Back Edges: %d\n", cycles);
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

    printf("\nGraph Details:\n");
    dfs(n, graph);

    return 0;
}
