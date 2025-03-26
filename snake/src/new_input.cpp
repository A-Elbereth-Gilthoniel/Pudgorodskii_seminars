#include "game.h"

void set_new_input() {
    struct termios tt;
    tcgetattr(STDIN_FILENO, &tt);
    tt.c_lflag &= ~ICANON;
    tt.c_lflag &= ~ECHO;
    tt.c_cc[VMIN] = 0;
    tt.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &tt);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

//===================================================

void set_old_input() {
    struct termios tt;
    tcgetattr(STDIN_FILENO, &tt);
    tt.c_lflag |= ICANON;
    tt.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tt);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}
