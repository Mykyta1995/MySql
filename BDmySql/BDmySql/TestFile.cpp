#include "stdafx.h"
#include "TestFile.h"


TestFile::TestFile()       //constructor
{
}


TestFile::~TestFile()      //destructor
{
}

bool TestFile::FileExist(const std::wstring & path)          //method for open file
{
	return _waccess(path.c_str(), 0)!=-1;
}
