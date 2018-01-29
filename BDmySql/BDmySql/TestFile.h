#pragma once
#include <io.h>
class TestFile    //class open file
{
public: 
	TestFile();                                          //constructor
	~TestFile();                                         //destructor
	static bool FileExist(const std::wstring &);          //method for test file
};

