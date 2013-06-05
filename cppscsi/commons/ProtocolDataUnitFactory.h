// ProtocolDataUnitFactory.h

#ifndef __PROTOCOLDATAUNITFACTORY_H__
#define __PROTOCOLDATAUNITFACTORY_H__

#include <string>
using namespace std;
#include "DigestFactory.h"
#include "OperationCode.h"

/**
 * ProtocolDataUnitFactory
 * A factory to create all supported the ProtocolDataUnit instances.
 */
class ProtocolDataUnit;
class ProtocolDataUnitFactory {

private:
    /** The factory to create the supported digests. */
    DigestFactory m_DigestFactory;
	ProtocolDataUnit *m_pProtocolDataUnit;

public:
    /**
     * Default constructor to create a new, empty ProtocolDataUnitFactory instance.
     */
    ProtocolDataUnitFactory();
    ~ProtocolDataUnitFactory();

    /**
     * This method creates a ProtocolDataUnit instance, which
     * initializes only the digests to use, and returns it.
     * 
     * @param headerDigest
     *            The name of the digest to use for the protection of the Basic
     *            Header Segment.
     * @param dataDigest
     *            The name of the digest to use for the protection of the Data
     *            Segment.
     * @return A new ProtocolDataUnit instance.
     */
    ProtocolDataUnit* create(const string &headerDigest, const string &dataDigest);

    /**
     * This method creates a ProtocolDataUnit instance, which is
     * initialized with the given settings, and returns it.
     * 
     * @param immediateFlag
     *            Should this PDU send immediately?
     * @param operationCode
     *            The Operation Code of this PDU.
     * @param finalFlag
     *            Is this PDU the last one in a sequence?
     * @param headerDigest
     *            The name of the digest to use for the protection of the Basic
     *            Header Segment.
     * @param dataDigest
     *            The name of the digest to use for the protection of the Data
     *            Segment.
     * @return A new ProtocolDataUnit instance.
     */
    ProtocolDataUnit* create(bool immediateFlag, bool finalFlag,
        int operationCode, const string &headerDigest, const string &dataDigest);

    ProtocolDataUnit* GetProtocolDataUnitPtr();
};

#endif // __PROTOCOLDATAUNITFACTORY_H__
