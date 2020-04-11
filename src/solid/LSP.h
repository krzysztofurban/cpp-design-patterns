//
// Created by Urban on 11.04.2020.
//

#ifndef BOOSTTEST_SRC_SOLID_LSP_H_
#define BOOSTTEST_SRC_SOLID_LSP_H_
class Rectangle
{
 public:
	Rectangle(int width, int height);
	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
	int area() const;
};
void process(class Rectangle & r);
#endif //BOOSTTEST_SRC_SOLID_LSP_H_
