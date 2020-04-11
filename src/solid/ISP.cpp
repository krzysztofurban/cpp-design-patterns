//
// Created by Urban on 11.04.2020.
//

#include "ISP.h"

struct Document;

struct IMachine
{
	virtual void print(Document& doc) = 0;
	virtual void scan(Document& doc) = 0;
	virtual void fax(Document& doc) = 0;
};

