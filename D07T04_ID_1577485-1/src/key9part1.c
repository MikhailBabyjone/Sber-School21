#include <stdio.h>
#define NMAX 10

int input(int* buffer, int* length);
void output(int* buffer, int length);
int sum_numbers(int* buffer, int length);
int find_numbers(int* buffer, int length, int number, int* numbers);

int main() {
    int buffer[NMAX];
    int numbers[NMAX];
    int length = 0;
    int sum = 0;
    int count = 0;
    int status = 0;

    if (input(buffer, &length) == 0) {
        printf("n/a");
    } else {
        sum = sum_numbers(buffer, length);
        if (sum == 0) {
            printf("n/a");
        } else {
            count = find_numbers(buffer, length, sum, numbers);
            printf("%d\n", sum);
            output(numbers, count);
        }
    }

    return status;
}

int input(int* buffer, int* length) {
    char c;
    int ok = 1;

    if (scanf("%d", length) != 1 || *length < 1 || *length > NMAX) {
        ok = 0;
    }
    if (ok) {
        c = getchar();
        if (c != EOF && c != ' ' && c != '\n') {
            ok = 0;
        }
    }
    for (int i = 0; i < *length && ok; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
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

void output(int* buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (i != 0) {
            printf(" ");
        }
        printf("%d", buffer[i]);
    }
}

int sum_numbers(int* buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
        }
    }

    return sum;
}

int find_numbers(int* buffer, int length, int number, int* numbers) {
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }

    return count;
}
