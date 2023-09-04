
#ifndef __DISABLECOPY_H__
#define __DISABLECOPY_H__

// Inherit from this class to disable the copy constructor and assignment operators.

class DisableCopy
{
public:
	DisableCopy() = default;
	~DisableCopy() = default;

	DisableCopy(const DisableCopy&) = delete;
	DisableCopy& operator=(DisableCopy&) = delete;
};

#endif // __DISABLECOPY_H__
