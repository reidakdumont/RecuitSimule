#ifndef POINTMETA_H
#define POINTMETA_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class PointMeta
{
    public:
        PointMeta(int x, int y);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
		vector<int> getLinks();
		void addLink(int p);
		int getNbLink();
		void setNbLink(int l); 
        virtual ~PointMeta();
    protected:
    private:
        int x;
		int y;
		vector<int> links;
		int nbLink;
		
};

#endif // POINTMETA_H