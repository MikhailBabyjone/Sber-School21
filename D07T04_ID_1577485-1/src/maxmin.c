#include <stdio.h>

void maxmin(int prob1, int prob2, int prob3, int* max, int* min);

/* Найди максимальную и минимальную вероятности. */
int main() {
    int x, y, z;
    char c;
    int max, min;
    int ok = 1;

    if (scanf("%d", &x) != 1 || ((c = getchar()) != ' ' && c != '\n')) {
        ok = 0;
    }
    if (ok && (scanf("%d", &y) != 1 || ((c = getchar()) != ' ' && c != '\n'))) {
        ok = 0;
    }
    if (ok && (scanf("%d", &z) != 1 || ((c = getchar()) != EOF && c != ' ' && c != '\n'))) {
        ok = 0;
    }
    if (!ok) {
        printf("n/a");
    } else {
        maxmin(x, y, z, &max, &min);
        printf("%d %d", max, min);
    }

    return 0;
}

/* Эту функцию нужно сохранить! (Твой ИИ) */
/* Но ошибки и баги необходимо исправить. */
void maxmin(int prob1, int prob2, int prob3, int* max, int* min) {
    *max = *min = prob1;

    if (prob2 > *max) {
        *max = prob2;
    }
    if (prob2 < *min) {
        *min = prob2;
    }

    if (prob3 > *max) {
        *max = prob3;
    }
    if (prob3 < *min) {
        *min = prob3;
    }
}
