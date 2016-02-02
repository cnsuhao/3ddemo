#include "FileReader.h"
#include "Utils.h"

FileReader::FileReader():
m_RowNum(0),
m_FieldsNum(0),
m_index(0)
{

}

FileReader::~FileReader()
{

}

bool FileReader::loadFromDelimiter(const string& filename, char delimiter)
{
	m_delimiter = delimiter;
	string data = trim(FileUtils::getInstance()->getStringFromFile(filename));
	stringstream stm;
	if (isUTF_BOM(data) == true)
	{
		stm << &data[3];
	}
	else
	{
		stm << data;
	}
	stm.seekg(0);
	char buff[1024 * 10];
	bool hasTitle = false;
	while (stm.getline(buff, sizeof(buff)))
	{
		if (isComment(buff) == true)
		{
			continue;
		}
		if (hasTitle == false)
		{
			readTitle(buff);
			hasTitle = true;
		} 
		else
		{
			readRow(buff);
		}
	}
	return true;
}

bool FileReader::readFromCsv(const string& filename)
{
	return loadFromDelimiter(filename,',');
}

bool FileReader::readFromTxt(const string& filename)
{
	return loadFromDelimiter(filename, '\t');
}

bool FileReader::isComment(const string& content)
{
	if (content.size() >= 2 && content.substr(0,2) == "//")
	{
		return true;
	}
	return false;
}

bool FileReader::readTitle(const string& content)
{
	vector<string> title = string_spilt(content, m_delimiter);
	for (int i = 0; i < title.size(); ++i)
	{
		m_Title.insert(make_pair(title[i],i));
	}
	m_FieldsNum = title.size();
	return true;
}

bool FileReader::readRow(const string& content)
{
	vector<Value> rowdata;
	vector<string> rowstr = string_spilt(content, m_delimiter);
	for (int i = 0; i < rowstr.size() && i < m_FieldsNum; ++i)
	{
		rowdata.push_back(Value(rowstr[i]));
	}
	m_Records.push_back(rowdata);
	m_RowNum++;
	return true;
}

void FileReader::moveNextRow()
{
	m_index++;
}

bool FileReader::isEof()
{
	return m_index < m_RowNum ? true : false;
}

cocos2d::Value FileReader::getValue(const string& fieldname)
{
	int index = m_Title[fieldname];
	if (index < m_FieldsNum && m_index < m_RowNum)
	{
		return m_Records[m_index][index];
	}
	return Value("");
}

std::string FileReader::trim(const string& content)
{
	string str = string_trim(content);
	str = string_replace(str, "\r", "");
	str = string_replace(str, "\"", "");
	return str;
}
