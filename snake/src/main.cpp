#include "game.h"


int main(int arc, const char* argv[])
{
    int a, bots_qnty;
    std::istringstream(argv[1]) >> a;
    std::istringstream(argv[2]) >> bots_qnty;
    Model* m = new Model(WIDTH, LENGTH, bots_qnty);
    View* hei = View::get_view(a);

    std::cout << std::unitbuf;
    hei->set_model(m);
    hei->run();
    std::cout << std::nounitbuf;

    return 0;
}
