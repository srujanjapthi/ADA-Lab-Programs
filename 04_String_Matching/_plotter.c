#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int stringMatching(char *text, int n, char *pattern, int m) {
    int count = 0;
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && ++count && pattern[j] == text[i + j]) {
            j++;
        }

        if (j == m) {
            return count;
        }
    }

    return count;
}

void plotter() {
    int n = 1000;
    FILE *fpBest = fopen("best_case.txt", "w");
    FILE *fpAvg = fopen("avg_case.txt", "w");
    FILE *fpWorst = fopen("worst_case.txt", "w");
    char *text = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < n; i++) {
        text[i] = 'a';
    }

    srand(time(NULL));
    for (int m = 10; m <= 1000; m += m < 100 ? 10 : 100) {
        char *pattern = (char *)malloc(m * sizeof(char));

        // Best Case Data Generation
        for (int i = 0; i < m; i++) {
            pattern[i] = 'a';
        }

        fprintf(fpBest, "%d\t%d\n", m, stringMatching(text, n, pattern, m));

        // Worst Case Data Generation
        pattern[m - 1] = 'b';

        fprintf(fpWorst, "%d\t%d\n", m, stringMatching(text, n, pattern, m));

        // Average Case Data Generation
        for (int i = 0; i < m; i++) {
            pattern[i] = 'a' + rand() % 3; // String consisting of only the characters 'a', 'b', 'c'
        }

        fprintf(fpAvg, "%d\t%d\n", m, stringMatching(text, n, pattern, m));

        free(pattern);
    }

    free(text);
    fclose(fpBest), fclose(fpAvg), fclose(fpWorst);
}

void main() {
    plotter();
}