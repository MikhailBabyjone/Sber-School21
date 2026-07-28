#include <stdio.h>
#define NMAX 10

int input(int* a, int* n);
void output(int* a, int n);
int max(int* a, int n);
int min(int* a, int n);
double mean(int* a, int n);
double variance(int* a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];

    if (input(data, &n) == 0) {
        printf("n/a");
    } else {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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

void output(int* a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");
}

int max(int* a, int n) {
    int max_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_v) {
            max_v = a[i];
        }
    }
    return max_v;
}

int min(int* a, int n) {
    int min_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_v) {
            min_v = a[i];
        }
    }
    return min_v;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}
