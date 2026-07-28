#include <stdio.h>
#define NMAX 10

int input(int* a, int n);
void sort_array(int* a, int n);
void output(int* a, int n);

int main() {
    int data[NMAX];
    int status = 0;

    if (input(data, NMAX) == 0) {
        printf("n/a");
    } else {
        sort_array(data, NMAX);
        output(data, NMAX);
        status = 0;
    }

    return status;
}

int input(int* a, int n) {
    char c;
    int ok = 1;

    for (int i = 0; i < n && ok; i++) {
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

void sort_array(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
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
