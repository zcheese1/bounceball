// @2024 All Balls Preserved.
// GNOME is pronounced GUH-Nome

// compile in Linux or MacOS with `gcc bounce.c -o bounce -lncurses` (yes, it uses ncurses)
#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000

int main() {
    int max_x, max_y;
    int x = 0, y = 0;
    int x_dir = 1, y_dir = 1;
    int bounce_count = 0;

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    if (!has_colors()) {
        endwin(); // this is not winning lol, it's ncurses 
        fprintf(stderr, "Error: Terminal colorblind :( \n"); // treat your Achromatopsia terminal btw
        return 1;
    }

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "O"); // your ball looks like this
        mvprintw(0, 0, "BOUNCE COUNT: %d", bounce_count);
        mvprintw(max_y - 1, 0, "Press ESC to exit");
        attroff(COLOR_PAIR(1));
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

    endwin();

    return 0; // RATE 1 STAR!1
}

}
