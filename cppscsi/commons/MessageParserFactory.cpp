// MessageParserFactory.cpp
#include "MessageParserFactory.h"
#include "OperationCode.h"
#include "AbstractMessageParser.h"
#include "ProtocolDataUnit.h"

MessageParserFactory::MessageParserFactory() {

}

MessageParserFactory::~MessageParserFactory() {

}

/**
 * Returns the parser object with the given operation code.
 *
 * @param protocolDataUnit
 * The reference ProtocolDataUnit instance, which
 * contains this AbstractMessageParser object.
 * @param operationCode
 * The operation code of the requested AbstractMessageParser.
 * @return The instance of the requested AbstractMessageParser.
 * @see org.jscsi.parser.OperationCode
 */
AbstractMessageParser* MessageParserFactory::getParser( ProtocolDataUnit protocolDataUnit, int operationCode) {

	return createParser(protocolDataUnit, operationCode);
}

/**
 * Creates an instance of a concrete AbstractMessageParser object.
 *
 * @param protocolDataUnit
 * The reference ProtocolDataUnit instance, which
 * contains this AbstractMessageParser object.
 * @param operationCode
 * The operation code of the requested AbstractMessageParser.
 * @return The instance of the requested AbstractMessageParser.
 * @see org.jscsi.parser.OperationCode
 */
AbstractMessageParser* MessageParserFactory::createParser( ProtocolDataUnit protocolDataUnit, int operationCode) {
#if 0
	switch (operationCode) {
		case LOGIN_REQUEST:
			return new LoginRequestParser(protocolDataUnit);
		case LOGIN_RESPONSE:
			return new LoginResponseParser(protocolDataUnit);
		case LOGOUT_REQUEST:
			return new LogoutRequestParser(protocolDataUnit);
		case LOGOUT_RESPONSE:
			return new LogoutResponseParser(protocolDataUnit);
		case TEXT_REQUEST:
			return new TextRequestParser(protocolDataUnit);
		case TEXT_RESPONSE:
			return new TextResponseParser(protocolDataUnit);
		case SCSI_DATA_OUT:
			return new DataOutParser(protocolDataUnit);
		case SCSI_DATA_IN:
			return new DataInParser(protocolDataUnit);
		case NOP_OUT:
			return new NOPOutParser(protocolDataUnit);
		case NOP_IN:
			return new NOPInParser(protocolDataUnit);
		case R2T:
			return new Ready2TransferParser(protocolDataUnit);
		case REJECT:
			return new RejectParser(protocolDataUnit);
		case SNACK_REQUEST:
			return new SNACKRequestParser(protocolDataUnit);
		case SCSI_TM_REQUEST:
			return new TaskManagementFunctionRequestParser(protocolDataUnit);
		case SCSI_TM_RESPONSE:
			return new TaskManagementFunctionResponseParser(protocolDataUnit);
		case SCSI_COMMAND:
			return new SCSICommandParser(protocolDataUnit);
		case SCSI_RESPONSE:
			return new SCSIResponseParser(protocolDataUnit);
		default:
	}
#else
	return NULL;
#endif
}
