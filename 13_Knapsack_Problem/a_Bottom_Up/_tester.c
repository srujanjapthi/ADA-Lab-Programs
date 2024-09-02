#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsackBottomUp(int n, int w, int weights[n], int values[n], int dp[n + 1][w + 1]) {
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
            if (j - weights[i - 1] < 0) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]]);
            }
        }
    }

    return dp[n][w];
}

void composition(int n, int w, int weights[n], int dp[n + 1][w + 1]) {
    int remCapacity = w, item = n;

    printf("\nComposition: ");
    while (remCapacity != 0 && item > 0) {
        if (dp[item][remCapacity] != dp[item - 1][remCapacity]) {
            printf("%d ", item);
            remCapacity -= weights[item - 1];
        }

        item--;
    }

    printf("\n");
}

int main() {
    int n, w;

    printf("Enter the number of Items: ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity: ");
    scanf("%d", &w);

    int weights[n], values[n];
    int dp[n + 1][w + 1];

    printf("\nEnter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d%d", &weights[i], &values[i]);
    }

    int maxValue = knapsackBottomUp(n, w, weights, values, dp);

    printf("\nKnapsack Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            printf("%-2d ", dp[i][j]);
        }

        printf("\n");
    }

    printf("\nMaximum profit: %d", maxValue);
    composition(n, w, weights, dp);

    return 0;
}
