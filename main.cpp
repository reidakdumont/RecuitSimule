#include "Recuit.h"

using namespace std;
using namespace cimg_library;

Recuit r;

double stringToDouble( std::string str )
{
    std::istringstream iss( str ) ;
    double d ;
    iss >> d ;
    return d ;
}

void swp1(int i, int j)
{
    r.swp(i,j);
}

double cost1()
{
    return r.cost();
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Use 3 arguments !" << std::endl;
        return -1;
    }
    Recuit r1(atoi(argv[1]),atoi(argv[2]));
    r = r1;
    r.draw(false, r.cost(), 0);
    //r.draw();
    double ((*f1) ());
    void ((*f2) (int, int));
    f1 = cost1;
    f2 = swp1;
    r.recuit(stringToDouble(argv[3]), f1, f2);
    return 0;
}
