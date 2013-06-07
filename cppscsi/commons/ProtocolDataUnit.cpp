#include "ProtocolDataUnit.h"
#include "IDigest.h"
#include "BasicHeaderSegment.h"
#include "AdditionalHeaderSegment.h"
#include "AbstractDataSegment.h"

ProtocolDataUnit::ProtocolDataUnit(IDigest initHeaderDigest, IDigest initDataDigest) 
{

    AHS_INITIAL_SIZE = 0;

	headerDigest = initHeaderDigest;

	dataDigest = initDataDigest;

	m_pBasicHeaderSegment = new BasicHeaderSegment();
}

ByteBuffer ProtocolDataUnit::serialize() 
{
	m_pBasicHeaderSegment->getParser()->checkIntegrity();

	ByteBuffer pdu; 
	pdu.resize(calcSize());

	int offset = 0;
	offset += m_pBasicHeaderSegment->serialize(pdu, offset);
#if 0
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace("Serialized Basic Header Segment:\n" + toString());
	}
#endif
	offset += serializeAdditionalHeaderSegments(pdu, offset);

	// write header digest
	// TODO: Move CRC calculation in BasicHeaderSegment.serialize?
	if (m_pBasicHeaderSegment->getParser()->canHaveDigests()) {
		offset += serializeDigest(pdu, headerDigest);
	}

	// serialize data segment
	offset += serializeDataSegment(pdu, offset);

	// write data segment digest
	// TODO: Move CRC calculation in BasicHeaderSegment.serialize?
	if (m_pBasicHeaderSegment->getParser()->canHaveDigests()) {
		offset += serializeDigest(pdu, dataDigest);
	}

	//return (ByteBuffer)pdu.rewind();
	return pdu;
}

int ProtocolDataUnit::deserialize(ByteBuffer pdu)
{

	int offset = deserializeBasicHeaderSegment(pdu);

	offset += deserializeAdditionalHeaderSegments(pdu, offset);

	offset += deserializeDataSegment(pdu, offset);

	m_pBasicHeaderSegment->getParser()->checkIntegrity();

	return offset;
}

int ProtocolDataUnit::deserializeBasicHeaderSegment(ByteBuffer bhs)
{

	int len = m_pBasicHeaderSegment->deserialize(*this, bhs);

	// read header digest and validate
	if (m_pBasicHeaderSegment->getParser()->canHaveDigests()) {
		len +=
			deserializeDigest(bhs, bhs.getReadPos() - BasicHeaderSegment::BHS_FIXED_SIZE,
					BasicHeaderSegment::BHS_FIXED_SIZE, headerDigest);
	}
#if 0
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace("Deserialized Basic Header Segment:\n" + toString());
	}
#endif
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
	int ahsLength = m_pBasicHeaderSegment->getTotalAHSLength();
	while (ahsLength != 0) {
		AdditionalHeaderSegment tmpAHS;
		tmpAHS.deserialize(pdu, off);

		additionalHeaderSegments.push_back(tmpAHS);
		ahsLength -= tmpAHS.getLength();

		off += tmpAHS.getSpecificField().getReadPos();
	}

	return off - offset;
}

int ProtocolDataUnit::serializeAdditionalHeaderSegments(ByteBuffer dst, int offset)
{
	int off = offset;
	for (int i=0; i<additionalHeaderSegments.size(); i++) {
		off += additionalHeaderSegments.at(i).serialize(dst, off);
	}

	return off - offset;
}

int ProtocolDataUnit::deserializeDataSegment(ByteBuffer pdu, int offset)
{
#if 0
	int length = m_pBasicHeaderSegment->getDataSegmentLength();

	if (dataSegment == null || dataSegment.limit() < length) {
		dataSegment = ByteBuffer.resize(AbstractDataSegment::getTotalLength(length));
	}

	dataSegment.put(pdu);

	dataSegment.flip();

	// read data segment digest and validate
	if (m_pBasicHeaderSegment->getParser()->canHaveDigests()) {
		deserializeDigest(pdu, offset, length, dataDigest);
	}

	if (dataSegment == null) {
		return 0;
	} else {
		return dataSegment.limit();
	}
#else
	return dataSegment.size();
#endif
}

int ProtocolDataUnit::serializeDataSegment(ByteBuffer dst, int offset)
{
#if 0
	dataSegment.rewind();
	dst.setWritePos(offset);
	dst.put(dataSegment);

	return dataSegment.limit();
#else
	return dataSegment.size();
#endif
}

int ProtocolDataUnit::write(/*SocketChannel sChannel*/) 
{
	// print debug informations
#if 0
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace(m_pBasicHeaderSegment->getParser()->getShortInfo());
	}
#endif

	ByteBuffer src = serialize();
	int length = 0;
#if 0
	while (length < src.limit()) {
		length += sChannel.write(src);
	}
#endif
	return length;
}

