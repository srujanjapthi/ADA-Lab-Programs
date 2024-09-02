#include <stdio.h>

int cycles = 0, count = 0;

void bfsUtil(int n, int graph[n][n], int curr, int vis[]) {
    int queue[n], front = 0, rear = 0;
    int visOrder = 0;

    vis[curr] = ++visOrder;
    queue[front] = curr;
    while (front <= rear) {
        int currNode = queue[front++];
        for (int i = 0; i < n; i++) {
            count++;
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

    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            bfsUtil(n, graph, i, vis);
        }
    }
}

void generateSparseGraph(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        graph[i][i + 1] = graph[i + 1][i] = 1;
    }
}

void generateDenseGraph(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = (i != j);
        }
    }
}

void plotter() {
    FILE *fp1 = fopen("dense_graph.txt", "w");
    FILE *fp2 = fopen("sparse_graph.txt", "w");

    for (int n = 10; n <= 100; n += 10) {
        int graph[n][n];

        count = 0;
        generateSparseGraph(n, graph);
        bfs(n, graph);
        fprintf(fp1, "%d\t%d\n", n, count);

        count = 0;
        generateDenseGraph(n, graph);
        bfs(n, graph);
        fprintf(fp2, "%d\t%d\n", n, count);
    }

    fclose(fp1), fclose(fp2);
}

void main() {
    plotter();
}
