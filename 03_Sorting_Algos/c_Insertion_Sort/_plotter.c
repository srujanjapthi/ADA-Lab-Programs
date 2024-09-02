#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertionSort(int n, int *arr) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        int element = arr[i], j = i - 1;
        while (j >= 0 && ++count && arr[j] > element) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = element;
    }

    return count;
}

void plotter() {
    FILE *fpBest = fopen("insertion_sort_best.txt", "w");
    FILE *fpAvg = fopen("insertion_sort_avg.txt", "w");
    FILE *fpWorst = fopen("insertion_sort_worst.txt", "w");

    srand(time(NULL));
    for (int n = 10; n <= 100; n += 10) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Best Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        fprintf(fpBest, "%d\t%d\n", n, insertionSort(n, arr));

        // Average Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        fprintf(fpAvg, "%d\t%d\n", n, insertionSort(n, arr));

        // Worst Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }

        fprintf(fpWorst, "%d\t%d\n", n, insertionSort(n, arr));
    }
}

void main() {
    plotter();
}
