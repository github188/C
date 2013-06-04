#include "DigestFactory.h"

DigestFactory::DigestFactory() 
{
}

IDigest DigestFactory::create(string digestName)
{
	IDigest digest;
	if (digestName.compare("None") == 0) {
		//digest = new NullDigest();
	} else if (digestName.compare("CRC32C") == 0) {
		//digest = new CRC32CDigest();
	} else {
		//throw new IllegalArgumentException("Digest Type (" + digestName + ") is unknown.");
	}

	return digest;
}
