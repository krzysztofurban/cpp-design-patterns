//
// Created by Urban on 11.04.2020.
//

#include "DI.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class Relationship
{
	parent, child, sibling
};

struct Person
{
	string name;
};

struct RelationshipBrowser
{
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser// low-level module
{
	vector<tuple<Person, Relationship, Person>> relations;

	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.emplace_back(parent, Relationship::parent, child);
		relations.emplace_back(child, Relationship::child, parent);
		cout << "Added relation - Parent: " << parent.name << " Child: " << child.name << endl;
	}

	vector<Person> find_all_children_of(const string& name) override
	{
		vector<Person> result;
		for (auto&&[first, rel, second] : relations)
		{
			if (rel == Relationship::parent && first.name == name)
			{
				result.push_back(second);
			}
		}
		return result;
	}
};

//Low level module should not depend on high level modules
//Research should not depend on Relationship
struct Research
{ // high-level
	RelationshipBrowser& browser;

	Research(RelationshipBrowser& browser) : browser{ browser }
	{
		const string PARENT_NAME = "John";
		const vector<Person>& vector = browser.find_all_children_of(PARENT_NAME);
		for (auto& item : vector)
		{
			cout << "Children of " << PARENT_NAME << " is " << item.name << endl;
		}
	}
};

int main_di()
{
	Person parent{ "John" };
	Person child1{ "Child1" }, child2{ "Child2" };
	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);
	Research research{relationships};
	return 0;
}