#include "stdafx.h"
#include "InsertBD.h"
#include <codecvt>




InsertBD::InsertBD()                        //construcor
{

}


InsertBD::~InsertBD()                                             //destructor
{

}

void InsertBD::In_name_table(const std::wstring & name)                                 //method for add new content in name table
{
	try
	{
		std::wstring command = L"INSERT name VALUES(0,'" + name + L"')";      //concats string(comand)
		QueryBD::InsertToTable(command);                       //command for add new content name
		command.clear();
	}
	catch (const my_ex_duplicat & ex)
	{
	
	}
	this->index_id = this->Searhc_index(L"SELECT id_name FROM name WHERE name_file='" + name + L"'");
}

void InsertBD::In_drive_table(const std::wstring & drive)           //method for add content in drive
{
	try
	{
		std::wstring command = L"INSERT drive VALUES(0,'" + drive + L"')";
		QueryBD::InsertToTable(command);
		command.clear();
	}
	catch (const my_ex_duplicat & ex)
	{

	}
	this->index_drive = this->Searhc_index((L"SELECT id FROM drive WHERE name_drive='" + drive + L"'")); //call method for search index
}

void InsertBD::In_folders_table(const std::wstring & folders)           //method for add content in folders
{
	std::wstringstream ss(folders);
	std::wstring item;
	wchar_t separate = '\\';
	while (std::getline(ss, item, separate))
	{
		try
		{
			std::wstring command = L"INSERT folders VALUES(0,'" + item + L"\\\\')";
			QueryBD::InsertToTable(command);
		}
		catch (const my_ex_duplicat & ex)
		{
			
		}
		this->index_folders += (this->Searhc_index((L"SELECT id FROM folders WHERE name_folders='" + item + L"\\\\'")) + L"\\\\");
	}
}

void InsertBD::In_path_table()
{
	try
	{
		std::wstring command = L"INSERT path VALUES(" + this->index_id + L"," + this->index_drive + L",'" + this->index_folders + L"')";
		QueryBD::InsertToTable(command);
	}
	catch (const my_ex_duplicat & ex)
	{
		
	}
}

bool InsertBD::Test_in_table(const std::wstring & name)
{
	try
	{
		std::wstring command = L"SELECT id_name FROM name WHERE name_file='" + name + L"'";
		MYSQL_RES * res = QueryBD::InsertToTable(command);
		if (res->row_count == 0)
			return true;
		else
			return false;
	}
	catch (const my_ex_duplicat & ex)
	{
	}
}


void InsertBD::Add(const std::wstring & path, const std::wstring & view, const std::wstring & word)                      //main method for add new content
{
	this->Reset();
	std::wstring name = path.substr(path.find_last_of('\\') + 1);
	std::wstring drive = path.substr(0, path.find_first_of('\\') + 1);   //drive content
	std::wstring folders = path.substr(path.find_first_of('\\') + 1, (path.size() - (name.size() + drive.size()))); //folders
	this->ReplaceString(drive);
	if (this->Test_in_table(name))                                    //call method for test content
	{
		this->In_name_table(name);
		this->In_drive_table(drive);
		this->In_folders_table(folders);
		this->In_path_table();
		this->In_view_table(view);
		this->In_word_table(word);
		this->In_con_info_table();
		this->In_info_table();
	}
	else
		throw my_ex_duplicat();
}

void InsertBD::In_view_table(const std::wstring & view)                    //method for add new content to view table
{
	try
	{
		std::wstring command = L"INSERT view VALUES(0,'" + view + L"')";
		QueryBD::InsertToTable(command);
	}
	catch (const my_ex_duplicat & ex)                                     //if insert duplicate
	{
	}
	this->index_view = this->Searhc_index((L"SELECT id FROM view WHERE view_file='" + view + L"'"));    //call method for search index view
}

void InsertBD::In_word_table(const std::wstring & word)
{
	try
	{
		std::wstring command = L"INSERT word VALUES(0,'" + word + L"')";
		QueryBD::InsertToTable(command);
	}
	catch (const my_ex_duplicat & ex)                                     //if insert duplicate
	{
		
	}
	this->index_word = this->Searhc_index((L"SELECT id FROM word WHERE words='" + word + L"'"));    //call method for search index word
}

void InsertBD::In_con_info_table()
{
	try
	{
		std::wstring command = L"INSERT con_info VALUES(0," + this->index_view + L"," + this->index_word + L")";
		QueryBD::InsertToTable(command);
	}
	catch (const my_ex_duplicat & ex)                                     //if insert duplicate
	{
	}
	this->index_info = this->Searhc_index((L"SELECT id FROM con_info WHERE id_view=" + this->index_view +
		L" AND id_word=" + this->index_word + L";"));    //call method for search index word
}

void InsertBD::In_info_table()
{
	try
	{
		std::wstring command = L"INSERT info VALUES(" + this->index_id + L"," + this->index_info + L')';
		QueryBD::InsertToTable(command);
	}
	catch (const my_ex_duplicat & ex)                                     //if insert duplicate
	{
	}
}

void InsertBD::Reset()   //method for reset
{
	this->index_id.clear();
	this->index_folders.clear();
	this->index_drive.clear();
}

std::wstring InsertBD::Searhc_index(const std::wstring &command)    //method for search index 
{
	try
	{
		MYSQL_RES * res = QueryBD::InsertToTable(command);   //return for max index(last content)
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != nullptr)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string str = row[0];
			std::wstring wstr = converter.from_bytes(str);
			return wstr;
		}
		else
			throw my_ex_empty_result();                   //if empty result
	}
	catch (const my_ex_empty_result & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void InsertBD::ReplaceString(std::wstring &str)           //method for replace string
{
	for (std::wstring::size_type n = 0; (n = str.find(L"\\", n)) != std::wstring::npos; ++n)
	{
		str.replace(n, 1, 2, L'\\\\');
		++n;
	}

}
