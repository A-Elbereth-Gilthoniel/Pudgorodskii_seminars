#include "game.h"

//======================================

Model::Model(int width, int length, int bots_size) : \
            width(width), length(length), bots_size(bots_size)
{
    snake = new Snake(width/2, length/2);
    snake_coords.insert(*snake->place.begin());
    snake_bots.reserve(bots_size);
    stars.reserve(1 + bots_size);
    for (int i = 0; i < bots_size; i++)
    {
        stars.push_back(new Star(width, length));
        snake_bots.push_back(new SnakeBot(width/2, (LENGTH / bots_size) * (i + 1) - 1));
        snake_coords.insert(*snake_bots.back()->place.begin());
    }
    stars.push_back(new Star(width, length));
}

//======================================================

Snake::Snake(int x, int y)
{
    place = {coord(x, y)};
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

    coord head_coord = *--snake->place.end();
    coord prehead = *(----snake->place.end());
    int dif_y = head_coord.y - prehead.y;
    int dif_x = head_coord.x - prehead.x;

    if ((dif_x == 0 && dif_y == 1 && dir == UP) ||
        (dif_x == 0 && dif_y == -1 && dir == DOWN) ||
        (dif_x == 1 && dif_y == 0 && dir == LEFT) ||
        (dif_x == -1 && dif_y == 0 && dir == RIGHT))
        return;
    snake->head = dir;
}

//======================================================

vector<coord> Model::update_model()
{
    vector<coord> clear_coords;
    coord clear_snake_coord = snake->update(snake_coords);
    if (clear_snake_coord != coord(-1, -1))
        clear_coords.push_back(clear_snake_coord);

    for (int i = 0; i < bots_size + 1; i++)
    {
        if (snake->place.back() == stars[i]->star_place)
        {
            clear_coords.push_back(stars[i]->star_place);
            snake->increase(snake_coords);
            coord star_place = stars[i]->get_star();
            while (find(snake->place.begin(), snake->place.end(), star_place) != snake->place.end())
            {
                star_place = stars[i]->get_star();
            }
        }
    }

    for (SnakeBot* snake_bot : snake_bots)
    {
        clear_snake_coord = snake_bot->update(snake_coords);
        if (clear_snake_coord != coord(-1, -1))
            clear_coords.push_back(clear_snake_coord);

        for (int i = 0; i < bots_size + 1; i++)
        {
            if (snake_bot->place.back() == stars[i]->star_place)
            {
                snake_bot->current_source = coord(-1, -1);
                clear_coords.push_back(stars[i]->star_place);
                snake_bot->increase(snake_coords);
                coord star_place = stars[i]->get_star();
                while (find(snake_bot->place.begin(), snake_bot->place.end(), star_place) != snake_bot->place.end())
                {
                    star_place = stars[i]->get_star();
                }
            }
        }
        if (snake_bot->current_source == *(--snake_bot->place.end()))
            snake_bot->current_source = coord(-1, -1);
        snake_bot->analyse(stars, snake_coords);

    }
    return clear_coords;
}

//======================================================

coord Snake::update(unordered_set<coord>& snake_coords)
{
    waiting++;
    if (waiting >= FPS/SPEED)
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
        if (snake_coords.find(neww) != snake_coords.end() ||
            neww.x >= WIDTH || neww.x < 0 || neww.y >= LENGTH || neww.y < 0)
        {
            set_old_input();
            exit(0);
            // for (list<coord>::iterator it = place.begin(); it != place.end(); ++it)
            //     snake_coords.erase(find(snake_coords.begin(), snake_coords.end(), *it));
        }
        coord cleared_coord = *place.begin();
        place.push_back(neww);
        place.pop_front();

        snake_coords.insert(neww);
        snake_coords.erase(cleared_coord);
        waiting = 0;

        return cleared_coord;
    }
    return coord(-1, -1);
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

void Snake::increase(unordered_set<coord>& snake_coords)
{
    auto it = --place.end();
    coord last = *it;
    coord neww = coord(-1, -1);
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
    place.push_back(neww);
    if (snake_coords.find(neww) == snake_coords.end())
        snake_coords.insert(neww);
}

//=====================================================

void SnakeBot::analyse(vector<Star*> stars, unordered_set<coord> snake_coords)
{
    coord head_coord = *(--place.end());
    int dist;
#if defined(STUPID)
    int max_dif=0;
#elif defined(SMART)
    int min_dif = WIDTH + LENGTH;
#endif
    coord source = coord(-1, -1);
#ifdef STUPID
    if (current_source == coord(-1, -1))
    {
#endif
        for (Star* star : stars)
        {
            dist = abs(head_coord.x - star->star_place.x) + abs(head_coord.y - star->star_place.y);
#if defined(STUPID)
            if (dist > max_dif)
            {
                max_dif = dist;
#elif defined(SMART)
            if (dist < min_dif)
            {
                min_dif = dist;
#endif
                source = star->star_place;
            }
        }
        current_source = source;
#ifdef STUPID
    }
#endif
    if (head_coord.y - current_source.y > 0 && head != DOWN)
        head = UP;
    else if (head_coord.y - current_source.y < 0 && head != UP)
        head = DOWN;
    else if (head_coord.x - current_source.x > 0 && head != RIGHT)
        head = LEFT;
    else if (head_coord.x - current_source.x < 0 && head != LEFT)
        head = RIGHT;

    int mask = 0b0000;                  // [0] - LEFT   [1] - RIGHT     [2] - UP    [3] - DOWN

    if (snake_coords.find(coord(head_coord.x - 1, head_coord.y)) != snake_coords.end()
        || head_coord.x == 0)
        mask |= 0b1000;
    if (snake_coords.find(coord(head_coord.x + 1, head_coord.y)) != snake_coords.end()
        || head_coord.x == WIDTH - 1)
        mask |= 0b0100;
    if (snake_coords.find(coord(head_coord.x, head_coord.y - 1)) != snake_coords.end()
        || head_coord.y == 0)
        mask |= 0b0010;
    if (snake_coords.find(coord(head_coord.x, head_coord.y + 1)) != snake_coords.end()
        || head_coord.y == LENGTH - 1)
        mask |= 0b0001;

    if (((head == LEFT) && ((mask | 0b1000) == mask)) || ((head == RIGHT) && ((mask | 0b0100) == mask)))
        head = ((mask | 0b0010) == mask) ? DOWN : UP;
    else if (((head == UP) && ((mask | 0b0010) == mask)) || ((head == DOWN) && ((mask | 0b0001) == mask)))
        head = ((mask | 0b0100) == mask) ? LEFT : RIGHT;
}

//==========================================================
