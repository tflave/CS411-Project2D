#include "Object2D.h"


Object2D::Object2D(void)
{
}


void Object2D::Draw(const int &x, const int &y) {
	for (int i = 0; i < polygons.size(); ++i) {
		polygons[i].Draw(x, y);
	}
}

void Object2D::Draw() {
	this->Draw(0, 0);
}

void Object2D::fillColor()
{
	for(int i=0;i<polygons.size();++i)
	{
		polygons[i].fillColor();
	}
}

void Object2D::Cut(int pieces)
{	
	int p = 0;
	int startx, starty, endx, endy, boundx, boundy, index, temp;
	bool flag = true;
	vector<Vec2f> intersect;
	vector<Line> lines;
	Line l;
	l.SetColor(polygons[0].getColor());
	Vec3f color;
	while(p<pieces-1)
	{
		if(flag)
		{
			// Choose the polygon with the biggest perimeter to cut	
			index = 0;
			for(int i = 1; i<polygons.size();++i)
			{
				if(polygons[i].Perimeter() > polygons[index].Perimeter())
					index = i;
			}
			boundx = polygons[index].xMax() - polygons[index].xMin();
			boundy = polygons[index].yMax() - polygons[index].yMin();

			lines = polygons[index].getLines();
			color = polygons[index].getColor();
		}

		startx = rand() % boundx + polygons[index].xMin();
		starty = rand() % boundy + polygons[index].yMin();
		endx = rand() % boundx + polygons[index].xMin();
		endy = rand() % boundy + polygons[index].yMin();
		l.setEndPoints(Vec2f(startx, starty), Vec2f(endx, endy));


		intersect.clear();
		flag = false; 


		Polygon positive(color), negative(color);
		for(int i = 0;i<lines.size();++i)
		{
			int sideOfStart = l.checkSide(lines[i].Start());
			int sideOfEnd = l.checkSide(lines[i].End());
			if(sideOfStart < 0 && sideOfEnd < 0)
				negative.addEdge(lines[i]);
			else if(sideOfStart > 0 && sideOfEnd > 0)
				positive.addEdge(lines[i]);
			else
			{
				Vec2f interpoint = l.intersection(lines[i]);
				Line posl, negl;
				posl.SetColor(color);
				negl.SetColor(color);
				if(sideOfStart > 0)
				{
					posl.setEndPoints(lines[i].Start(), interpoint);
					negl.setEndPoints(lines[i].End(), interpoint);
				}
				else
				{
					posl.setEndPoints(lines[i].End(), interpoint);
					negl.setEndPoints(lines[i].Start(), interpoint);
				}
				intersect.push_back(interpoint);
				positive.addEdge(posl);
				negative.addEdge(negl);
			}

		}
		if(!intersect.empty())
		{
			sort(intersect.begin(), intersect.end());
			for(int i =0;i<intersect.size()-1;i+=2)
			{
				Line l(intersect[i], intersect[i+1], color);
				positive.addEdge(l);
				negative.addEdge(l);
			}
		}
		if(positive.Perimeter()>=MININUM_PERIMETER && negative.Perimeter()>=MININUM_PERIMETER)
		{
			flag = true; //We made a cut
			++p;
			polygons[index] = positive; // replace the old polygon by a new one
			polygons.push_back(negative);	// add one more polygon
		}
	}
}

Object2D::~Object2D(void)
{
}


bool Object2D::isInside(const int &x, const int &y) {
	for (int i = 0; i < polygons.size(); ++i) {
		if (polygons[i].isInside(x, y))
			return true;
	}

	return false;
}