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
    void draw_snake();
    void draw_star();
    void clrscr();
    Model* settings;
};
