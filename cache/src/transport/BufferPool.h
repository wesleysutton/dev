#ifndef __BufferPool_h__
#define __BufferPool_h__

#include <boost/noncopyable.hpp>
#include "Buffer.h"

class BufferPool
  : boost::noncopyable
{
public:
    static BufferPool& instance();

    Buffer::Ptr acquire(size_t bytes = Buffer::DEFAULT_SIZE);
    void release(Buffer::Ptr);
};

#endif // __BufferPool_h__

