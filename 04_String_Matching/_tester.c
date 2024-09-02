#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool stringmatching(char *text, int n, char *pattern, int m) {
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && pattern[j] == text[i + j]) {
            j++;
        }

        if (j == m) {
            return true;
        }
    }

    return false;
}

int main() {
    char *text = (char *)malloc(100 * sizeof(char));
    char *pattern = (char *)malloc(100 * sizeof(char));

    printf("Enter the text: ");
    gets(text);
    printf("Enter the pattern: ");
    gets(pattern);

    int n = strlen(text), m = strlen(pattern);
    bool isMatched = stringmatching(text, n, pattern, m);

    if (isMatched) {
        printf("\nPattern '%s' matched with Text '%s'\n", pattern, text);
    } else {
        printf("\nPattern '%s' doesn't match with the Text '%s'\n", pattern, text);
    }
}