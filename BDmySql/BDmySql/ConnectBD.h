#pragma once
#include <WinSock2.h>
#include <iostream>
#include <mysql.h>

class ConnectBD                      //class for connect to myslq
{
public:
	ConnectBD()=default;            //default constructor
	static MYSQL * GetMysql();      //static method for connect ro mysql
	~ConnectBD() = default;         //default desctructor
};

