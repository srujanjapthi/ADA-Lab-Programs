#include <stdio.h>
#include <stdlib.h>

int linearSearch(int n, int *arr, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }

    return -1;
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

    int pos = linearSearch(n, arr, key);
    if (pos != -1) {
        printf("\nKey Found at position %d\n", pos + 1);
    } else {
        printf("\nKey Not Found...\n");
    }

    return 0;
}