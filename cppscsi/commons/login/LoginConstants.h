// LoginConstants.h

#ifndef __LOGINCONSTANTS_H__
#define __LOGINCONSTANTS_H__

/** Current Stage bit mask. */
const int CSG_FLAG_MASK = 0x000C0000;

/** Number of bits to shift to the current stage. */
const int CSG_BIT_SHIFT = 18;

/** Next Stage bit mask. */
const int NSG_FLAG_MASK = 0x00030000;

/** Bit mask, where the 11th and 12th bit are set. */
const int BIT_11_AND_12_FLAG_MASK = 0x00300000;
 
#endif // __LOGINCONSTANTS_H__
