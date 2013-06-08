#include "ProtocolDataUnitFactory.h"
#include "ProtocolDataUnit.h"
#include "BasicHeaderSegment.h"

ProtocolDataUnitFactory::ProtocolDataUnitFactory() 
{
	m_pProtocolDataUnit = NULL;
}

ProtocolDataUnitFactory::~ProtocolDataUnitFactory() 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::create(const string &headerDigest, 
		const string &dataDigest) 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;

	m_pProtocolDataUnit = new ProtocolDataUnit(
			*m_DigestFactory.create(headerDigest), 
			*m_DigestFactory.create(dataDigest));

	return m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::create(bool immediateFlag, 
		bool finalFlag, int operationCode, const string &headerDigest, 
		const string &dataDigest) 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;

	m_pProtocolDataUnit = new ProtocolDataUnit(
			*m_DigestFactory.create(headerDigest), 
			*m_DigestFactory.create(dataDigest));

	m_pProtocolDataUnit->getBasicHeaderSegment()->setImmediate(immediateFlag);
	m_pProtocolDataUnit->getBasicHeaderSegment()->setFinal(finalFlag);
	m_pProtocolDataUnit->getBasicHeaderSegment()->setOperationCode(*m_pProtocolDataUnit, 
			operationCode);

	return m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::GetProtocolDataUnitPtr()
{
	return m_pProtocolDataUnit;
}
