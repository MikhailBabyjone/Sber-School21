#include <stdio.h>
#include <stdlib.h>

int input(int *a, int n);
void sort_array(int *a, int n);
void output(int *a, int n);

int main() {
    int n;
    int *data = NULL;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    }
    data = (int *)malloc(n * sizeof(int));
    if (data == NULL) {
        printf("n/a");
        return 0;
    }

    if (input(data, n) == 0) {
        printf("n/a");
    } else {
        sort_array(data, n);
        output(data, n);
    }
    free(data);

    return 0;
}

int input(int *a, int n) {
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

void sort_array(int *a, int n) {
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

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
}
