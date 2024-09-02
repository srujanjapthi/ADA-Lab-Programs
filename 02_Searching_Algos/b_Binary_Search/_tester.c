#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int key, int low, int high) {
    int mid = (low + high) >> 1;
    if (low > high) {
        // Key not found
        return -1;
    } else if (arr[mid] == key) {
        // Key Found
        return mid;
    } else if (arr[mid] > key) {
        // Search in the left half
        return binarySearch(arr, key, low, mid - 1);
    } else {
        // Search in the right half
        return binarySearch(arr, key, mid + 1, high);
    }
}

int main() {
    int n, key;
    printf("Enter the size of the Array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter Elements of the Array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the Key to be Searched: ");
    scanf("%d", &key);

    int pos = binarySearch(arr, key, 0, n - 1);
    if (pos != -1) {
        printf("\nKey Found at position %d\n", pos + 1);
    } else {
        printf("\nKey Not Found...\n");
    }

    return 0;
}