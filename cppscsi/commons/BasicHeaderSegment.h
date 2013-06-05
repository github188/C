#ifndef __BASICHEADERSEGMENT_H__
#define __BASICHEADERSEGMENT_H__

#include "ByteBuffer.h"
#include <string>
using namespace std;

typedef int OperationCode;
typedef unsigned char byte;
typedef char* Object;

class AbstractMessageParser;
class ProtocolDataUnit;
class BasicHeaderSegment {

public:

    /** The BHS has a fixed size of 48 bytes. */
    const static int BHS_FIXED_SIZE = 48;

    /** Offset of the byte 8 till 11 in the BHS. */
    const static int BYTES_8_11 = 8;

    /** Offset of the byte 16 till 19 in the BHS. */
    const static int BYTES_16_19 = 16;

    /** Offset of the byte 20 till 23 in the BHS. */
    const static int BYTES_20_23 = 20;


private:
    /** Bit mask to extract the immediate flag of a 32 bit number. */
    const static int IMMEDIATE_FLAG_MASK = 0x40000000;

    /** Bit mask to extract the operation code of a 32 bit number. */
    const static int OPERATION_CODE_MASK = 0x3F000000;

    /** Bit mask to extract the flag of a 32 bit number. */
    const static int FINAL_FLAG_MASK = 0x00800000;

public:
    /**
     * For request PDUs, the I bit set to 1 is an
     * immediate delivery marker.
     */
    bool immediateFlag;

    /**
     * The operation code indicates the type of iSCSI PDU the header
     * encapsulates. The operation codes are divided into two categories: initiator opcodes and
     * target opcodes. Initiator opcodes
     * are in PDUs sent by the initiator (request PDUs). Target opcodes are in
     * PDUs sent by the target (response PDUs).
     * Initiators MUST NOT use target opcodes and targets MUST NOT use initiator opcodes.
     */
    int operationCode;

    /**
     * When set to 1 it indicates the (or only) PDU of a
     * sequence.
     */
    bool finalFlag;

    /**
     * Total length of all AHS header segments in units of four byte words including padding, if
     * any.
     * The TotalAHSLength is only used in PDUs that have an AHS and MUST be 0 in all
     * other PDUs.
     */
    char totalAHSLength;

    /**
     * This is the data segment payload length in bytes (excluding padding). The
     * DataSegmentLength MUST be 0 whenever the PDU has no data
     * segment.
     */
    int dataSegmentLength;

    /**
     * The initiator assigns a Task Tag to each iSCSI task it issues. While a
     * task exists, this tag MUST uniquely identify the task session-wide. SCSI
     * may also use the initiator task tag as part of the SCSI task identifier
     * when the timespan during which an iSCSI initiator task tag must be unique
     * extends over the timespan during which a SCSI task tag must be unique.
     * However, the iSCSI Initiator Task Tag must exist and be unique even for
     * untagged SCSI commands.
     */
    int initiatorTaskTag;

    /** The used parser for the messages. */
    AbstractMessageParser *m_pMessageParser;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /** Default constructor, creates new, empty BasicHeaderSegment object. */
    BasicHeaderSegment();

	~BasicHeaderSegment();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * This method serializes the informations of this BHS object to the byte
     * representation defined by the iSCSI Standard.
     * 
     * @param dst
     *            The destination array to write in.
     * @param offset
     *            The start offset in dst.
     * @return The length (in bytes) of the serialized form of this BHS object.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    int serialize(ByteBuffer dst, int offset);

    /**
     * Extract from the given Protocol Data Unit the BHS. After an successful
     * extraction this methods and setreturns the right message parser object
     * for this kind of message.
     * 
     * @param protocolDataUnit
     *            The reference ProtocolDataUnit instance, which
     *            contains this BasicHeaderSegment object.
     * @param src
     *            The bytes representation of a Protocol Data Unit.
     * @return The length (in bytes), which are read from pdu.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    int deserialize(ProtocolDataUnit protocolDataUnit, ByteBuffer src);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * The Length of the Data Segment.
     * 
     * @return length of the data segment
     */
    int getDataSegmentLength();

    /**
     * When this flag is set it indicates the (or only) PDU of a sequence.
     * In some kinds of messages (PDU) this methods has the meaning of the TransitFlag.
     * 
     * @return The state of the flag.
     */
    bool isFinalFlag();

    /**
     * For request PDUs, the immediate flag can be set as an immediate delivery
     * marker.
     * 
     * @return The state of the immediate flag.
     */
    bool isImmediateFlag();

    /**
     * The initiator assigns a Task Tag to each iSCSI task it issues. While a
     * task exists, this tag MUST uniquely identify the task session-wide. SCSI
     * may also use the initiator task tag as part of the SCSI task identifier
     * when the timespan during which an iSCSI initiator task tag must be unique
     * extends over the timespan during which a SCSI task tag must be unique.
     * However, the iSCSI Initiator Task Tag must exist and be unique even for
     * untagged SCSI commands.
     * 
     * @return the initiator task tag.
     */
    int getInitiatorTaskTag();

    /**
     * The length of the Additional Header Segment.
     * 
     * @return The length of the contained AHSs
     */
    char getTotalAHSLength();

    /**
     * Returns the operation code, which is used in this BHS.
     * 
     * @return The operation code of this BHS.
     */
    //OperationCode getOpCode();

    /**
     * Returns a object of the used parser of this BHS.
     * 
     * @return The parser object to use for this PDU.
     */
    AbstractMessageParser getParser();

    /**
     * Set a new length for the data segment.
     * 
     * @param initDataSegmentLength
     *            The new length of this BasicHeaderSegment object.
     */
    void setDataSegmentLength(int initDataSegmentLength);

    /**
     * Changes the state of the flag.
     * 
     * @param initFinalFlag
     *            The new state of the flag.
     */
    void setFinal(bool initFinalFlag);

    /**
     * Changes the state of the immediate flag.
     * 
     * @param initImmediateFlag
     *            The new state of the immediate flag.
     */
    void setImmediate(bool initImmediateFlag);

    /**
     * Changes the value of the initiator task tag.
     * 
     * @param initInitiatorTaskTag
     *            The new value of the initiator task tag.
     */
    void setInitiatorTaskTag(int initInitiatorTaskTag);

    /**
     * This sets the length (in units of four bytes) of the total length of the
     * given AHS.
     * 
     * @param initTotalAHSLength
     *            The new length.
     */
    void setTotalAHSLength(byte initTotalAHSLength);

    /**
     * Set a new operation code for this BHS object.
     * 
     * @param protocolDataUnit
     *            The reference ProtocolDataUnit instance, which
     *            contains this BasicHeaderSegment object.
     * @param initOperationCode
     *            The new operation code.
     */
    void setOperationCode(ProtocolDataUnit protocolDataUnit, OperationCode initOperationCode);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Creates a string object with all values for easy debugging.
     * 
     * @return The string with all informations of this BHS.
     */
    string toString();

    /** {@inheritDoc} */
    bool equals(Object o);

    /**
     * Clears all the stored content of this BasicHeaderSegment object.
     */
    void clear();
};

#endif //__BASICHEADERSEGMENT_H__ 

