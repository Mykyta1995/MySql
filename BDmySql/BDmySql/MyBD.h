#pragma once
class MyBD         //class BD
{
	MYSQL * mysql = nullptr;
	MyBD()             //constructor
	{
		this->GetMysql();
		mysql_set_character_set(this->mysql, "utf8");
	}
public:

	MyBD(const MyBD &) = delete;  //constructor copy
	MyBD(MyBD &&) = delete;      //constructor move

	void GetMysql()                           //static method for connect ro mysql
	{
		this->mysql = mysql_init(nullptr);                 //create pointer to mysql
		if (!mysql)
		{
			std::cout << mysql_error(mysql) << std::endl;
			return;
		}
		MYSQL * conn = mysql_real_connect(mysql,            //connect to BD
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
			return;
		}
	}

	MYSQL* Get()      //method for return pointer
	{
		return this->mysql;
	}

	static MyBD & GetInstance()  //
	{
		static MyBD my_sql;
		return my_sql;
	}
	~MyBD()
	{
		mysql_close(mysql);
	}
};

