// LoginResponseParser.h
#ifndef __LOGINRESPONSEPARSER_H__
#define __LOGINRESPONSEPARSER_H__

#include <string>
#include "TargetMessageParser.h"
#include "LoginStatus.h"
#include "LoginStage.h"
#include "Constants.h"
#include "ISID.h"

class LoginResponseParser : public TargetMessageParser {
private:
    /** The Continue Flag. */
    bool continueFlag;

    /**
     * The Status returned in a Login Response indicates the execution status of
     * the Login Phase. The status includes:
     * <ul>
     * <li>Status-Class</li>
     * <li>Status-Detail</li>
     * </ul>
     * <p>
     * <code>0</code> Status-Class indicates success.
     * <p>
     * A non-zero Status-Class indicates an exception. In this case, Status-Class is sufficient for a simple
     * initiator to use when handling exceptions, without having to look at the Status-Detail. The
     * Status-Detail allows finer-grained exception handling for more sophisticated initiators and for better
     * information for logging.
     * <p>
     * If the Status Class is not <code>0</code>, the initiator and target MUST close the TCP connection.
     * <p>
     * If the target wishes to reject the Login Request for more than one reason, it should return the primary
     * reason for the rejection.
     * 
     * @see LoginStatus
     */
    LoginStatus status;

    /** Current stage. */
    LoginStage currentStageNumber;

    /** Next stage. */
    LoginStage nextStageNumber;

    /** The maximum version. */
    int maxVersion;

    /** The active version. */
    int activeVersion;

    /** Initiator Session ID (ISID). */
    ISID initiatorSessionID;

    /** Target Session Identifying Handle (TSIH). */
    short targetSessionIdentifyingHandle;

public:
    /**
     * Default constructor, creates a new, empty <code>LoginResponseParser</code> object.
     * 
     * @param initProtocolDataUnit
     *            The reference <code>ProtocolDataUnit</code> instance, which
     *            contains this <code>LoginResponseParser</code> subclass
     *            object.
     */
    LoginResponseParser();
    LoginResponseParser(ProtocolDataUnit *pInitProtocolDataUnit);

    std::string toString();

    void clear();

    DataSegmentFormat getDataSegmentFormat();

    bool canHaveDigests();

    /**
     * The Status returned in a Login Response indicates the execution status of
     * the Login Phase. The status includes:
     * <ul>
     * <li>Status-Class</li>
     * <li>Status-Detail</li>
     * </ul>
     * <p>
     * <code>0</code> Status-Class indicates success.
     * <p>
     * A non-zero Status-Class indicates an exception. In this case, Status-Class is sufficient for a simple
     * initiator to use when handling exceptions, without having to look at the Status-Detail. The
     * Status-Detail allows finer-grained exception handling for more sophisticated initiators and for better
     * information for logging.
     * 
     * @return The status of this LoginResponseParser object.
     */
    LoginStatus getStatus();

    /**
     * When set to <code>1</code>, indicates that the text (set of key=value
     * pairs) in this Login Response is not complete (it will be continued on
     * subsequent Login Responses); otherwise, it indicates that this Login
     * Response ends a set of key=value pairs. A Login Response with the <code>C</code> bit set to
     * <code>1</code> MUST have the <code>T</code> bit
     * set to <code>0</code>.
     * 
     * @return The status of the Continue Flag of this <code>LoginResponseParser</code> object.
     */
    bool isContinueFlag();

    /**
     * Returns the <em>Current Stage Number</em> of this Login Response Message.
     * 
     * @return Number of the Current Stage.
     * @see org.jscsi.parser.login.LoginStage
     */
    LoginStage getCurrentStageNumber();

    /**
     * Returns the Initiator Session ID (ISID) of this LoginResponseParser
     * object.
     * 
     * @return Returns the Initiator Session ID (ISID) of this
     *         LoginResponseParser object.
     * @see ISID
     */
    ISID getInitiatorSessionID();

    /**
     * This is the highest version number supported by the target.
     * <p>
     * All Login Responses within the Login Phase MUST carry the same Version-max.
     * <p>
     * The initiator MUST use the value presented as a response to the first Login Request.
     * 
     * @return The maximum version of this login request message.
     */
    int getMaxVersion();

    /**
     * Indicates the highest version supported by the target and initiator.
     * <p>
     * If the target does not support a version within the range specified by the initiator, the target
     * rejects the login and this field indicates the lowest version supported by the target.
     * <p>
     * All Login Responses within the Login Phase MUST carry the same Version-active.
     * <p>
     * The initiator MUST use the value presented as a response to the first Login Request.
     * 
     * @return The active version of this <code>LoginResponseParser</code> object.
     */
    int getActiveVersion();

    /**
     * Returns the <em> Next Stage Number</em> of this Login Response Message.
     * 
     * @return The Number of the Next Stage.
     * @see org.jscsi.parser.login.LoginStage
     */
    LoginStage getNextStageNumber();

    /**
     * The TSIH is the target assigned session identifying handle. Its internal
     * format and content are not defined by this protocol except for the value <code>0</code> that is
     * reserved. With the exception of the Login
     * Final-Response in a new session, this field should be set to the TSIH
     * provided by the initiator in the Login Request. For a new session, the
     * target MUST generate a non-zero TSIH and ONLY return it in the Login
     * Final-Response (see Section 5.3 Login Phase).
     * 
     * @return Returns the Target Session Identifying Handle of this <code>LoginResponseParser</code> object.
     */
    short getTargetSessionIdentifyingHandle();
    void setStatus(LoginStatus status);
    void setContinueFlag(bool continueFlag);
    void setCurrentStageNumber(LoginStage currentStage);
    void setNextStageNumber(LoginStage nextStage);
    void setInitiatorSessionID(ISID initiatorSessionID);
    void setTargetSessionIdentifyingHandle(short targetSessionIdentifyingHandle);

protected:
    void deserializeBytes1to3(int line);
    void deserializeBytes12to15(int line);
    void deserializeBytes36to39(int line);
    void checkIntegrity();
    int serializeBytes1to3();
    int serializeBytes36to39();
};

#endif // __LOGINRESPONSEPARSER_H__
