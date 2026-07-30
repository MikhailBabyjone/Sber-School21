#include <ctype.h>
#include <stdio.h>

#define MAX_LEN 101

static int normalize_char(char c) {
    int result = -1;

    if (isalpha((unsigned char)c)) {
        result = tolower((unsigned char)c);
    } else if (isdigit((unsigned char)c)) {
        result = c;
    }

    return result;
}

static int is_palindrome(const char *str) {
    int left = 0;
    int right = 0;
    int is_pal = 1;

    while (str[right] != '\0' && str[right] != '\n') {
        right++;
    }
    right--;

    while (left < right && is_pal) {
        int left_char = normalize_char(str[left]);
        int right_char = normalize_char(str[right]);

        while (left_char == -1 && left < right) {
            left++;
            left_char = normalize_char(str[left]);
        }
        while (right_char == -1 && left < right) {
            right--;
            right_char = normalize_char(str[right]);
        }

        if (left_char != right_char) {
            is_pal = 0;
        } else {
            left++;
            right--;
        }
    }

    return is_pal;
}

int main(void) {
    char str[MAX_LEN];

    if (fgets(str, MAX_LEN, stdin) != NULL) {
        if (is_palindrome(str)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
