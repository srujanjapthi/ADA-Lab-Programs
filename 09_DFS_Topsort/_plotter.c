#include <stdio.h>
#include <stdbool.h>

int count = 0, k = 0;

// In plotter, since we always provide the correct test case, there is no need of extra recursion stack to keep track of how many nodes are currently in stack.
void topSortDFSUtil(int n, int graph[n][n], int vertex, bool vis[n], int *topSort) {
    vis[vertex] = true;

    for (int i = 0; i < n; i++) {
        count++;
        if (!vis[i] && graph[vertex][i]) {
            topSortDFSUtil(n, graph, i, vis, topSort);
        }
    }

    topSort[--k] = vertex;
}

void topSortDFS(int n, int graph[n][n]) {
    int topSort[n];
    bool vis[n];

    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    k = n;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            topSortDFSUtil(n, graph, i, vis, topSort);
        }
    }
}

void generateTestCase1(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = j > i;
        }
    }
}

void generateTestCase2(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        graph[i][i + 1] = 1;
    }
}

void plotter() {
    FILE *fp1 = fopen("top_sort1.txt", "w");
    FILE *fp2 = fopen("top_sort2.txt", "w");

    for (int n = 10; n <= 100; n += 10) {
        int graph[n][n];

        count = 0;
        generateTestCase1(n, graph);
        topSortDFS(n, graph);
        fprintf(fp1, "%d\t%d\n", n, count);

        count = 0;
        generateTestCase2(n, graph);
        topSortDFS(n, graph);
        fprintf(fp2, "%d\t%d\n", n, count);

    }

    fclose(fp1), fclose(fp2);
}

void main() {
    plotter();
}
