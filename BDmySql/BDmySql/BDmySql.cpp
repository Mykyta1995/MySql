// BDmySql.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "QueryBD.h"
#include "InsertBD.h"
#include <algorithm>
#include "TestFile.h"
#include "SearchBD.h"
#include<windows.h>


void Add();
void Menu();
void Show(const std::wstring &);
void Search();

int main()
{
	_wsetlocale(LC_ALL, L".866");
	Menu();
	return 0;
}

void Add()       //method for add new item in BD
{
	try
	{
		std::cout << "________________________________________________" << std::endl;
		std::cout << "Enter path:";
		std::wstring path;
		std::getline(std::wcin, path);
		std::wcout << path << std::endl;
		if (TestFile::FileExist(path))
		{
			InsertBD BD;
			std::cout << "Enter view content.For example:book,video...." << std::endl;
			std::cout << "You choise:";
			std::wstring view;
			std::getline(std::wcin, view);
			std::cout << "Enter infomation content.For example:C++,my training...." << std::endl;
			std::cout << "You choise:";
			std::wstring words;
			std::getline(std::wcin, words);
			BD.Add(path, view, words);
		}
		else
		{
			std::cout << "Wrong way" << std::endl;
		}
	}
	catch (const my_ex_duplicat & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void Menu()                                              //method for main menu
{
	int number = 0;
	do
	{
		if (MyBD::GetInstance().Get()->db == nullptr)
		{
			std::wcout << "Not connect to BD" << std::endl;
			return;
		}
		std::cout << "1)Add new item" << std::endl;
		std::cout << "2)Search content" << std::endl;
		std::cout << "3)Exit" << std::endl;
		std::cout << "Your choise:";
		std::string choise;
		std::getline(std::cin, choise);
		number = atoi(choise.c_str());
		if (number == 1)
			Add();
		else if (number == 2)
			Search();
	} while (number != 3);
}

void Show(std::vector<std::wstring> vec)
{
	std::cout << "________________________________________________" << std::endl;
	for (auto view : vec)
		std::wcout << view << std::endl;
	std::cout << "________________________________________________" << std::endl;
}

void Search()                                                       //method for show search path file
{
	SearchBD search;
	std::cout << "________________________________________________" << std::endl;
	std::cout << "1)View all files" << std::endl;
	std::cout << "2)View files through information" << std::endl;
	std::cout << "3)View files through view file" << std::endl;
	std::cout << "4)View files through name file" << std::endl;
	std::cout << "5)Exit" << std::endl;
	std::cout << "Your choise:";
	std::string choise;
	std::getline(std::cin, choise);
	int number = 0;
	number = atoi(choise.c_str());
	if (number == 1)
	{
		std::cout << "________________________________________________" << std::endl;
		search.Search_on_words(L"");
	}
	else if (number == 2)
	{
		std::cout << "________________________________________________" << std::endl;
		std::cout << "Enter information file:";
		std::wstring path;
		std::getline(std::wcin, path);
		std::wcout << "Search results:" << """" << path << """" << std::endl;
		std::cout << "________________________________________________" << std::endl;
		search.Search_on_words(path);
	}
	else if (number == 3)
	{
		std::cout << "View BD:" << std::endl;
		Show(search.Result_view());
		std::cout << "Enter information file.For example:document ...." << std::endl;
		std::cout << "Your choise:";
		std::wstring path;
		std::getline(std::wcin, path);
		std::cout << "________________________________________________" << std::endl;
		search.Search_on_view(path);
	}
	else if (number == 4)
	{
		std::cout << "Enter name file:";
		std::wstring path;
		std::getline(std::wcin, path);
		std::cout << "________________________________________________" << std::endl;
		search.Search_on_name(path);
	}
}

