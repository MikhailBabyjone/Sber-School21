#include <stdio.h>

#define N 15
#define M 13

void transform(int* buf, int** matr, int n, int m);
void make_picture(int** picture, int n, int m);
void reset_picture(int** picture, int n, int m);
void output(int** picture, int n, int m);

int main() {
    int picture_data[N][M];
    int* picture[N];

    transform((int*)picture_data, picture, N, M);
    make_picture(picture, N, M);
    output(picture, N, M);

    return 0;
}

void make_picture(int** picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);

    reset_picture(picture, n, m);

    /* Солнце справа вверху */
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            picture[1 + i][7 + j] = sun_data[i][j];
        }
    }

    /* Крона дерева */
    for (int i = 0; i < 4; i++) {
        picture[3][2 + i] = tree_foliage[i];
        picture[4][2 + i] = tree_foliage[i];
    }
    picture[2][3] = tree_foliage[0];
    picture[2][4] = tree_foliage[1];
    picture[5][3] = tree_foliage[2];
    picture[5][4] = tree_foliage[3];

    /* Ствол дерева */
    for (int i = 0; i < 4; i++) {
        picture[10][2 + i] = tree_trunk[i];
    }
    picture[6][3] = tree_trunk[0];
    picture[6][4] = tree_trunk[1];
    picture[8][3] = tree_trunk[0];
    picture[8][4] = tree_trunk[1];
    picture[9][3] = tree_trunk[2];
    picture[9][4] = tree_trunk[3];

    /* Рама окна: верх, середина, низ */
    for (int i = 0; i < length_frame_w; i++) {
        picture[0][i] = frame_w[i];
        picture[7][i] = frame_w[i];
        picture[n - 1][i] = frame_w[i];
    }

    /* Рама окна: левый, средний и правый столбец */
    for (int i = 0; i < length_frame_h; i++) {
        picture[i][0] = frame_h[i];
        picture[i][6] = frame_h[i];
        picture[i][m - 1] = frame_h[i];
    }
}

void reset_picture(int** picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int* buf, int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void output(int** picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j != 0) {
                printf(" ");
            }
            printf("%d", picture[i][j]);
        }
        if (i != n - 1) {
            printf("\n");
        }
    }
}
