#include "LoginRequestParser.h"

LoginRequestParser::LoginRequestParser() {

}

string LoginRequestParser::getShortInfo() {

	return "";
}

string LoginRequestParser::toString() {
	return "";
}

void LoginRequestParser::clear() {
	continueFlag = false;

	currentStageNumber = SECURITY_NEGOTIATION;
	nextStageNumber = SECURITY_NEGOTIATION;

	maxVersion = 0x00;
	minVersion = 0x00;

	initiatorSessionID.clear();

	targetSessionIdentifyingHandle = 0x0000;
	connectionID = 0x00000000;
}


void LoginRequestParser::deserializeBytes1to3(int line) {

	continueFlag = (line & CONTINUE_FLAG_MASK);

	currentStageNumber =(line & CSG_FLAG_MASK) >> CSG_BIT_SHIFT;
	nextStageNumber =((byte)((line & NSG_FLAG_MASK) >> TWO_BYTES_SHIFT));

	maxVersion = (byte)((line & THIRD_BYTE_MASK) >> ONE_BYTE_SHIFT);
	minVersion = (byte)(line & FOURTH_BYTE_MASK);
}

void LoginRequestParser::deserializeBytes12to15(int line) {

	// use the logicalUnitNumber variable as temporary storage
	long l = line;

	logicalUnitNumber |= l;
	initiatorSessionID.deserialize(logicalUnitNumber);

	targetSessionIdentifyingHandle = (short)(line & LAST_TWO_BYTES_MASK);
}

void LoginRequestParser::deserializeBytes20to23(int line) {

	connectionID = (line & FIRST_TWO_BYTES_MASK) >> TWO_BYTES_SHIFT;
}

void LoginRequestParser::checkIntegrity() {
	do {
		BasicHeaderSegment bhs = protocolDataUnit.getBasicHeaderSegment();
		if (bhs.isFinalFlag() && continueFlag) {
			cout << "Transit and Continue Flag cannot be set at the same time." << endl;
			break;
		}

		if (!bhs.isFinalFlag() && nextStageNumber != SECURITY_NEGOTIATION) {
			cout << "NextStageNumber is reserved, when the TransitFlag is not set." << endl;
			break;
		}

		if (bhs.isFinalFlag()) {
			if (currentStageNumber == SECURITY_NEGOTIATION) {
				if (nextStageNumber == SECURITY_NEGOTIATION) {
					cout << "This transition (SNP -> SNP) is not allowed." << endl;
					break;
				}
			} else if (currentStageNumber == LOGIN_OPERATIONAL_NEGOTIATION) {
				if (nextStageNumber == SECURITY_NEGOTIATION) {
					cout << "This transition (LONP -> SNP) is not allowed." << endl;
					break;
				} else if (nextStageNumber == LOGIN_OPERATIONAL_NEGOTIATION) {
					cout << "This transition (LONP -> LONP) is not allowed." << endl;
					break;
				}
			}
		}

		if (minVersion != 0x00) {
			cout << "MinVersion is not in a valid range." << endl;
			break;
		}

		if (maxVersion != 0x00) {
			cout << "MaxVersion is not in a valid range." << endl;
			break;
		}

		if (minVersion != maxVersion) {
			cout << "MinVersion and MaxVersion have not the same value." << endl;
			break;
		}

		// message is checked correctly
		return;
	} while (false);
}

int LoginRequestParser::serializeBytes1to3() {

	int line = minVersion;
	line |= maxVersion << ONE_BYTE_SHIFT;

	line |= nextStageNumber.value() << TWO_BYTES_SHIFT;
	line |= currentStageNumber.value() << CSG_BIT_SHIFT;

	if (continueFlag) {
		line |= CONTINUE_FLAG_MASK;
	}

	return line;
}

int LoginRequestParser::serializeBytes8to11() {

	logicalUnitNumber = initiatorSessionID.serialize();
	return (int)(logicalUnitNumber >> FOUR_BYTES_SHIFT);
}

int LoginRequestParser::serializeBytes12to15() {

	int line = (int)(logicalUnitNumber & LAST_FOUR_BYTES_MASK);
	line |= targetSessionIdentifyingHandle;

	return line;
}

int LoginRequestParser::serializeBytes20to23() {

	return connectionID << TWO_BYTES_SHIFT;
}
