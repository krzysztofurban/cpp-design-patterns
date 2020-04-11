//
// Created by Urban on 11.04.2020.
//

#include <string>
#include <iostream>

using namespace std;
class Rectangle
{
 protected:
	int width, height;
 public:
	Rectangle(int width, int height) : width(width), height(height)
	{
	}

	int GetWidth() const
	{
		return width;
	}
	virtual void SetWidth(int width)
	{
		Rectangle::width = width;
	}
	int GetHeight() const
	{
		return height;
	}
	virtual void SetHeight(int height)
	{
		Rectangle::height = height;
	}

	int area() const
	{
		return width * height;
	}

	~Rectangle()
	{
		cout << "Destroying rectangle" << endl;
	}
};

void process(Rectangle& r)
{
	int w = r.GetWidth();
	r.SetHeight(10);

	cout << "expected area = " << (w * 10) << ", got " << r.area() << endl;
}

int ignoremain()
{
	Rectangle rectangle(3, 4);
	process(rectangle);

	return 0;
}