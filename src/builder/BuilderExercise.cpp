//
// Created by Urban on 12.04.2020.
//

#include "BuilderExercise.h"

#include <string>
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

class CodeBuilder
{
 public:
	std::string class_name;
	std::vector<pair<string, string>> field_list{};

	CodeBuilder(const string& class_name) : class_name{ class_name }
	{
	}

	CodeBuilder& add_field(const string& name, const string& type)
	{
		field_list.emplace_back(make_pair(type, name));
		return *this;
	}

	friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
	{
		os << "class " << obj.class_name << endl << "{" << endl;
		for (auto& field : obj.field_list)
		{
			os << "  " <<field.first << " " << field.second << ";" << endl;
		}
		os << "};";
		return os;
	}
};

int main()
{
	auto cb = CodeBuilder{ "Person" }.add_field("name", "string").add_field("age", "int");
	std::cout << cb;
	return 0;
}