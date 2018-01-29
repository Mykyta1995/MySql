#pragma once
#include "QueryBD.h"
#include "InsertBD.h"
#include "my_ex_not_found.h"

class SearchBD :public QueryBD, public InsertBD
{
	std::vector<std::wstring> id_words;             //field for id_words
	std::vector<std::wstring> id_con_info;          //field for id table con_info
	std::vector<std::wstring> id_name;              //field for id_name in table info
	std::vector<std::wstring> id_path;              //field for id_path in table path
	std::vector<std::wstring> id_view;              //filed for id_view int table view
	std::wstring fullPath;                          //filed for fullpath;
	void Search_id_words(const std::wstring &);     //method for search index in table word
	void Result_index(const std::wstring &, std::vector<std::wstring> &);                           //method for write index
	void Search(std::vector<std::wstring> &, const std::wstring &, std::vector<std::wstring> &);                     //method for search index in table con_info
	void Search_id_info();                          //method for search index in table info
	void Search_id_con_info(const std::wstring &);                     //method for search index in table con_info
	void Search_id_path();                          //method for search index in table path
	void Search_drive();                            //method for search name drive in table drive
	void Search_folders();                          //method for search folders in table folders
	void Search_name(const std::wstring &);         //method for search name file in table name
	void Search_id_view(const std::wstring &);      //method for search index view in table con_info
	void Search_id_name(const std::wstring &);      //method for search index id in table name
public:
	SearchBD();                                    //constructor
	~SearchBD();                                   //destructor
	void Search_on_words(const std::wstring &);    //method for search on word
	void Search_on_view(const std::wstring &);     //method for search on view
	void Search_on_name(const std::wstring &);     //method for search on name
	std::vector<std::wstring> Result_view();       //method for return view
};

