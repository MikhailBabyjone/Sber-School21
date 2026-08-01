#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main(void) {
    double *data;
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("NO");
        return 0;
    }

    data = (double *)malloc(n * sizeof(double));
    if (data == NULL) {
        printf("NO");
        return 0;
    }

    input(data, n);

    if (make_decision(data, n)) {
        printf("YES");
    } else {
        printf("NO");
    }

    free(data);
    return 0;
}