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
     * The <b>read-only</b> reference to the <code>ProtocolDataUnit</code> instance, which contains this
     * <code>AbstractMessageParser</code> type.
     */
     ProtocolDataUnit *m_protocolDataUnit;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Some opcodes operate on a specific Logical Unit. The Logical Unit Number
     * (LUN) field identifies which Logical Unit. If the opcode does not relate
     * to a Logical Unit, this field is either ignored or may be used in an
     * opcode specific way. The LUN field is 64-bits and should be formatted in
     * accordance with [SAM2]. For example, LUN[0] from [SAM2] is BHS byte <code>8</code> and so on up to
     * LUN[7] from [SAM2], which is BHS byte <code>15</code>.
     */
    long logicalUnitNumber;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Default Contructor to create a new, empty AbstractMessageParser object.
     * 
     * @param initProtocolDataUnit
     *            The reference <code>ProtocolDataUnit</code> instance, which
     *            contains this <code>AbstractMessageParser</code> object.
     */
    AbstractMessageParser(ProtocolDataUnit initProtocolDataUnit) {

        protocolDataUnit = initProtocolDataUnit;
    }

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

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
     *            The destination <code>ByteBuffer</code> to write to.
     * @param offset
     *            The start offset in <code>dst</code>.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void serializeBasicHeaderSegment(ByteBuffer dst, int offset);

public:
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * If this method returns <code>true</code>, hen it indicates that the data
     * segment data is interpreted as binary data. Else the data segment data
     * must be interpreted as Text Format.
     * 
     * @return Returns a format defined by the DataSegmentFormat enumeration.
     * @see DataSegmentFormat
     */
    DataSegmentFormat getDataSegmentFormat() = 0;

    /**
     * If this method returns <code>true</code>, it indicates that this derived
     * AbstractMessageParser can contain one or more Additional Header Segments.
     * 
     * @return Returns <code>true</code>, if this AbstractMessageParser object
     *         can contain one or more AHSs.
     * @see AdditionalHeaderSegment
     */
    inline bool canContainAdditionalHeaderSegments() {

        return false;
    }

    /**
     * If this method returns <code>true</code>, then it indicates that this
     * derived <code>AbstractMessageParser</code> instance can be by a
     * digest.
     * 
     * @return <code>true</code>, if the ProtocolDataUnit can be by a
     *         header and/or a data digest. Else <code>false</code>.
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
     * This <code>AbstractMessageParser</code> instance affects the
     * incrementation of a <code>Sequence Number</code> counter.
     * 
     * @return <code>true</code>, if the counter has to be incremented.
     */
    virtual bool incrementSequenceNumber() = 0;

    /**
     * Returns the Logical Unit Number (LUN) of this <code>AbstractMessageParser</code> object.
     * 
     * @return The Logical Unit Number of this object.
     */
    inline long getLogicalUnitNumber() {

        return logicalUnitNumber;
    }

    /**
     * Set the Logical Unit Number (LUN) of this <code>AbstractMessageParser</code> object.
     * 
     * @param logicalUnitNumber
     *            The Logical Unit Number of this object.
     */
    void setLogicalUnitNumber(long logicalUnitNumber);

protected:
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Parse the bytes <code>1</code> till <code>3</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes1to3(int line) = 0;

    /**
     * Parse the bytes <code>8</code> till <code>11</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserializeBytes8to11(int line);

    /**
     * Parse the bytes <code>12</code> till <code>15</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserializeBytes12to15(int line);

    /**
     * Parse the bytes <code>20</code> till <code>23</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes20to23(int line) = 0;

    /**
     * Parse the bytes <code>24</code> till <code>27</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes24to27(int line) = 0;

    /**
     * Parse the bytes <code>28</code> till <code>31</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes28to31(int line) = 0;

    /**
     * Parse the bytes <code>32</code> till <code>35</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes32to35(int line) = 0;

    /**
     * Parse the bytes <code>36</code> till <code>39</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes36to39(int line) = 0;

    /**
     * Parse the bytes <code>40</code> till <code>43</code> in the Basic Header
     * Segment.
     * 
     * @param line
     *            The actual line
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    virtual void deserializeBytes40to43(int line) = 0;

    /**
     * Parse the bytes <code>44</code> till <code>47</code> in the Basic Header
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
     * Serializes the bytes <code>1</code> till <code>3</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes1to3() = 0;

    /**
     * Serializes the bytes <code>8</code> till <code>11</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     * @throws InternetSCSIException
     *             if any violation of the iSCSI Standard (RFC3720) occurs.
     */
    int serializeBytes8to11();

    /**
     * Serializes the bytes <code>12</code> till <code>15</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    int serializeBytes12to15();

    /**
     * Serializes the bytes <code>20</code> till <code>23</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    int serializeBytes20to23() = 0;

    /**
     * Serializes the bytes <code>24</code> till <code>27</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes24to27() = 0;

    /**
     * Serializes the bytes <code>28</code> till <code>31</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes28to31() = 0;

    /**
     * Serializes the bytes <code>32</code> till <code>35</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes32to35() = 0;

    /**
     * Serializes the bytes <code>36</code> till <code>39</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes36to39() = 0;

    /**
     * Serializes the bytes <code>40</code> till <code>43</code> in the Basic
     * Header Segment.
     * 
     * @return The serialized byte representation.
     */
    virtual int serializeBytes40to43() = 0;

    /**
     * Serializes the bytes <code>44</code> till <code>47</code> in the Basic
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
