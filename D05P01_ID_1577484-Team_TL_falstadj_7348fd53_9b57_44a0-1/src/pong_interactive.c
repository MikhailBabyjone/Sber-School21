#include <ncurses.h>
#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_LENGTH 3
#define WIN_SCORE 21
#define GAME_SPEED_MS 140

typedef struct {
    int ball_x;
    int ball_y;
    int dir_x;
    int dir_y;
    int paddle1_y;
    int paddle2_y;
    int score1;
    int score2;
} GameState;

typedef struct {
    GameState state;
    int should_quit;
} InputResult;

GameState create_initial_state(void);
char cell_at(int x, int y, GameState state);
void render_field(GameState state);
void render_hud(GameState state);
void render_game(GameState state);
InputResult read_input(GameState state);
GameState reset_ball_after_score(GameState state, int dir_x, int dir_y);
GameState move_ball(GameState state);
void print_winner(GameState state);
void print_stopped(void);

int main(void) {
    int running = 1;
    int quit = 0;
    GameState state = create_initial_state();

    initscr();
    render_game(state);
    mvprintw(FIELD_HEIGHT + 2, 0, "Press any key to start");
    refresh();
    getch();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    while (running == 1) {
        InputResult input = read_input(state);
        state = input.state;
        quit = input.should_quit;
        state = move_ball(state);
        render_game(state);
        napms(GAME_SPEED_MS);
        if (state.score1 >= WIN_SCORE || state.score2 >= WIN_SCORE) {
            running = 0;
        }
        if (quit == 1) {
            running = 0;
        }
    }
    endwin();
    if (quit == 1) {
        print_stopped();
    } else {
        print_winner(state);
    }
    return 0;
}

GameState create_initial_state(void) {
    GameState state;

    state.ball_x = FIELD_WIDTH / 2;
    state.ball_y = FIELD_HEIGHT / 2;
    state.dir_x = 1;
    state.dir_y = 1;
    state.paddle1_y = (FIELD_HEIGHT / 2) - 1;
    state.paddle2_y = state.paddle1_y;
    state.score1 = 0;
    state.score2 = 0;
    return state;
}

char cell_at(int x, int y, GameState state) {
    char result = ' ';

    if (x == 0 || x == FIELD_WIDTH - 1) {
        result = 'X';
    } else if (x == 1 && y >= state.paddle1_y && y < state.paddle1_y + PADDLE_LENGTH) {
        result = '|';
    } else if (x == FIELD_WIDTH - 2 && y >= state.paddle2_y && y < state.paddle2_y + PADDLE_LENGTH) {
        result = '|';
    } else if (y == 0 || y == FIELD_HEIGHT - 1) {
        result = '#';
    } else if (x == state.ball_x && y == state.ball_y) {
        result = 'o';
    }
    return result;
}

void render_field(GameState state) {
    int y = 0;

    while (y < FIELD_HEIGHT) {
        int x = 0;

        while (x < FIELD_WIDTH) {
            mvaddch(y, x, cell_at(x, y, state));
            x = x + 1;
        }
        y = y + 1;
    }
}

void render_hud(GameState state) {
    mvprintw(FIELD_HEIGHT + 1, 0, "P1:  %d  ||  P2:  %d", state.score1, state.score2);
    mvprintw(FIELD_HEIGHT + 2, 0, "A/Z - left, K/M - right, Q - quit");
}

void render_game(GameState state) {
    erase();
    render_field(state);
    render_hud(state);
    refresh();
}

InputResult read_input(GameState state) {
    InputResult result;
    int key = 0;

    result.state = state;
    result.should_quit = 0;
    key = getch();
    if (key == ERR) {
        return result;
    }
    if (key == 'q' || key == 'Q') {
        result.should_quit = 1;
    } else if (key == 'a' || key == 'A') {
        if (state.paddle1_y > 1) {
            result.state.paddle1_y = state.paddle1_y - 1;
        }
    } else if (key == 'z' || key == 'Z') {
        if (state.paddle1_y < FIELD_HEIGHT - 1 - PADDLE_LENGTH) {
            result.state.paddle1_y = state.paddle1_y + 1;
        }
    } else if (key == 'k' || key == 'K') {
        if (state.paddle2_y > 1) {
            result.state.paddle2_y = state.paddle2_y - 1;
        }
    } else if (key == 'm' || key == 'M') {
        if (state.paddle2_y < FIELD_HEIGHT - 1 - PADDLE_LENGTH) {
            result.state.paddle2_y = state.paddle2_y + 1;
        }
    }
    return result;
}

GameState reset_ball_after_score(GameState state, int dir_x, int dir_y) {
    state.ball_x = FIELD_WIDTH / 2;
    state.ball_y = FIELD_HEIGHT / 2;
    state.dir_x = dir_x;
    state.dir_y = dir_y;
    return state;
}

GameState move_ball(GameState state) {
    state.ball_x = state.ball_x + state.dir_x;
    state.ball_y = state.ball_y + state.dir_y;
    if (state.ball_y <= 0 || state.ball_y >= FIELD_HEIGHT - 1) {
        state.dir_y = -state.dir_y;
        state.ball_y = state.ball_y + state.dir_y;
    }
    if (state.ball_x == 1 && state.ball_y >= state.paddle1_y &&
        state.ball_y < state.paddle1_y + PADDLE_LENGTH) {
        state.dir_x = -state.dir_x;
        state.ball_x = state.ball_x + state.dir_x;
    }
    if (state.ball_x == FIELD_WIDTH - 2 && state.ball_y >= state.paddle2_y &&
        state.ball_y < state.paddle2_y + PADDLE_LENGTH) {
        state.dir_x = -state.dir_x;
        state.ball_x = state.ball_x + state.dir_x;
    }
    if (state.ball_x < 0) {
        state.score2 = state.score2 + 1;
        state = reset_ball_after_score(state, 1, 1);
    } else if (state.ball_x > FIELD_WIDTH - 1) {
        state.score1 = state.score1 + 1;
        state = reset_ball_after_score(state, -1, -1);
    }
    return state;
}

void print_winner(GameState state) {
    int winner = 0;

    if (state.score1 >= WIN_SCORE) {
        winner = 1;
    } else if (state.score2 >= WIN_SCORE) {
        winner = 2;
    }
    if (winner == 1) {
        printf("Good Game!\nPlayer 1 wins\n");
    }
    if (winner == 2) {
        printf("Good Game!\nPlayer 2 wins\n");
    }
}

void print_stopped(void) {
    printf("Game stopped\n");
}
