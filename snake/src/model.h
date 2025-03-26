class Snake {
public:
    Snake(int width, int length);

    void update();
    void increase();
    list<coord> place;
    enum direction head;
    int waiting = 0;
};

class Star {
public:
    int width;
    int length;
    coord star_place = coord(0, 0);
    Star(int width1, int length1) : width(width1), length(length1) {}

    coord get_star();

};

class Model {
public:
    Model(int width, int length);
    void update_direction(enum direction dir);
    void update_model();

    int start = 1;
    int width;
    int length;

    Snake* snake;
    Star* star;
};
