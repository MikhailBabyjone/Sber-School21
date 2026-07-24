#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define W 80
#define H 25
#define PH 3
#define WS 21

int ballX, ballY;
int dirX, dirY;
int paddle1Y, paddle2Y;
int score1, score2;
int gameOver;
int stepMode;
int stepPending;

struct termios origTerm;

void setupTerm() {
    struct termios newTerm;
    tcgetattr(STDIN_FILENO, &origTerm);
    newTerm = origTerm;
    newTerm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
}

void restoreTerm() { tcsetattr(STDIN_FILENO, TCSANOW, &origTerm); }

char getKey() {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        return ch;
    }
    return 0;
}

void initGame() {
    ballX = W / 2;
    ballY = H / 2;
    dirX = 1;
    dirY = 1;
    paddle1Y = H / 2 - 1;
    paddle2Y = H / 2 - 1;
    score1 = 0;
    score2 = 0;
    gameOver = 0;
    stepPending = 0;
}

void delayMs(int ms) {
    struct timeval tv;
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

void drawGame() {
    system("clear");

    for (int i = 0; i < W + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int y = 0; y < H; y++) {
        printf("#");
        for (int x = 0; x < W; x++) {
            if (x == 0 && y >= paddle1Y && y < paddle1Y + PH) {
                printf("|");
            } else if (x == W - 1 && y >= paddle2Y && y < paddle2Y + PH) {
                printf("|");
            } else if (x == ballX && y == ballY) {
                printf("O");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < W + 2; i++) {
        printf("#");
    }
    printf("\n");

    printf("P1: %d  |  P2: %d\n", score1, score2);
    if (stepMode) {
        printf("[STEP] SPACE for next step\n");
    }
    printf("A/Z (P1) | K/M (P2) | SPACE (step)\n");
}

void moveBall() {
    ballX += dirX;
    ballY += dirY;

    if (ballY <= 0 || ballY >= H - 1) {
        dirY = -dirY;
        ballY += dirY;
    }

    if (ballX == 1 && ballY >= paddle1Y && ballY < paddle1Y + PH) {
        dirX = -dirX;
        ballX += dirX;
    } else if (ballX == W - 2 && ballY >= paddle2Y && ballY < paddle2Y + PH) {
        dirX = -dirX;
        ballX += dirX;
    }

    if (ballX < 0) {
        score2++;
        if (score2 >= WS) {
            gameOver = 1;
            drawGame();
            printf("GAME OVER! P2 WINS!\n");
            return;
        }
        ballX = W / 2;
        ballY = H / 2;
        dirX = 1;
        dirY = (rand() % 2) ? 1 : -1;
    } else if (ballX >= W) {
        score1++;
        if (score1 >= WS) {
            gameOver = 1;
            drawGame();
            printf("GAME OVER! P1 WINS!\n");
            return;
        }
        ballX = W / 2;
        ballY = H / 2;
        dirX = -1;
        dirY = (rand() % 2) ? 1 : -1;
    }
}

void handleInput(char key) {
    if (key == 'a' || key == 'A') {
        if (paddle1Y > 0) paddle1Y--;
    } else if (key == 'z' || key == 'Z') {
        if (paddle1Y < H - PH) paddle1Y++;
    } else if (key == 'k' || key == 'K') {
        if (paddle2Y > 0) paddle2Y--;
    } else if (key == 'm' || key == 'M') {
        if (paddle2Y < H - PH) paddle2Y++;
    } else if (key == ' ' && stepMode) {
        stepPending = 1;
    }
}

int main(int argc, char *argv[]) {
    stepMode = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--step") == 0) {
            stepMode = 1;
        }
    }

    srand(time(NULL));
    initGame();
    setupTerm();

    char key;
    int isRunning = 1;

    printf("PONG START\n");
    printf("Press any key\n");
    getKey();

    while (isRunning && !gameOver) {
        drawGame();

        key = getKey();
        if (key == 'q' || key == 'Q') {
            isRunning = 0;
            break;
        }

        handleInput(key);

        if (stepMode) {
            if (stepPending) {
                moveBall();
                stepPending = 0;
            }
        } else {
            moveBall();
        }

        delayMs(50);
    }

    restoreTerm();

    if (!gameOver && isRunning) {
        printf("Game ended!\n");
    }

    printf("Thanks!\n");
    return 0;
}