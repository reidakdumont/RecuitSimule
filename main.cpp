#include "Recuit.h"
#include <sstream>

using namespace std;
using namespace cimg_library;

double stringToDouble( std::string str )
{
    std::istringstream iss( str ) ;
    double d ;
    iss >> d ;
    return d ;
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Use 3 arguments !" << std::endl;
        return -1;
    }
    Recuit r(atoi(argv[1]),atoi(argv[2]));
    r.draw(false);
    //r.draw();
    r.recuit(stringToDouble(argv[3]));
    return 0;
}
