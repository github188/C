// NullDigest.h
#ifndef __NULLDIGEST_H__
#define __NULLDIGEST_H__

#include "IDigest.h"

class NullDigest : public IDigest 
{
private:
	/** The size of the digest number (in bytes) to serialize. */
	const static int DIGEST_SIZE = 0;

public:
	NullDigest();
	~NullDigest();
	void update(int b);
	void update(char *data, int off, int len);
	long getValue();
	void reset();
	void validate();
	int getSize();
};

#endif // __NULLDIGEST_H__
