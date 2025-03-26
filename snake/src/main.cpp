#include "game.h"


int main(int arc, const char* argv[])
{
    int a;
    istringstream(argv[1]) >> a;
    Model* m = new Model(WIDTH, LENGTH);
    View* hei = View::get_view(a);

    cout << unitbuf;
    hei->set_model(m);
    hei->run();
    cout << nounitbuf;

    return 0;
}
