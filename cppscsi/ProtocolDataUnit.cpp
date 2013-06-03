#include "ProtocolDataUnit.h"
#include "IDigest.h"
#include "BasicHeaderSegment.h"

ProtocolDataUnit::ProtocolDataUnit(IDigest initHeaderDigest, IDigest initDataDigest) 
{

    AHS_INITIAL_SIZE = 0;

	headerDigest = initHeaderDigest;

	dataSegment = ByteBuffer.allocate(0);
	dataDigest = initDataDigest;
}

ByteBuffer ProtocolDataUnit::serialize() 
{
	m_basicHeaderSegment.getParser().checkIntegrity();

	ByteBuffer pdu = ByteBuffer.allocate(calcSize());

	int offset = 0;
	offset += m_basicHeaderSegment.serialize(pdu, offset);

	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace("Serialized Basic Header Segment:\n" + toString());
	}

	offset += serializeAdditionalHeaderSegments(pdu, offset);

	// write header digest
	// TODO: Move CRC calculation in BasicHeaderSegment.serialize?
	if (m_basicHeaderSegment.getParser().canHaveDigests()) {
		offset += serializeDigest(pdu, headerDigest);
	}

	// serialize data segment
	offset += serializeDataSegment(pdu, offset);

	// write data segment digest
	// TODO: Move CRC calculation in BasicHeaderSegment.serialize?
	if (m_basicHeaderSegment.getParser().canHaveDigests()) {
		offset += serializeDigest(pdu, dataDigest);
	}

	return (ByteBuffer)pdu.rewind();
}

int ProtocolDataUnit::deserialize(ByteBuffer pdu)
{

	int offset = deserializeBasicHeaderSegment(pdu);

	offset += deserializeAdditionalHeaderSegments(pdu, offset);

	offset += deserializeDataSegment(pdu, offset);

	m_basicHeaderSegment.getParser().checkIntegrity();

	return offset;
}

int ProtocolDataUnit::deserializeBasicHeaderSegment(ByteBuffer bhs)
{

	int len = m_basicHeaderSegment.deserialize(this, bhs);

	// read header digest and validate
	if (m_basicHeaderSegment.getParser().canHaveDigests()) {
		len +=
			deserializeDigest(bhs, bhs.position() - BasicHeaderSegment.BHS_FIXED_SIZE,
					BasicHeaderSegment.BHS_FIXED_SIZE, headerDigest);
	}

	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace("Deserialized Basic Header Segment:\n" + toString());
	}

	return len;
}

int ProtocolDataUnit::deserializeAdditionalHeaderSegments(ByteBuffer pdu) 
{

	return deserializeAdditionalHeaderSegments(pdu, 0);
}

int ProtocolDataUnit::deserializeAdditionalHeaderSegments(ByteBuffer pdu, int offset)
{
	// parsing Additional Header Segment
	int off = offset;
	int ahsLength = m_basicHeaderSegment.getTotalAHSLength();
	while (ahsLength != 0) {
		AdditionalHeaderSegment tmpAHS = new AdditionalHeaderSegment();
		tmpAHS.deserialize(pdu, off);

		additionalHeaderSegments.push_back(tmpAHS);
		ahsLength -= tmpAHS.getLength();

		off += tmpAHS.getSpecificField().position();
	}

	return off - offset;
}

int ProtocolDataUnit::serializeAdditionalHeaderSegments(ByteBuffer dst, int offset)
{
	int off = offset;
	for (int i=0; i<additionalHeaderSegments.size(); i++)
		off += additionalHeaderSegments.at(i).serialize(dst, off);
	}

	return off - offset;
}

int ProtocolDataUnit::deserializeDataSegment(ByteBuffer pdu, int offset)
{
	int length = m_basicHeaderSegment.getDataSegmentLength();

	if (dataSegment == null || dataSegment.limit() < length) {
		dataSegment = ByteBuffer.allocate(AbstractDataSegment.getTotalLength(length));
	}
	dataSegment.put(pdu);

	dataSegment.flip();

	// read data segment digest and validate
	if (m_basicHeaderSegment.getParser().canHaveDigests()) {
		deserializeDigest(pdu, offset, length, dataDigest);
	}

	if (dataSegment == null) {
		return 0;
	} else {
		return dataSegment.limit();
	}
}

int ProtocolDataUnit::serializeDataSegment(ByteBuffer dst, int offset)
{
	dataSegment.rewind();
	dst.position(offset);
	dst.put(dataSegment);

	return dataSegment.limit();
}

int ProtocolDataUnit::write(SocketChannel sChannel) 
{
	// print debug informations
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace(m_basicHeaderSegment.getParser().getShortInfo());
	}

	ByteBuffer src = serialize();
	int length = 0;

	while (length < src.limit()) {
		length += sChannel.write(src);
	}

	return length;
}

