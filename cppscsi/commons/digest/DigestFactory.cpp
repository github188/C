#include <stdio.h>
#include "DigestFactory.h"
#include "NullDigest.h"
#include "CRC32CDigest.h"

DigestFactory::DigestFactory() 
{
	m_pDigest = NULL;
}

DigestFactory::~DigestFactory() 
{
	if (m_pDigest) delete m_pDigest;
}

IDigest* DigestFactory::create(const string &digestName)
{
	if (m_pDigest) delete m_pDigest;

	if (digestName.compare("None") == 0) {
		m_pDigest = new NullDigest();
	} else if (digestName.compare("CRC32C") == 0) {
		m_pDigest = new CRC32CDigest();
	} else {
		printf("Digest Type (%s) is unknown\n", digestName.c_str());
	}

	return m_pDigest;
}
