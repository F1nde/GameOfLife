
#ifndef __DISABLECOPY_H__
#define __DISABLECOPY_H__

class DisableCopy
{
public:
	DisableCopy() = default;
	~DisableCopy() = default;

	// Disable copy constructor and assignement operators
	DisableCopy(const DisableCopy&) = delete;
	DisableCopy& operator=(DisableCopy&) = delete;
};

#endif // __DISABLECOPY_H__
