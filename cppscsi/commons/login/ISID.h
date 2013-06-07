// ISID.h

#ifndef __ISID_H__
#define __ISID_H__

class ISID {
private:
	enum Format {
		/** ISID is in the Organization Unique Identifier Format. */
		OUI_FORMAT = 0,
		/** ISID is in the EN-Format (IANA Enterprise Number). */
		IANA_ENTERPRISE_NUMBER = 1,
		/** ISID is in the "Random" Format. */
		RANDOM = 2,
		/** ISID is in the Reserved. */
		RESERVED = 3,
	};

public:
	ISID();
	ISID(Format initT, unsigned char initA, short initB, unsigned char  initC, short initD);
	~ISID();

	void clear();
	long serialize();
	void deserialize(long isid);
protected:
private:

	/** Bit mask to extract the first int out from a long. */
    const static long FIRST_LINE_FLAG_MASK = 0xFFFFFFFF00000000L;

    /** Bit flag mask to get the field <code>A</code> in this ISID. */
    const static int A_FIELD_FLAG_MASK = 0x3F000000;

    /** Number of bits to shift to get the field <code>T</code> in this ISID. */
    const static int T_FIELD_SHIFT = 30;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /** The field <code>T</code> defined in the RFC 3720. */
    Format t;

    /** The field <code>A</code> defined in the RFC 3720. */
    unsigned char a;

    /** The field <code>B</code> defined in the RFC 3720. */
    short b;

    /** The field <code>C</code> defined in the RFC 3720. */
    unsigned char c;

    /** The field <code>D</code> defined in the RFC 3720. */
    short d;
};

#endif // __ISID_H__
