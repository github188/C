// CRC32CDigest.h
#ifndef __CRC32CDIGEST_H__
#define __CRC32CDIGEST_H__

#include "IDigest.h"

class CRC32CDigest : public IDigest
{

private:

	/**
	 * Shift a given number by 8 bits or 1 byte.
	 */
	const static int ONE_BYTE_SHIFT = 8;

	/**
	 * Shift a given number by 16 bits or 2 bytes.
	 */
	const static int TWO_BYTES_SHIFT = 16;

	/** Number of bits in a byte. */
	const static int BITS_PER_BYTE = 8;

	/** The java data type int need 4 bytes. */
	const static int BYTES_PER_INT = sizeof(int) * BITS_PER_BYTE / BITS_PER_BYTE;

	/** Bit mask to extract the fourth byte of a 32 bit number. */
	const static int FOURTH_BYTE_MASK = 0x000000FF;

	/** The flag mask to convert an integer number to a long number. */
	const static long INT_FLAG_MASK_LONG = 0x00000000FFFFFFFFL;

	/** The size of the digest number (in bytes) to serialize. */
	const static int DIGEST_SIZE = 4;

	// --------------------------------------------------------------------------
	// --------------------------------------------------------------------------

	/**
	 * The initial value of the CRC32CDigest algorithm (defined by the iSCSI
	 * Standard).
	 */
	const static int INITIAL_VALUE = 0xFFFFFFFF;

	/** The remainder after calculating the digest. */
	const static long FINAL_REMAINDER = 0x1C2D19EDL;

	// --------------------------------------------------------------------------
	// --------------------------------------------------------------------------

	const static int CRC_TABLE_32[8*32];
	const static int CRC_TABLE_40[8*32];
	const static int CRC_TABLE_48[8*32];
	const static int CRC_TABLE_56[8*32];

	/**
	 * Flag to indicate, if the crc has changed but the last XOR operation was
	 * not invoked.
	 */
	bool dirty;

	/** The currenct CRC. */
	int crc;

public:
	/** Creates a new CRC32CDigest (slicing-by-8) object. */
	CRC32CDigest();
	~CRC32CDigest();

	void update(int b);
	void update(char *data, int off, int len);
	void reset();
	long getValue();
	void validate();
	int getSize();
	//bool equals(Object o);
protected:
	/**
	 * This method calculates the CRC with Slicing-by-4 algorithm.
	 *
	 * @param data
	 * An integer data value, which is added to the CRC.
	 */
	void slicingBy4(int data);

	/**
	 * This method calculates the CRC with Slicing-by-4 algorithm.
	 *
	 * @param data
	 * An integer array, which elements all are added to the CRC.
	 */
	void slicingBy4(int data[]);
};

#endif //__CRC32CDIGEST_H__
