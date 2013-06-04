#include "ProtocolDataUnitFactory.h"
#include "ProtocolDataUnit.h"
ProtocolDataUnitFactory::ProtocolDataUnitFactory() 
{

}

ProtocolDataUnitFactory::~ProtocolDataUnitFactory() 
{

}

ProtocolDataUnit ProtocolDataUnitFactory::create(string headerDigest, string dataDigest) 
{
	return new ProtocolDataUnit(digestFactory.create(headerDigest), digestFactory.create(dataDigest));
}

ProtocolDataUnit ProtocolDataUnitFactory::create(bool immediateFlag, bool finalFlag,
        OperationCode operationCode, string headerDigest, string dataDigest) 
{

	ProtocolDataUnit *p_protocolDataUnit = new ProtocolDataUnit(
			digestFactory.create(headerDigest), 
			digestFactory.create(dataDigest));

	p_protocolDataUnit->getBasicHeaderSegment().setImmediate(immediateFlag);
	p_protocolDataUnit->getBasicHeaderSegment().setFinal(finalFlag);
	p_protocolDataUnit->getBasicHeaderSegment().setOperationCode(protocolDataUnit, 
			operationCode);

	return protocolDataUnit;
}

