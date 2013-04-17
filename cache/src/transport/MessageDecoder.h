#ifndef __MessageDecoder_h__
#define __MessageDecoder_h__

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <TypeDefs.h>
#include <Message.pb.h>
#include <IoService.h>

class MessageDecoder
{
public:
    class Callback
    {
        virtual ~Callback() {}
        virtual void onMessage(const Message::Ptr) = 0;
    };

    MessageDecoder(IoService& ios, Callback* cb)
      : _ioservice(ios)
      : _callback(cb)
      , 
    virtual ~MessageDecoder()
    {
    }

    virtual void decode(std::istream& input, bool async = false)
    {
        if(!_callback || input.bad() || input.eof())
           return;

        if(async)
        {
            asyncCall(boost::bind(&MessageDecoder::decode, this, input, false));
            return;
        }
      
/*
        std::streambuf sbuf;

        buffer.pubsetbuf(buffer.data(), buffer.size());
        buffer.setg((char*)data, (char*)data, (char*)data+sz);
        buffer.setp((char*)data, (char*)data+sz);

        std::istream iss(&buffer);
*/

        Message::Ptr msg(new Message);
        if (!msg->ParseFromIstream(&input))
        {
            LOG4CXX_ERROR(_log, "Failed to decode message");
            return;
        }

        // TODO: Measure/restrict callback time.
        _callback->(msg);
    }

  private:
    Callback* _callback;

  public:
    static log4cxx::LoggerPtr _log;
};

#endif // __MessageDecoder_h__
