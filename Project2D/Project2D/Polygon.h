#pragma once
#include <vector>
#include "Line.h"
#include <iostream>

class Polygon
{
	vector<Line> v;
	Vec3f color;
	int xmax, xmin, ymax, ymin;
public:
	Polygon(void);
	Polygon(Vec3f color);
	~Polygon(void);

	void fillColor();
	void addEdge(Vec2f &start, Vec2f &end);
	void addEdge(Line &line);
	void Draw(const int &x, const int &y);
	double Perimeter();
	void Draw();
	int xMax();
	int xMin();
	int yMax();
	int yMin();
	vector<Line> getLines();
	bool isInside(const int &x, const int &y);
	void updateLimits();
	Vec3f getColor();
};

