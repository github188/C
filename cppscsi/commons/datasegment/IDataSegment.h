// IDataSegment.h
#ifndef __IDATASEGMENT_H__
#define __IDATASEGMENT_H__

#include "ByteBuffer.h"
/**
 * IDataSegment
 * This interface defines all methods, which a class must to support, if it is a DataSegment.
 */
class IDataSegment {
public: 
    /**
     * This method imports len bytes from the given ByteBuffer.
     * 
     * @param src
     *            Source ByteBuffer object.
     * @param len
     *            The number of bytes to import from src.
     * @return The number of bytes, which are imported. Typically, this should
     *         be equal as len.
     */
    int deserialize(ByteBuffer src, int len);

    /**
     * This method appends len bytes from the given ByteBuffer at the end of the
     * data buffer of this instance.
     * 
     * @param src
     *            Source ByteBuffer object.
     * @param len
     *            The number of bytes to append from src.
     * @return The number of bytes of the complete data buffer of this instance.
     */
    int append(ByteBuffer src, int len);

    /**
     * This method exports the data buffer to the given ByteBuffer object, which is padded to a
     * integer number of 4 byte words.
     * 
     * @param dst
     *            Destination ByteBuffer object.
     * @param off
     *            Start position in dst, where to serialize.
     * @return The number of exported bytes (in bytes).
     */
    int serialize(ByteBuffer dst, int off);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Returns an iterator over the chunks of this data segment in proper
     * sequence.
     * 
     * @return an iterator over the chunks of this data segment in proper
     *         sequence.
     */
    //IDataSegmentIterator iterator();

    /**
     * Returns a SettingsMap instance of this IDataSegment instance. This is only
     * useful with a TextParameterDataSegment instance.
     * 
     * @return The settings of this TextParameterDataSegment instance.
     * @throws InternetSCSIException
     *             if any violation of the iSCSI Standard occurs.
     */
    //SettingsMap getSettings();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Clears all made settings of this object. After the call of this method,
     * this object can be reused.
     */
    void clear();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Returns the length, which is really used by the dataBuffer.
     * 
     * @return The really used length.
     */
    int getLength();

    /**
     * Sets the data buffer to the given buffer src. Starting from
     * the position offset with length of len.
     * 
     * @param src
     *            The buffer to read from.
     * @param off
     *            The start offset to read from.
     * @param len
     *            The number of bytes to read.
     * @return The number of bytes really read.
     */
    int setDataBuffer(ByteBuffer src, int off, int len);

};

#endif // __IDATASEGMENT_H__
