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

enum class Color {red, blue, green};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Color color;
    Size size;

    Product(string name, Color color, Size size): name(name), color(color), size(size) {}
};

// Interface to define specification
template <typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) = 0;
};

// Interface to create filter
template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

template <typename T>
struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T> &first, Specification<T> &second): first(first), second(second) {}

    bool is_satisfied(T* item)
    {
	return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template <typename T> 
AndSpecification<T> operator&& (Specification<T>& first, Specification<T>& second)
{
  return { first, second };
}

struct ProductFilter: Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) 
    {
	vector<Product*> result;
	for (auto& item: items) 
	{
	    if (spec.is_satisfied(item))
		result.push_back(item);
	
	}
	return result;
    }
};

struct SizeSpecification: Specification<Product>
{
    Size size;
    SizeSpecification(Size size) : size(size) {}

    bool is_satisfied(Product* item) override
    {
   	return item->size == size; 
    }
};
struct ColorSpecification: Specification<Product>
{
    Color color;
    ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product* item) override
    {
   	return item->color == color; 
    }
};

int main()
{
    Product table("Table", Color::green, Size::medium);
    Product chair("Chair", Color::red, Size::large);
    Product laptop("Laptop", Color::red, Size::medium);

    vector<Product*>product {&table, &chair, &laptop};
    ColorSpecification colorRed = ColorSpecification(Color::red);
    SizeSpecification sizeMedium = SizeSpecification(Size::medium);
    ProductFilter pf;
    auto res = pf.filter(product, colorRed);
    cout << "COLOR RED\n";
    for (auto r : res)
    {
	cout<< r->name << endl;;
    }
    cout << "SIZE medium\n";
    for (auto r : pf.filter(product, sizeMedium))
    {
    	cout << r->name << endl;
    }
    AndSpecification<Product> rm(colorRed, sizeMedium);


    cout << "SIZE medium color Red\n";
    for (auto r : pf.filter(product, rm))
    {
    	cout << r->name << endl;
    }
    cout << "SIZE medium color Red\n";
    auto spec = colorRed && sizeMedium;
    for (auto& x : pf.filter(product, spec))
        cout << x->name << endl;
    return 0;
}
