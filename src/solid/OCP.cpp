//
// Created by Urban on 11.04.2020.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color
{
	red, green, blue
};

enum class Size
{
	small, medium, large
};

struct Product
{
	string name;
	Color color;
	Size size;
};

struct ProductFilter
{
	static vector<Product*> by_color(const vector<Product*>& items, Color color)
	{
		vector < Product * > result;
		for (auto& i : items)
		{
			if (i->color == color) result.push_back(i);
		}
		return result;
	}
};

template<typename T>
struct Specification
{
	virtual bool is_satisfied(T* item) = 0;
};

template<typename T>
struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override
	{
		vector < Product * > result;
		for (auto& item : items)
			if (spec.is_satisfied(item))
				result.push_back(item);
		return result;
	}
};

struct ColorSpecification : Specification<Product>
{
	Color color;
	explicit ColorSpecification(Color color) : color(color)
	{
	}

	bool is_satisfied(Product* item) override
	{
		return item->color == this->color;
	}
};

struct SizeSpecification : Specification<Product>
{
	Size size;
	explicit SizeSpecification(Size size) : size{ size }
	{
	}

	bool is_satisfied(Product* item) override
	{
		return item->size == this->size;
	}
};

template<typename T>
struct AndSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;

	AndSpecification(Specification<T>& first, Specification<T>& second) : first{ first }, second{ second }
	{
	};

	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

int _main()
{
	Product apple{ "Apple", Color::green, Size::small };
	Product tree{ "Tree", Color::green, Size::medium };
	Product house{ "House", Color::blue, Size::medium };
	vector < Product * > product_vector{ &apple, &tree, &house };
	BetterFilter bf;
	ColorSpecification green{ Color::green };
	SizeSpecification mid{ Size::medium };
	AndSpecification<Product> green_and_medium(green, mid);

	auto items = bf.filter(product_vector, green_and_medium);
	for (auto& item : items)
	{
		cout << item->name << endl;
	}
	return 0;
}
