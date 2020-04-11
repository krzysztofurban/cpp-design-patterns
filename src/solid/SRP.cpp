//
// Created by Urban on 11.04.2020.
//

#include <boost/lexical_cast.hpp>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;
using namespace boost;

struct Journal
{
	string title;
	vector<string> entries;

	Journal(string title) : title{ std::move(title) }
	{
	};

	void add_entry(const string& entry)
	{
		static int count = 1;
		entries.push_back(to_string(count++) + ": " + entry);
	}
};

struct PersistenceManager
{
	static void save(const Journal& journal, const string& filename)
	{
		ofstream ofs(filename);
		for (auto& e : journal.entries) ofs << e << endl;
	}
};

int ignoremain()
{
	Journal journal{ "Dear Diary" };
	journal.add_entry("I ate a bug");
	journal.add_entry("I cried today");
	journal.add_entry("I cried today");
	journal.add_entry("I cried today");
	journal.add_entry("I cried today");
	PersistenceManager::save(journal, "PMTest.txt");
	return 0;
}