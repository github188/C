// ProtocolDataUnitFactory.h

#ifndef __PROTOCOLDATAUNITFACTORY_H__
#define __PROTOCOLDATAUNITFACTORY_H__

#include <string>
using namespace std;

#if 0
package org.jscsi.parser;

import org.jscsi.parser.digest.DigestFactory;
#endif

/**
 * <h1>ProtocolDataUnitFactory</h1>
 * <p/>
 * A factory to create all supported the <code>ProtocolDataUnit</code> instances.
 * 
 * @author Volker Wildi
 */
class DigestFactory;
class ProtocolDataUnit;
class ProtocolDataUnitFactory {

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

private:
    /** The factory to create the supported digests. */
    DigestFactory digestFactory = new DigestFactory();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

public:
    /**
     * Default constructor to create a new, empty <code>ProtocolDataUnitFactory</code> instance.
     */
    ProtocolDataUnitFactory();

    /**
     * This method creates a <code>ProtocolDataUnit</code> instance, which
     * initializes only the digests to use, and returns it.
     * 
     * @param headerDigest
     *            The name of the digest to use for the protection of the Basic
     *            Header Segment.
     * @param dataDigest
     *            The name of the digest to use for the protection of the Data
     *            Segment.
     * @return A new <code>ProtocolDataUnit</code> instance.
     */
    ProtocolDataUnit create(string headerDigest, string dataDigest);

    /**
     * This method creates a <code>ProtocolDataUnit</code> instance, which is
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
     * @return A new <code>ProtocolDataUnit</code> instance.
     */
    ProtocolDataUnit create(bool immediateFlag, bool finalFlag,
        OperationCode operationCode, string headerDigest, string dataDigest);
};

#endif // __PROTOCOLDATAUNITFACTORY_H__
