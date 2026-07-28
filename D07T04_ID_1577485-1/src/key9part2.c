#include <stdio.h>

#define LEN 100

void sum(int* buff1, int len1, int* buff2, int len2, int* result, int* result_length);
void sub(int* buff1, int len1, int* buff2, int len2, int* result, int* result_length);
int read_number(int* buff);
int compare_numbers(int* a, int len_a, int* b, int len_b);
void print_number(int* buff, int len);
int trim_leading(int* buff, int len);

int main() {
    int buff1[LEN];
    int buff2[LEN];
    int sum_res[LEN + 1];
    int sub_res[LEN + 1];
    int len1 = 0;
    int len2 = 0;
    int sum_len = 0;
    int sub_len = 0;
    int status = 0;

    len1 = read_number(buff1);
    len2 = read_number(buff2);
    if (len1 <= 0 || len2 <= 0) {
        printf("n/a");
    } else {
        sum(buff1, len1, buff2, len2, sum_res, &sum_len);
        print_number(sum_res, sum_len);
        printf("\n");
        if (compare_numbers(buff1, len1, buff2, len2) < 0) {
            printf("n/a");
        } else {
            sub(buff1, len1, buff2, len2, sub_res, &sub_len);
            print_number(sub_res, sub_len);
        }
    }

    return status;
}

int read_number(int* buff) {
    int len = 0;
    int ch = getchar();
    int ok = 1;

    while (ok && ch != EOF && ch != '\n') {
        if (ch == ' ') {
            ch = getchar();
        } else if (ch >= '0' && ch <= '9') {
            if (len >= LEN) {
                ok = 0;
            } else {
                buff[len] = ch - '0';
                len++;
                ch = getchar();
            }
        } else {
            ok = 0;
        }
    }
    if (!ok || len == 0) {
        len = -1;
    }
    return len;
}

int compare_numbers(int* a, int len_a, int* b, int len_b) {
    int sa = trim_leading(a, len_a);
    int sb = trim_leading(b, len_b);
    int ea = len_a;
    int eb = len_b;
    int result = 0;

    if (ea - sa != eb - sb) {
        result = (ea - sa) - (eb - sb);
    } else {
        int i = sa;
        while (i < ea && result == 0) {
            if (a[i] != b[sb + (i - sa)]) {
                result = a[i] - b[sb + (i - sa)];
            }
            i++;
        }
    }
    return result;
}

int trim_leading(int* buff, int len) {
    int start = 0;

    while (start < len - 1 && buff[start] == 0) {
        start++;
    }
    return start;
}

void print_number(int* buff, int len) {
    int start = trim_leading(buff, len);

    for (int i = start; i < len; i++) {
        if (i != start) {
            printf(" ");
        }
        printf("%d", buff[i]);
    }
}

void sum(int* buff1, int len1, int* buff2, int len2, int* result, int* result_length) {
    int temp[LEN + 1];
    int i = len1 - 1;
    int j = len2 - 1;
    int k = 0;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int d1 = 0;
        int d2 = 0;
        int s = 0;

        if (i >= 0) {
            d1 = buff1[i];
        }
        if (j >= 0) {
            d2 = buff2[j];
        }
        s = d1 + d2 + carry;
        temp[k] = s % 10;
        carry = s / 10;
        k++;
        if (i >= 0) {
            i--;
        }
        if (j >= 0) {
            j--;
        }
    }
    for (int r = 0; r < k; r++) {
        result[r] = temp[k - 1 - r];
    }
    *result_length = k;
}

void sub(int* buff1, int len1, int* buff2, int len2, int* result, int* result_length) {
    int temp[LEN + 1];
    int i = len1 - 1;
    int j = len2 - 1;
    int k = 0;
    int borrow = 0;

    while (i >= 0) {
        int d1 = buff1[i] - borrow;
        int d2 = 0;
        int diff = 0;

        if (j >= 0) {
            d2 = buff2[j];
        }
        if (d1 < d2) {
            d1 = d1 + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        diff = d1 - d2;
        temp[k] = diff;
        k++;
        i--;
        if (j >= 0) {
            j--;
        }
    }
    for (int r = 0; r < k; r++) {
        result[r] = temp[k - 1 - r];
    }
    *result_length = k;
    while (*result_length > 1 && result[0] == 0) {
        for (int s = 0; s < *result_length - 1; s++) {
            result[s] = result[s + 1];
        }
        (*result_length)--;
    }
}
