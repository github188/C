#include "InitiatorMessageParser.h"

InitiatorMessageParser::InitiatorMessageParser() {
}

InitiatorMessageParser::InitiatorMessageParser(ProtocolDataUnit *pInitProtocolDataUnit) {
	m_pProtocolDataUnit = pInitProtocolDataUnit;
}

string InitiatorMessageParser::getShortInfo() {

	return "";
}

string InitiatorMessageParser::toString() {
	return "";
}

void InitiatorMessageParser::clear() {
	commandSequenceNumber = 0;
	expectedStatusSequenceNumber = 0;
}
