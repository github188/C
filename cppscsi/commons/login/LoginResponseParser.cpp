#include "LoginResponseParser.h"
#include "BasicHeaderSegment.h"
#include "LoginConstants.h"

LoginResponseParser::LoginResponseParser() {
}

LoginResponseParser::LoginResponseParser(ProtocolDataUnit *pInitProtocolDataUnit) {
	m_pProtocolDataUnit = pInitProtocolDataUnit;
}

std::string LoginResponseParser::toString() {
	return "";
}

void LoginResponseParser::clear() {
	continueFlag = false;

	currentStageNumber = SECURITY_NEGOTIATION;
	nextStageNumber = SECURITY_NEGOTIATION;

	maxVersion = 0;
	activeVersion = 0;

	initiatorSessionID.clear();

	targetSessionIdentifyingHandle = 0;
}

DataSegmentFormat LoginResponseParser::getDataSegmentFormat() {

	return TEXT;
}

bool LoginResponseParser::canHaveDigests() {

	return false;
}

LoginStatus LoginResponseParser::getStatus() {

	return status;
}

bool LoginResponseParser::isContinueFlag() {

	return continueFlag;
}

LoginStage LoginResponseParser::getCurrentStageNumber() {

	return currentStageNumber;
}

ISID LoginResponseParser::getInitiatorSessionID() {

	return initiatorSessionID;
}

int LoginResponseParser::getMaxVersion() {

	return maxVersion;
}

int LoginResponseParser::getActiveVersion() {

	return activeVersion;
}

LoginStage LoginResponseParser::getNextStageNumber() {

	return nextStageNumber;
}

short LoginResponseParser::getTargetSessionIdentifyingHandle() {

	return targetSessionIdentifyingHandle;
}

void LoginResponseParser::setStatus(LoginStatus status) {
	status = status;
}

void LoginResponseParser::setContinueFlag(bool continueFlag) {
	continueFlag = continueFlag;
}

void LoginResponseParser::setCurrentStageNumber(LoginStage currentStage) {
	currentStageNumber = currentStage;
}

void LoginResponseParser::setNextStageNumber(LoginStage nextStage) {
	nextStageNumber = nextStage;
}

void LoginResponseParser::setInitiatorSessionID(ISID initiatorSessionID) {
	initiatorSessionID = initiatorSessionID;
}

void LoginResponseParser::setTargetSessionIdentifyingHandle(short targetSessionIdentifyingHandle) {
	targetSessionIdentifyingHandle = targetSessionIdentifyingHandle;
}

void LoginResponseParser::deserializeBytes1to3(int line)  {

	continueFlag = line & CONTINUE_FLAG_MASK;
#if 0
	currentStageNumber = (line & CSG_FLAG_MASK) >> CSG_BIT_SHIFT;
	nextStageNumber = (line & NSG_FLAG_MASK) >> TWO_BYTES_SHIFT;
#endif

	maxVersion = (line & THIRD_BYTE_MASK) >> ONE_BYTE_SHIFT;
	activeVersion = line & FOURTH_BYTE_MASK;
}

void LoginResponseParser::deserializeBytes12to15(int line)  {

	// use the logicalUnitNumber variable as temporary storage
	logicalUnitNumber |= line;
	initiatorSessionID.deserialize(logicalUnitNumber);

	targetSessionIdentifyingHandle = (short)(line & LAST_TWO_BYTES_MASK);
}

void LoginResponseParser::deserializeBytes36to39(int line)  {
#if 0
	status = (line & FIRST_TWO_BYTES_MASK) >> TWO_BYTES_SHIFT;
#endif
}


void LoginResponseParser::checkIntegrity()  {

	do {
		if (status != SUCCESS && statusSequenceNumber != 0) {
			//cout << "While no successful login is preformed, the StatusSequenceNumber must be 0." << endl;
			break;
		}

		// message is checked correctly
		return;
	} while (false);
}


int LoginResponseParser::serializeBytes1to3() {

	int line = activeVersion;
	line |= maxVersion << ONE_BYTE_SHIFT;
	line |= nextStageNumber << TWO_BYTES_SHIFT;
	line |= currentStageNumber << CSG_BIT_SHIFT;

	if (continueFlag) {
		line |= CONTINUE_FLAG_MASK;
	}
	return line;
}

int LoginResponseParser::serializeBytes36to39() {

	int line = 0;
	line |= status<< TWO_BYTES_SHIFT;

	return line;
}
