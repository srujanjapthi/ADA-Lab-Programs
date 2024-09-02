#include <stdio.h>
#include <stdlib.h>

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

int warshallsTransitiveClosure(int n, int graph[n][n], int tClosure[n][n]) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tClosure[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (tClosure[i][k] != 0) {
                for (int j = 0; j < n; j++) {
                    count++;
                    tClosure[i][j] |= tClosure[k][j];
                }
            }
        }
    }

    return count;
}

void generateBestCaseData(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        graph[i][i + 1] = graph[i + 1][i] = 1;
    }

    graph[0][n - 1] = graph[n - 1][0] = 1;
}

void generateWorstCaseData(int n, int graph[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 1;
        }
    }
}

void plotter() {
    FILE *fpBest = fopen("warshall_best.txt", "w");
    FILE *fpWorst = fopen("warshall_worst.txt", "w");
    FILE *testCaseBest = fopen("warshalls_test_case_best.txt", "w");
    FILE *testCaseWorst = fopen("warshalls_test_case_worst.txt", "w");
    FILE *resultBest = fopen("warshalls_result_best.txt", "w");
    FILE *resultWorst = fopen("warshalls_result_worst.txt", "w");

    for (int n = 2; n <= 12; n++) {
        int graph[n][n], tClosure[n][n];

        generateBestCaseData(n, graph);
        printToFile(n, graph, testCaseBest);
        fprintf(fpBest, "%d\t%d\n", n, warshallsTransitiveClosure(n, graph, tClosure));
        printToFile(n, tClosure, resultBest);

        generateWorstCaseData(n, graph);
        printToFile(n, graph, testCaseWorst);
        fprintf(fpWorst, "%d\t%d\n", n, warshallsTransitiveClosure(n, graph, tClosure));
        printToFile(n, tClosure, resultWorst);
    }

    fclose(fpBest), fclose(fpWorst);
    fclose(testCaseBest), fclose(testCaseWorst);
    fclose(resultBest), fclose(resultWorst);
}

void main() {
    plotter();
}
