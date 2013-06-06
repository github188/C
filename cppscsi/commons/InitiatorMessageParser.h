// InitiatorMessageParser.h
#ifndef __INITIATORMESSAGEPARSER_H__
#define __INITIATORMESSAGEPARSER_H__

#include "AbstractMessageParser.h"
#include "Constants.h"

class InitiatorMessageParser : public AbstractMessageParser {
protected:
	/**
	 * Command Sequence Number.
	 * Enables ordered delivery across multiple connections in a single session.
	 */
	int commandSequenceNumber;

	/**
	 * Expected Status Sequence Number.
	 * Command responses up to expectedStatusSequenceNumber - 1 (mod 2**32) have been received
	 * (acknowledges status) on the connection.
	 */
	int expectedStatusSequenceNumber;

public: 
	/**
	 * Default constructor, creates a new, empty LogoutRequestParser object.
	 *
	 * @param initProtocolDataUnit
	 * The reference ProtocolDataUnit instance, which
	 * contains this InitiatorMessageParser object.
	 */
	InitiatorMessageParser();

public: 
	string getShortInfo();

	string toString();

	void clear();

	/**
	 * This AbstractMessageParser instance affects the
	 * incrementation of the Command Sequence Number.
	 *
	 * @return true, if the counter has to be incremented. Else false.
	 */
	inline bool incrementSequenceNumber() {

		return false;
	}

public:
	/**
	 * Returns the Command Sequence Number of this InitiatorMessageParser object.
	 *
	 * @return The Command Sequence Number.
	 */
	inline int getCommandSequenceNumber() {

		return commandSequenceNumber;
	}

	/**
	 * Returns the Expected Status Sequence Number of this InitiatorMessageParser object.
	 *
	 * @return The Expected Status Sequence Number.
	 */
	inline int getExpectedStatusSequenceNumber() {

		return expectedStatusSequenceNumber;
	}

	/**
	 * Sets the Command Sequence Number of this InitiatorMessageParser object to the given value.
	 *
	 * @param initCmdSN
	 * The new Command Sequence Number.
	 */
	inline void setCommandSequenceNumber(int initCmdSN) {

		commandSequenceNumber = initCmdSN;
	}

	/**
	 * Sets the Expected Status Sequence Number of this InitiatorMessageParser object to the
	 * given value.
	 *
	 * @param initExpStatSN
	 * The new Expected Status Sequence Number.
	 */
	inline void setExpectedStatusSequenceNumber(int initExpStatSN) {

		expectedStatusSequenceNumber = initExpStatSN;
	}

protected:
	/** Override */
	inline void deserializeBytes1to3(int line) {

	}

	inline void deserializeBytes20to23(int line) {

	}

	inline void deserializeBytes24to27(int line) {

	}

	inline void deserializeBytes28to31(int line) {

		expectedStatusSequenceNumber = line;
	}

	inline void deserializeBytes32to35(int line) {

	}

	inline void deserializeBytes36to39(int line) {

	}

	inline void deserializeBytes40to43(int line) {

	}

	inline void deserializeBytes44to47(int line) {

	}

	inline int serializeBytes1to3() {

		return RESERVED_INT;
	}

	inline int serializeBytes20to23() {

		return RESERVED_INT;
	}

	inline int serializeBytes24to27() {

		return commandSequenceNumber;
	}

	inline int serializeBytes28to31() {

		return expectedStatusSequenceNumber;
	}

	inline int serializeBytes32to35() {

		return RESERVED_INT;
	}

	inline int serializeBytes36to39() {

		return RESERVED_INT;
	}

	inline int serializeBytes40to43() {

		return RESERVED_INT;
	}

	inline int serializeBytes44to47() {

		return RESERVED_INT;
	}
};

#endif // __INITIATORMESSAGEPARSER_H__
