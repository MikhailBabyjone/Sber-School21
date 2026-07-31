#include <ncurses.h>
#include <stdio.h>

#define HEIGHT 25
#define WIDTH 80
#define DELAY_MIN 50
#define DELAY_MAX 1000
#define DELAY_STEP 50
#define DELAY_START 200

int read_field(int field[HEIGHT][WIDTH]);
int count_neighbors(int field[HEIGHT][WIDTH], int row, int col);
void next_generation(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]);
void draw_field(int field[HEIGHT][WIDTH]);
void handle_input(int *delay_ms, int *running);

int main(void) {
    int current[HEIGHT][WIDTH];
    int next[HEIGHT][WIDTH];
    int delay_ms = DELAY_START;
    int running = 1;

    if (!read_field(current)) {
        printf("n/a\n");
        return 1;
    }

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (running) {
        draw_field(current);
        handle_input(&delay_ms, &running);
        if (running) {
            next_generation(current, next);
            napms(delay_ms);
        }
    }

    endwin();
    return 0;
}

int read_field(int field[HEIGHT][WIDTH]) {
    int i;
    int j;
    int c;
    int ok = 1;

    for (i = 0; i < HEIGHT && ok; i++) {
        for (j = 0; j < WIDTH && ok; j++) {
            c = getchar();
            while (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
                c = getchar();
            }
            if (c == '0' || c == '1') {
                field[i][j] = c - '0';
            } else {
                ok = 0;
            }
        }
    }
    return ok;
}

int count_neighbors(int field[HEIGHT][WIDTH], int row, int col) {
    int count = 0;
    int di;
    int dj;
    int ni;
    int nj;

    for (di = -1; di <= 1; di++) {
        for (dj = -1; dj <= 1; dj++) {
            if (di != 0 || dj != 0) {
                ni = (row + di + HEIGHT) % HEIGHT;
                nj = (col + dj + WIDTH) % WIDTH;
                count += field[ni][nj];
            }
        }
    }
    return count;
}

void next_generation(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    int i;
    int j;
    int neighbors;
    int alive;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            neighbors = count_neighbors(current, i, j);
            alive = current[i][j];
            if (alive && (neighbors == 2 || neighbors == 3)) {
                next[i][j] = 1;
            } else if (!alive && neighbors == 3) {
                next[i][j] = 1;
            } else {
                next[i][j] = 0;
            }
        }
    }
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            current[i][j] = next[i][j];
        }
    }
}

void draw_field(int field[HEIGHT][WIDTH]) {
    int i;
    int j;

    erase();
    for (j = 0; j < WIDTH + 2; j++) {
        mvaddch(0, j, '-');
        mvaddch(HEIGHT + 1, j, '-');
    }
    for (i = 0; i < HEIGHT + 2; i++) {
        mvaddch(i, 0, '|');
        mvaddch(i, WIDTH + 1, '|');
    }
    mvaddch(0, 0, '+');
    mvaddch(0, WIDTH + 1, '+');
    mvaddch(HEIGHT + 1, 0, '+');
    mvaddch(HEIGHT + 1, WIDTH + 1, '+');
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (field[i][j]) {
                mvaddch(i + 1, j + 1, 'O');
            } else {
                mvaddch(i + 1, j + 1, ' ');
            }
        }
    }
    refresh();
}

void handle_input(int *delay_ms, int *running) {
    int key;

    key = getch();
    if (key == ' ') {
        *running = 0;
    } else if (key == 'a' || key == 'A') {
        *delay_ms -= DELAY_STEP;
        if (*delay_ms < DELAY_MIN) {
            *delay_ms = DELAY_MIN;
        }
    } else if (key == 'z' || key == 'Z') {
        *delay_ms += DELAY_STEP;
        if (*delay_ms > DELAY_MAX) {
            *delay_ms = DELAY_MAX;
        }
    }
}
