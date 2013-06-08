// ProtocolDataUnit.h

#ifndef __PROTOCOLDATAUNIT_H__
#define __PROTOCOLDATAUNIT_H__

#include <string>
#include <vector>
using namespace std;
#include "IDigest.h"
#include "ByteBuffer.h"
#include "AdditionalHeaderSegment.h"

/**
 * ProtocolDataUnit
 * This class encapsulates a Protocol Data Unit (PDU), which is defined in the 
 * iSCSI Standard (RFC 3720).
 */
class BasicHeaderSegment;
class AdditionalHeaderSegment;
class ProtocolDataUnit {

private:

    /** The initial size of the Additional Header Segment. */
    int AHS_INITIAL_SIZE;

    /** The Log interface. */
    //static Logger LOGGER = LoggerFactory.getLogger(ProtocolDataUnit.class);

    /** The Basic Header Segment of this PDU. */
    BasicHeaderSegment *m_pBasicHeaderSegment;

    /** The Additional Header Segment 1...n (optional) of this PDU. */
    vector<AdditionalHeaderSegment> additionalHeaderSegments;

    /**
     * The (optional) Data Segment contains PDU associated data. Its payload
     * effective length is provided in the BHS field - DataSegmentLength. The Data Segment is
     * also padded to
     * multiple of a 4 byte words.
     */
    ByteBuffer dataSegment;

    /**
     * Optional header and data digests protect the integrity of the header and
     * data, respectively. The digests, if present, are located, respectively,
     * after the header and PDU-specific data, and cover respectively the header
     * and the PDU data, each including the padding bytes, if any.
     * The existence and type of digests are negotiated during the Login Phase.
     * The separation of the header and data digests is useful in iSCSI routing applications, in which only
     * the header changes when a message is forwarded. In this case, only the header digest should be
     * recalculated.
     * Digests are not included in data or header length fields.
     * A zero-length Data Segment also implies a zero-length data-digest.
     */

    /** Digest of the header of this PDU. */
    IDigest headerDigest;

    /** Digest of the data segment of this PDU. */
    IDigest dataDigest;

public: 
    /**
     * Default constructor, creates a new, empty ProtcolDataUnit object.
     * 
     * @param initHeaderDigest
     *            The instance of the digest to use for the Basic Header Segment
     *            protection.
     * @param initDataDigest
     *            The instance of the digest to use for the Data Segment
     *            protection.
     */
    ProtocolDataUnit();
    ProtocolDataUnit(IDigest initHeaderDigest, IDigest initDataDigest);

    /**
     * Serialize all informations of this PDU object to its byte representation.
     * 
     * @return The byte representation of this PDU.
     */
    ByteBuffer serialize();

    /**
     * Deserializes (parses) a given byte representation of a PDU to an PDU
     * object.
     * 
     * @param pdu
     *            The byte representation of an PDU to parse.
     * @return The number of bytes, which are serialized.
     */
    int deserialize(ByteBuffer pdu);

private:
    /**
     * Deserializes a given array starting from offset 0 and store
     * the informations in the BasicHeaderSegment object..
     * 
     * @param bhs
     *            The array to read from.
     */
    int deserializeBasicHeaderSegment(ByteBuffer bhs);

    /**
     * Deserializes a array (starting from offset 0) and store the
     * informations to the AdditionalHeaderSegment object.
     * 
     * @param pdu
     *            The array to read from.
     * @return The length of the read bytes.
     */
    int deserializeAdditionalHeaderSegments(ByteBuffer pdu);

    /**
     * Deserializes a array (starting from the given offset) and store the
     * informations to the AdditionalHeaderSegment object.
     * 
     * @param pdu
     *            The ByteBuffer to read from.
     * @param offset
     *            The offset to start from.
     * @return The length of the written bytes.
     */
    int deserializeAdditionalHeaderSegments(ByteBuffer pdu, int offset);

