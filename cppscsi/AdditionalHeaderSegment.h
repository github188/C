#ifndef __ADDITIONALHEADERSEGMENT_H__
#define __ADDITIONALHEADERSEGMENT_H__

#include "ByteBuffer.h"
#include <string>
using namespace std;

/**
 * <h1>AdditionalHeaderSegment</h1>
 * <p>
 * This class encapsulate an Additional Header Segment (AHS) defined in iSCSI Protocol (RFC3720).
 * <p>
 * It provides all methods to serialize and deserialize such an AHS. Further there are getter methods to
 * access the specific data, which is contained in this AHS.
 * 
 * @author Volker Wildi
 */
class AdditionalHeaderSegment {

    enum AdditionalHeaderSegmentType {
        /**
         * This type of AHS MUST NOT be used if the <code>CDBLength</code> is
         * less than <code>17</code>. The length includes the reserved byte <code>3</code>.
         */
        EXTENDED_CDB,

        /**
         * The Expected Bidirectional Read Data Length. But this is not good
         * documented in the iSCSI Protocol (RFC3720).
         */
        EXPECTED_BIDIRECTIONAL_READ_DATA_LENGTH;

        value;

        static Map<Byte, AdditionalHeaderSegmentType> mapping;

        static {
            AdditionalHeaderSegmentType.mapping = new HashMap<Byte, AdditionalHeaderSegmentType>();
            for (AdditionalHeaderSegmentType s : values()) {
                AdditionalHeaderSegmentType.mapping.put(s.value, s);
            }
        }

        AdditionalHeaderSegmentType(byte newValue) {

            value = newValue;
        }

        /**
         * Returns the value of this enumeration.
         * 
         * @return The value of this enumeration.
         */
        byte value();

        /**
         * Returns the constant defined for the given <code>value</code>.
         * 
         * @param value
         *            The value to search for.
         * @return The constant defined for the given <code>value</code>. Or <code>null</code>, if this value
         *         is not defined by this
         *         enumeration.
         */
        static AdditionalHeaderSegmentType valueOf(final byte value);

    }

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Factor, which must be muliplied with the <code>totalAHSLength</code> contained in a
     * <code>BasicHeaderSegment</code> object.
     */
    static int AHS_FACTOR = 4;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /** Offset of the first complete line in the AHS specific field. */
    static int EXTENDED_CDB_OFFSET = 1;

    /**
     * The length of AHS, if the type of the AHS is the Bidirectional Expected
     * Read-Data Length.
     */
    static int EXPECTED_BIDIRECTIONAL_LENGTH = 0x0005;

    /**
     * Length of the specific field <code>ByteBuffer</code>, which is expected,
     * if the AHS type is the <code>AdditionalHeaderSegmentType.EXPECTED_BIDIRECTIONAL_READ_DATA_LENGTH</code>
     * .
     */
    static int EXPECTED_BIDIRECTIONAL_SPECIFIC_FIELD_LENGTH = 5;

    /**
     * This is the size (in bytes) of the <code>AHSLength</code> and the <code>AHSType</code>, which are also
     * included in the serialized AHS form
     * of this object.
     */
    static int FIX_SIZE_OVERHEAD = 3;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * This field contains the effective length in bytes of the AHS excluding
     * AHSType and AHSLength and padding, if any. The AHS is padded to the
     * smallest integer number of 4 byte words (i.e., from 0 up to 3 padding
     * bytes).
     */
    short length;

    /**
     * The type of this AHS. <br/>
     * <br/>
     * <table border="1">
     * <tr>
     * <th>Bits</th>
     * <th>Meaning</th>
     * </tr>
     * <tr>
     * <td>0-1</td>
     * <td>Reserved</td>
     * </tr>
     * <tr>
     * <td>2-7</td>
     * <td>AHS code</td>
     * </tr>
     * </table>
     * <br/>
     * 
     * @see AdditionalHeaderSegmentType
     */
    AdditionalHeaderSegmentType type;

    /**
     * This array contains the informations, which are type specific fields.
     */
    ByteBuffer specificField;

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
public:
    /**
     * Default constructor, creates a new, empty AdditionalHeaderSegment object.
     */
    AdditionalHeaderSegment();
	~AdditionalHeaderSegment();

    /**
     * This method serializes the informations of this AHS object to the byte
     * representation defined by the iSCSI Standard.
     * 
     * @param dst
     *            The destination array to write in.
     * @param offset
     *            The start offset in <code>dst</code>.
     * @return The length of used integers of the serialized form of this AHS
     *         object.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    int serialize(final ByteBuffer dst, final int offset);


    /**
     * Extract the informations given by the int array to this Additional Header
     * Segment object.
     * 
     * @param pdu
     *            The Protocol Data Unit to be parsed.
     * @param offset
     *            The offset, where to start in the pdu.
     * @throws InternetSCSIException
     *             If any violation of the iSCSI-Standard emerge.
     */
    void deserialize(final ByteBuffer pdu, final int offset);

    /**
     * Returns the length of this AHS object. Expected values are greater than <code>0</code> and a maximum of
     * <code>65536</code>
     * 
     * @return The length of this AHS object.
     */
    short getLength();

    /**
     * Returns an array with the type specific fields of this AHS object.
     * 
     * @return The type specific fields.
     */
    ByteBuffer getSpecificField();

    /**
     * Returns the type of this AHS object. Expected values are defined as
     * constants in the class AdditionalHeaderSegmentTypes.
     * 
     * @return The value of this AHS object.
     */
    AdditionalHeaderSegmentType getType();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /**
     * Creates a string object with all values for easy debugging.
     * 
     * @return The string with all informations of this AHS.
     */
    public final String toString();

    /**
     * Clears all the stored content of this <code>AdditionalHeaderSegment</code> object.
     */
    void clear();

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    /** {@inheritDoc} */
    bool equals(Object o);

    /**
     * This method checks the integrity of the this Additional Header Segment
     * object to garantee a valid specification.
     * 
     * @throws InternetSCSIException
     *             If the fields are not valid for this AHS type.
     */
    void checkIntegrity();
}

#endif // __ADDITIONALHEADERSEGMENT_H__
