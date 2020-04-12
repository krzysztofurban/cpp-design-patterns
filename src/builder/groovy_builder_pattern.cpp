//
// Created by Urban on 12.04.2020.
//

#include "groovy_builder_pattern.h"

#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

struct Tag
{
	string name, text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;

	friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
	{
		os << "<" << tag.name;

		for (const auto& att : tag.attributes)
			os << " " << att.first << "=\"" << att.second << "\"";

		if (tag.children.empty() && tag.text.length() == 0)
			os << "/>" << endl;
		else
		{
			os << ">" << std::endl;

			if (tag.text.length())
				os << tag.text << endl;

			for (const auto& child :tag.children)
				os << child;

			os << "</" << tag.name << ">" << endl;
		}
		return os;
	}

 protected:
 public:
	Tag(string name, string text) : name(std::move(name)), text(std::move(text))
	{
	}
	Tag(string name, vector<Tag> children) : name{ std::move(name) }, children{ std::move(children) }
	{
	};

};

struct P : Tag
{
	P(const string& text) : Tag("p", text)
	{
	}
	P(initializer_list<Tag> children) : Tag{ "p", children }
	{
	}
};

struct IMG : Tag
{
	explicit IMG(const string& url) : Tag{ "img", "" }
	{
		attributes.emplace_back(make_pair("src", url));
	}
};

int main()
{
	cout << P{ IMG{ "http://some.pl/some/some" }} << endl ;
	return 0;
}