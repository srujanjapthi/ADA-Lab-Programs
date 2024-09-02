#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsackBottomUp(int n, int w, int weights[n], int values[n], int dp[n + 1][w + 1]) {
    int count = 0;

    // Initialize the dp table with zeroes for first row and column.
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int j = 1; j <= w; j++) {
        dp[0][j] = 0;
    }

    // Table Filling Step.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= w; j++) {
            count++;
            if (j - weights[i - 1] < 0) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]);
            }
        }
    }

    return count;
}

// This function can be avoided for plotter
void composition(int n, int w, int weights[n], int dp[n + 1][w + 1], FILE *fp) {
    int remCapacity = w, item = n;

    fprintf(fp, "\nComposition: ");
    while (remCapacity != 0 && item > 0) {
        if (dp[item][remCapacity] != dp[item - 1][remCapacity]) {
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
    int dp[n + 1][w + 1];

    printf("\nEnter weight and value of each item:\n");
    fprintf(outputFile, "\nEnter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        fprintf(outputFile, "Item %d: ", i + 1);
        scanf("%d%d", &weights[i], &values[i]);
        fprintf(outputFile, "%d %d\n", weights[i], values[i]);
    }

    fprintf(fp, "%d\t%d\n", n, knapsackBottomUp(n, w, weights, values, dp));

    fprintf(outputFile, "\nKnapsack Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            fprintf(outputFile, "%-3d ", dp[i][j]);
        }

        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "\nMaximum profit: %d", dp[n][w]);
    composition(n, w, weights, dp, outputFile);
    fprintf(outputFile, "------------------------------------------------------------\n\n");
}

void plotter() {
    FILE *fp = fopen("knapsack.txt", "w");
    FILE *outputFile = fopen("knapsack_output.txt", "w");

    for (int i = 0; i < 5; i++) {
        plotterUtil(fp, outputFile);
    }

    fclose(fp), fclose(outputFile);
}

void main() {
    plotter();
}
