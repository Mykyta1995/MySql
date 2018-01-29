#pragma once
class my_ex_not_found:public std::exception   //class my exeption not found content
{
public:
	my_ex_not_found();
	~my_ex_not_found();
	const char* what() const noexcept override       //method for return message error
	{
		return "Information not found";
	}
};

