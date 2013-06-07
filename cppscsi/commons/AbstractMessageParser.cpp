#include "AbstractMessageParser.h"
#include "BasicHeaderSegment.h"
#include "Constants.h"

AbstractMessageParser::AbstractMessageParser() {

}

void AbstractMessageParser::deserializeBasicHeaderSegment(ByteBuffer pdu) {

	deserializeBytes1to3(pdu.getInt() & FIRST_SPECIFIC_FIELD_MASK);
	pdu.setReadPos(BasicHeaderSegment::BYTES_8_11);
	deserializeBytes8to11(pdu.getInt());
	deserializeBytes12to15(pdu.getInt());

	pdu.setReadPos(BasicHeaderSegment::BYTES_20_23);
	deserializeBytes20to23(pdu.getInt());
	deserializeBytes24to27(pdu.getInt());
	deserializeBytes28to31(pdu.getInt());
	deserializeBytes32to35(pdu.getInt());
	deserializeBytes36to39(pdu.getInt());
	deserializeBytes40to43(pdu.getInt());
	deserializeBytes44to47(pdu.getInt());
}

void AbstractMessageParser::serializeBasicHeaderSegment(ByteBuffer dst, int offset)
{

	dst.setWritePos(offset);
	dst.putInt(offset, dst.getInt() | serializeBytes1to3());

	dst.setWritePos(offset + BasicHeaderSegment::BYTES_8_11);
	dst.putInt(serializeBytes8to11());
	dst.putInt(serializeBytes12to15());

	dst.setWritePos(offset + BasicHeaderSegment::BYTES_20_23);
	dst.putInt(serializeBytes20to23());
	dst.putInt(serializeBytes24to27());
	dst.putInt(serializeBytes28to31());
	dst.putInt(serializeBytes32to35());
	dst.putInt(serializeBytes36to39());
	dst.putInt(serializeBytes40to43());
	dst.putInt(serializeBytes44to47());
}

string AbstractMessageParser::toString() {
	return "";
}

long AbstractMessageParser::getLogicalUnitNumber() {

	return logicalUnitNumber;
}

void AbstractMessageParser::setLogicalUnitNumber(long logicalUnitNumber) {
	this->logicalUnitNumber = logicalUnitNumber;
}

void AbstractMessageParser::deserializeBytes8to11(int line) {

	logicalUnitNumber = line;
	logicalUnitNumber <<= FOUR_BYTES_SHIFT;
}

void AbstractMessageParser::deserializeBytes12to15(int line) {

	logicalUnitNumber |= line;
}

int AbstractMessageParser::serializeBytes8to11() {

	return (int)(logicalUnitNumber >> FOUR_BYTES_SHIFT);
}

int AbstractMessageParser::serializeBytes12to15() {

	return (int)(logicalUnitNumber & LAST_FOUR_BYTES_MASK);
}

