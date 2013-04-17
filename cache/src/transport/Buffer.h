#ifndef __Buffer_h__
#define __Buffer_h__

#include <stdint.h>
#include <vector>
#include <boost/shared_ptr.hpp>

class Buffer
  : public std::vector<uint8_t>
{
public:
    typedef boost::shared_ptr<Buffer> Ptr;

    enum { DEFAULT_SIZE = 1500 }; // MTU

    Buffer(size_t bytes)
      : std::vector<uint8_t>(bytes)
    {
    }

    virtual ~Buffer()
    {

    }
};

#endif // __DataBuffer_h__

