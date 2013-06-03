#include "AdditionalHeaderSegment.h"

AdditionalHeaderSegment::AdditionalHeaderSegment() 
{ 
}

AdditionalHeaderSegment::~AdditionalHeaderSegment() 
{ 
}

int AdditionalHeaderSegment::serialize(final ByteBuffer dst, final int offset);
{ 
	return 0;
}

void AdditionalHeaderSegment::deserialize(final ByteBuffer pdu, final int offset);
{ 
}

short AdditionalHeaderSegment::getLength();
{ 
	return 0;
}

ByteBuffer AdditionalHeaderSegment::getSpecificField();
{ 
	ByteBuffer tmp;
	return tmp;
}

AdditionalHeaderSegmentType AdditionalHeaderSegment::getType();
{
	AdditionalHeaderSegmentType tmp;
	return tmp;
}

string AdditionalHeaderSegment::toString();
{ 
	string strTmp = "";
	return strTmp;
}

void AdditionalHeaderSegment::clear();
{ 
}

bool AdditionalHeaderSegment::equals(Object o);
{ 
	return false;
}

void AdditionalHeaderSegment::checkIntegrity();
{ 
}

