#include "InitiatorMessageParser.h"

InitiatorMessageParser::InitiatorMessageParser() {

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
