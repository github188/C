#include <stdio.h>
#include "BasicHeaderSegment.h"
#include "Constants.h"
#include "OperationCode.h"
#include "ProtocolDataUnit.h"
#include "MessageParserFactory.h"

BasicHeaderSegment::BasicHeaderSegment()
{
	m_pMessageParser = NULL;
	m_pMessageParserFactory = new MessageParserFactory();
}

BasicHeaderSegment::~BasicHeaderSegment()
{
	if (m_pMessageParserFactory) delete m_pMessageParserFactory;
}

#if 0
int BasicHeaderSegment::serialize(ByteBuffer dst, int offset)
{
	// has the destination array enough space to store this basic header
	// segment
	dst.setWritePos(offset);
	if (dst.bytesRemaining() < BHS_FIXED_SIZE) {
		printf("Destination array is too small.");
	}

	int line = 0;
	if (immediateFlag) {
		line |= IMMEDIATE_FLAG_MASK;
	}

	line |= operationCode << THREE_BYTES_SHIFT;

	if (finalFlag) {
		line |= FINAL_FLAG_MASK;
	}
	dst.putInt(line);

	dst.putInt(dataSegmentLength | (totalAHSLength << THREE_BYTES_SHIFT));
	dst.putInt(BYTES_16_19, initiatorTaskTag);

	m_pMessageParser->serializeBasicHeaderSegment(dst, offset);

	return BHS_FIXED_SIZE;	
}

#endif 
int BasicHeaderSegment::deserialize(const ProtocolDataUnit &protocolDataUnit, ByteBuffer src)
{
	if (src.bytesRemaining() < BHS_FIXED_SIZE) {
		printf("This Protocol Data Unit does not contain an valid Basic Header Segment.");
	}

	int firstLine = src.getInt();
	immediateFlag = firstLine & IMMEDIATE_FLAG_MASK;
	int code = (firstLine & OPERATION_CODE_MASK) >> THREE_BYTES_SHIFT;
	operationCode = code;
	finalFlag = firstLine & FINAL_FLAG_MASK;

	totalAHSLength = src.get();
	dataSegmentLength = src.get() << TWO_BYTES_SHIFT;
	dataSegmentLength += src.get() << ONE_BYTE_SHIFT;
	dataSegmentLength += src.get();

	initiatorTaskTag = src.getInt(BYTES_16_19);

	//src.rewind();

	m_pMessageParser = m_MessageParserFactory.getParser(protocolDataUnit, operationCode);
	m_pMessageParser->deserializeBasicHeaderSegment(src);

	return BHS_FIXED_SIZE;	
}
int BasicHeaderSegment::getDataSegmentLength()
{
	return dataSegmentLength;
}

bool BasicHeaderSegment::isFinalFlag()
{
	return finalFlag;
}

bool BasicHeaderSegment::isImmediateFlag()
{
	return immediateFlag;
}

int BasicHeaderSegment::getInitiatorTaskTag()
{
	return initiatorTaskTag;
}

char BasicHeaderSegment::getTotalAHSLength()
{
	return totalAHSLength;
}

int BasicHeaderSegment::getOpCode()
{
	return operationCode;
}

AbstractMessageParser* BasicHeaderSegment::getParser()
{
	return m_pMessageParser;
}

void BasicHeaderSegment::setDataSegmentLength(int initDataSegmentLength)
{
	dataSegmentLength = initDataSegmentLength;
}

void BasicHeaderSegment::setFinal(bool initFinalFlag)
{
	finalFlag = initFinalFlag;
}

void BasicHeaderSegment::setImmediate(bool initImmediateFlag)
{
	immediateFlag = initImmediateFlag;
}

void BasicHeaderSegment::setInitiatorTaskTag(int initInitiatorTaskTag)
{
	// FIXME: Change to allow fixed values
	initiatorTaskTag = initInitiatorTaskTag;
}

void BasicHeaderSegment::setTotalAHSLength(unsigned char initTotalAHSLength)
{
	totalAHSLength = initTotalAHSLength;
}

#if 1
void BasicHeaderSegment::setOperationCode(ProtocolDataUnit protocolDataUnit, int initOperationCode)
{
	operationCode = initOperationCode;
	m_pMessageParser = m_pMessageParserFactory->getParser(protocolDataUnit, initOperationCode);
}
#endif 

string BasicHeaderSegment::toString()
{
	if (m_pMessageParser == NULL)
		return "Empty parser";
#if 0
	cout << "ParserClass: " << endl;
	cout << "ImmediateFlag: " << immediateFlag << endl;
	cout << "OpCode: " << operationCode << endl;
	cout << "FinalFlag: " << finalFlag << endl;
	cout << "TotalAHSLength: " << totalAHSLength << endl;
	cout << "DataSegmentLength: " << dataSegmentLength << endl;
	cout << "InitiatorTaskTag: " << initiatorTaskTag << endl;
#endif
	return "";
}

bool BasicHeaderSegment::equals(BasicHeaderSegment &o)
{
	return false;
}

void BasicHeaderSegment::clear()
{
	immediateFlag = false;
	operationCode = LOGIN_REQUEST;
	finalFlag = false;

	totalAHSLength = 0x00;
	dataSegmentLength = 0x00000000;
	initiatorTaskTag = 0x00000000;

	m_pMessageParser = NULL;
}

