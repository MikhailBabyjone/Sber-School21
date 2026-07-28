#include <stdio.h>
#define NMAX 10

int input(int* a, int* n, int* c);
void cycle_shift(int* a, int n, int c);
void output(int* a, int n);

int main() {
    int n, c, data[NMAX];
    int status = 0;

    if (input(data, &n, &c) == 0) {
        printf("n/a");
    } else {
        cycle_shift(data, n, c);
        output(data, n);
        status = 0;
    }

    return status;
}

int input(int* a, int* n, int* c) {
    char ch;
    int ok = 1;

    if (scanf("%d", n) != 1 || *n < 1 || *n > NMAX) {
        ok = 0;
    }
    if (ok) {
        ch = getchar();
        if (ch != EOF && ch != ' ' && ch != '\n') {
            ok = 0;
        }
    }
    for (int i = 0; i < *n && ok; i++) {
        if (scanf("%d", &a[i]) != 1) {
            ok = 0;
        } else {
            ch = getchar();
            if (ch != EOF && ch != ' ' && ch != '\n') {
                ok = 0;
            }
        }
    }
    if (ok && scanf("%d", c) != 1) {
        ok = 0;
    }
    if (ok) {
        ch = getchar();
        if (ch != EOF && ch != ' ' && ch != '\n') {
            ok = 0;
        }
    }
    return ok;
}

void cycle_shift(int* a, int n, int c) {
    int tmp[NMAX];

    for (int i = 0; i < n; i++) {
        int idx = ((i + c) % n + n) % n;
        tmp[i] = a[idx];
    }
    for (int i = 0; i < n; i++) {
        a[i] = tmp[i];
    }
}

void output(int* a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
}
