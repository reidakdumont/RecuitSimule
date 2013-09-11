#include "Recuit.h"

using namespace std;

int main()
{
    Recuit r(5,5);
    std::cout << r.cost() << std::endl;
    std::cout << "(" << r.getMat().at(10).getX() << "," << r.getMat().at(10).getY() << ")" << std::endl;
    std::cout << "(" << r.getMat().at(4).getX() << "," << r.getMat().at(4).getY() << ")" << std::endl;
    r.swap(10, 4);
    std::cout << "(" << r.getMat().at(10).getX() << "," << r.getMat().at(10).getY() << ")" << std::endl;
    std::cout << "(" << r.getMat().at(4).getX() << "," << r.getMat().at(4).getY() << ")" << std::endl;
    r.swap(10, 4);
    std::cout << "(" << r.getMat().at(10).getX() << "," << r.getMat().at(10).getY() << ")" << std::endl;
    std::cout << "(" << r.getMat().at(4).getX() << "," << r.getMat().at(4).getY() << ")" << std::endl;
    std::cout << r.cost() << std::endl;
    r.recuit(100);
    cout << "Hello world!" << endl;
    return 0;
}
