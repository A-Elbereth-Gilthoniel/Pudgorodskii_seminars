#include "game.h"


int main(int arc, const char* argv[])
{
    int a, bots_qnty;
    istringstream(argv[1]) >> a;
    istringstream(argv[2]) >> bots_qnty;
    Model* m = new Model(WIDTH, LENGTH, bots_qnty);
    View* hei = View::get_view(a);

    cout << unitbuf;
    hei->set_model(m);
    hei->run();
    cout << nounitbuf;

    return 0;
}
