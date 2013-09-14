#include "Recuit.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char** argv)
{
    Recuit r(5,5);
    //r.draw();
    r.recuit(0.999);
    cout << "Hello world!" << endl;
    return 0;
}
