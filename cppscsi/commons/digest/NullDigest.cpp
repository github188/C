#include "NullDigest.h"

NullDigest::NullDigest() 
{
}

NullDigest::~NullDigest() 
{
}

void NullDigest::update(int b) 
{
	// do nothing
}

void NullDigest::update(char *b, int off, int len) 
{
	// do nothing
}

long NullDigest::getValue() 
{
	return 0;
}

void NullDigest::reset() 
{
	// do nothing
}

void NullDigest::validate()
{
	// do nothing
}

int NullDigest::getSize() 
{
	return DIGEST_SIZE;
}
