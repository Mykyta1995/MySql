#pragma once
#include "QueryBD.h"
#include "my_ex_empty_result.h"

class InsertBD :QueryBD                          //class for insert to BD
{
	std::wstring index_id = { 0 };       //field for max id_name in table main_table
	std::wstring index_drive = { 0 };    //filed for index drive
	std::wstring index_folders = { 0 };  //filed for index folders
	std::wstring index_view = { 0 };     //field for index view
	std::wstring index_word = { 0 };     //field for index word
	std::wstring index_info = { 0 };     //filed for index info

	void ReplaceString(std::wstring &);                    //method for replace string
	void Reset();                                         //method for reset content
	void In_name_table(const std::wstring &);              //method for add new content to name table
	void In_drive_table(const std::wstring &);             //method for add new content to drive table
	void In_folders_table(const std::wstring &);           //method for add new content to folders table
	void In_path_table();                                 //method for add new content to path table
	bool Test_in_table(const std::wstring &);              //method for test a new content to table name
	void In_view_table(const std::wstring &);              //method for add new content to view table
	void In_word_table(const std::wstring &);              //method for add new content to word table
	void In_con_info_table();                             //method for add new content to con_info table
	void In_info_table();                                 //method for add new content to info table
protected:
	std::wstring Searhc_index(const std::wstring &);          //method for search index driver in table drive
public:
	InsertBD();                                           //constructor
	~InsertBD();                                          //destructor
	void Add(const std::wstring &, const std::wstring &, const std::wstring &);                        //main method for add new content
};

