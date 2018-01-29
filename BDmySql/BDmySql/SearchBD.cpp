#include "stdafx.h"
#include "SearchBD.h"
#include <codecvt>


SearchBD::SearchBD()        //default constructor
{
}


SearchBD::~SearchBD()       //destructor
{
}

void SearchBD::Search_id_words(const std::wstring & search)                  //method for search id con_info                                  
{
	try
	{
		std::wstring command = L"SELECT id FROM word WHERE words LIKE'%" + search + L"%';";
		this->Result_index(command, this->id_words);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	if (this->id_words.size() == 0)
		throw my_ex_not_found();
}

void SearchBD::Result_index(const std::wstring & command, std::vector<std::wstring> & vec)          //method for add result index
{
	try
	{
		MYSQL_RES * res = QueryBD::InsertToTable(command);
		while (MYSQL_ROW row = mysql_fetch_row(res))
		{
			for (auto i = 0; i < mysql_num_fields(res); i++)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				std::string str = row[0];
				std::wstring wstr = converter.from_bytes(str);
				vec.push_back(wstr);
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search(std::vector<std::wstring> & old_index, const std::wstring & command, std::vector<std::wstring> & new_index)               //method fro search index in table con_info
{
	try
	{
		std::wstring query = { 0 };
		for (auto index : old_index)
		{
			query = command + index;
			this->Result_index(query, new_index);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_id_info()                    //method for search index in table info
{
	try
	{
		this->Search(this->id_con_info, L"SELECT id FROM info WHERE id_info=", this->id_name);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_id_con_info(const std::wstring & command)                 //method for searcj index in table con_info
{
	try
	{
		this->Search(this->id_words, command, this->id_con_info);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_id_path()                  //method for search full path
{
	try
	{
		std::wstring command = { 0 };
		for (auto index : this->id_name)
		{
			command = L"SELECT id_disk,id_folders FROM path WHERE id=" + index;
			this->Result_index(command, this->id_path);
			this->Search_drive();
			this->Search_folders();
			this->Search_name(index);
			std::wcout << fullPath << std::endl;
			std::cout << "________________________________________________" << std::endl;
			this->id_path.clear();
		}

	}
	catch (const std::exception&ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_drive()                       //method for search name drive
{
	try
	{
		std::wstring command = L"SELECT name_drive FROM drive WHERE id=" + this->id_path[0];
		this->fullPath = InsertBD::Searhc_index(command);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_folders()                    //method for search name folders
{
	try
	{
		std::wstringstream ss(this->id_path[1]);
		std::wstring item;
		wchar_t separate = '\\';
		while (std::getline(ss, item, separate))
		{
			std::wstring command = L"SELECT name_folders FROM folders WHERE id=" + item;
			this->fullPath = this->fullPath + InsertBD::Searhc_index(command);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_name(const std::wstring & index)         //method for search name file in table name
{
	try
	{
		std::wstring command = L"SELECT name_file FROM name WHERE id_name=" + index;
		this->fullPath = this->fullPath + InsertBD::Searhc_index(command);
	}
	catch (const std::exception&ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_id_view(const std::wstring & view)                                   //method for search in table view
{
	try
	{
		std::wstring command = L"SELECT id FROM view WHERE view_file ='" + view + L"';";
		this->Result_index(command, this->id_words);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	if (this->id_words.size() == 0)
		throw my_ex_not_found();
}

void SearchBD::Search_id_name(const std::wstring & name)
{
	try
	{
		std::wstring command = L"SELECT id_name FROM name WHERE name_file LIKE'%" + name + L"%';";
		this->Result_index(command, this->id_name);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_on_words(const std::wstring & words)                            //main mathod for search info in table words
{
	try
	{
		this->Search_id_words(words);
		this->Search_id_con_info(L"SELECT id FROM con_info WHERE id_word=");
		this->Search_id_info();
		this->Search_id_path();
	}
	catch (const my_ex_not_found ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_on_view(const std::wstring & view)                                  //main method for search in table view
{
	try
	{
		this->Search_id_view(view);
		this->Search_id_con_info(L"SELECT id FROM con_info WHERE id_view=");
		this->Search_id_info();
		this->Search_id_path();
	}
	catch (const my_ex_not_found ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void SearchBD::Search_on_name(const std::wstring & name)                                 //main method for search name 
{
	try
	{
		this->Search_id_name(name);
		this->Search_id_path();
	}
	catch (const my_ex_not_found ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

std::vector<std::wstring> SearchBD::Result_view()                                        //method for return view
{
	try
	{
		std::vector<std::wstring> view;
		std::wstring command = L"SELECT view_file FROM view";
		this->Result_index(command, view);
		return view;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
