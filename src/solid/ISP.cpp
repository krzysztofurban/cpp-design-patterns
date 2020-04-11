//
// Created by Urban on 11.04.2020.
//

#include "ISP.h"
#include <iostream>
#include <string>

using namespace std;

struct Document
{
	string text;
};

struct IPrinter
{
	virtual void print(Document& doc) = 0;
};

struct IScanner
{
	virtual void scan(Document& doc) = 0;
};

struct IFax
{
	virtual void fax(Document& doc) = 0;
};

struct Printer : IPrinter
{
	void print(Document& doc) override
	{
		cout << doc.text << endl;
	}
};

struct Scanner : IScanner
{
	void scan(Document& doc) override
	{
		cout << "Scanning: " << doc.text << endl;
	}
};

struct Fax : IFax
{
	void fax(Document& doc) override
	{
		cout << "Faxing: " << doc.text << endl;
	}
};

struct Machine : IScanner, IPrinter, IFax
{
	IFax& faxmachine;
	IScanner& scanner;
	IPrinter& printer;

	Machine(IFax& faxmachine, IScanner& scanner, IPrinter& printer) : faxmachine(faxmachine), scanner(scanner), printer(printer)
	{
	}

	void print(Document& doc) override
	{
		printer.print(doc);
	}
	void scan(Document& doc) override
	{
		scanner.scan(doc);
	}
	void fax(Document& doc) override
	{
		faxmachine.fax(doc);
	}
};

