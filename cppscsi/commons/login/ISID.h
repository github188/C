// ISID.h

#ifndef __ISID_H__
#define __ISID_H__

class ISID {
public:
	ISID();
	~ISID();

	void clear();
	void serialize(long isid);
	void deserialize(long isid);
protected:
private:
};

#endif // __ISID_H__
