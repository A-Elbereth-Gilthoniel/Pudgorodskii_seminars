typedef struct coord {
    int x;
    int y;
    coord(int x1, int y1) : x(x1), y(y1) {}

    bool operator==(const coord& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const coord& other) const {
        return (x != other.x && y != other.y);
    }
} coord;

namespace std {
    template<>
    struct hash<coord> {
        size_t operator()(const coord& c) const {
            return hash<int>()(c.x) ^ (hash<int>()(c.y) << 1);
        }
    };
}
