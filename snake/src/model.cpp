#include "game.h"

//======================================

Model::Model(int width, int length) : \
            width(width), length(length)
{
    star = new Star(width, length);
    snake = new Snake(width, length);
}

//======================================================

Snake::Snake(int width, int length)
{
    place = {coord(width / 2, length / 2)};
    head = LEFT;
}

//======================================================

void Model::update_direction(enum direction dir)
{
    if ((snake->head == LEFT && dir == RIGHT) ||
        (snake->head == RIGHT && dir == LEFT) ||
        (snake->head == DOWN && dir == UP) ||
        (snake->head == UP && dir == DOWN))
        return;
    snake->head = dir;
}

//======================================================

void Model::update_model()
{
    snake->update();
    if (snake->place.back() == star->star_place || start == 1)
    {
        snake->increase();
        coord star_place = star->get_star();
        while (find(snake->place.begin(), snake->place.end(), star_place) != snake->place.end())
        {
            star_place = star->get_star();
        }
        start = 0;
    }

}

//======================================================

void Snake::update()
{
    waiting++;
    if (waiting >= FPS/SPEED)
    // if (1)
    {
        auto it = --place.end();
        coord last = *it;
        coord neww = coord(0, 0);
        switch (head)
        {
            case UP:
                neww = coord(last.x, last.y - 1);
                break;
            case DOWN:
                neww = coord(last.x, last.y + 1);
                break;
            case LEFT:
                neww = coord(last.x - 1, last.y);
                break;
            case RIGHT:
                neww = coord(last.x + 1, last.y);
                break;
        }
        if (find(place.begin(), place.end(), neww) != place.end() ||
            neww.x >= WIDTH || neww.x < 0 || neww.y >= LENGTH || neww.y < 0)
        {
            set_old_input();
            exit(0);
        }

        place.push_back(neww);
        place.pop_front();

        waiting = 0;
    }
}

//===========================================

coord Star::get_star()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, width-1);
    uniform_int_distribution<> dis2(1, length-1);

    star_place = coord(dis(gen), dis2(gen));
    return star_place;
}

//==========================================

void Snake::increase()
{
    auto it = --place.end();
    coord last = *it;
    switch (head)
        {
            case UP:
                place.push_back(coord(last.x, last.y - 1));
                break;
            case DOWN:
                place.push_back(coord(last.x, last.y + 1));
                break;
            case LEFT:
                place.push_back(coord(last.x - 1, last.y));
                break;
            case RIGHT:
                place.push_back(coord(last.x + 1, last.y));
                break;

        }
}
