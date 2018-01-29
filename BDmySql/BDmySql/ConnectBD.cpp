#include "stdafx.h"
#include "ConnectBD.h"

MYSQL * ConnectBD::GetMysql()                           //static method for connect ro mysql
{
	MYSQL *mysql = mysql_init(nullptr);                 //create pointer to mysql
	if (!mysql)
	{
		std::cout << mysql_error(mysql) << std::endl;
		return nullptr;
	}
	MYSQL *conn = mysql_real_connect(mysql,            //connect to BD
		"localhost",
		"root",
		"1111",
		"content",
		3306,
		0,
		0);
	if (!conn)                                         //test for connect to BD or not
	{
		std::cout << mysql_error(mysql) << std::endl;
		return nullptr;
	}
	return mysql;
}
