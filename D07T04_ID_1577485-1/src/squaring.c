#include <stdio.h>
#define NMAX 10

int input(int* a, int* n);
void output(int* a, int n);
void squaring(int* a, int n);

int main() {
    int n, data[NMAX];

    if (input(data, &n) == 0) {
        printf("n/a");
    } else {
        squaring(data, n);
        output(data, n);
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
}

void squaring(int* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
