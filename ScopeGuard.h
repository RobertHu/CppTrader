#ifndef SCOPEGUARD_H
#define SCOPEGUARD_H
#include <functional>
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()> onExitScope)
		:_onExistScope(onExitScope),_dismissed(false)
	{
	}

	~ScopeGuard()
	{
		if(!_dismissed)
		{
			_onExistScope();
		}
	}

private:
	std::function<void()> _onExistScope;
	bool _dismissed;
private:
	ScopeGuard(const ScopeGuard&);
	ScopeGuard& operator= (const ScopeGuard&);
};


#define SCOPEGUARD_LINENAME_CAT(name,line) name##line

#define SCOPEGUARD_LINENAME(name,line) SCOPEGUARD_LINENAME_CAT(name,line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)

#endif 