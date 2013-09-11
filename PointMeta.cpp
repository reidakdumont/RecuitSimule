#include "PointMeta.h"

PointMeta::PointMeta(int x, int y)
{
	this->x = x;
	this->y = y;
	this->nbLink = 0;
}

int PointMeta::getX()
{
	return this->x;
}

int PointMeta::getY()
{
	return this->y;
}

void PointMeta::setX(int x)
{
	this->x = x;
}

void PointMeta::setY(int y)
{
	this->y = y;
}

vector<int> PointMeta::getLinks()
{
	return this->links;
}

void PointMeta::addLink(int p)
{
	this->links.push_back(p);
}

int PointMeta::getNbLink()
{
	return this->nbLink;
}

void PointMeta::setNbLink(int l)
{
	this->nbLink = l;
}

PointMeta::~PointMeta()
{
}
