#include <string>
#include "IDigest.h"
using namespace std;

/**
 * <h1>DigestFactory</h1>
 * <p/>
 * A factory to create instances of the supported digest algorithms.
 * 
 * @author Volker Wildi
 */
class DigestFactory {

public:

    /**
     * Constructor to create new, empty <code>DigestFactory</code> instance.
     */
    DigestFactory(); 

    /**
     * This method creates an <code>IDigest</code> instance of the given type.
     * 
     * @param digestName
     *            The name of the digest type.
     * @return The <code>IDigest</code> instance of the given type.
     */
    IDigest create(string digestName);
};
