#include "game.h"

//==============================================

View* View::get_view(int a)
{
    if (a == 1)
    {
        TView* b = new TView;
        return b;
    }
    return NULL;
}

//=============================================

void TView::draw()
{
    draw_snake();
    draw_star();
}

//==============================================

void TView::clrscr()
{
    list<coord>::iterator it;
    for (it = settings->snake->place.begin(); it != settings->snake->place.end(); ++it)
    {
        cout << "\033[s";
        cout << "\033[" << (*it).y + 1 << "B";
        cout << "\033["<< (*it).x + 2 << "C";
        cout << "\033[D ";
        cout << "\033[u";
    }
    cout << "\033[s";
    cout << "\033[" << settings->star->star_place.y + 1 << "B";
    cout << "\033[" << settings->star->star_place.x + 2 << "C";
    cout << "\033[D ";
    cout << "\033[u";

}

//==============================================

void TView::galaxy(int width, int length)
{
    cout << "\033[s";
    cout << RED;
    cout << string(width + 2, '-') << endl;

    for (int i = 0; i < length; i++)
    {
            cout << "|";
            cout << string(width, ' ');
            cout << "|";
            cout << endl;
    }

    cout << string(width + 2, '-') << endl;
    cout << RED;

    cout << "\033[u";
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

        clrscr();
        settings->update_model();
        draw();
    }
    clrscr();
    set_old_input();
}

//==============================================

void TView::draw_snake()
{
    list<coord>::iterator it;
    for (it = settings->snake->place.begin(); it != --settings->snake->place.end(); ++it)
    {
        cout << "\033[s" << GREEN;
        cout << "\033[" << (*it).y + 1 << "B";
        cout << "\033["<< (*it).x + 2 << "C";
        cout << "\033[D#";
        cout << GREEN << "\033[u";
    }
    cout << "\033[s" << GREEN;
    cout << "\033[" << (*it).y + 1 << "B";
    cout << "\033[" << (*it).x + 2 << "C";
    switch (settings->snake->head)
    {
        case UP:
            cout << "\033[D^";
            break;
        case DOWN:
            cout << "\033[Dv";
            break;
        case LEFT:
            cout << "\033[D<";
            break;
        case RIGHT:
            cout << "\033[D>";
            break;
    }
    cout << GREEN <<"\033[u";
}

//===============================================

void TView::draw_star()
{
    cout << "\033[s";
    cout << "\033[" << settings->star->star_place.y + 1 << "B";
    cout << "\033[" << settings->star->star_place.x + 2 << "C";
    cout << "\033[D*";
    cout << "\033[u";
}
