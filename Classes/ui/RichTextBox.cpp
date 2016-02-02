#include "RichTextBox.h"

LinkText* LinkText::create(const string& str)
{
	LinkText* widget = new (std::nothrow) LinkText();
	if (widget && widget->init())
	{
		widget->setString(str);
		widget->setFontSize(22);
		widget->setColor(Color3B::GREEN);
		widget->initLine();
		widget->autorelease();
		return widget;
	}
	return widget;
}

void LinkText::onTouchClickCallBack(Ref* sender)
{
	MessageBox(_data.c_str(),"鎻愮ず");
}

bool LinkText::initLine()
{
	_line = DrawNode::create();
	_line->setAnchorPoint(Point::ZERO);
	this->addChild(_line);
	_line->drawSegment(Point::ZERO, Point(this->getContentSize().width,0), 1, Color4F::GREEN);

	return true;
}

void LinkText::setLinkColor(const Color3B& color)
{
	_color = color;
	this->setColor(_color);
	if (_line)
	{
		_line->drawSegment(Point::ZERO, Point(this->getContentSize().width, 0), 1, Color4F(_color));
	}
}

void LinkText::setLinkSize(int fSize)
{
	this->setFontSize(fSize);
	if (_line)
	{
		_line->drawSegment(Point::ZERO, Point(this->getContentSize().width, 0), 1, Color4F(_color));
	}
}

void LinkText::setLinkData(const string& data)
{
	_data = data;
	this->setTouchEnabled(true);
	this->addClickEventListener(CC_CALLBACK_1(LinkText::onTouchClickCallBack, this));
}


Color3B parseColorFromStr(const string& str)
{
	int color = strtol(str.c_str(), nullptr, 16);

	return Color3B((GLubyte)(color >> 16), (GLubyte)(color >> 8), (GLubyte)color);
}
void RichTextData::formateType()
{
	// 琛ㄦ儏
	auto it = _typeMap.find("emot");
	if (it != _typeMap.end())
	{
		_richType = RichType::Emoticon;
		return;
	}
	// 瓒呴摼鎺?
	it = _typeMap.find("link");
	if (it != _typeMap.end())
	{
		_richType = RichType::Link;
		return;
	}
	// 姝ｅ父
	_richType = RichType::Normal;
}

std::string RichTextData::getLinkValue()
{
	auto it = _typeMap.find("link");
	if (it != _typeMap.end())
	{
		return it->second;
	}
	return "";
}

std::string RichTextData::getContentStr()
{
	return _contentStr;
}

cocos2d::Color3B RichTextData::getTextColor()
{
	auto it = _typeMap.find("c");
	if (it != _typeMap.end())
	{
		return parseColorFromStr(it->second);
	}
	if (_richType == RichType::Link)
	{
		return Color3B::GREEN;
	}
	return Color3B::WHITE;
}

int RichTextData::getFontSize()
{
	auto it = _typeMap.find("s");
	if (it != _typeMap.end())
	{
		return atoi(it->second.c_str());
	}
	return 22;
}

std::string RichTextData::getEmoticonName()
{
	auto it = _typeMap.find("emot");
	if (it != _typeMap.end())
	{
		return it->second;
	}
	return "default";
}



RichTextParse::RichTextParse()
{
	_dataVec.clear();
}

RichTextParse::~RichTextParse()
{
	_dataVec.clear();
}

bool RichTextParse::parseTextString(const string& richStr)
{
	_richStr = richStr;
	if (_richStr.empty() == true) return false;
	int index = 0;
	for (int i = 0; i < _richStr.length(); ++i)
	{
		switch (richStr[i])
		{
		case '[':
			{
					int pos = checkAnotherSign(i);
					if (pos != -1)
					{
						auto data = getParseData(i, pos);
						if (data)
						{
							_dataVec.push_back(data);
							i = pos;
							index = i + 1;
						}
					}
					break;
			}

		default:
			{
				   int pos = checkNormalText(i);
				   if (pos <= _richStr.length())
				   {
					   string content = _richStr.substr(index, pos - index);
					   auto data = RichTextData::create();
					   data->_contentStr = content;
					   data->_typeMap.insert(make_pair("c", "FFFFFF"));
					   data->formateType();
					   _dataVec.push_back(data);
					   index = i;
					   i = pos - 1;
				   }
				   break;
			}

		}
	}

	return true;
}

