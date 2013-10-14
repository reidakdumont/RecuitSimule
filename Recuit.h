#ifndef RECUIT_H
#define RECUIT_H

#include "PointMeta.h"
#include "CImg.h"

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Recuit
{
    public:
        Recuit();
        Recuit(int n, int m);
		void swp(int i, int j);
		double cost();
		void recuit(double tau0, double (*f1) (), void (*f2) (int,int));
		vector<PointMeta> getMat();
		void setMat(vector<PointMeta> m);
		void draw(bool fin, int cost, double temp);
        virtual ~Recuit();
    protected:
    private:
        double getInitialTemp(double tau0, double (*f1) (), void (*f2) (int, int));
        void initializeLink();
		int n;
		int m;
		vector<PointMeta> mat;
		vector<PointMeta> sol;
		int nbPieces;
		int countimg;

};

#endif // RECUIT_H
