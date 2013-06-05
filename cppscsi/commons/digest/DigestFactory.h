#include <string>
#include "IDigest.h"
using namespace std;

/**
 * DigestFactory
 * A factory to create instances of the supported digest algorithms.
 */
class DigestFactory {
private:
	IDigest *m_pDigest;

public:

    /**
     * Constructor to create new, empty DigestFactory instance.
     */
    DigestFactory(); 
    ~DigestFactory(); 

    /**
     * This method creates an IDigest instance of the given type.
     * 
     * @param digestName
     *            The name of the digest type.
     * @return The IDigest instance of the given type.
     */
    IDigest* create(const string &digestName);
};
