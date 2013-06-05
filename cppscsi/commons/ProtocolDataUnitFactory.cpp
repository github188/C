#include "ProtocolDataUnitFactory.h"
#include "ProtocolDataUnit.h"

ProtocolDataUnitFactory::ProtocolDataUnitFactory() 
{
	m_pProtocolDataUnit = NULL;
}

ProtocolDataUnitFactory::~ProtocolDataUnitFactory() 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::create(string headerDigest, 
		string dataDigest) 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;

	m_pProtocolDataUnit = new ProtocolDataUnit(
			m_DigestFactory.create(headerDigest), 
			m_DigestFactory.create(dataDigest));

	return m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::create(bool immediateFlag, 
		bool finalFlag, OperationCode operationCode, string headerDigest, 
		string dataDigest) 
{
	if (m_pProtocolDataUnit) delete m_pProtocolDataUnit;

	m_pProtocolDataUnit = new ProtocolDataUnit(
			m_DigestFactory.create(headerDigest), 
			m_DigestFactory.create(dataDigest));
#if 0
	m_pProtocolDataUnit->getBasicHeaderSegment().setImmediate(immediateFlag);
	m_pProtocolDataUnit->getBasicHeaderSegment().setFinal(finalFlag);
	m_pProtocolDataUnit->getBasicHeaderSegment().setOperationCode(protocolDataUnit, 
			operationCode);
#endif
	return m_pProtocolDataUnit;
}

ProtocolDataUnit* ProtocolDataUnitFactory::GetProtocolDataUnitPtr()
{
	return m_pProtocolDataUnit;
}

