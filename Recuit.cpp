#include "Recuit.h"

#define T_INIT 6666666
#define T_STEP 0.9
#define T_STOP 0.00000001


using namespace cimg_library;

bool find(std::vector<int> vect, int f)
{
    for (unsigned int i = 0; i < vect.size(); i++)
        if (vect.at(i) == f)
            return true;
    return false;
}

Recuit::Recuit(int n, int m)
{
	this->n = n;
	this->m = m;
    this->nbPieces = this->n*this->m;
	int nbPoint2 = 4;
	int nbPoint3 = 2*(this->n - 2) + 2*(this->m - 2);
	int nbPoint4 = this->n*this->m - (nbPoint2 + nbPoint3);
	int nbPoint2Tot = 0;
	int nbPoint3Tot = 0;
	int nbPoint4Tot = 0;
	srand (time(NULL));
	//std::random_device rd;
	for (int i = 0; i < this->n*this->m; i++)
	{
		int y = i % this->m;
		int x = (i-y) / this->n;
		PointMeta p(x*5,y*5);
		bool cont = true;
		do
		{
			int r = rand() % 3;
			if (r == 0)
			{
				if (nbPoint2Tot < nbPoint2)
				{
					p.setNbLink(2);
					nbPoint2Tot = nbPoint2Tot + 1;
					cont = false;
				}
			}
			else if (r == 1)
			{
				if (nbPoint3Tot < nbPoint3)
				{
					p.setNbLink(3);
					cont = false;
					nbPoint3Tot = nbPoint3Tot + 1;
				}
			}
			else
			{
				if (nbPoint4Tot < nbPoint4)
				{
					p.setNbLink(4);
					cont = false;
					nbPoint4Tot = nbPoint4Tot + 1;
				}
			}
		} while(cont);
		this->mat.push_back(p);
	}
	std::cout << nbPoint2Tot << " " << nbPoint3Tot << " " << nbPoint4Tot << std::endl;
	//std::random_shuffle(this->mat.begin(), this->mat.end());
	this->initializeLink();
	this->sol = this->mat;
}

void Recuit::draw()
{
    CImg<unsigned char> visu(200,200,1,3,0);
    const unsigned char white[] = {255,255,255}, red[] = {255, 0, 0};
    CImgDisplay draw_disp(visu, "Draw prob");
    visu.fill(0);
    for (int i = 0; i < this->nbPieces; i++)
    {
        PointMeta p = this->mat.at(i);
        int x = p.getX() + 10 + 20*p.getX()/5;
        int y = p.getY() + 10 + 20*p.getY()/5;
        visu.draw_rectangle(x - 10, y-10, x+10, y+10, white);
    }
    for (int i = 0; i  < this->nbPieces; i++)
    {
        PointMeta p = this->mat.at(i);
        int x = p.getX() + 10 + 20*p.getX()/5;
        int y = p.getY() + 10 + 20*p.getY()/5;
        for (int j = 0; j < p.getLinks().size(); j++)
        {
            PointMeta p2 = this->mat.at(p.getLinks().at(j));
            int x2 = p2.getX() + 10 + 20*p2.getX()/5;
            int y2 = p2.getY() + 10 + 20*p2.getY()/5;
            visu.draw_line(x, y, x2, y2, red);
        }
    }
    visu.display(draw_disp);
    draw_disp.show();
    while (!draw_disp.is_closed())
        draw_disp.wait();
}

void Recuit::initializeLink()
{
    for (int i = 0; i < this->nbPieces; i++)
    {
        PointMeta* p = &(this->mat.at(i));
        p->getLinks().clear();
    }
    std::cout << std::endl;
    for (int i = 0; i < this->nbPieces; i++)
	{
		PointMeta* p = &(this->mat.at(i));
		int s = (p->getNbLink() - p->getLinks().size());
		int c = 0;
		for (int j = 0; j < s; j++)
		{
			int r = rand() % (this->nbPieces);
			PointMeta* p1 = &(this->mat.at(r));
			if (r != i && p1->getLinks().size() < p1->getNbLink() && !find(p->getLinks(), r) && !find(p1->getLinks(), i))
			{
				p->addLink(r);
				p1->addLink(i);
                c = 0;
			}
			else
            {
                c = c + 1;
                if (c % 100 == 0)
                {
                    std::cout << r << " " << p1->getLinks().size() << " " << p1->getNbLink() << " ";
                    if (!find(p->getLinks(), r))
                        std::cout << "false" << std::endl;
                    else
                        std::cout << "true" << std::endl;
                    Sleep(500);
                }
                if (c % 2000 == 0)
                {
                    srand (time(NULL));
                }
				j = j - 1;
            }
		}
		std::cout << "(" << i << ")" << std::endl;
	}
}

