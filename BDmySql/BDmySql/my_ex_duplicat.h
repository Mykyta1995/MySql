#pragma once
#include <exception>
class my_ex_duplicat:public std::exception
{
public:
	my_ex_duplicat();
	~my_ex_duplicat();
	const char* what() const noexcept override        //method for return message error
	{
		return "Duplicat!";
	}
};

