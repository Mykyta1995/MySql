#pragma once
#include <exception>
class my_ex_empty_result :public std::exception          //class exeption
{
public:
	my_ex_empty_result();                    //contructor default
	~my_ex_empty_result();                   //destructor
	const char* what() const noexcept override        //method for return message error
	{
		return "Empty result!";
	}
};

