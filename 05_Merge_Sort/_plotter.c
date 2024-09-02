#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int merge(int *arr, int start, int mid, int end) {
    int n1 = mid - start + 1, n2 = end - mid;
    int leftHalf[n1], rightHalf[n2];
    int k = start, leftPtr = 0, rightPtr = 0;
    int count = 0;

    for (int i = 0; i < n1; i++) {
        leftHalf[i] = arr[start + i];
    }

    for (int j = 0; j < n2; j++) {
        rightHalf[j] = arr[mid + j + 1];
    }

    while (leftPtr < n1 && rightPtr < n2) {
        count++;
        if (leftHalf[leftPtr] <= rightHalf[rightPtr]) {
            arr[k++] = leftHalf[leftPtr++];
        } else {
            arr[k++] = rightHalf[rightPtr++];
        }
    }

    while (leftPtr < n1) {
        arr[k++] = leftHalf[leftPtr++];
    }

    while (rightPtr < n2) {
        arr[k++] = rightHalf[rightPtr++];
    }

    return count;
}

int mergeSort(int *arr, int start, int end) {
    if (start >= end) {
        return 0;
    } else {
        int mid = (start + end) >> 1;
        int left = mergeSort(arr, start, mid);
        int right = mergeSort(arr, mid + 1, end);
        return left + right + merge(arr, start, mid, end);
    }
}

void generateWorstCaseData(int *arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) >> 1;
        int n1 = mid - start + 1, n2 = end - mid;
        int leftHalf[n1], rightHalf[n2];
        int k = 0;

        for (int i = 0; i < n1; i++) {
            leftHalf[i] = arr[2 * i];
        }

        for (int j = 0; j < n2; j++) {
            rightHalf[j] = arr[2 * j + 1];
        }

        generateWorstCaseData(leftHalf, start, mid);
        generateWorstCaseData(rightHalf, mid + 1, end);

        for (int i = 0; i < n1; i++) {
            arr[k++] = leftHalf[i];
        }

        for (int j = 0; j < n2; j++) {
            arr[k++] = rightHalf[j];
        }
    }
}

void plotter() {
    FILE *fpBest = fopen("best_case.txt", "w");
    FILE *fpAvg = fopen("avg_case.txt", "w");
    FILE *fpWorst = fopen("worst_case.txt", "w");

    srand(time(NULL));
    for (int n = 2; n <= 1024; n *= 2) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Best Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        fprintf(fpBest, "%d\t%d\n", n, mergeSort(arr, 0, n - 1));

        // Worst Case Data Generation
        generateWorstCaseData(arr, 0, n - 1);
        fprintf(fpWorst, "%d\t%d\n", n, mergeSort(arr, 0, n - 1));

        // Average Case Data Generation
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 2000;
        }

        fprintf(fpAvg, "%d\t%d\n", n, mergeSort(arr, 0, n - 1));

        free(arr);
    }

    fclose(fpBest), fclose(fpAvg), fclose(fpWorst);
}

void main() {
    plotter();
}
