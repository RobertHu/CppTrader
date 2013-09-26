#include "MaxSuffixHelper.h"
#include <regex>
#include <sstream>


MaxSuffixHelper MaxSuffixHelper::Default;

MaxSuffixHelper::MaxSuffixHelper(void)
{
}


MaxSuffixHelper::~MaxSuffixHelper(void)
{
}


int MaxSuffixHelper::getMaxSuffixIndex(const std::vector<std::string>& objectNames)
{
	int maxSuffixIndex = 0;
	std::string pattern = "[a-zA-Z]+(\\d+)";
	std::regex rgx(pattern);
	std::smatch match;
	for(auto begin = objectNames.cbegin(), end= objectNames.cend(); begin!=end; ++begin)
	{
		if(std::regex_search(*begin,match,rgx))
		{
			std::stringstream stream(match[1]);
			int index;
			if(stream >> index)
			{
				if(maxSuffixIndex < index)
				{
					maxSuffixIndex = index;
				}
			}
		}
	}
	return maxSuffixIndex;
}
