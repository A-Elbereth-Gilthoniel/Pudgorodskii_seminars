#include "game.h"

#define CELL_WIDTH (WINDOW_WIDTH/WIDTH)
#define CELL_HEIGHT (WINDOW_HEIGHT/LENGTH)

void GView::set_model(Model* m)
{
    settings = m;
}

//====================================

void GView::run()
{
    texture_red.loadFromFile("./images/red_square.png");
    texture_green.loadFromFile("./images/green_square.png");
    texture_star.loadFromFile("./images/star.png");
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake", sf::Style::Default);
    window.setFramerateLimit(FPS);
    sf::Clock clock;
    int microsec;

    while (window.isOpen())
    {
        // clock.restart();
        check_keyboard_events(window);


        // microsec = static_cast<int>(clock.restart().asMicroseconds());
        // if ((int)(1000000 / FPS - microsec) > 0)
        //     sf::sleep(sf::microseconds(1000000 / FPS - microsec));

        window.clear(sf::Color::Black);

        draw();

        window.display();
        settings->update_model();
    }
    set_old_input();
    // return;
}

//======================================================

void GView::check_keyboard_events(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::A:
                    settings->update_direction(LEFT);
                    break;
                case sf::Keyboard::W:
                    settings->update_direction(UP);
                    break;
                case sf::Keyboard::S:
                    settings->update_direction(DOWN);
                    break;
                case sf::Keyboard::D:
                    settings->update_direction(RIGHT);
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default: break;
            }
        }
    }
}


//============================================================

void GView::draw()
{
    draw_snake(settings->snake, GREEN);
    for (Snake* snake : settings->snake_bots)
        draw_snake(snake, RED);

    draw_star();
    // window.display();
}

//================================================================

void GView::draw_snake(Snake* snake, const std::string color)
{
    sf::Texture texture;
    if (color == RED)
        texture = texture_red;
    else
        texture = texture_green;
    // std::vector<sf::Sprite> bodies;
    sf::Sprite body;
    body.setTexture(texture);
    body.setScale(CELL_WIDTH/(float)texture.getSize().x, CELL_HEIGHT/(float)texture.getSize().y);

    for (std::list<coord>::iterator it = snake->place.begin(); it != snake->place.end(); ++it)
    {
        body.setPosition((*it).x * CELL_WIDTH, (*it).y * CELL_HEIGHT);
        // bodies.push_back(body);
        window.draw(body);
    }
}

//=================================================================

void GView::draw_star()
{

    sf::Sprite body;
    body.setTexture(texture_star);
    body.setScale(CELL_WIDTH/(float)texture_star.getSize().x, CELL_HEIGHT/(float)texture_star.getSize().y);

    for (int i = 0; i < settings->bots_size + 1; i++)
    {
        body.setPosition(settings->stars[i]->star_place.x * CELL_WIDTH, settings->stars[i]->star_place.y * CELL_HEIGHT);
        window.draw(body);
    }
}
