#include "BufferPool.h"

#include <set>
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <boost/lockfree/queue.hpp>
#include "Buffer.h"

#include <stdio.h>

using namespace std;
using namespace boost;

namespace // anonymous
{

static BufferPool _instance;
    
static void release(Buffer* buffer)
{
    assert(buffer);
    printf("Release buffer: %ld\n", buffer->size());
    delete buffer;
}

} // anonymous namespace


BufferPool& BufferPool::instance()
{
    return _instance;
}

Buffer::Ptr BufferPool::acquire(size_t bytes)
{
    printf("Acquire buffer: %ld\n", bytes);
    return Buffer::Ptr(new Buffer(bytes), ::release);
}