int RichTextParse::checkAnotherSign(int begin)
{
	int endpos = _richStr.find_first_of(']', begin);
	if (endpos == string::npos)
	{
		return -1;
	}
	return endpos;
}

// [aaaaa/c:ff00ff] [/emoti:smile1] [aaa/link:c]
RichTextData* RichTextParse::getParseData(int begin, int end)
{
	RichTextData* data = nullptr;
	string str = _richStr.substr(begin + 1, end - begin - 1);
	int pos1 = str.find_first_of('/', 0);
	if (pos1 != string::npos)
	{
		// 鍐呭
		string content = str.substr(0, pos1);
		string typeStr = str.substr(pos1 + 1, str.size() - pos1 - 1);

		data = RichTextData::create();
		data->_contentStr = content;
		data->_typeMap = checkMap(typeStr);
		data->formateType();
	}

	return data;
}

int RichTextParse::checkNormalText(int begin)
{
	int endpos = _richStr.find_first_of('[', begin);
	if (endpos == string::npos)
	{
		return _richStr.length();
	}
	return endpos;
}

RichText* RichTextParse::formatText()
{
	auto richText = RichText::create();
	for (int i = 0; i < _dataVec.size(); ++i)
	{
		switch (_dataVec[i]->_richType)
		{
		case RichType::Normal:
		{
								 Color3B color = _dataVec[i]->getTextColor();
								 int fsize = _dataVec[i]->getFontSize();
								 string content = _dataVec[i]->getContentStr();
								 auto element = RichElementText::create(i, color, 255, content, "", fsize);
								 richText->pushBackElement(element);
			break;
		}
		case RichType::Emoticon:
		{
								   Color3B color = _dataVec[i]->getTextColor();
								   int fsize = _dataVec[i]->getFontSize();
								   string emotName = _dataVec[i]->getEmoticonName();
								   SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("emot/%s/001.Png", emotName.c_str()));
								   if (frame)
								   {
									   Sprite* emot = Sprite::createWithSpriteFrame(frame);
									   Animation* anim = Animation::create();
									   anim->setDelayPerUnit(0.2f);
									   for (int i = 1; i < 100; ++i)
									   {
										   string name = StringUtils::format("emot/%s/%03d.Png", emotName.c_str(), i);
										   SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
										   if (frame)
										   {
											   anim->addSpriteFrame(frame);
										   }
										   else
										   {
											   break;
										   }
									   }
									   emot->runAction(RepeatForever::create(Animate::create(anim)));
									   auto element = RichElementCustomNode::create(i, Color3B::WHITE, 255, emot);
									   richText->pushBackElement(element);
								   }
								   break;
		}

		case RichType::Link:
		{
							   Color3B color = _dataVec[i]->getTextColor();
							   int fsize = _dataVec[i]->getFontSize();
							   string content = _dataVec[i]->getContentStr();
							   string data = _dataVec[i]->getLinkValue();
							   auto link = LinkText::create(content);
							   link->setLinkColor(color);
							   link->setLinkSize(fsize);
							   link->setLinkData(data);
							   auto element = RichElementCustomNode::create(i, Color3B::WHITE, 255, link);
							   richText->pushBackElement(element);
							   //richText->setTouchEnabled(true);
							   break;
		}

		default:
			break;
		}
	}

	return richText;
}
// aa:ss;bb:dd;aa:ss
map<string, string> RichTextParse::checkMap(const string& str)
{
	map<string, string> _map;
	int index = 0;
	string _key = "";
	string _val = "";
	while (index < str.size())
	{
		int pos = str.find_first_of(':', index);
		if (pos == string::npos)
		{
			break;
		}
		else
		{
			_key = str.substr(index, pos - index);
			int endpos = str.find_first_of(';', pos);
			if (endpos == string::npos)
			{
				endpos = str.size();
			}
			_val = str.substr(pos + 1, endpos - pos - 1);
			_map.insert(make_pair(_key, _val));
			index = endpos + 1;
		}
	}
	return _map;
}

