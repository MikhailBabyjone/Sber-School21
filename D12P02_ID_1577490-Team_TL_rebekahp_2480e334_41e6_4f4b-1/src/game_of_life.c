
#include <stdio.h>
#include <ncurses.h>

#define HEIGHT 25
#define WIDTH 80
#define DELAY_MIN 100
#define DELAY_MAX 1000

void draw_field(int current[HEIGHT][WIDTH], int delay);
void keyinput(int*delay, int* condition);
int count_neighbours(int current[HEIGHT][WIDTH], int r, int c);
void process_game(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]);
void preset_input(int current[HEIGHT][WIDTH]);

int main(void){
    int current[HEIGHT][WIDTH];
    int next[HEIGHT][WIDTH];
    int delay = 200;
    int condition = 1;

    preset_input(current);
    freopen("/dev/tty", "r", stdin);
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    while (condition)
    {   
        draw_field(current, delay);
        keyinput(&delay, &condition);
        if (condition){
        process_game(current, next);
        napms(delay);
        }
    }

    endwin();
    return 0;
    
    
    
    



}

void draw_field(int current[HEIGHT][WIDTH], int delay){
        erase();
        int i = 0;
        int j =0;
        for (i = 0; i < HEIGHT + 2;i++){
            mvaddch(i, 0, '|');
            mvaddch(i, WIDTH +1, '|');
        }
        for (j = 0; j < WIDTH + 2;j++){
            mvaddch(0, j, '-');
            mvaddch(HEIGHT+1, j, '-');
        }
        mvaddch (0, 0, '+');
        mvaddch (HEIGHT+1, 0, '+');
        mvaddch (0 , WIDTH + 1, '+');
        mvaddch (HEIGHT+1, WIDTH+1, '+');
        for (i = 0; i < HEIGHT; i++){
            for(j = 0; j<WIDTH; j++){
                if (current[i][j] == 1){
                    mvaddch(i + 1, j + 1, 'o');
                } else if (current[i][j] == 0){
                    mvaddch(i + 1, j + 1, ' ');
                }
            }
        }
        mvprintw(HEIGHT + 3, 0, "A faster | Z slower | SPACE exit | current speed=%d", 1100-delay);
        refresh();

}

void keyinput(int* delay, int* condition){
    int key;
    int delay_step = 100;

    key = getch();
    if (key == ' '){
        *condition = 0;
    }
    else if (key == 'A' || key == 'a'){
        *delay -= delay_step;
        if (*delay < DELAY_MIN){
            *delay = DELAY_MIN;
        }
    }
    else if (key == 'Z' || key == 'z'){
        *delay += delay_step;
        if (*delay > DELAY_MAX){
        *delay = DELAY_MAX;
        }
    }
    
    


}

int count_neighbours(int current[HEIGHT][WIDTH], int r, int c) {
    int count = 0;
    int nei_r;
    int nei_c;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!(i == 0 && j == 0)) {
            

            nei_r = (r + i + HEIGHT) % HEIGHT;
            nei_c = (c + j + WIDTH) % WIDTH;
            
            if (current[nei_r][nei_c]) {
                count++;
            }
            }
        }
    }

    return count;
}



void process_game(int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    int i = 0;
    int j = 0;
    int neighbours;
    
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            neighbours = count_neighbours(current, i, j);
            
            if (current[i][j] == 1) {
                if (neighbours < 2 || neighbours > 3) {
                    next[i][j] = 0;
                } else {
                    next[i][j] = 1;
                }
            } else {
                if (neighbours == 3) {
                    next[i][j] = 1;
                } else {
                    next[i][j] = 0;
                }
            }
        }
    }

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            current[i][j] = next[i][j];
        }
    }
}



void preset_input(int current[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            current[i][j] = 0;
        }
    }

    int r = 0;
    int c = 0;
    int ch;

    while (r < HEIGHT && (ch = getchar()) != EOF) {
        if (ch == '1') {
            current[r][c] = 1;
            c++;
        } else if (ch == '0') {
            current[r][c] = 0;
            c++;
        }
        if (c >= WIDTH) {
            c = 0;
            r++;
        }
    }
}
