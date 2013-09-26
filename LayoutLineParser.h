#ifndef LAYOUTLINEPARSER_H
#define LAYOUTLINEPARSER_H
#include <vector>
class LayoutLineParser
{
public:
	~LayoutLineParser(void);
	static LayoutLineParser  Default;
	std::vector<std::string> parse(const std::string& line,const char separator);
private:
	LayoutLineParser(void);
};
#endif

