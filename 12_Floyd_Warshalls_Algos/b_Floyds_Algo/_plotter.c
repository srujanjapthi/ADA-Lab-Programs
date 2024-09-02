#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printToFile(int n, int graph[n][n], FILE *fp) {
    fprintf(fp, "For V = %d\n", n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(fp, "%d ", graph[i][j]);
        }

        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");
}

int floydWarshalls(int n, int graph[n][n], int cost[n][n]) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = graph[i][j] ? graph[i][j] : INT_MAX;
        }

        cost[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (cost[i][k] != INT_MAX) {
                for (int j = 0; j < n; j++) {
                    count++;
                    if (cost[k][j] != INT_MAX && cost[i][k] + cost[k][j] < cost[i][j]) {
                        cost[i][j] = cost[i][k] + cost[k][j];
                    }
                }
            }
        }
    }

    return count;
}

void plotter() {
    FILE *fp = fopen("floyd_warshall.txt", "w");
    FILE *testCase = fopen("floyds_test_case.txt", "w");
    FILE *result = fopen("floyds_result.txt", "w");

    for (int n = 2; n <= 12; n++) {
        int graph[n][n], cost[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = rand() % 10;
            }

            graph[i][i] = 0;
        }

        printToFile(n, graph, testCase);
        fprintf(fp, "%d\t%d\n", n, floydWarshalls(n, graph, cost));
        printToFile(n, cost, result);
    }

    fclose(fp), fclose(testCase), fclose(result);
}

void main() {
    plotter();
}
