class View {
public:
    View() {}

    virtual void draw() = 0;
    virtual void set_model(Model* m) = 0;
    virtual void run() = 0;
    virtual ~View() {}

    static View* get_view(int a);

};

//=============================================

class TView : public View {
public:
    void draw();
    void set_model(Model* m);
    void run();

private:
    void galaxy(int width, int length);
    void draw_snake(Snake* snake, const std::string color);
    void draw_star();
    void clrscr(std::vector<coord> clear_coords);
    Model* settings;
};

//============================================

class GView : public View {
public:
    void draw();
    void set_model(Model* m);
    void run();


private:
    sf::Texture texture_red, texture_green, texture_star;
    sf::RenderWindow window;
    Model* settings;
    void check_keyboard_events(sf::RenderWindow &window);
    void draw_snake(Snake* snake, const std::string color);
    void draw_star();
};
