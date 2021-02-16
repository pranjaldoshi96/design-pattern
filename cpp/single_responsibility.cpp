#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal
{
    /*
     *Class to store journal
     */
    string title;
    vector<string> entries;
    
    Journal(const string &title) : title(title) {}

    void add_entry(const string& entry)
    {
       static int count = 1;
       entries.push_back(lexical_cast<string>(count++)	+ ": " + entry);
    }
};


struct PersistenceManager 
{
    /*
     * Persist any object
     */
    void save(Journal& j, const string& filename) 
    {
    	ofstream ofs(filename);
	for (auto& e: j.entries)
	    ofs << e << endl;
    }
};


int main() {
    Journal journal{"Dear diary"};
    journal.add_entry("I woke up at 7");
    journal.add_entry("I didn nothing");
    PersistenceManager pm;
    pm.save(journal, "diary.txt");
}
