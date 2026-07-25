#include <ncurses.h>
#include <stdio.h>

char Key = '\0';
int dirX = 1, dirY = 1;
int Width = 80;
int Height = 25;
int P1U = 0;
int PL = 3;
int P2U = 0;
int ballX = 0;
int ballY = 0;
int S1 = 0;
int S2 = 0;
int Input = 0;
int Speed = 140;
void draw(void);
int keyinput(void);
void move_ball(void);
int main(void) {
    ballX = Width / 2;
    ballY = Height / 2;
    P1U = (Height / 2) - 1;
    P2U = P1U;
    initscr();
    draw();
    mvprintw(Height + 2, 0, "Press any key to start");
    refresh();
    getch();

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    while (S1 < 21 && S2 < 21 && Input != -1) {
        Input = keyinput();
        if (Input != -1) {
            move_ball();
            draw();
            napms(Speed);
        }
    }
    endwin();
    if (S1 == 21) {
        printf("Good Game!\nPlayer 1 wins\n");
    } else if (S2 == 21) {
        printf("Good Game!\nPlayer 2 wins\n");
    } else {
        printf("Game stopped\n");
    }
    return 0;
}

void draw() {
    erase();
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            if (x == 0 || x == Width - 1) {
                mvaddch(y, x, 'X');
            } else if ((x == 1) && y >= P1U && y < P1U + PL) {
                mvaddch(y, x, '|');
            } else if ((x == Width - 2) && y >= P2U && y < P2U + PL) {
                mvaddch(y, x, '|');
            } else if (y == 0 || y == Height - 1) {
                mvaddch(y, x, '#');
            } else if (x == ballX && y == ballY) {
                mvaddch(y, x, 'o');
            } else {
                mvaddch(y, x, ' ');
            }
        }
    }
    mvprintw(Height + 1, Width / 2,
             "P1:  %d  ||  P2:  %d\n\nA/Z - left, K/M - right, Space - stepn\n\n\n\n\n", S1, S2);
    refresh();
}
int keyinput() {
    Key = getch();
    int Correct = 1;
    if ((Key == 'a' || Key == 'A') && P1U > 1) {
        P1U--;
    } else if ((Key == 'z' || Key == 'Z') && P1U < Height - 1 - PL) {
        P1U++;
    } else if ((Key == 'k' || Key == 'K') && P2U > 1) {
        P2U--;
    } else if ((Key == 'm' || Key == 'M') && P2U < Height - 1 - PL) {
        P2U++;
    } else if (Key == 'q' || Key == 'Q') {
        Correct = -1;
    }
    return Correct;
}

void move_ball() {
    ballX += dirX;
    ballY += dirY;
    if (ballY <= 0 || ballY >= Height - 1) {
        dirY = -dirY;
        ballY += dirY;
    }
    if (ballX == 1 && ballY >= P1U && ballY < P1U + PL) {
        dirX = -dirX;
        ballX += dirX;
    }
    if (ballX == Width - 2 && ballY >= P2U && ballY < P2U + PL) {
        dirX = -dirX;
        ballX += dirX;
    }
    if (ballX < 0) {
        S2++;
        ballX = Width / 2;
        ballY = Height / 2;
        dirX = 1;
        dirY = 1;
    }
    if (ballX > Width - 1) {
        S1++;
        ballX = Width / 2;
        ballY = Height / 2;
        dirX = -1;
        dirY = -1;
    }
}
