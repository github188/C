// AbstractMessageParser.h
#ifndef __ABSTRACTMESSAGEPARSER_H__
#define __ABSTRACTMESSAGEPARSER_H__

#include <string>
using namespace std;

#include "ByteBuffer.h"
#include "common.h"

/**
 * AbstractMessageParser
 * Abstract class from which each parser (initiator or target message parser) 
 * for a specific Protocol Data Unit (PDU) is inherited. The version of iSCSI 
 * Protocol is the RFC3720.
 */
class ProtocolDataUnit;
class AbstractMessageParser {

private:
    /** Bit mask to extract the first operation code specific field. */
    const static int FIRST_SPECIFIC_FIELD_MASK = 0x007FFFFF;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

protected:
    /**
     * The read-only reference to the ProtocolDataUnit instance, which contains this
     * AbstractMessageParser type.
     */
     ProtocolDataUnit *m_protocolDataUnit;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Some opcodes operate on a specific Logical Unit. The Logical Unit Number
     * (LUN) field identifies which Logical Unit. If the opcode does not relate
     * to a Logical Unit, this field is either ignored or may be used in an
     * opcode specific way. The LUN field is 64-bits and should be formatted in
     * accordance with [SAM2]. For example, LUN[0] from [SAM2] is BHS byte 8 and so on up to
     * LUN[7] from [SAM2], which is BHS byte 15.
     */
    long logicalUnitNumber;

    /**
     * Default Contructor to create a new, empty AbstractMessageParser object.
     * 
     * @param initProtocolDataUnit
     *            The reference ProtocolDataUnit instance, which
     *            contains this AbstractMessageParser object.
     */
    AbstractMessageParser(ProtocolDataUnit *pInitProtocolDataUnit);

    /**
     * This method defines the order of the parsing process of the operation
     * code specific fields and check their integtity.
     * 
     * @param pdu
     *            Array which contains the total Protocol Data Unit.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserializeBasicHeaderSegment(ByteBuffer pdu);

    /**
     * This method serializes the whole BHS to its byte representation.
     * 
     * @param dst
     *            The destination ByteBuffer to write to.
     * @param offset
     *            The start offset in dst.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void serializeBasicHeaderSegment(ByteBuffer dst, int offset);

public:
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * If this method returns true, hen it indicates that the data
     * segment data is interpreted as binary data. Else the data segment data
     * must be interpreted as Text Format.
     * 
     * @return Returns a format defined by the DataSegmentFormat enumeration.
     * @see DataSegmentFormat
     */
    virtual int getDataSegmentFormat() = 0;

    /**
     * If this method returns true, it indicates that this derived
     * AbstractMessageParser can contain one or more Additional Header Segments.
     * 
     * @return Returns true, if this AbstractMessageParser object
     *         can contain one or more AHSs.
     * @see AdditionalHeaderSegment
     */
    inline bool canContainAdditionalHeaderSegments() {

        return false;
    }

    /**
     * If this method returns true, then it indicates that this
     * derived AbstractMessageParser instance can be by a
     * digest.
     * 
     * @return true, if the ProtocolDataUnit can be by a
     *         header and/or a data digest. Else false.
     */
    inline bool canHaveDigests() {

        return true;
    }

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Returns the short version of the used sequence numbers of this parser
     * instance.
     * 
     * @return The string with all needed sequence numbers.
     */
    virtual string getShortInfo() = 0;

    /**
     * This method concatenate all the fields of a derived parser to allow an
     * easy generation of debug informations.
     * 
     * @return The debug formatted string.
     */
    string toString();

    /**
     * This method sets all settings to their initial values.
     */
    inline void clear() {

        logicalUnitNumber = 0x0000000000000000L;
    }

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * This AbstractMessageParser instance affects the
     * incrementation of a Sequence Number counter.
     * 
     * @return true, if the counter has to be incremented.
     */
    virtual bool incrementSequenceNumber() = 0;

    /**
     * Returns the Logical Unit Number (LUN) of this AbstractMessageParser object.
     * 
     * @return The Logical Unit Number of this object.
     */
    inline long getLogicalUnitNumber() {

        return logicalUnitNumber;
    }

    /**
     * Set the Logical Unit Number (LUN) of this AbstractMessageParser object.
     * 
     * @param logicalUnitNumber
     *            The Logical Unit Number of this object.
     */
    void setLogicalUnitNumber(long logicalUnitNumber);

protected:
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Parse the bytes 1 till 3 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes1to3(int line) = 0;

    /**
     * Parse the bytes 8 till 11 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserializeBytes8to11(int line);

    /**
     * Parse the bytes 12 till 15 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserializeBytes12to15(int line);

    /**
     * Parse the bytes 20 till 23 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes20to23(int line) = 0;

    /**
     * Parse the bytes 24 till 27 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes24to27(int line) = 0;

    /**
     * Parse the bytes 28 till 31 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes28to31(int line) = 0;

    /**
     * Parse the bytes 32 till 35 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes32to35(int line) = 0;

    /**
     * Parse the bytes 36 till 39 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes36to39(int line) = 0;

    /**
     * Parse the bytes 40 till 43 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes40to43(int line) = 0;

    /**
     * Parse the bytes 44 till 47 in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes44to47(int line) = 0;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Serializes the bytes 1 till 3 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes1to3() = 0;

    /**
     * Serializes the bytes 8 till 11 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     * @throws InternetSCSIException
     *             if any violation of the iSCSI Standard (RFC3720) occurs.
     */
    int serializeBytes8to11();

    /**
     * Serializes the bytes 12 till 15 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    int serializeBytes12to15();

    /**
     * Serializes the bytes 20 till 23 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes20to23() = 0;

    /**
     * Serializes the bytes 24 till 27 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes24to27() = 0;

    /**
     * Serializes the bytes 28 till 31 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes28to31() = 0;

    /**
     * Serializes the bytes 32 till 35 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes32to35() = 0;

    /**
     * Serializes the bytes 36 till 39 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes36to39() = 0;

    /**
     * Serializes the bytes 40 till 43 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes40to43() = 0;

    /**
     * Serializes the bytes 44 till 47 in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes44to47() = 0;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * This method checks, if all parsed fields are valid. Because there are
     * several fields, which are reserved for future versions, and these must be
     * zero. Is this the case an exception will be thrown.
     * 
     * @throws InternetSCSIException
     *             If the integrity is violated.
     */
    virtual void checkIntegrity() = 0;

};

#endif // __ABSTRACTMESSAGEPARSER_H__
