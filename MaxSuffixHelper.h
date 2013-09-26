#ifndef  MAXSUFFIXHELPER_H
#define MAXSUFFIXHELPER_H
#include <vector>
class MaxSuffixHelper
{
public:
	~MaxSuffixHelper(void);
	static MaxSuffixHelper Default;
	int getMaxSuffixIndex(const std::vector<std::string>& objectNames);
private:
	MaxSuffixHelper(void);



};
#endif

