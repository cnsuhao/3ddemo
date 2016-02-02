#ifndef __RICHTEXTBOX__
#define __RICHTEXTBOX__

#include "CocosHead.h"

// 字段说明
enum class RichType
{
	Null		= 0,
	Normal		= 1,
	Emoticon	= 2,
	Link		= 3
};

class LinkText :public Text
{
public:
	LinkText() :_line(nullptr), _color(Color3B::GREEN), _data(""){};

	virtual ~LinkText(){};

	static LinkText* create(const string& str);

	virtual bool initLine();

	CREATE_FUNC(LinkText);

	void setLinkColor(const Color3B& color);

	void setLinkSize(int fSize);

	void setLinkData(const string& data);

	void onTouchClickCallBack(Ref* sender);
private:

	DrawNode* _line;
	Color3B  _color;
	string	_data;
};

// 文本段
class RichTextData:public Node
{
public:
	RichTextData():_color(Color3B::WHITE){};

	virtual ~RichTextData(){};

	CREATE_FUNC(RichTextData);
	// 文本
	string getContentStr();
	// 颜色
	Color3B getTextColor();
	// 字体大小
	int getFontSize();
	// 类型
	void formateType();
	// 超链接内容
	string getLinkValue();
	// 表情名字
	string getEmoticonName();


	// 类型
	RichType _richType;
	// 内容文字
	string _contentStr;
	// 类型标志
	map<string, string> _typeMap;
	// 颜色
	Color3B _color;
};

// 解析
class RichTextParse :public Node
{

public:
	RichTextParse();

	virtual ~RichTextParse();

	bool parseTextString(const string& richStr);

	CREATE_FUNC(RichTextParse);

	RichText* formatText();

private:

	int checkNormalText(int begin);

	int checkAnotherSign(int begin);

	map<string, string> checkMap(const string& str);

	RichTextData* getParseData(int begin,int end);

	vector<RichTextData*> _dataVec;

	string _richStr;
};
#endif