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

/*Recuit::Recuit(int n, int m)
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
}*/

Recuit::Recuit(int n, int m)
{
    this->n = n;
	this->m = m;
    this->nbPieces = this->n*this->m;
    for (int i = 0; i < this->n*this->m; i++)
	{
		int x = i % this->m;
		int y = (i-x) / this->n;
		x = x*5;
		y = y*5;
		PointMeta p(x,y);
		this->mat.push_back(p);
	}
	for (int i = 0; i < this->nbPieces; i++)
    {
        PointMeta* p = &(this->mat.at(i));
        int x = p->getX();
        int y = p->getY();
        std::cout << "(" << x << "," << y << ") " << i << std::endl;
        if (x != 0)
        {
            PointMeta* p1 = &(this->mat.at(i-1));
            p->addLink(i-1);
            p1->addLink(i);
        }
        if (y != 0)
        {
            PointMeta* p1 = &(this->mat.at(i-this->m));
            p->addLink(i-this->m);
            p1->addLink(i);
        }
    }
    initializeLink();
    this->sol = this->mat;
}

void Recuit::draw(bool fin)
{
    CImg<unsigned char> visu(400,400,1,3,255);
    const unsigned char white[] = {255,255,255}, red[] = {255, 0, 0}, black[] = {0,0,0};
    char* n;
    if (fin)
        n = "Draw final prob";
    else
        n = "Draw prob";
    CImgDisplay draw_disp(visu, const_cast<char*>(n));
    for (int i = 0; i < this->nbPieces; i++)
    {
        PointMeta p = this->mat.at(i);
        int x = p.getX() + 30 + 60*p.getX()/5;
        int y = p.getY() + 30 + 60*p.getY()/5;
        visu.draw_rectangle(x - 20, y-20, x+20, y+20, black);
    }
    for (int i = 0; i  < this->nbPieces; i++)
    {
        PointMeta p = this->mat.at(i);
        int x = p.getX() + 30 + 60*p.getX()/5;
        int y = p.getY() + 30 + 60*p.getY()/5;
        const unsigned char col1[] = {i*10, i*10, i*5};
        const unsigned char col2[] = {i*10, i*5, i*10};
        const unsigned char col3[] = {i*5, i*10, i*10};
        for (int j = 0; j < p.getLinks().size(); j++)
        {
            PointMeta p2 = this->mat.at(p.getLinks().at(j));
            /*if (fin)
                std::cout << "(" << p.getX() << "," << p.getY() << "," << p.getNbLink() << ") , (" << p2.getX() << "," << p2.getY() << "," << p2.getNbLink() << ")" << std::endl;*/
            int x2 = p2.getX() + 30 + 60*p2.getX()/5;
            int y2 = p2.getY() + 30 + 60*p2.getY()/5;
            int rd = rand() % 3;
            if (rd == 0)
                visu.draw_line(x, y, x2, y2, col1);
            else if (rd == 1)
                visu.draw_line(x, y, x2, y2, col2);
            else
                visu.draw_line(x, y, x2, y2, col3);
        }
    }
    visu.display(draw_disp);
    draw_disp.show();
    if (!fin)
        Sleep(3000);
    else
        while(!draw_disp.is_closed())
            draw_disp.wait();
}

void Recuit::initializeLink()
{
    std::uniform_int_distribution<int> distrib(0,this->nbPieces-1);
    std::default_random_engine generator;
    for (int i = 0; i < 100; i++)
    {
        int r1 = distrib(generator);
        int r2 = 0;
        do
        {
            r2 = distrib(generator);
        }
        while (r1 == r2) ;
        this->swp(r1,r2);
    }
}

/*void Recuit::initializeLink()
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
			    if ((p->getNbLink() == 2 && p1->getNbLink() == 4) || (p1->getNbLink() == 2 && p->getNbLink() == 4))
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
                        initializeLink();
                        return;
                    }
                    j = j - 1;
                }
                else
                {
                    p->addLink(r);
                    p1->addLink(i);
                    c = 0;
                }
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
                    initializeLink();
                    return;
                }
				j = j - 1;
            }
		}
		std::cout << "(" << i << ") " << p->getLinks().size() << " " << p->getNbLink() << std::endl;
	}
}*/

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
            int pos = p.getLinks().at(j);
            int d = distance(p, this->mat.at(pos));
            res = res + d;
        }
	}
	return res/2;
}

vector<PointMeta> Recuit::getMat()
{
    return this->mat;
}

void Recuit::swp(int i, int j)
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
    std::uniform_int_distribution<int> distrib(0,this->nbPieces-1);
    std::default_random_engine generator;
    for (int i = 0; i < 100; i++)
    {
        int r1 = distrib(generator);
        int r2 = 0;
        do
        {
            r2 = distrib(generator);
        }
        while (r1 == r2) ;
        double firstcost = this->cost();
        this->swp(r1, r2) ;
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
    this->sol = this->mat;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    std::uniform_int_distribution<int> distrib(0,this->nbPieces-1);
    for (int h = 0; h < 10; h++)
    {
        this->initializeLink();
        double T0 = this->getInitialTemp(tau0);
        double T = T0;
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
            while (t != 100*nbpieces && (accept+acceptdelta) != 12*nbpieces && cont)
            {
                t++ ;
                nbiter++ ;
                //Compute inititial cost
                cost_i = this->cost();
                //Pick up two aleatory pieces
                i = distrib(generator);
                do
                {
                    j = distrib(generator);
                }
                while (i == j) ;
                this->swp(i, j);
                //Compute new cost
                cost_j = this->cost();
                // Back up best solution
                delta = cost_j - cost_i;
                if (delta < 0)
                {
                    if (cost_j < best_cost)
                    {
                        best_cost = cost_j;
                        this->sol = this->mat;
                    }
                    if (best_cost == 200)
                    {
                        cont = false;
                        std::cout << "Solution trouve, iteration : " << nbiter << std::endl;
                    }
                    std::cout << "accept" << std::endl;
                    accept++; //Accept the swap
                    std::cout << delta << " " << cost_j << " " << cost_i << " " << best_cost << " T = " << T << std::endl;
                }
                else if (delta > 0)
                {
                    double p = distribution(generator);
                    double e = exp(-delta / T);
                    rnd = rnd + e;
                    if (p < e)
                    {
                        std::cout << "accept" << std::endl;
                        acceptdelta++; //Accept the swap
                        std::cout << delta << " " << cost_j << " " << cost_i << " " << best_cost << " T = " << T << std::endl;
                    }
                    else
                        this->swp(i,j); //Refuse the swap, so we reput the last conﬁguration
                }
            }
            std::cout << "T : " << T << " , t : " << t << " , nbiter : " << nbiter << " , accept : " << accept << " , acceptdelta : " << acceptdelta << " , moyrnd : " << rnd/(t-accept) << " , best_cost : " << best_cost << std::endl;
            this->draw(false);
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
        if (cont)
            std::cout << best_cost << " true" << std::endl;
        else
            std::cout << best_cost << " false" << std::endl;
    }
    this->mat = this->sol;
    this->draw(true);
}
