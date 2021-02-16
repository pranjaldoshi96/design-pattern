/*
 * Open clonse principle: It says that you code must be
 * open and easy to extend (e.g inherit) but close to 
 * modification
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace boost;

enum class Color {red, blue, green};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Color color;
    Size size;
};

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) = 0;
};

template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
}

struct ProductFilter: Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) {
	vector<Product*> result;
	for (auto& item: items) 
	{
	    if (spec.is_satisfied(item)
		result.push_back(item)
	
	}
	return result;
    }
};

struct ColorSpecification: Specification<Product>
{
    Color color;
    ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product* item) 
    {
   	return item->color == color; 
    }
}
int main()
{
    Product table("Table", Color::green, Size::medium);
    Product chair("Chair", Color::red, Size::large);
    Product laptop("Laptop", Color::red, Size::medium);

    vector<Product> {&table, &chair, &laptop};
    return 0;
}
