#include "stdafx.h"
#include "QueryBD.h"
#include <codecvt>


QueryBD::QueryBD()                                  //constructor default
{
}


MYSQL_RES* QueryBD::InsertToTable(const std::wstring & command)    //method for insert table
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	std::string str = myconv.to_bytes(command);
	if (mysql_query(MyBD::GetInstance().Get(), str.c_str()))
	{
		throw my_ex_duplicat();
	}
	if (this->res = mysql_store_result(MyBD::GetInstance().Get()))
	{
		return this->res;
	}
	else
		return nullptr;
}


QueryBD::~QueryBD()                                 //destructor
{
	mysql_free_result(this->res);
}

QueryBD::QueryBD(QueryBD && obj)                   //constructor move
{
	this->res = obj.res;
	mysql_free_result(obj.res);
}

void QueryBD::Reset()                              //method for reset
{
	mysql_free_result(this->res);
}


