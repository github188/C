#include "BasicHeaderSegment.h"
#include "ProtocolDataUnit.h"
#include "AbstractMessageParser.h"

BasicHeaderSegment::BasicHeaderSegment()
{
}

BasicHeaderSegment::~BasicHeaderSegment()
{
}

int BasicHeaderSegment::serialize(ByteBuffer dst, int offset)
{
	return 0;
}

int BasicHeaderSegment::deserialize(ProtocolDataUnit protocolDataUnit, ByteBuffer src)
{
	return 0;
}

int BasicHeaderSegment::getDataSegmentLength()
{
	return 0;
}

bool BasicHeaderSegment::isFinalFlag()
{
	return false;
}

bool BasicHeaderSegment::isImmediateFlag()
{
	return false;
}

int BasicHeaderSegment::getInitiatorTaskTag()
{
	return 0;
}

char BasicHeaderSegment::getTotalAHSLength()
{
	return 0;
}

OperationCode BasicHeaderSegment::getOpCode()
{
}
#if 0
AbstractMessageParser BasicHeaderSegment::getParser()
{
}
#endif

void BasicHeaderSegment::setDataSegmentLength(int initDataSegmentLength)
{
}

void BasicHeaderSegment::setFinal(bool initFinalFlag)
{
}

void BasicHeaderSegment::setImmediate(bool initImmediateFlag)
{
}

void BasicHeaderSegment::setInitiatorTaskTag(int initInitiatorTaskTag)
{
}

void BasicHeaderSegment::setTotalAHSLength(byte initTotalAHSLength)
{
}

void BasicHeaderSegment::setOperationCode(ProtocolDataUnit protocolDataUnit, OperationCode initOperationCode)
{
}

string BasicHeaderSegment::toString()
{
	string strTmp = "";
	return strTmp;
}

bool BasicHeaderSegment::equals(Object o)
{
	return false;
}

void BasicHeaderSegment::clear()
{
}

