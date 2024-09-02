#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int selectionSort(int n, int *arr) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }

    return count;
}

void plotter() {
    FILE *fp = fopen("selection_sort_data.txt", "w");

    srand(time(NULL));
    for (int n = 10; n <= 100; n += 10) {
        int *arr = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        fprintf(fp, "%d\t%d\n", n, selectionSort(n, arr));
    }
}

void main() {
    plotter();
}
