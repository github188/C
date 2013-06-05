#include "AdditionalHeaderSegment.h"

AdditionalHeaderSegment::AdditionalHeaderSegment() 
{ 
}

AdditionalHeaderSegment::~AdditionalHeaderSegment() 
{ 
}

int AdditionalHeaderSegment::serialize(ByteBuffer dst, int offset)
{ 
	return 0;
}

void AdditionalHeaderSegment::deserialize(ByteBuffer pdu, int offset)
{ 
}

short AdditionalHeaderSegment::getLength()
{ 
	return 0;
}

ByteBuffer AdditionalHeaderSegment::getSpecificField()
{ 
	ByteBuffer tmp;
	return tmp;
}

int AdditionalHeaderSegment::getType()
{
	return EXTENDED_CDB;
}

string AdditionalHeaderSegment::toString()
{ 
	return "";
}

void AdditionalHeaderSegment::clear()
{ 
}

bool AdditionalHeaderSegment::equals(AdditionalHeaderSegment &o)
{ 
	return false;
}

void AdditionalHeaderSegment::checkIntegrity()
{ 
}

