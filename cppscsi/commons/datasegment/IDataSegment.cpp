#include "IDataSegment.h"

int IDataSegment::deserialize(ByteBuffer src, int len)
{
	return 0;
}

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
int IDataSegment::append(ByteBuffer src, int len)
{
	return 0;
}

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
int IDataSegment::serialize(ByteBuffer dst, int off)
{
	return 0;
}

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
void IDataSegment::clear()
{
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

/**
 * Returns the length, which is really used by the dataBuffer.
 * 
 * @return The really used length.
 */
int IDataSegment::getLength()
{
	return 0;
}

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
int IDataSegment::setDataBuffer(ByteBuffer src, int off, int len)
{
	return 0;
}
