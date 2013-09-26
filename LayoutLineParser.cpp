#include "LayoutLineParser.h"

LayoutLineParser LayoutLineParser::Default;

LayoutLineParser::LayoutLineParser(void)
{
}


LayoutLineParser::~LayoutLineParser(void)
{
}


std::vector<std::string> LayoutLineParser::parse(const std::string& line,const char separator)
{
	std::vector<std::string> result;
	size_t lastIndex = 0;
	size_t index = line.find(separator,lastIndex);
	while(index!=std::string::npos)
	{
		result.push_back(line.substr(lastIndex,index - lastIndex));
		lastIndex = index + 1;
		index = line.find(separator,lastIndex);
	}
	if(!line.empty())
	{
		result.push_back(line.substr(lastIndex, line.length() - lastIndex));
	}
	return result;
}