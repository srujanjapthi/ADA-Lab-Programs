#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int start, int mid, int end) {
    int n1 = mid - start + 1, n2 = end - mid;
    int leftHalf[n1], rightHalf[n2];
    int k = start, leftPtr = 0, rightPtr = 0;

    for (int i = 0; i < n1; i++) {
        leftHalf[i] = arr[start + i];
    }

    for (int j = 0; j < n2; j++) {
        rightHalf[j] = arr[mid + j + 1];
    }

    while (leftPtr < n1 && rightPtr < n2) {
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
}

void mergeSort(int *arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) >> 1;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int main() {
    int n;
    printf("Enter the size of the Array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter Elements of the Array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray Before Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    mergeSort(arr, 0, n - 1);

    printf("\nArray After Sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
