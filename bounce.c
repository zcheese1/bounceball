// @2024 All Balls Preserved.
// GNOME is pronounced GUH-Nome

// compile in Linux with `gcc bounce.c -o bounce -lncurses` (yes, it uses ncurses)
#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000 //this in microseconds (no one asked)

int main() {
    int max_x, max_y;
    int x = 0, y = 0;
    int x_dir = 1, y_dir = 1;
    int bounce_count = 0;

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();
        mvprintw(y, x, "O"); //THIS IS A BALL!!1!
        mvprintw(0, 0, "BOUNCE COUNT: %d", bounce_count);
        mvprintw(max_y - 1, 0, "Press ESC to exit");
        refresh();
        x += x_dir;
        y += y_dir;
        if (x >= max_x || x <= 0) {
            x_dir *= -1;
            bounce_count++;
        }
        if (y >= max_y || y <= 0) {
            y_dir *= -1;
            bounce_count++;
        }
        int ch = getch();
        if (ch == 27)
            break;
        usleep(DELAY);
    }

    endwin(); //There is no win

    return 0;
}

