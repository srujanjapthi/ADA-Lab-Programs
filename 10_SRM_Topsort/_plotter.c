#include <stdio.h>

int topSortSRM(int n, int graph[n][n]) {
    int topSort[n], stack[n], indeg[n];
    int top = -1, k = 0;
    int count = 0;

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
            count++;
            if (graph[curr][i] && --indeg[i] == 0) {
                stack[++top] = i;
            }
        }
    }

    return count;
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

        generateTestCase1(n, graph);
        fprintf(fp1, "%d\t%d\n", n, topSortSRM(n, graph));

        generateTestCase2(n, graph);
        fprintf(fp2, "%d\t%d\n", n, topSortSRM(n, graph));

    }

    fclose(fp1), fclose(fp2);
}

void main() {
    plotter();
}
