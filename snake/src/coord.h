typedef struct coord {
    int x;
    int y;
    coord(int x1, int y1) : x(x1), y(y1) {}

    bool operator==(const coord& other) const {
        return (x == other.x && y == other.y);
    }
} coord;


