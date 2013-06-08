// LoginRequestParser.h
#ifndef __LOGINREQUESTPARSER_H__
#define __LOGINREQUESTPARSER_H__

#include "InitiatorMessageParser.h"
#include "LoginStatus.h"
#include "LoginConstants.h"
#include "Constants.h"
#include "ISID.h"

#ifndef byte
#define byte unsigned char
#endif

class LoginRequestParser : public InitiatorMessageParser {
private:
    /** The Continue Flag. */
    bool continueFlag;

    /** The Current stage in the session. */
    int currentStageNumber;

    /** The next stage in the session. */
    int nextStageNumber;

    /** The maximum version number to support. */
    byte maxVersion;

    /** The minimum version number to support. */
    byte minVersion;

    /** The Initiator Session ID (ISID). */
    ISID initiatorSessionID;

    /** The Target Session Identifying Handle (TSIH). */
    short targetSessionIdentifyingHandle;

    /** The Connection ID. */
    int connectionID;

public:
	/**
	 * Default constructor, creates a new, empty LoginRequestParser object.
	 *
	 * @param initProtocolDataUnit
	 * The reference ProtocolDataUnit instance, which
	 * contains this LoginRequestParser subclass object.
	 */
    LoginRequestParser();
    LoginRequestParser(ProtocolDataUnit *pInitProtocolDataUnit);

    string toString();
	string getShortInfo();

    DataSegmentFormat getDataSegmentFormat() {
        return TEXT;
    }

    bool canHaveDigests() {

        return false;
    }

    void clear();

	/**
	 * A unique ID for this connection within the session.
	 * <p>
	 * All Login Requests within the Login Phase MUST carry the same CID.
	 * <p>
	 * The target MUST use the value presented with the first Login Request.
	 * <p>
	 * A Login Request with a non-zero TSIH and a CID equal to that of an existing
	 * connection implies a logout of the connection followed by a Login (see Section 5.3.4 Connection
	 * Reinstatement). For the details of the implicit Logout Request, see Section 10.14 Logout Request.
	 *
	 * @return The Connection ID of this LoginRequestParser object.
	 */
    int getConnectionID() {

        return connectionID;
    }

	/**
	 * When set to 1, indicates that the text (set of key=value
	 * pairs) in this Login Request is not complete (it will be continued on
	 * subsequent Login Requests); otherwise, it indicates that this Login
	 * Request ends a set of key=value pairs. A Login Request with the C bit set to
	 * 1 MUST have the T bit
	 * set to 0.
	 *
	 * @return Returns true, if the Continue Bit is set. Else false.
	 */
	bool isContinueFlag() {

		return continueFlag;
	}

	/**
	 * Returns the <em>Current Stage Number</em> of this Login Request Message.
	 * <p>
	 * Through these fields, Current Stage (CSG) and Next Stage (NSG), the Login negotiation requests and
	 * responses are associated with a specific stage in the session (SecurityNegotiation,
	 * LoginOperationalNegotiation, FullFeaturePhase) and may indicate the next stage to which they want to
	 * move (see Chapter 5). The next stage value is only valid when the T bit is 1; otherwise, it is
	 * reserved.
	 * <p>
	 * The stage codes are:
	 * <ul>
	 * <li>0 - SecurityNegotiation</li>
	 * <li>1 - LoginOperationalNegotiation</li>
	 * <li>3 - FullFeaturePhase</li>
	 * </ul>
	 * <p>
	 * All other codes are reserved.
	 *
	 * @return Number of the Current Stage.
	 * @see org.jscsi.parser.login.LoginStage
	 */
	int getCurrentStageNumber() {

		return currentStageNumber;
	}

	/**
	 * Returns the <em>Initiator Session ID (ISID)</em> of this
	 * LoginRequestParser object.
	 *
	 * @return Returns the <em>Initiator Session ID (ISID)</em> of this LoginRequestParser
	 * object.
	 * @see ISID
	 */
	ISID getInitiatorSessionID() {

		return initiatorSessionID;
	}

	/**
	 * Maximum Version number supported.
	 * <p>
	 * All Login Requests within the Login Phase MUST carry the same Version-max.
	 * <p>
	 * The target MUST use the value presented with the first Login Request.
	 *
	 * @return The maximum version of this login request message.
	 */
	byte getMaxVersion() {

		return maxVersion;
	}

	/**
	 * All Login Requests within the Login Phase MUST carry the same
	 * Version-min. The target MUST use the value presented with the first Login
	 * Request.
	 *
	 * @return The minimum version of this login request message.
	 */
	byte getMinVersion() {

		return minVersion;
	}

