#pragma once
#include <WinSock2.h>
#include "my_ex_duplicat.h"

class QueryBD          //base class for insert information in table
{
	MYSQL_RES * res = nullptr;
protected:
	MYSQL_RES * InsertToTable(const std::wstring &);     //method for insert table
public:
	QueryBD();         //constructor default
	~QueryBD();        //destructor
	QueryBD(const QueryBD &)=delete;     //constructor copy
	QueryBD(QueryBD &&);                 //constructor move
	void Reset();
};

