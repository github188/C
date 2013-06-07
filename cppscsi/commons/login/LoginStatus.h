// LoginStatus.h

#ifndef __LOGINSTATUS_H__
#define __LOGINSTATUS_H__

enum _LoginStatus {
	SUCCESS = 0x0000,

	/**
	 * The requested iSCSI Target Name (ITN) has temporarily moved to the
	 * address provided.
	 */
	TARGET_MOVED_TEMPORARILY = 0x0101,

	/**
	 * The requested ITN has permanently moved permanently to the address
	 * provided.
	 */
	TARGET_MOVED = 0x0102,

	/**
	 * Miscellaneous iSCSI initiator errors.
	 */
	INITIATOR_ERROR = 0x0200,

	/**
	 * The initiator could not be successfully authenticated or target
	 * authentication is not supported.
	 */
	AUTHENTICATION_FAILURE = 0x0201,

	/**
	 * The initiator is not allowed access to the given target.
	 */
	AUTHORIZATION_FAILURE = 0x0202,

	/**
	 * The requested ITN does not exist at this address.
	 */
	NOT_FOUND = 0x0203,

	/**
	 * The requested ITN has been removed and no forwarding address is provided.
	 */
	TARGET_REMOVED = 0x0204,

	/**
	 * The requested iSCSI version range is not supported by the target.
	 */
	UNSUPPORTED_VERSION = 0x0205,

	/**
	 * Too many connections on this SSID.
	 */
	TOO_MANY_CONNECTIONS = 0x0206,

	/**
	 * Missing parameters (e.g., iSCSI Initiator and/or Target Name).
	 */
	MISSING_PARAMETER = 0x0207,

	/**
	 * Target does not support session spanning to this connection (address).
	 */
	CANNOT_INCLUDE_IN_SESSION = 0x0208,

	/**
	 * Target does not support this type of of session or not from this
	 * Initiator.
	 */
	SESSION_TYPE_NOT_SUPPORTED = 0x0209,

	/**
	 * Attempt to add a connection to a non-existent session.
	 */
	SESSION_DOSE_NOT_EXIST = 0x020A,

	/**
	 * Invalid Request type during Login.
	 */
	INVALID_DURING_LOGIN = 0x020B,

	/**
	 * Target hardware or software error.
	 */
	TARGET_ERROR = 0x0300,

	/**
	 * The iSCSI service or target is not currently operational.
	 */
	SERVICE_UNAVAILABLE = 0x0301,

	/**
	 * The target has insufficient session, connection, or other resources.
	 */
	OUT_OF_RESOURCES = 0x0302,
} LoginStatus;

#endif // __LOGINSTATUS_H__
