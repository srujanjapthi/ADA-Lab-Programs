#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int bubbleSort(int n, int *arr) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        bool isSorted = true;
        for (int j = 0; j < n - i - 1; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                isSorted = false;
            }
        }

        if (isSorted) {
            break;
        }
    }

    return count;
}

void plotter() {
    FILE *fpBest = fopen("bubble_sort_best.txt", "w");
    FILE *fpAvg = fopen("bubble_sort_avg.txt", "w");
    FILE *fpWorst = fopen("bubble_sort_worst.txt", "w");

    srand(time(NULL));
    for (int n = 10; n <= 100; n += 10) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Best Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        fprintf(fpBest, "%d\t%d\n", n, bubbleSort(n, arr));

        // Average Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        fprintf(fpAvg, "%d\t%d\n", n, bubbleSort(n, arr));

        // Worst Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }

        fprintf(fpWorst, "%d\t%d\n", n, bubbleSort(n, arr));
    }
}

void main() {
    plotter();
}