#include "ISID.h"

ISID::ISID() {
}

ISID::ISID(Format initT, unsigned char initA, short initB, unsigned char  initC, short initD) {
	t = initT;
	a = initA;
	b = initB;
	c = initC;
	d = initD;
}

ISID::~ISID() {
}

void ISID::clear() {
}


void ISID::deserialize(long isid) {
}

long ISID::serialize() {
}
