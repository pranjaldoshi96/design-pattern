#include <iostream>

using namespace std;

/*
 *This demonstrate that when required to create an Interface which
 *Looks more complicated it's time to break it into smaller chunks.
 *Here I have splitted a IMachine interface which can print and scan
 *into smaller chunks of IPrinter and IScanner
 * */
struct Document;

struct IPrinter
{
	virtual void print(Document& doc) = 0;
};

struct IScanner
{
	virtual void scan(Document& doc) = 0;
};


struct IMachine : IPrinter, IScanner {};

struct Scanner : IScanner
{
	void scan(Document& doc)
	{
	
	}
};

struct Printer : IPrinter
{
	void print(Document& doc) 
	{
	
	}
};

struct Machine : IMachine
{
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

	void print(Document& doc)
	{
	
	}

	void scan(Document& doc)
	{
	
	}
};

int main()
{
	return 0;
}
