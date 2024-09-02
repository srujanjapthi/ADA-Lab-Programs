#include <stdio.h>
#include <limits.h>

int euclidsGCD(int m, int n) {
    int count = 0;
    while (n != 0) {
        int rem = m % n;
        m = n;
        n = rem;
        count++;
    }

    return count;
}

int consecutiveIntegerCheckGCD(int m, int n) {
    int min = m < n ? m : n;
    int count = 0;

    for (int i = min; i > 1; i--) {
        count++;
        if (m % i == 0 && ++count && n % i == 0) {
            return count;
        }
    }

    return count;
}

int modifiedEuclidsGCD(int m, int n) {
    int count = 0;
    while (n != 0) {
        count++;
        if (m < n) {
            int temp = m;
            m = n;
            n = temp;
        }

        m -= n;
    }

    return count;
}

void plotter(int choice) {
    FILE *fpBest, *fpWorst;

    switch (choice) {
        case 1:
            fpBest = fopen("euclids_best.txt", "w");
            fpWorst = fopen("euclids_worst.txt", "w");
            break;

        case 2:
            fpBest = fopen("consecutive_best.txt", "w");
            fpWorst = fopen("consecutive_worst.txt", "w");
            break;

        case 3:
            fpBest = fopen("modified_best.txt", "w");
            fpWorst = fopen("modified_worst.txt", "w");
            break;
    }

    for (int i = 10; i <= 100; i += 10) {
        int minCount = INT_MAX, maxCount = INT_MIN;
        for (int j = 2; j <= i; j++) {
            for (int k = 2; k <= i; k++) {
                int count = 0;
                switch (choice) {
                    case 1:
                        count = euclidsGCD(j, k);
                        break;

                    case 2:
                        count = consecutiveIntegerCheckGCD(j, k);
                        break;

                    case 3:
                        count = modifiedEuclidsGCD(j, k);
                        break;
                }

                minCount = count < minCount ? count : minCount;
                maxCount = count > maxCount ? count : maxCount;
            }
        }

        fprintf(fpBest, "%d\t%d\n", i, minCount);
        fprintf(fpWorst, "%d\t%d\n", i, maxCount);
    }

    fclose(fpBest), fclose(fpWorst);
}

void main() {
    plotter(1), plotter(2), plotter(3);
}