    /**
     * Serialize all the contained additional header segments to the destination
     * array starting from the given offset.
     * 
     * @param dst
     *            The destination array to write in.
     * @param offset
     *            The offset to start to write in dst.
     * @return The written length.
     */
    int serializeAdditionalHeaderSegments(ByteBuffer dst, int offset);

    /**
     * Deserializes a array (starting from the given offset) and store the
     * informations to the Data Segment.
     * 
     * @param pdu
     *            The array to read from.
     * @param offset
     *            The offset to start from.
     * @return The length of the written bytes.
     * @throws IOException
     *             if an I/O error occurs.
     */
    int deserializeDataSegment(ByteBuffer pdu, int offset);

public:
    /**
     * Serializes the data segment (binary or key-value pairs) to a destination
     * array, staring from offset to write.
     * 
     * @param dst
     *            The array to write in.
     * @param offset
     *            The start offset to start from in dst.
     * @return The written length.
     */
    int serializeDataSegment(ByteBuffer dst, int offset);

public:
    /**
     * Writes this ProtocolDataUnit object to the given SocketChannel.
     * 
     * @param sChannel
     *            SocketChannel to write to.
     * @return The number of bytes written, possibly zero.
     */
    int write(/*SocketChannel sChannel*/);

    /**
     * Reads from the given SocketChannel all the neccassary bytes
     * to fill this PDU.
     * 
     * @param sChannel
     *            SocketChannel to read from.
     * @return The number of bytes, possibly zero,or -1 if the
     *         channel has reached end-of-stream
     */
    int read(/*SocketChannel sChannel*/);

    /**
     * Clears all stored content of this ProtocolDataUnit object.
     */
    void clear();

    /**
     * Returns an iterator to all contained Additional Header Segment in this
     * PDU.
     * 
     * @return The iterator to the contained Additional Header Segment.
     * @see AdditionalHeaderSegment
     */
    //Iterator<AdditionalHeaderSegment> getAdditionalHeaderSegments();

    /**
     * Returns the Basic Header Segment contained in this PDU.
     * 
     * @return The Basic Header Segment.
     * @see BasicHeaderSegment
     */
    BasicHeaderSegment* getBasicHeaderSegment();

    /**
     * Gets the data segment in this PDU.
     * 
     * @return The data segment of this ProtocolDataUnit object.
     */
    ByteBuffer getDataSegment();

    void setDataSegment(ByteBuffer dataSegment);

    /**
     * Sets a new data segment in this PDU.
     * 
     * @param chunk
     *            The new data segment of this ProtocolDataUnit object.
     */
    //void setDataSegment(IDataSegmentChunk chunk);

    /**
     * Returns the instance of the used digest algorithm for the header.
     * 
     * @return The instance of the header digest.
     */
    IDigest getHeaderDigest();

    /**
     * Sets the digest of the header to use for data integrity.
     * 
     * @param newHeaderDigest
     *            An instance of the new header digest.
     */
    void setHeaderDigest(IDigest newHeaderDigest);

    /**
     * Returns the instance of the used digest algorithm for the data segment.
     * 
     * @return The instance of the data digest.
     */
    IDigest getDataDigest();

    /**
     * Sets the digest of the data segment to use for data integrity.
     * 
     * @param newDataDigest
     *            An instance of the new data segment digest.
     */
    void setDataDigest(IDigest newDataDigest);

    /** {@inheritDoc} */
    //@Override
    string toString();

    /** {@inheritDoc} */
    //@Override
    bool equals(ProtocolDataUnit &o);

private:
    /**
     * Calculates the needed size (in bytes) of serializing this object.
     * 
     * @return The needed size to store this object.
     */
    int calcSize();

    int serializeDigest(ByteBuffer pdu, IDigest digest);

    int deserializeDigest(ByteBuffer pdu, int offset, int length, IDigest digest);

};

#endif // __PROTOCOLDATAUNIT_H__