Recuit::~Recuit()
{
}

void Recuit::setMat(vector<PointMeta> ma)
{
    this->mat = ma;
}

double distance(PointMeta p1, PointMeta p2)
{
	return abs(p1.getX()-p2.getX())+abs(p1.getY()-p2.getY());
}

double Recuit::cost()
{
	int s1 = this->mat.size();
	double res = 0;
	//std::cout << "Distance" << std::endl;
	for (int i = 0; i < s1; i++)
	{
		PointMeta p = this->mat.at(i);
		int s2 = p.getLinks().size();
		for (int j = 0; j < s2; j++)
        {
            int d = distance(p, this->mat.at(p.getLinks().at(j)));
            //std::cout << d  << " : (" << p.getX() << "," << p.getY() << ") , (" << this->mat.at(p.getLinks().at(j)).getX() << "," << this->mat.at(p.getLinks().at(j)).getY() << ")" << std::endl;
			res = res + d;
			//Sleep(500);
        }
	}
	//std::cout << "Fin Distance" << std::endl;
	return res/2;
}

vector<PointMeta> Recuit::getMat()
{
    return this->mat;
}

void Recuit::swap(int i, int j)
{
	int tempX = mat.at(i).getX();
	int tempY = mat.at(i).getY();
	mat.at(i).setX(mat.at(j).getX());
	mat.at(i).setY(mat.at(j).getY());
	mat.at(j).setX(tempX);
	mat.at(j).setY(tempY);
}

double Recuit::getInitialTemp(double tau0)
{
    double res = 0;
    srand (time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int r1 = (rand()) % this->nbPieces;
        int r2 = 0;
        do
        {
            r2 = (rand()) % this->nbPieces ;
        }
        while (r1 == r2) ;
        double firstcost = this->cost();
        this->swap(r1, r2) ;
        double secondcost = this->cost();
        res = res + abs(firstcost-secondcost);
    }
    res = res / 100;
    double T0 = - res / log(tau0);
    std::cout << "res = " << res << " , log = " << 100 * log(tau0) << std::endl;
    return T0;
}

void Recuit::recuit(double tau0)
{
    double best_cost = 0;
    best_cost = this->cost();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    /*for (int h = 0; h < 100; h++)
    {*/
        this->initializeLink();
        double T = this->getInitialTemp(tau0);
        std::cout << "T = " << T << std::endl;
        static const unsigned int nbpieces = this->nbPieces;
        unsigned int t = 0, nbiter = 0 ;
        double cost_i, cost_j;
        int delta;
        unsigned int i, j;
        srand (time(NULL));
        bool cont = true;
        int accept = 0;
        int acceptdelta = 0;
        int palierSansAccept = 0;
        double rnd = 0;
        while (T > T_STOP && cont)
        {
            t++ ;
            nbiter++ ;
            //Compute inititial cost
            cost_i = this->cost();
            //Pick up two aleatory pieces
            i = (rand()) % nbpieces ;
            do
            {
                j = (rand()) % nbpieces ;
            }
            while (i == j) ;
            this->swap(i, j);
            //Compute new cost
            cost_j = this->cost();
            // Back up best solution
            if (cost_j < best_cost)
            {
                best_cost = cost_j;
                this->sol = this->mat;
            }
            if (cost_j == 200)
            {
                cont = false;
                std::cout << "Solution trouve, iteration : " << nbiter << std::endl;
            }
            delta = cost_j - cost_i;
            if (delta < 0)
                accept++; //Accept the swap
            else if (delta > 0)
            {
                double x = distribution(generator);
                double e = exp(-(delta / T));
                rnd = rnd + e;
                if (e > x)
                    acceptdelta++; //Accept the swap
                else
                    this->swap(j,i); //Refuse the swap, so we reput the last conﬁguration
            }
            //Decrease temperature
            if (t == 100*nbpieces || (accept+acceptdelta) == 12*nbpieces)
            {
                std::cout << "T : " << T << " , t : " << t << " , nbiter : " << nbiter << " , accept : " << accept << " , acceptdelta : " << acceptdelta << " , moyrnd : " << rnd/(t-accept) << " , best_cost : " << best_cost << std::endl;
                if (accept+acceptdelta == 0)
                    palierSansAccept++;
                else
                    palierSansAccept = 0;
                T *= T_STEP ;
                t = 0 ;
                accept = 0;
                acceptdelta = 0;
                rnd = 0;
                if (palierSansAccept == 3)
                    cont = false;
            }
        }
        if (cont)
            std::cout << best_cost << " true" << std::endl;
        else
            std::cout << best_cost << "false" << std::endl;
        this->draw();
    //}
}
