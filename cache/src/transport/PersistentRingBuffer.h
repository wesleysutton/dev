#ifndef __PersistentRingBuffer_h__
#define __PersistentRingBuffer_h__

class PersistentRingBuffer
{
public:
  
private:

    inline bool put(uint32_t v)
    {
      if(getBytesLeft() < sizeof(v))
          return false;

      v = htonl(v);
      memcpy(_head, &v, sizeof(v));      
    }

    inline bool put(uint16_t v)
    {
      if(getBytesLeft() < sizeof(v))
          return false;

      v = htons(v);
      memcpy(_head, &v, sizeof(v));
      return true;
    }

};

#endif // __PersistentRingBuffer_h__
