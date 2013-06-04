#include "AdditionalHeaderSegment.h"

AdditionalHeaderSegment::AdditionalHeaderSegment() 
{ 
}

AdditionalHeaderSegment::~AdditionalHeaderSegment() 
{ 
}

int AdditionalHeaderSegment::serialize(ByteBuffer dst, int offset);
{ 
	return 0;
}

void AdditionalHeaderSegment::deserialize(ByteBuffer pdu, int offset);
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

