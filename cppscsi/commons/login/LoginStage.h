// LoginStage.h

#ifndef __LOGINSTAGE_H__
#define __LOGINSTAGE_H__

enum LoginStage {
	/** The Security Negotiation Flag. */
    SECURITY_NEGOTIATION = 0,

    /** The Login Operational Negotiation Flag. */
    LOGIN_OPERATIONAL_NEGOTIATION = 1,

    /** The Full Feature Phase Flag. */
    FULL_FEATURE_PHASE = 3,	
};

#endif // __LOGINSTAGE_H__
