#include <stdio.h>
#include <stdlib.h>

#define STATIC_MAX 100

int input(int **matrix, int n, int m);
void output(int **matrix, int n, int m);

int **alloc_static(int n, int m, int static_buf[STATIC_MAX][STATIC_MAX], int *static_ptrs[STATIC_MAX]);
int **alloc_dynamic1(int n, int m);
int **alloc_dynamic2(int n, int m, int **data_block);
int **alloc_dynamic3(int n, int m);
void free_dynamic1(int **matrix, int n);
void free_dynamic2(int **matrix, int *data_block);
void free_dynamic3(int **matrix);

int main() {
    int mode;
    int n, m;
    int **matrix = NULL;
    int static_buf[STATIC_MAX][STATIC_MAX];
    int *static_ptrs[STATIC_MAX];
    int *data_block = NULL;
    int ok = 1;

    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 4) {
        printf("n/a");
        return 0;
    }
    if (scanf("%d%d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }
    if (mode == 1 && (n > STATIC_MAX || m > STATIC_MAX)) {
        printf("n/a");
        return 0;
    }

    if (mode == 1) {
        matrix = alloc_static(n, m, static_buf, static_ptrs);
    } else if (mode == 2) {
        matrix = alloc_dynamic1(n, m);
    } else if (mode == 3) {
        matrix = alloc_dynamic2(n, m, &data_block);
    } else {
        matrix = alloc_dynamic3(n, m);
    }

    if (matrix == NULL) {
        printf("n/a");
        return 0;
    }

    if (input(matrix, n, m) == 0) {
        ok = 0;
    } else {
        output(matrix, n, m);
    }

    if (mode == 2) {
        free_dynamic1(matrix, n);
    } else if (mode == 3) {
        free_dynamic2(matrix, data_block);
    } else if (mode == 4) {
        free_dynamic3(matrix);
    }

    if (!ok) {
        printf("n/a");
    }
    return 0;
}

int **alloc_static(int n, int m, int static_buf[STATIC_MAX][STATIC_MAX], int *static_ptrs[STATIC_MAX]) {
    (void)m;
    for (int i = 0; i < n; i++) {
        static_ptrs[i] = static_buf[i];
    }
    return static_ptrs;
}

int **alloc_dynamic1(int n, int m) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(m * sizeof(int));
        if (matrix[i] == NULL) {
            free_dynamic1(matrix, n);
            return NULL;
        }
    }
    return matrix;
}

int **alloc_dynamic2(int n, int m, int **data_block) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    *data_block = (int *)malloc(n * m * sizeof(int));
    if (*data_block == NULL) {
        free(matrix);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = *data_block + i * m;
    }
    return matrix;
}

int **alloc_dynamic3(int n, int m) {
    int **matrix = (int **)malloc(n * sizeof(int *) + n * m * sizeof(int));
    int *data;
    if (matrix == NULL) {
        return NULL;
    }
    data = (int *)(matrix + n);
    for (int i = 0; i < n; i++) {
        matrix[i] = data + i * m;
    }
    return matrix;
}

void free_dynamic1(int **matrix, int n) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_dynamic2(int **matrix, int *data_block) {
    free(data_block);
    free(matrix);
}

void free_dynamic3(int **matrix) { free(matrix); }

int input(int **matrix, int n, int m) {
    char c;
    int ok = 1;

    for (int i = 0; i < n && ok; i++) {
        for (int j = 0; j < m && ok; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                ok = 0;
            } else {
                c = getchar();
                if (c != EOF && c != ' ' && c != '\n') {
                    ok = 0;
                }
            }
        }
    }
    return ok;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j != 0) {
                printf(" ");
            }
            printf("%d", matrix[i][j]);
        }
        if (i != n - 1) {
            printf("\n");
        }
    }
}