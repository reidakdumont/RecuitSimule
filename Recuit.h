#ifndef RECUIT_H
#define RECUIT_H

#include "PointMeta.h"

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <windows.h>

using namespace std;

class Recuit
{
    public:
        Recuit(int n, int m);
		void swap(int i, int j);
		double cost();
		void recuit(double tau0);
		vector<PointMeta> getMat();
        virtual ~Recuit();
    protected:
    private:
        double getInitialTemp(double tau0);
		int n;
		int m;
		vector<PointMeta> mat;
		int nbPieces;

};

#endif // RECUIT_H
