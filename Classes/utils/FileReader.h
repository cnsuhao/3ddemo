#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include "CocosHead.h"

class FileReader	
{
public:
	FileReader();
	~FileReader();
	bool readFromCsv(const string& filename);
	bool readFromTxt(const string& filename);
	void moveNextRow();
	bool isEof();
	Value getValue(const string& fieldname);
	bool loadFromDelimiter(const string& filename, char delimiter);
private:
	bool readTitle(const string& content);
	bool readRow(const string& content);
	bool isComment(const string& content);
	string trim(const string& content);
	int m_RowNum;
	int	m_FieldsNum;
	int m_index;
	char m_delimiter;
	std::map<string, int> m_Title;
	std::vector<std::vector<Value>> m_Records;
};

#endif