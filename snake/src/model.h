class Star {
public:
    int width;
    int length;
    coord get_star();
    coord star_place = coord(0, 0);
    Star(int width1, int length1) : width(width1), length(length1), star_place(get_star()) {}

};

class Snake {
public:
    Snake(int x, int y);
    coord update(unordered_set<coord>& snake_coords);
    void increase(unordered_set<coord>& snake_coords);
    list<coord> place;
    enum direction head;
    int waiting = 0;
    ~Snake();
};

class SnakeBot : public Snake {
public:
    using Snake::Snake;
    void analyse(vector<Star*> stars, unordered_set<coord> snake_coords);
    coord current_source = coord(-1, -1);
};

class Model {
public:
    Model(int width, int length, int bots_size);
    virtual void update_direction(enum direction dir);
    vector<coord>  update_model();

    int start = 1;
    int width;
    int length;
    int bots_size;

    Snake* snake;
    vector<Star*> stars;
    unordered_set<coord> snake_coords;
    vector<SnakeBot*> snake_bots;
    // Star* star;
};