	/**
	 * Returns the <em>Next Stage Number</em> of this Login Request Message.
	 * <p>
	 * Through these fields, Current Stage (CSG) and Next Stage (NSG), the Login negotiation requests and
	 * responses are associated with a specific stage in the session (SecurityNegotiation,
	 * LoginOperationalNegotiation, FullFeaturePhase) and may indicate the next stage to which they want to
	 * move (see Chapter 5). The next stage value is only valid when the T bit is 1; otherwise, it is
	 * reserved.
	 * <p>
	 * The stage codes are:
	 * <ul>
	 * <li>0 - SecurityNegotiation</li>
	 * <li>1 - LoginOperationalNegotiation</li>
	 * <li>3 - FullFeaturePhase</li>
	 * </ul>
	 * <p>
	 * All other codes are reserved.
	 *
	 * @return The Number of the Next Stage.
	 * @see org.jscsi.parser.login.LoginStage
	 */
	int getNextStageNumber() {

		return nextStageNumber;
	}

	/**
	 * <em>Target Session Identifying Handle (TSIH)</em> must be set in the
	 * first Login Request. The reserved value 0 MUST be used on
	 * the first connection for a new session. Otherwise, the <em>TSIH</em> sent
	 * by the target at the conclusion of the successful login of the first
	 * connection for this session MUST be used. The <em>TSIH</em> identifies to
	 * the target the associated existing session for this new connection.
	 * <p>
	 * All Login Requests within a Login Phase MUST carry the same <em>TSIH</em>.
	 * <p>
	 * The target MUST check the value presented with the first Login Request and act as specified in Section
	 * 5.3.1 Login Phase Start.
	 *
	 * @return Returns the Target Session Identifying Handle of this
	 * LoginRequestParser object.
	 */
	short getTargetSessionIdentifyingHandle() {

		return targetSessionIdentifyingHandle;
	}

	// --------------------------------------------------------------------------
	// --------------------------------------------------------------------------

	/**
	 * Sets the new Connection ID of this LoginRequestParser object.
	 *
	 * @param initCID
	 * The new Connection ID.
	 * @see #getConnectionID()
	 */
	void setConnectionID(int initCID) {

		connectionID = initCID;
	}

	/**
	 * Sets the new state of the <em>Continue Flag</em> of this LoginRequestParser obejct.
	 *
	 * @param initContinueFlag
	 * The new state of the Continue Flag.
	 * @see #isContinueFlag()
	 */
	void setContinueFlag(bool initContinueFlag) {

		continueFlag = initContinueFlag;
	}

	/**
	 * Sets the new <em>Current Stage Number</em> of this LoginRequestParser object.
	 *
	 * @param initCSG
	 * The new Current Stage Number.
	 * @see #getCurrentStageNumber()
	 */
	void setCurrentStageNumber(int initCSG) {

		currentStageNumber = initCSG;
	}

	/**
	 * Sets the new <em>Initiator Session ID (ISID)</em> of this LoginRequestParser object.
	 *
	 * @param initISID
	 * The new Initiator Session ID (ISID).
	 */
	void setInitiatorSessionID(ISID initISID) {

		initiatorSessionID = initISID;
	}

	/**
	 * Sets the new <em>Maximum Version number</em> of this LoginRequestParser object.
	 *
	 * @param initMaxVersion
	 * The new Maximum Version.
	 * @see #getMaxVersion
	 */
	void setMaxVersion(byte initMaxVersion) {

		maxVersion = initMaxVersion;
	}

	/**
	 * Sets the new <em>Minimum Version number</em> of this LoginRequestParser object.
	 *
	 * @param initMinVersion
	 * The new Minimum Version.
	 * @see #getMinVersion
	 */
	inline void setMinVersion(byte initMinVersion) {

		minVersion = initMinVersion;
	}

	/**
	 * Sets the new <em>Next Stage Number</em> of this LoginRequestParser object.
	 *
	 * @param initNSG
	 * The new Next Stage Number.
	 * @see #getNextStageNumber()
	 */
	inline void setNextStageNumber(int initNSG) {

		nextStageNumber = initNSG;
	}

	/**
	 * Sets the new <em>Target Session Identifying Handle</em> of this LoginRequestParser object.
	 *
	 * @param initTSIH
	 * The new Target Session Identifying Handle.
	 */
	inline void setTargetSessionIdentifyingHandle(short initTSIH) {

		targetSessionIdentifyingHandle = initTSIH;
	}

protected:
	void deserializeBytes1to3(int line);

	void deserializeBytes12to15(int line);

	void deserializeBytes20to23(int line);

	void checkIntegrity();

	int serializeBytes1to3();

	int serializeBytes8to11();

	int serializeBytes12to15();

	int serializeBytes20to23();
};

#endif // __LOGINREQUESTPARSER_H__
