// Constants.h
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

/** Number of bits in a byte. */
const int BITS_PER_BYTE = 8;

/** The java data type int need 4 bytes. */
const int BYTES_PER_INT = sizeof(int);

/** The intial size of the StringBuilder used for logging. */
const int LOG_INITIAL_SIZE = 50;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

/**
 * Shift a given number by 8 bits or 1 byte.
 */
const int ONE_BYTE_SHIFT = 8;

/**
 * Shift a given number by 16 bits or 2 bytes.
 */
const int TWO_BYTES_SHIFT = 16;

/**
 * Shift a given number by 24 bits or 3 bytes.
 */
const int THREE_BYTES_SHIFT = 24;

/**
 * Shift a given number by 32 bits or 4 bytes.
 */
const int FOUR_BYTES_SHIFT = 32;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

/** Bit mask to extract the first byte of a 32 bit number. */
const int FIRST_BYTE_MASK = 0xFF000000;

/** Bit mask to extract the second byte of a 32 bit number. */
const int SECOND_BYTE_MASK = 0x00FF0000;

/** Bit mask to extract the third byte of a 32 bit number. */
const int THIRD_BYTE_MASK = 0x0000FF00;

/** Bit mask to extract the fourth byte of a 32 bit number. */
const int FOURTH_BYTE_MASK = 0x000000FF;

/**
 * Bit mask to extract the first two bytes of a 32 bit number.
 */
const int FIRST_TWO_BYTES_MASK = 0xFFFF0000;

/**
 * Bit mask to extract the second and third bytes of a 32 bit
 * number.
 */
const int MIDDLE_TWO_BYTES_SHIFT = 0x00FFFF00;

/** Bit mask to extract the last bytes of a 32 bit number. */
const int LAST_TWO_BYTES_MASK = 0x0000FFFF;

/**
 * Bit mask to extract the three last bytes of a 32 bit number.
 */
const int LAST_THREE_BYTES_MASK = 0x00FFFFFF;

/**
 * Bit mask to extract the last four bytes of a 64 bit number.
 */
const long LAST_FOUR_BYTES_MASK = 0x00000000FFFFFFFFL;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

/** Reserved fields are marked as zeros in a byte data type. */
const byte RESERVED_BYTE = 0x00;

/** Reserved fields are marked as zeros in a short data type. */
const short RESERVED_SHORT = 0x0;

/** Reserved fields are marked as zeros in a integer data type. */
const int RESERVED_INT = 0x0;

/** Reserved fields are marked as zeros in a long data type. */
const long RESERVED_LONG = 0x0L;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

/** Bit mask to extract the continue flag of a 32 bit number. */
const int CONTINUE_FLAG_MASK = 0x00400000;

/**
 * Set for Residual Overflow. In this case, the Residual Count indicates the
 * number of bytes that were not transferred because the initiator's
 * Expected Data Transfer Length was not sufficient. For a bidirectional
 * operation, the Residual Count contains the residual for the write
 * operation.
 */
const int RESIDUAL_OVERFLOW_FLAG_MASK = 0x00040000;

/**
 * Set for Residual Underflow. In this case, the Residual Count indicates
 * the number of bytes that were not transferred out of the number of bytes
 * that were expected to be transferred. For a bidirectional operation, the
 * Residual Count contains the residual for the write operation.
 */
const int RESIDUAL_UNDERFLOW_FLAG_MASK = 0x00020000;

/**
 * Set for Bidirectional Read Residual Overflow. In this case, the
 * Bidirectional Read Residual Count indicates the number of bytes that were
 * not transferred to the initiator because the initiator¿s Expected
 * Bidirectional Read Data Transfer Length was not sufficient.
 */
const int READ_RESIDUAL_OVERFLOW_FLAG_MASK = 0x00080000;

/**
 * Set for Bidirectional Read Residual Underflow. In this case, the
 * Bidirectional Read Residual Count indicates the number of bytes that were
 * not transferred to the initiator out of the number of bytes expected to
 * be transferred.
 */
const int READ_RESIDUAL_UNDERFLOW_FLAG_MASK = 0x00100000;


#endif // __CONSTANTS_H__
