#include <stdio.h>

int euclidsGCD(int m, int n) {
    while (n != 0) {
        int rem = m % n;
        m = n;
        n = rem;
    }

    return m;
}

int consecutiveIntegerCheckGCD(int m, int n) {
    int min = m < n ? m : n;
    for (int i = min; i > 1; i--) {
        if (m % i == 0 && n % i == 0) {
            return i;
        }
    }

    return 1;
}

int modifiedEuclidsGCD(int m, int n) {
    while (n != 0) {
        if (m < n) {
            int temp = m;
            m = n;
            n = temp;
        }

        m -= n;
    }

    return m;
}

int main() {
    int m, n;

    printf("Enter 2 numbers : ");
    scanf("%d%d", &m, &n);

    if (m < 0 || n < 0) {
        printf("Cannot find GCD... Try giving non negative Integers...");
    } else {
        printf("GCD using different Algorithms:\n");
        printf("Euclid's algorithm: %d\n", euclidsGCD(m, n));
        printf("Consecutive Integer Checking: %d\n", consecutiveIntegerCheckGCD(m, n));
        printf("Modified Euclid's Algorithm: %d\n", modifiedEuclidsGCD(m, n));
    }

    return 0;
}
