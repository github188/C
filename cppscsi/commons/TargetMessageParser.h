// TargetMessageParser.h
#ifndef __TARGETMESSAGEPARSER_H__
#define __TARGETMESSAGEPARSER_H__

#include "AbstractMessageParser.h"
#include "Constants.h"

class TargetMessageParser : public AbstractMessageParser {
protected:
	/** Status Sequence Number. */
	int statusSequenceNumber;

	/** Next Expected Commamd Sequence Number. */
	int expectedCommandSequenceNumber;

	/** Maximum Command Sequence Number. */
	int maximumCommandSequenceNumber;

public:
	/**
	 * Default constructor, creates a new, empty TargetMessageParser object.
	 *
	 * @param initProtocolDataUnit
	 * The reference ProtocolDataUnit instance, which
	 * contains this TargetMessageParser subclass
	 * object.
	 */
	TargetMessageParser();

	string getShortInfo();

	string toString();

	void clear();

	/**
	 * This AbstractMessageParser instance affects the
	 * incrementation of the Expected Status Sequence Number.
	 *
	 * @return true, if the counter has to be incremented. Else false.
	 */
	inline bool incrementSequenceNumber() {

		return true;
	}

	/**
	 * Next Expected Commamd Sequence Number from this Initiator ExpCmdSN is a Sequence Number
	 * that the target iSCSI returns
	 * to the initiator to acknowledge command reception. It is used to update a
	 * local variable with the same name. An ExpCmdSN equal to MaxCmdSN+1 indicates
	 * that the target cannot accept new
	 * commands.
	 *
	 * @return Expected Command Sequence Number.
	 */
	inline int getExpectedCommandSequenceNumber() {

		return expectedCommandSequenceNumber;
	}

	/**
	 * Maximum Command Sequence Number from this Initiator MaxCmdSN is a Sequence Number that the
	 * target iSCSI returns to the initiator to
	 * indicate the maximum CmdSN the initiator can send. It is
	 * used to update a local variable with the same name. If MaxCmdSN is equal to
	 * ExpCmdSN-1, this indicates
	 * to the initiator that the target cannot receive any additional commands.
	 * When MaxCmdSN changes at the target while the target has no
	 * pending PDUs to convey this information to the initiator, it MUST
	 * generate a NOP-IN to carry the new MaxCmdSN.
	 *
	 * @return Maximum Command Sequence Number.
	 */
	inline int getMaximumCommandSequenceNumber() {

		return maximumCommandSequenceNumber;
	}

	/**
	 * The Status Sequence Number (StatSN) is a Sequence Number that the target
	 * iSCSI layer generates per connection and that in turn, enables the
	 * initiator to acknowledge status reception. StatSN is
	 * incremented by 1 for every response/status sent on a
	 * connection except for responses sent as a result of a retry or SNACK. In
	 * the case of responses sent due to a retransmission request, the StatSN MUST be the same as
	 * the first time the PDU was sent
	 * unless the connection has since been restarted.
	 *
	 * @return Status Sequence Number.
	 */
	inline int getStatusSequenceNumber() {

		return statusSequenceNumber;
	}

	/**
	 * Sets the Expected Command Sequence Number of this TargetMessageParser object to the given
	 * value.
	 *
	 * @param newExpectedCommandSequenceNumber
	 * The new Expected Command Sequence Number.
	 */
	inline void setExpectedCommandSequenceNumber(int newExpectedCommandSequenceNumber) {

		expectedCommandSequenceNumber = newExpectedCommandSequenceNumber;
	}

	/**
	 * Sets the Maximum Command Sequence Number of this TargetMessageParser object to the given
	 * value.
	 *
	 * @param newMaximumCommandSequenceNumber
	 * The new Maximum Command Sequence Number.
	 */
	inline void setMaximumCommandSequenceNumber(int newMaximumCommandSequenceNumber) {

		maximumCommandSequenceNumber = newMaximumCommandSequenceNumber;
	}

	/**
	 * Sets the Status Sequence Number of this TargetMessageParser object to the given value.
	 *
	 * @param newStatusSequenceNumber
	 * The new Status Sequence Number.
	 */
	inline void setStatusSequenceNumber(int newStatusSequenceNumber) {

		statusSequenceNumber = newStatusSequenceNumber;
	}

	inline void deserializeBytes1to3(int line) {

	}

	inline void deserializeBytes20to23(int line) {

	}

	inline void deserializeBytes24to27(int line) {

		statusSequenceNumber = line;
	}

	inline void deserializeBytes28to31(int line) {

		expectedCommandSequenceNumber = line;
	}

	inline void deserializeBytes32to35(int line) {

		maximumCommandSequenceNumber = line;
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

		return statusSequenceNumber;
	}

	inline int serializeBytes28to31() {

		return expectedCommandSequenceNumber;
	}

	inline int serializeBytes32to35() {

		return maximumCommandSequenceNumber;
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

#endif // __TARGETMESSAGEPARSER_H__
