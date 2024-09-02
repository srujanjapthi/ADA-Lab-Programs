#include <stdio.h>

int cycles = 0;

void bfsUtil(int n, int graph[n][n], int curr, int vis[]) {
    int queue[n], front = 0, rear = 0;
    int visOrder = 0;

    vis[curr] = ++visOrder;
    queue[front] = curr;
    while (front <= rear) {
        int currNode = queue[front++];

        printf("%d ", currNode);
        for (int i = 0; i < n; i++) {
            if (graph[currNode][i]) {
                if (!vis[i]) {
                    vis[i] = ++visOrder;
                    queue[++rear] = i;
                } else if (vis[i] > vis[currNode]) {
                    cycles++;
                }
            }

            i += (i == currNode - 1);
        }
    }
}

void bfs(int n, int graph[n][n]) {
    int vis[n];
    int components = 0;

    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            printf("Component %d: ", ++components);
            bfsUtil(n, graph, i, vis);
            printf("\n");
        }
    }

    printf("\nTotal Connected Components: %d\n", components);
    printf("Total Independant Cycles: %d\n", cycles);
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

    printf("Adjacency Matrix (Graph):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }

    printf("\nGraph Details:\n");
    bfs(n, graph);

    return 0;
}
