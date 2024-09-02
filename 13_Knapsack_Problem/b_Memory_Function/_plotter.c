#include <stdio.h>
#include <stdlib.h>

int count = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsackTopDownMemo(int n, int w, int weights[n], int values[n], int **memo) {
    if (memo[n][w] != -1) {
        return memo[n][w];
    }

    count++;
    if (weights[n - 1] <= w) {
        int pick = values[n - 1] + knapsackTopDownMemo(n - 1, w - weights[n - 1], weights, values, memo);
        int notPick = knapsackTopDownMemo(n - 1, w, weights, values, memo);

        return memo[n][w] = max(pick, notPick);
    } else {
        return memo[n][w] = knapsackTopDownMemo(n - 1, w, weights, values, memo);
    }
}

// This function can be avoided for plotter
void composition(int n, int w, int weights[n], int **memo, FILE *fp) {
    int remCapacity = w, item = n;

    fprintf(fp, "\nComposition: ");
    while (remCapacity != 0 && item > 0) {
        if (memo[item][remCapacity] != memo[item - 1][remCapacity]) {
            fprintf(fp, "%d ", item);
            remCapacity -= weights[item - 1];
        }

        item--;
    }

    fprintf(fp, "\n");
}

void plotterUtil(FILE *fp, FILE *outputFile) {
    int n, w;

    printf("\nEnter the number of Items: ");
    fprintf(outputFile, "Enter the number of Items: ");
    scanf("%d", &n);
    fprintf(outputFile, "%d\n", n);

    printf("Enter the knapsack capacity: ");
    fprintf(outputFile, "Enter the knapsack capacity: ");
    scanf("%d", &w);
    fprintf(outputFile, "%d\n", w);

    int weights[n], values[n];
    int **memo = (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        memo[i] = (int *)malloc((w + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            memo[i][j] = (i == 0 || j == 0) ? 0 : -1;
        }
    }

    printf("\nEnter weight and value of each item:\n");
    fprintf(outputFile, "\nEnter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        fprintf(outputFile, "Item %d: ", i + 1);
        scanf("%d%d", &weights[i], &values[i]);
        fprintf(outputFile, "%d %d\n", weights[i], values[i]);
    }

    knapsackTopDownMemo(n, w, weights, values, memo);
    fprintf(fp, "%d\t%d\n", n, count);

    fprintf(outputFile, "\nKnapsack Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (memo[i][j] == -1) {
                fprintf(outputFile, "NA ", memo[i][j]);
            } else {
                fprintf(outputFile, "%-3d ", memo[i][j]);
            }
        }

        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "\nMaximum profit: %d", memo[n][w]);
    composition(n, w, weights, memo, outputFile);
    fprintf(outputFile, "------------------------------------------------------------\n\n");
}

void plotter() {
    FILE *fp = fopen("knapsack.txt", "w");
    FILE *outputFile = fopen("knapsack_output.txt", "w");

    for (int i = 0; i < 5; i++) {
        count = 0;
        plotterUtil(fp, outputFile);
    }

    fclose(fp), fclose(outputFile);
}

void main() {
    plotter();
}