int ProtocolDataUnit::read(/*SocketChannel sChannel*/) 
{

	// read Basic Header Segment first to determine the total length of this
	// Protocol Data Unit.
	clear();

	ByteBuffer bhs/* = ByteBuffer.allocate(BasicHeaderSegment.BHS_FIXED_SIZE)*/;
	int len = 0;
	int lens;
	while (len < BasicHeaderSegment::BHS_FIXED_SIZE) {
#if 0
		lens = sChannel.read(bhs);
#endif
		if (lens == -1) {
			// The Channel was closed at the Target (e.g. the Target does
			// not support Multiple Connections)
			// throw new ClosedChannelException();
			return lens;
		}
		len += lens;
#if 0
		LOGGER.trace("Receiving through SocketChannel: " + len + " of maximal "
				+ BasicHeaderSegment::BHS_FIXED_SIZE);
#endif

	}
	//bhs.flip();

	deserializeBasicHeaderSegment(bhs);
	// check for further reading
	if (m_pBasicHeaderSegment->getTotalAHSLength() > 0) {
		ByteBuffer ahs /*= ByteBuffer.allocate(m_pBasicHeaderSegment->getTotalAHSLength())*/;
		int ahsLength = 0;
		while (ahsLength < m_pBasicHeaderSegment->getTotalAHSLength()) {
#if 0
			ahsLength += sChannel.read(ahs);
#endif
		}
		len += ahsLength;
		//ahs.flip();

		deserializeAdditionalHeaderSegments(ahs);
	}
	if (m_pBasicHeaderSegment->getDataSegmentLength() > 0) {
		int dataSegmentLength = 0;
#if 0
		dataSegment =
			ByteBuffer.allocate(AbstractDataSegment.getTotalLength(m_basicHeaderSegment
						.getDataSegmentLength()));
		while (dataSegmentLength < m_pBasicHeaderSegment->getDataSegmentLength()) {
			dataSegmentLength += sChannel.read(dataSegment);
		}
#endif		
		len += dataSegmentLength;
		//dataSegment.flip();
	}

	// print debug informations
#if 0
	if (LOGGER.isTraceEnabled()) {
		LOGGER.trace(m_pBasicHeaderSegment->getParser()->getShortInfo());
	}
#endif

	return len;
}

void ProtocolDataUnit::clear() 
{

	m_pBasicHeaderSegment->clear();

	//headerDigest.reset();

	additionalHeaderSegments.clear();

	dataSegment.clear();
	//dataSegment.flip();

	//dataDigest.reset();
}

#if 0
Iterator<AdditionalHeaderSegment> ProtocolDataUnit::getAdditionalHeaderSegments() 
{

	return additionalHeaderSegments.iterator();
}
#endif

BasicHeaderSegment* ProtocolDataUnit::getBasicHeaderSegment() {

	return m_pBasicHeaderSegment;
}

ByteBuffer ProtocolDataUnit::getDataSegment() {

	return dataSegment;
}

void ProtocolDataUnit::setDataSegment(ByteBuffer dataSegment) {
	dataSegment.clear();
	dataSegment = dataSegment;
	m_pBasicHeaderSegment->setDataSegmentLength(dataSegment.size());
}

#if 0
void ProtocolDataUnit::setDataSegment(IDataSegmentChunk chunk) {

	if (chunk == null) {
		throw new NullPointerException();
	}

	dataSegment = ByteBuffer.allocate(chunk.getTotalLength());
	dataSegment.put(chunk.getData());
	m_pBasicHeaderSegment->setDataSegmentLength(chunk.getLength());
}
#endif

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
	m_pBasicHeaderSegment->toString();

	for (int i=0; i<additionalHeaderSegments.size(); i++) {
		additionalHeaderSegments.at(i).toString();
	}

	return "";
}

bool ProtocolDataUnit::equals(ProtocolDataUnit &o) {
#if 0
	ProtocolDataUnit oPdu = (ProtocolDataUnit)o;

	Iterator<AdditionalHeaderSegment> ahs1 = oPdu.getAdditionalHeaderSegments();
	Iterator<AdditionalHeaderSegment> ahs2 = this.getAdditionalHeaderSegments();

	while (ahs1.hasNext()) {
		if (!ahs1.equals(ahs2))
			return false;
		ahs1.next();
		ahs2.next();
	}

	if (oPdu.getBasicHeaderSegment()->equals(this.getBasicHeaderSegment())
			&& oPdu.getDataDigest().equals(this.getDataDigest())
			&& oPdu.getHeaderDigest().equals(this.getHeaderDigest())
			&& oPdu.getDataSegment().equals(this.getDataSegment()))
		return true;

#endif
	return false;
}

int ProtocolDataUnit::calcSize() {

	int size = BasicHeaderSegment::BHS_FIXED_SIZE;
	size += m_pBasicHeaderSegment->getTotalAHSLength() * AdditionalHeaderSegment::AHS_FACTOR;

	// plus the sizes of the used digests
	size += headerDigest.getSize();
	size += dataDigest.getSize();

	size += m_pBasicHeaderSegment->getDataSegmentLength();

	return size;
}

int ProtocolDataUnit::serializeDigest(ByteBuffer pdu, IDigest digest) {

	int size = digest.getSize();
	if (size > 0) {
		//digest.reset();
		//pdu.mark();
		digest.update(pdu, 0, BasicHeaderSegment::BHS_FIXED_SIZE);
		//pdu.putInt((int)digest.getValue());
		//pdu.reset();
	}

	return size;
}

int ProtocolDataUnit::deserializeDigest(ByteBuffer pdu, int offset, int length, IDigest digest)
{

	//pdu.mark();
	digest.update(pdu, offset, length);
	digest.validate();
	//pdu.reset();

	return digest.getSize();
}

