/*
 *Dependency inversion states that
 *1. High level module should not depend on low level module. They both
 *   should depend on an abstraction
 *2. Abstraction should not depend on details. Details should be on 
 *   asbstraction
 * */
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

enum class Relationship {
    parent,
    child,
    sibling
};

struct Person {
    string name;
};

struct RelationshipBrowser {
    virtual vector<Person> find_child(const string& name) = 0;
};

struct Relations : RelationshipBrowser {
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_relation(Person parent, Person child) {
	relations.push_back({parent, Relationship::parent, child});
	relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_child(const string& name) override {
	vector<Person> result;
	for (auto&& [first, rel, second] : relations) {
	    if (first.name == name && rel == Relationship::parent) {
		result.push_back(second);
	    }
	}
	return result;
    }
};

struct Research {
    Research(RelationshipBrowser& browser) {
	for (auto& child : browser.find_child("Mr. A")) {
	    cout << " " << child.name << endl;
	}
    }
};

int main() {
    Person parent{"Mr. A"}, child1{"Child A1"}, child2{"Child A2"};
    Relations relationships;
    relationships.add_parent_relation(parent, child1);
    relationships.add_parent_relation(parent, child2);

    Research _(relationships);
    return 0;
}
