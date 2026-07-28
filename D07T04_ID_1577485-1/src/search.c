#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int* a, int* n);
double mean(int* a, int n);
double variance(int* a, int n);
int search(int* a, int n);

int main() {
    int n, data[NMAX];

    if (input(data, &n) == 0) {
        printf("n/a");
    } else {
        printf("%d", search(data, n));
    }

    return 0;
}

int input(int* a, int* n) {
    char c;
    int ok = 1;

    if (scanf("%d", n) != 1 || *n < 1 || *n > NMAX) {
        ok = 0;
    }
    if (ok) {
        c = getchar();
        if (c != EOF && c != ' ' && c != '\n') {
            ok = 0;
        }
    }
    for (int i = 0; i < *n && ok; i++) {
        if (scanf("%d", &a[i]) != 1) {
            ok = 0;
        } else {
            c = getchar();
            if (c != EOF && c != ' ' && c != '\n') {
                ok = 0;
            }
        }
    }
    return ok;
}

double mean(int* a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int* a, int n) {
    double m = mean(a, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double d = a[i] - m;
        sum += d * d;
    }
    return sum / n;
}

int search(int* a, int n) {
    double m = mean(a, n);
    double upper = m + 3.0 * sqrt(variance(a, n));
    int result = 0;
    int i = 0;

    while (i < n && result == 0) {
        if (a[i] != 0 && a[i] % 2 == 0 && a[i] >= m && a[i] <= upper) {
            result = a[i];
        }
        i++;
    }
    return result;
}
