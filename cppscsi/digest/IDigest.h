// IDigest.h

#ifndef __IDIGEST_H__
#define __IDIGEST_H__


#include "ByteBuffer.h"

/**
 * <h1>IDigest</h1>
 * <p>
 * An interface representing a digest.
 * 
 * @author Volker Wildi
 */
class IDigest {

public: 
	IDigest();
	~IDigest();

    /**
     * This method updates the used digest with the values of the given <code>ByteBuffer</code> object.
     * 
     * @param data
     *            The values used for updating the checksum.
     * @param off
     *            Start offset.
     * @param len
     *            Length of the used values. (Must be a multiple of <code>4</code> bytes)
     */
    void update(ByteBuffer data, int off, int len);

    /**
     * This method validates the calculated checksum with the expected checksum.
     * 
     * @throws DigestException
     *             Dismatch between the calculated and expected checksum.
     */
    void validate();

    /**
     * Returns the length in bytes, which are needed to store this digest.
     * 
     * @return The number of bytes of this digest.
     */
    int getSize();

};

#endif // __IDIGEST_H__
