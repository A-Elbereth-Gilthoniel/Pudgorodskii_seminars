#include "game.h"

//==============================================

View* View::get_view(int a)
{
    if (a == 1)
    {
        TView* b = new TView;
        return b;
    }
    else if (a == 2)
    {
        GView* b = new GView;
        return b;
    }
    return NULL;
}

//=============================================

void TView::draw()
{
    draw_snake(settings->snake, GREEN);
    for (Snake* snake : settings->snake_bots)
        draw_snake(snake, RED);
    draw_star();
}

//==============================================

void TView::clrscr(std::vector<coord> clear_coords)
{
    for (coord i : clear_coords)
    {
        std::cout << "\033[s";
        std::cout << "\033[" << i.y + 1 << "B";
        std::cout << "\033["<< i.x + 2 << "C";
        std::cout << "\033[D ";
        std::cout << "\033[u";
    }
}

//==============================================

void TView::galaxy(int width, int length)
{
    std::cout << "\033[s";
    std::cout << RED;
    std::cout << std::string(width + 2, '-') << std::endl;

    for (int i = 0; i < length; i++)
    {
            std::cout << "|";
            std::cout << std::string(width, ' ');
            std::cout << "|";
            std::cout << std::endl;
    }

    std::cout << std::string(width + 2, '-') << std::endl;
    std::cout << RED;

    std::cout << "\033[u";
}

//==============================================

void TView::set_model(Model* m)
{
    settings = m;
}

//==============================================

void TView::run()
{
    set_new_input();
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    int select;
    struct timespec start, end;

    int timeout = 50;
    char key = 0;
    galaxy(settings->width, settings->length);
    while (key != 'q')
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        select = poll(fds, 1, timeout);

        clock_gettime(CLOCK_MONOTONIC, &end);
        if (select > 0)
        {
            if (fds[0].revents & POLLIN)
            {
                read(STDIN_FILENO, &key, 1);
                switch (key)
                {
                    case 'a':
                        settings->update_direction(LEFT);
                        break;
                    case 'w':
                        settings->update_direction(UP);
                        break;
                    case 's':
                        settings->update_direction(DOWN);
                        break;
                    case 'd':
                        settings->update_direction(RIGHT);
                        break;
                }
            }
            if ((int)(1000000/FPS - (end.tv_sec - start.tv_sec)*1000000 - (end.tv_nsec - start.tv_nsec)/1000) > 0)
                usleep((int)(1000000/FPS - (end.tv_sec - start.tv_sec)*1000000 - (end.tv_nsec - start.tv_nsec)/1000));
        }

        clrscr(settings->update_model());
        draw();
    }
    // clrscr();
    set_old_input();
}

//==============================================

void TView::draw_snake(Snake* snake, const std::string color)
{
    std::list<coord>::iterator it;
    for (it = snake->place.begin(); it != --snake->place.end(); ++it)
    {
        std::cout << "\033[s" << color;
        std::cout << "\033[" << (*it).y + 1 << "B";
        std::cout << "\033["<< (*it).x + 2 << "C";
        std::cout << "\033[D#";
        std::cout << color << "\033[u";
    }
    std::cout << "\033[s" << color;
    std::cout << "\033[" << (*it).y + 1 << "B";
    std::cout << "\033[" << (*it).x + 2 << "C";
    switch (snake->head)
    {
        case UP:
            std::cout << "\033[D^";
            break;
        case DOWN:
            std::cout << "\033[Dv";
            break;
        case LEFT:
            std::cout << "\033[D<";
            break;
        case RIGHT:
            std::cout << "\033[D>";
            break;
    }
    std::cout << color <<"\033[u";
}

//===============================================

void TView::draw_star()
{
    for (int i = 0; i < settings->bots_size + 1; i++)
    {
        std::cout << "\033[s";
        std::cout << "\033[" << settings->stars[i]->star_place.y + 1 << "B";
        std::cout << "\033[" << settings->stars[i]->star_place.x + 2 << "C";
        std::cout << "\033[D*";
        std::cout << "\033[u";
    }
}