int ProtocolDataUnit::read(SocketChannel sChannel) 
{

	// read Basic Header Segment first to determine the total length of this
	// Protocol Data Unit.
	clear();

	ByteBuffer bhs = ByteBuffer.allocate(BasicHeaderSegment.BHS_FIXED_SIZE);
	int len = 0;
	while (len < BasicHeaderSegment.BHS_FIXED_SIZE) {
		int lens = sChannel.read(bhs);
		if (lens == -1) {
			// The Channel was closed at the Target (e.g. the Target does
			// not support Multiple Connections)
			// throw new ClosedChannelException();
			return lens;
		}
		len += lens;
		LOGGER.trace("Receiving through SocketChannel: " + len + " of maximal "
				+ BasicHeaderSegment.BHS_FIXED_SIZE);

	}
	bhs.flip();

	deserializeBasicHeaderSegment(bhs);
	// check for further reading
	if (getBasicHeaderSegment().getTotalAHSLength() > 0) {
		ByteBuffer ahs = ByteBuffer.allocate(m_basicHeaderSegment.getTotalAHSLength());
		int ahsLength = 0;
		while (ahsLength < getBasicHeaderSegment().getTotalAHSLength()) {
			ahsLength += sChannel.read(ahs);
		}
		len += ahsLength;
		ahs.flip();

		deserializeAdditionalHeaderSegments(ahs);
	}
	if (m_basicHeaderSegment.getDataSegmentLength() > 0) {
		dataSegment =
			ByteBuffer.allocate(AbstractDataSegment.getTotalLength(m_basicHeaderSegment
						.getDataSegmentLength()));
		int dataSegmentLength = 0;
		while (dataSegmentLength < m_basicHeaderSegment.getDataSegmentLength()) {
			dataSegmentLength += sChannel.read(dataSegment);
		}
		len += dataSegmentLength;
		dataSegment.flip();
	}

	// print debug informations
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace(m_basicHeaderSegment.getParser().getShortInfo());
	}

	return len;
}

void ProtocolDataUnit::clear() 
{

	m_basicHeaderSegment.clear();

	headerDigest.reset();

	additionalHeaderSegments.clear();

	dataSegment.clear();
	dataSegment.flip();

	dataDigest.reset();
}

#if 0
Iterator<AdditionalHeaderSegment> ProtocolDataUnit::getAdditionalHeaderSegments() 
{

	return additionalHeaderSegments.iterator();
}
#endif

BasicHeaderSegment getBasicHeaderSegment() {

	return m_basicHeaderSegment;
}

ByteBuffer ProtocolDataUnit::getDataSegment() {

	return dataSegment;
}

void ProtocolDataUnit::setDataSegment(ByteBuffer dataSegment) {
	dataSegment.clear();
	this.dataSegment = dataSegment;
	m_basicHeaderSegment.setDataSegmentLength(dataSegment.capacity());
}

void ProtocolDataUnit::setDataSegment(IDataSegmentChunk chunk) {

	if (chunk == null) {
		throw new NullPointerException();
	}

	dataSegment = ByteBuffer.allocate(chunk.getTotalLength());
	dataSegment.put(chunk.getData());
	m_basicHeaderSegment.setDataSegmentLength(chunk.getLength());
}

IDigest ProtocolDataUnit::getHeaderDigest() {

	return headerDigest;
}

void ProtocolDataUnit::setHeaderDigest(IDigest newHeaderDigest) {

	headerDigest = newHeaderDigest;
}

IDigest ProtocolDataUnit::getDataDigest() {

	return dataDigest;
}

void ProtocolDataUnit::setDataDigest(IDigest newDataDigest) {

	dataDigest = newDataDigest;
}

string ProtocolDataUnit::toString() {

#if 0
	StringBuilder sb = new StringBuilder(Constants.LOG_INITIAL_SIZE);

	sb.append(m_basicHeaderSegment.toString());

	for (AdditionalHeaderSegment ahs : additionalHeaderSegments) {
		sb.append(ahs.toString());
	}

	return sb.toString();
#else
	string strTmp = "";
	return strTmp;
#endif
}

#if 0
bool ProtocolDataUnit::equals(Object o) {
	if (o instanceof ProtocolDataUnit == false)
		return false;

	ProtocolDataUnit oPdu = (ProtocolDataUnit)o;

	Iterator<AdditionalHeaderSegment> ahs1 = oPdu.getAdditionalHeaderSegments();
	Iterator<AdditionalHeaderSegment> ahs2 = this.getAdditionalHeaderSegments();

	while (ahs1.hasNext()) {
		if (!ahs1.equals(ahs2))
			return false;
		ahs1.next();
		ahs2.next();
	}

	if (oPdu.getBasicHeaderSegment().equals(this.getBasicHeaderSegment())
			&& oPdu.getDataDigest().equals(this.getDataDigest())
			&& oPdu.getHeaderDigest().equals(this.getHeaderDigest())
			&& oPdu.getDataSegment().equals(this.getDataSegment()))
		return true;

	return false;
}
#endif

int ProtocolDataUnit::calcSize() {

	int size = BasicHeaderSegment.BHS_FIXED_SIZE;
	size += m_basicHeaderSegment.getTotalAHSLength() * AdditionalHeaderSegment.AHS_FACTOR;

	// plus the sizes of the used digests
	size += headerDigest.getSize();
	size += dataDigest.getSize();

	size += AbstractDataSegment.getTotalLength(m_basicHeaderSegment.getDataSegmentLength());

	return size;
}

int ProtocolDataUnit::serializeDigest(ByteBuffer pdu, IDigest digest) {

	int size = digest.getSize();
	if (size > 0) {
		digest.reset();
		pdu.mark();
		digest.update(pdu, 0, BasicHeaderSegment.BHS_FIXED_SIZE);
		pdu.putInt((int)digest.getValue());
		pdu.reset();
	}

	return size;
}

int ProtocolDataUnit::deserializeDigest(ByteBuffer pdu, int offset, int length, IDigest digest)
{

	pdu.mark();
	digest.update(pdu, offset, length);
	digest.validate();
	pdu.reset();

	return digest.getSize();
}

