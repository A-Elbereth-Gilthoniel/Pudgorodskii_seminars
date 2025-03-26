#ifndef LIBR
#define LIBR

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <list>
#include <algorithm>
#include <random>
#include <termios.h>
#include <fcntl.h>
#include <poll.h>

using namespace std;

#define LENGTH 20
#define WIDTH 50
#define SNAKE_COLOR 31
#define FIELD_COLOR 32
#define RED "\033[31m"
#define GREEN "\033[32m"
#define FPS 20
#define SPEED 5

enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif              // libr
