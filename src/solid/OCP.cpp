//
// Created by Urban on 11.04.2020.
//

#include <iostream>
"x86_64-w64-mingw32/bits/c++config.h"
"bits/istream.tcc"
"bits/istream.tcc"
"bits/istream.tcc"
"x86_64-w64-mingw32/bits/c++config.h"
"bits/stringfwd.h"
"bits/postypes.h"
"bits/istream.tcc"
"x86_64-w64-mingw32/bits/c++config.h"
"bits/exception.h"
"bits/exception_ptr.h"
"bits/nested_exception.h"
"bits/char_traits.h"
"bits/localefwd.h"
"bits/ios_base.h"
"bits/istream.tcc"
"x86_64-w64-mingw32/bits/c++config.h"
"bits/istream.tcc"
"bits/localefwd.h"
"bits/ios_base.h"
"bits/cpp_type_traits.h"
"ext/type_traits.h"
"bits/streambuf.tcc"
"bits/basic_ios.h"
"bits/ostream_insert.h"
"bits/ostream.tcc"
"bits/istream.tcc"
"bits/istream.tcc"
"bits/istream.tcc"
"bits/istream.tcc"
#include <string>
#include <vector>
"bits/stl_algobase.h"
"bits/allocator.h"
"bits/stl_construct.h"
"bits/stl_uninitialized.h"
"bits/stl_vector.h"
"bits/stl_bvector.h"
"bits/range_access.h"
"bits/vector.tcc"

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
	static vector<Product*> by_color(vector<Product*> items, Color color)
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
