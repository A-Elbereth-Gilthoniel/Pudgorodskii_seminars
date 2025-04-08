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
#include <unordered_set>
#include <SFML/Graphics.hpp>

// using namespace std;

#define LENGTH 20
#define WIDTH 50
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1920
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
