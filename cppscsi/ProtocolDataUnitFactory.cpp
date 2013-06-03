#include "ProtocolDataUnitFactory.h"

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

	ProtocolDataUnit protocolDataUnit = new ProtocolDataUnit(
			digestFactory.create(headerDigest), 
			digestFactory.create(dataDigest));

	protocolDataUnit.getBasicHeaderSegment().setImmediate(immediateFlag);
	protocolDataUnit.getBasicHeaderSegment().setFinal(finalFlag);
	protocolDataUnit.getBasicHeaderSegment().setOperationCode(protocolDataUnit, 
			operationCode);

	return protocolDataUnit;
}

