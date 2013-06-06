#include "TargetMessageParser.h"

TargetMessageParser::TargetMessageParser() {

}

string TargetMessageParser::getShortInfo() {
	return "";
}

string TargetMessageParser::toString() {
	return "";
}

void TargetMessageParser::clear() {
	statusSequenceNumber = 0;
	expectedCommandSequenceNumber = 0;
	maximumCommandSequenceNumber = 0;
}
